// BattleManager.h
#pragma once
#include "Character.h"
#include "Monster.h"
#include "ConsoleUI.h"

class BattleManager {
private:
    ConsoleUI& ui;
    QuestManager& questMgr;

    void ProcessPlayerTurn(Character& p, Monster& m, int choice);
    void ProcessMonsterTurn(Character& p, Monster& m);
    bool PostBattleCheck(Character& p, Monster& m);

public:
    BattleManager(ConsoleUI& ui, QuestManager& qm);
    bool ProcessBattle(Character& p, Monster& m);
};
