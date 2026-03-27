// Character.h
#pragma once
#include <string>
#include <vector>
#include <set>
#include <memory>
#include "Types.h"
#include "Item.h"

class Character {
private:
    std::string name;
    Job job;
    Element baseElement;
    Stats stats;
    int level;
    int exp;
    int gold; // 재화 추가
    bool newSkillLearned;
    std::vector<Skill> skills; // 배운 스킬 목록

    std::vector<std::shared_ptr<Item>> inventory;
    std::shared_ptr<Item> equippedWeapon; // 인벤토리와 장비창이 동일한 weapon 을 가리키도록
    std::shared_ptr<Item> equippedArmor;

public:
    Character(std::string n, Job j, Element e, Stats s);

    // Getter
    std::string GetName() const;
    Job GetJob() const;
    Stats GetBaseStats() const;
    int GetLevel() const;
    int GetExp() const;
    int GetGold() const;
    bool IsDead() const;
    bool IsLearned() const;

    const std::vector<std::shared_ptr<Item>>& GetInventory() const;
    const std::vector<Skill>& GetSkills() const;

    Element GetElement() const;
    Element GetAttackElement() const;
    int GetTotalAttack() const;
    int GetTotalDefense() const;

    // Setter / 로직
    int TakeDamage(int damage);
    void ConsumeMp(int amount);
    void HealFull();
    void Heal(int amount); // 소모품용 회복
    void HealMp(int amount);
    bool UseConsumable(int index);
    void GainExp(int amount);
    void LevelUp();

    void AddGold(int amount);
    bool SpendGold(int amount);

    void AddItem(std::shared_ptr<Item> item);
    void EquipItem(int index);
    void LearnSkill(Skill skill);  // 스킬 배우기
    void AddQuest(Quest q);
    void UpdateQuestProgress(QuestType type, int amount);
};