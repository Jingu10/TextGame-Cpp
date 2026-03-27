#pragma once
// ConsoleUI.h
#pragma once
#include <string>
#include "Character.h"
#include "Monster.h"
#include "QuestManager.h"

class ConsoleUI {
public:
    void PrintLine();
    int InputSelect(const std::string& msg);
    std::string InputString(const std::string& msg);

    void PrintTown(const Character& p);
    void PrintInventory(const Character& p);
    void PrintBattleMenu(const Character& p, const Monster& m);
    void PrintDamage(const std::string& atk, const std::string& def, int dmg, bool isSuper);
    void PrintMessage(const std::string& msg);
    void PrintLevelUp(int newLevel);
    void PrintSkills(const std::vector<Skill>& skills);
    void PrintConsumables(const Character& p);
    void PrintQuests(const QuestManager& qm);
    void PrintMonsterArt(const std::string& monsterName);
    void PrintSkillEffect(const std::string& skillName);
};