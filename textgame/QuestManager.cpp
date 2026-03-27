#include "QuestManager.h"

QuestManager::QuestManager() {
    quests = {
        {"초보 사냥꾼", "아무 몬스터나 3마리 처치", QuestType::KILL_MONSTER, 3, 0, 300, 100, QuestState::NOT_ACCEPTED},
        {"스킬 마스터", "스킬 5회 사용", QuestType::USE_SKILL, 5, 0, 500, 200, QuestState::NOT_ACCEPTED},
        {"중급자 증명", "중급자 던전 1회 클리어", QuestType::CLEAR_DUNGEON, 1, 0, 1000, 500, QuestState::NOT_ACCEPTED}
    };
}

const std::vector<Quest>& QuestManager::GetQuests() const { return quests; }

bool QuestManager::AcceptQuest(int index) {
    if (index < 0 || index >= quests.size()) return false;
    if (quests[index].state == QuestState::NOT_ACCEPTED) {
        quests[index].state = QuestState::IN_PROGRESS;
        return true;
    }
    return false;
}

void QuestManager::UpdateProgress(QuestType type, int amount) {
    for (auto& q : quests) {
        if (q.state == QuestState::IN_PROGRESS && q.type == type) {
            q.current += amount;
            if (q.current >= q.target) {
                q.current = q.target;
                q.state = QuestState::CAN_REWARD; // 목표 달성 시 보상 수령 가능 상태로 전환
            }
        }
    }
}

bool QuestManager::ClaimReward(int index, Character& player) {
    if (index < 0 || index >= quests.size()) return false;
    if (quests[index].state == QuestState::CAN_REWARD) {
        player.AddGold(quests[index].rewardGold);
        player.GainExp(quests[index].rewardExp);
        quests[index].state = QuestState::COMPLETED; // 보상 수령 완료
        return true;
    }
    return false;
}