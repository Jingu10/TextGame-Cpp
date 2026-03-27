#include "BattleManager.h"
#include "Policy.h"

BattleManager::BattleManager(ConsoleUI& ui, QuestManager& qm) : ui(ui), questMgr(qm) {}

bool BattleManager::ProcessBattle(Character& p, Monster& m) {
    ui.PrintLine();
    ui.PrintMessage("🚨 야생의 [" + m.GetName() + "] 이(가) 나타났습니다! 🚨");

    while (!p.IsDead() && !m.IsDead()) {
        ui.PrintBattleMenu(p, m);
        int choice = ui.InputSelect("행동 선택");

        if (choice == 4) {
            ui.PrintMessage("\n무사히 도망쳤습니다!");
            return false;
        }

        ProcessPlayerTurn(p, m, choice);
        if (m.IsDead()) break;
        ProcessMonsterTurn(p, m);
    }
    return PostBattleCheck(p, m);
}

void BattleManager::ProcessPlayerTurn(Character& p, Monster& m, int choice) {
    float skillMult = 1.0f;
    std::string atkName = "기본 공격";

    if (choice == 3) {
        ui.PrintConsumables(p);
        int idx = ui.InputSelect("사용할 아이템 번호 (0: 취소)");
        if (p.UseConsumable(idx - 1)) ui.PrintMessage("  ▶ 포션을 사용하여 회복했습니다!");
        else ui.PrintMessage("  ▶ 취소했습니다. 턴이 넘어갑니다.");
        return; // 아이템을 썼으므로 공격 스킵
    }

    if (choice == 2) {
        ui.PrintSkills(p.GetSkills());
        int sIdx = ui.InputSelect("사용할 스킬 번호 (0: 취소)");

        if (sIdx > 0 && sIdx <= p.GetSkills().size()) {
            Skill sel = p.GetSkills()[sIdx - 1];
            if (p.GetBaseStats().mp >= sel.mpCost) {
                p.ConsumeMp(sel.mpCost);
                questMgr.UpdateProgress(QuestType::USE_SKILL);
                skillMult = sel.damageMultiplier;
                atkName = "[" + sel.name + "] 스킬";
            }
            else ui.PrintMessage("  ▶ MP 부족! 기본 공격으로 대체합니다.");
        }
        else ui.PrintMessage("  ▶ 취소했습니다. 기본 공격을 합니다.");
    }

    ui.PrintMessage("  ▶ " + atkName + " 사용!");
    ui.PrintSkillEffect(atkName);
    auto res = BattlePolicy::CalcDamage(p.GetTotalAttack(), skillMult, p.GetAttackElement(), m.GetElement());
    int actualDmg = m.TakeDamage(res.damage);
    ui.PrintDamage(p.GetName(), m.GetName(), actualDmg, res.isSuperEffective);
}

void BattleManager::ProcessMonsterTurn(Character& p, Monster& m) {
    ui.PrintMessage("  ▶ " + m.GetName() + "의 반격!");
    auto res = BattlePolicy::CalcDamage(m.GetAttack(), 1.0f, m.GetElement(), p.GetElement());
    int actualDmg = p.TakeDamage(res.damage);
    ui.PrintDamage(m.GetName(), p.GetName(), actualDmg, res.isSuperEffective);
}

bool BattleManager::PostBattleCheck(Character& p, Monster& m) {
    ui.PrintLine();
    if (p.IsDead()) {
        // [수정 1] 죽으면 체력/마나 풀회복 시키고 마을로 쫓아냄
        ui.PrintMessage("💀 아앗! 눈앞이 깜깜해졌다... (마을에서 부활합니다)");
        p.HealFull();
        return false;
    }

    // [수정 2] 골드 획득 (경험치의 2배를 골드로 지급)
    int earnedGold = m.GetDropExp() * 2;
    p.GainExp(m.GetDropExp());
    p.AddGold(earnedGold);
    questMgr.UpdateProgress(QuestType::KILL_MONSTER);

    ui.PrintMessage("🏆 전투 승리!");
    ui.PrintMessage("경험치 " + std::to_string(m.GetDropExp()) + " / 골드 " + std::to_string(earnedGold) + "G 획득!");

    while (SystemPolicy::CheckLevelUp(p.GetLevel(), p.GetExp())) {
        p.LevelUp();
        ui.PrintLevelUp(p.GetLevel());
    }

    auto drop = SystemPolicy::GenerateDropItem();
    p.AddItem(drop);
    ui.PrintMessage("🎁 전리품 [" + drop->GetName() + "] 획득!");
    return true;
}