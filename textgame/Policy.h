#pragma once
// Policy.h
#pragma once
#include <memory>
#include "Types.h"
#include "Item.h"

class BattlePolicy {
public:
    static float GetElementMultiplier(Element atk, Element def);
    static DamageResult CalcDamage(int attack, float skillMult, Element atkElem, Element defElem);
    static Skill GetJobSkill(Job job);
};

class SystemPolicy {
public:
    static bool CheckLevelUp(int level, int exp);
    static std::shared_ptr<Item> GenerateDropItem();
};