#pragma once
// Scene.h
#pragma once
#include "Character.h"
#include "ConsoleUI.h"
#include "BattleManager.h"
#include "Policy.h"

enum class SceneType { TOWN, DUNGEON, SHOP, QUEST, EXIT };

// 추상 클래스
class Scene {
public:
    virtual ~Scene() = default;
    virtual SceneType Update(Character& player, ConsoleUI& ui) = 0;
};

class TownScene : public Scene {
public:
    SceneType Update(Character& player, ConsoleUI& ui) override;
};

class ShopScene : public Scene {
public:
    SceneType Update(Character& player, ConsoleUI& ui) override;
};

class DungeonScene : public Scene {
private:
    BattleManager& battleMgr;
    QuestManager& questMgr; // 던전 클리어 시 퀘스트 업데이트를 위해 추가
    SceneType ProcessDungeonRun(Character& p, ConsoleUI& ui, std::vector<Monster>& waves, int cGold, int cExp, int dunLevel);
public:
    DungeonScene(BattleManager& bm, QuestManager& qm) : battleMgr(bm), questMgr(qm) {}
    SceneType Update(Character& player, ConsoleUI& ui) override;
};

class QuestScene : public Scene {
private:
    QuestManager& questMgr;
public:
    QuestScene(QuestManager& qm) : questMgr(qm) {}
    SceneType Update(Character& player, ConsoleUI& ui) override;
};