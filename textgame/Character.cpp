// Character.cpp
#include "Character.h"
#include "Policy.h"
#include <algorithm>

Character::Character(std::string n, Job j, Element e, Stats s)
    : name(n), job(j), baseElement(e), stats(s), level(1), exp(0), gold(10000),
    equippedWeapon(nullptr), equippedArmor(nullptr), newSkillLearned(false) {
    skills.push_back(BattlePolicy::GetJobSkill(job)); // 직업 기본 스킬 부여
}

std::string Character::GetName() const { return name; }
Job Character::GetJob() const { return job; }
Stats Character::GetBaseStats() const { return stats; }
int Character::GetLevel() const { return level; }
int Character::GetExp() const { return exp; }
int Character::GetGold() const { return gold; }
bool Character::IsDead() const { return stats.hp <= 0; }
bool Character::IsLearned() const { return newSkillLearned; }

const std::vector<std::shared_ptr<Item>>& Character::GetInventory() const { return inventory; }
const std::vector<Skill>& Character::GetSkills() const { return skills; }

Element Character::GetElement() const { return baseElement; }
Element Character::GetAttackElement() const { return equippedWeapon ? equippedWeapon->GetElement() : baseElement; }

int Character::GetTotalAttack() const { return stats.attack + (equippedWeapon ? equippedWeapon->GetBonus() : 0); }
int Character::GetTotalDefense() const { return stats.defense + (equippedArmor ? equippedArmor->GetBonus() : 0); }

int Character::TakeDamage(int damage) {
    int actualDmg = std::max(1, damage - GetTotalDefense());
    stats.hp = std::max(0, stats.hp - actualDmg);
    return actualDmg;
}

void Character::ConsumeMp(int amount) { stats.mp = std::max(0, stats.mp - amount); }
void Character::HealFull() { stats.hp = stats.maxHp; stats.mp = stats.maxMp; }
void Character::Heal(int amount) { stats.hp = std::min(stats.maxHp, stats.hp + amount); }
void Character::GainExp(int amount) { exp += amount; }

void Character::LevelUp() {
    exp -= (level * 50);
    level++;
    stats.maxHp += 20; stats.maxMp += 10;
    stats.attack += 5; stats.defense += 2;
    HealFull();
}

void Character::AddGold(int amount) { gold += amount; }
bool Character::SpendGold(int amount) {
    if (gold >= amount) { gold -= amount; return true; }
    return false;
}

void Character::AddItem(std::shared_ptr<Item> item) { inventory.push_back(item); }

void Character::EquipItem(int index) {
    if (index < 0 || index >= inventory.size()) return;
    auto item = inventory[index];
    if (item->GetType() == ItemType::WEAPON) equippedWeapon = item;
    else if (item->GetType() == ItemType::ARMOR) equippedArmor = item;
}

bool Character::UseConsumable(int index) {
    if (index < 0 || index >= inventory.size()) return false;
    auto item = inventory[index];

    if (item->GetType() == ItemType::CONSUMABLE) {
        if (item->GetConsType() == ConsumableType::HP) Heal(item->GetBonus());
        else if (item->GetConsType() == ConsumableType::MP) HealMp(item->GetBonus());

        inventory.erase(inventory.begin() + index); // 사용 후 소모
        return true;
    }
    return false;
}

void Character::LearnSkill(Skill skill) {
    if (!IsLearned()) {
        skills.push_back(skill);
        newSkillLearned = true;
    }
}

void Character::HealMp(int amount) { stats.mp = std::min(stats.maxMp, stats.mp + amount); }

