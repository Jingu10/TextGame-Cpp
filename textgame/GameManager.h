#pragma once
// GameManager.h
#pragma once
#include "ConsoleUI.h"
#include "BattleManager.h"
#include "QuestManager.h"
#include "Character.h"

class GameManager {
private:
    ConsoleUI ui;
    BattleManager battleMgr;
    QuestManager questMgr;

public:
    GameManager();
    void Run();
};