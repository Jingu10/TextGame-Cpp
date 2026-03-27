// Scene.cpp
#include "Scene.h"

// 1. 마을 로직
SceneType TownScene::Update(Character& p, ConsoleUI& ui) {
    ui.PrintTown(p);
    int choice = ui.InputSelect("1.던전  2.상점  3.퀘스트  4.인벤토리  5.휴식  6.종료 ");

    if (choice == 1) return SceneType::DUNGEON;
    if (choice == 2) return SceneType::SHOP;
    if (choice == 3) return SceneType::QUEST;
    if (choice == 4) {
        ui.PrintInventory(p);
        int itemIdx = ui.InputSelect("장착/사용할 아이템 번호 (0: 취소)");
        if (itemIdx > 0 && itemIdx <= p.GetInventory().size()) {
            if (p.GetInventory()[itemIdx - 1]->GetType() == ItemType::CONSUMABLE) p.UseConsumable(itemIdx - 1);
            else p.EquipItem(itemIdx - 1);
        }
    }
    if (choice == 5) { p.HealFull(); ui.PrintMessage("휴식을 취했습니다."); }
    if (choice == 6) return SceneType::EXIT;
    return SceneType::TOWN;
}

// 2. 상점 로직 (무기/방어구, 소모품, 스킬)
SceneType ShopScene::Update(Character& p, ConsoleUI& ui) {
    ui.PrintMessage("\n[상점] 보유 골드: " + std::to_string(p.GetGold()) + "G");
    int choice = ui.InputSelect("1.무기(200G)  2.HP 포션(50G)  3.MP 포션(50G)  4.스킬북(300G)  5.나가기 ");

    if (choice == 1 && p.SpendGold(200)) {
        p.AddItem(std::make_shared<Item>("강철 검 ", ItemType::WEAPON, 15, Element::NORMAL, Rarity::RARE));
        ui.PrintMessage("강철 검 구매 완료!");
    }
    else if (choice == 2 && p.SpendGold(50)) {
        p.AddItem(std::make_shared<Item>("HP 포션 ", ItemType::CONSUMABLE, 50, Element::NORMAL, Rarity::NORMAL, ConsumableType::HP));
        ui.PrintMessage("HP 포션 구매 완료!");
    }
    else if (choice == 3 && p.SpendGold(50)) {
        p.AddItem(std::make_shared<Item>("MP 포션 ", ItemType::CONSUMABLE, 30, Element::NORMAL, Rarity::NORMAL, ConsumableType::MP));
        ui.PrintMessage("MP 포션 구매 완료!");
    }
    else if (choice == 4 && p.SpendGold(300)) {
        p.LearnSkill({ "필살기 ", 30, 2.5f });
        ui.PrintMessage("필살기 습득 완료!");
    }
    else if (choice != 5) {
        ui.PrintMessage("골드가 부족합니다.");
    }
    return SceneType::TOWN;
}

// 3. 던전 로직 (던전 3개 구현)
SceneType DungeonScene::Update(Character& p, ConsoleUI& ui) {
    ui.PrintMessage("\n🏰 [던전 선택]");
    int choice = ui.InputSelect("1.초보자(2층)  2.중급자(3층)  3.심연(보스전)  4.돌아가기");

    std::vector<Monster> waves;
    int clearGold = 0, clearExp = 0;

    if (choice == 1) {
        waves = { Monster("약한 고블린", Element::FIRE, {30,30,0,0,8,2}, 20),
                  Monster("고블린 대장", Element::FIRE, {60,60,0,0,15,5}, 50) };
        clearGold = 300; clearExp = 100;
    }
    else if (choice == 2) {
        waves = { Monster("물방울 슬라임", Element::WATER, {50,50,0,0,12,3}, 40),
                  Monster("독 슬라임", Element::WATER, {70,70,0,0,20,8}, 60),
                  Monster("슬라임 킹", Element::WATER, {120,120,0,0,30,12}, 150) };
        clearGold = 800; clearExp = 300;
    }
    else if (choice == 3) {
        waves = { Monster("에인션트 드래곤", Element::GRASS, {300,300,0,0,60,20}, 500) };
        clearGold = 2000; clearExp = 1000;
    }
    else return SceneType::TOWN;

    return ProcessDungeonRun(p, ui, waves, clearGold, clearExp, choice);
}

SceneType DungeonScene::ProcessDungeonRun(Character& p, ConsoleUI& ui, std::vector<Monster>& waves, int cGold, int cExp, int dunLevel) {
    ui.PrintMessage("\n던전에 입장합니다... 전투가 시작됩니다!");
    bool isCleared = true;

    for (size_t i = 0; i < waves.size(); ++i) {
        ui.PrintMessage("\n--- [ 던전 " + std::to_string(i + 1) + "층 진입 ] ---");
        if (!battleMgr.ProcessBattle(p, waves[i])) {
            isCleared = false;
            break;
        }
    }

    if (isCleared) {
        ui.PrintLine();
        ui.PrintMessage("🎉 [던전 클리어!] 모든 몬스터를 처치했습니다!");
        ui.PrintMessage("클리어 보상: " + std::to_string(cGold) + "G / EXP " + std::to_string(cExp) + " 획득!");
        p.AddGold(cGold);
        p.GainExp(cExp);

        if (dunLevel == 2) questMgr.UpdateProgress(QuestType::CLEAR_DUNGEON);

        while (SystemPolicy::CheckLevelUp(p.GetLevel(), p.GetExp())) {
            p.LevelUp(); ui.PrintLevelUp(p.GetLevel());
        }
    }
    else ui.PrintMessage("\n공략에 실패하여 마을로 귀환합니다.");

    return SceneType::TOWN;
}

SceneType QuestScene::Update(Character& p, ConsoleUI& ui) {
    ui.PrintQuests(questMgr);
    int choice = ui.InputSelect("퀘스트 번호 선택 (수락/보상 수령) (0: 돌아가기)");

    if (choice > 0 && choice <= questMgr.GetQuests().size()) {
        int idx = choice - 1;
        auto q = questMgr.GetQuests()[idx];

        if (q.state == QuestState::NOT_ACCEPTED) {
            questMgr.AcceptQuest(idx);
            ui.PrintMessage("\n📝 퀘스트 [" + q.name + "] 를 수락했습니다!");
        }
        else if (q.state == QuestState::CAN_REWARD) {
            if (questMgr.ClaimReward(idx, p)) {
                ui.PrintMessage("\n🎉 보상 수령! (" + std::to_string(q.rewardExp) + "EXP와 " + std::to_string(q.rewardGold) + "G 획득)");
                while (SystemPolicy::CheckLevelUp(p.GetLevel(), p.GetExp())) {
                    p.LevelUp(); ui.PrintLevelUp(p.GetLevel());
                }
            }
        }
        else {
            ui.PrintMessage("\n진행 중이거나 이미 완료된 퀘스트입니다.");
        }
    }
    return SceneType::TOWN;
}