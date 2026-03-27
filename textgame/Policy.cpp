// Policy.cpp
#include "Policy.h"
#include <cstdlib>

float BattlePolicy::GetElementMultiplier(Element atk, Element def) {
    if (atk == Element::WATER && def == Element::FIRE) return 1.5f;
    if (atk == Element::FIRE && def == Element::GRASS) return 1.5f;
    if (atk == Element::GRASS && def == Element::WATER) return 1.5f;
    return 1.0f;
}

DamageResult BattlePolicy::CalcDamage(int attack, float skillMult, Element atkElem, Element defElem) {
    float elemMult = GetElementMultiplier(atkElem, defElem);
    int finalDmg = static_cast<int>(attack * skillMult * elemMult);
    return { finalDmg, elemMult > 1.1f };
}

Skill BattlePolicy::GetJobSkill(Job job) {
    if (job == Job::WARRIOR) return { "파워 슬래시 ", 10, 1.5f };
    if (job == Job::MAGE) return { "파이어 볼 ", 15, 2.0f };
    return { "백스탭 ", 12, 1.8f };
}

bool SystemPolicy::CheckLevelUp(int level, int exp) {
    return exp >= (level * 50);
}

std::shared_ptr<Item> SystemPolicy::GenerateDropItem() {
    int r = std::rand() % 6;
    if (r == 0) return std::make_shared<Item>("불꽃의 검 ", ItemType::WEAPON, 8, Element::FIRE);
    if (r == 1) return std::make_shared<Item>("얼음 지팡이 ", ItemType::WEAPON, 8, Element::WATER);
    if (r == 2) return std::make_shared<Item>("자연의 단검 ", ItemType::WEAPON, 8, Element::GRASS);
    if (r == 3) return std::make_shared<Item>("낡은 철검 ", ItemType::WEAPON, 5, Element::NORMAL);
    if (r == 4) return std::make_shared<Item>("강철 갑옷 ", ItemType::ARMOR, 6, Element::NORMAL);
    return std::make_shared<Item>("가죽 튜닉 ", ItemType::ARMOR, 3, Element::NORMAL);
}