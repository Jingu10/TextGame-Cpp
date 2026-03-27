// GameManager.cpp 의 Run() 내부 로직
#include "GameManager.h"
#include "Scene.h"

GameManager::GameManager() : battleMgr(ui, questMgr) {} // 의존성 주입

void GameManager::Run() {
    ui.PrintMessage("=== RPG 세계에 오신 것을 환영합니다 === ");
    std::string name = ui.InputString("캐릭터 이름을 입력하세요 ");
    int jobSel = ui.InputSelect("직업 선택 (1.전사  2.마법사  3.도적) ");

    Job job = Job::WARRIOR; Element elem = Element::NORMAL;
    if (jobSel == 2) { job = Job::MAGE; elem = Element::FIRE; }
    else if (jobSel == 3) { job = Job::ROGUE; elem = Element::GRASS; }

    Stats initStats = { 100, 100, 30, 30, 15, 5 };
    Character player(name, job, elem, initStats);

    // 씬 객체들 초기화
    TownScene town;
    ShopScene shop;
    QuestScene quest(questMgr);
    DungeonScene dungeon(battleMgr, questMgr);

    SceneType currentScene = SceneType::TOWN;

    // 객체지향적 상태 머신 (Scene 전환)
    while (currentScene != SceneType::EXIT) {
        if (currentScene == SceneType::TOWN) currentScene = town.Update(player, ui);
        else if (currentScene == SceneType::DUNGEON) currentScene = dungeon.Update(player, ui);
        else if (currentScene == SceneType::SHOP) currentScene = shop.Update(player, ui);
        else if (currentScene == SceneType::QUEST) currentScene = quest.Update(player, ui);
    }
    ui.PrintMessage("게임이 종료되었습니다. ");
}