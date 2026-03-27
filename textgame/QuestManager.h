#pragma once
// QuestManager.h
#pragma once
#include <vector>
#include "Types.h"
#include "Character.h"

class QuestManager {
private:
    std::vector<Quest> quests;
public:
    QuestManager();
    const std::vector<Quest>& GetQuests() const;

    bool AcceptQuest(int index);
    void UpdateProgress(QuestType type, int amount = 1);
    bool ClaimReward(int index, Character& player);
};