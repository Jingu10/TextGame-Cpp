#pragma once
// Types.h
#pragma once
#include <string>

enum class Element { FIRE, WATER, GRASS, NORMAL };
enum class Job { WARRIOR, MAGE, ROGUE };
enum class ItemType { WEAPON, ARMOR, CONSUMABLE }; 
enum class Rarity { NORMAL, RARE, UNIQUE }; 
enum class ConsumableType { NONE, HP, MP };
enum class QuestType { KILL_MONSTER, USE_SKILL, CLEAR_DUNGEON };
enum class QuestState { NOT_ACCEPTED, IN_PROGRESS, CAN_REWARD, COMPLETED };

struct Stats {
    int hp, maxHp;
    int mp, maxMp;
    int attack;
    int defense;
};

struct Skill {
    std::string name;
    int mpCost;
    float damageMultiplier;
};

struct DamageResult {
    int damage;
    bool isSuperEffective;
};

struct Quest {
    std::string name;
    std::string desc;
    QuestType type;
    int target;
    int current;
    int rewardGold;
    int rewardExp;
    QuestState state;
};

inline std::string ElemToStr(Element e) {
    if (e == Element::FIRE) return "불 ";
    if (e == Element::WATER) return "물 ";
    if (e == Element::GRASS) return "풀 ";
    return "무속성 ";
}

inline std::string JobToStr(Job j) {
    if (j == Job::WARRIOR) return "전사 ";
    if (j == Job::MAGE) return "마법사 ";
    return "도적 ";
}

inline std::string RarityToStr(Rarity r) {
    if (r == Rarity::UNIQUE) return "유니크 ";
    if (r == Rarity::RARE) return "레어 ";
    return "일반 ";
}