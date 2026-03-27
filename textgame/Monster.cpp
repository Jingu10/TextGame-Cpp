// Monster.cpp
#include "Monster.h"
#include <algorithm>

Monster::Monster(std::string n, Element e, Stats s, int exp)
    : name(n), element(e), stats(s), dropExp(exp) {
}

std::string Monster::GetName() const { return name; }
Element Monster::GetElement() const { return element; }
int Monster::GetAttack() const { return stats.attack; }
int Monster::GetHp() const { return stats.hp; }
int Monster::GetMaxHp() const { return stats.maxHp; }
int Monster::GetDropExp() const { return dropExp; }
bool Monster::IsDead() const { return stats.hp <= 0; }

int Monster::TakeDamage(int damage) {
    int actualDmg = std::max(1, damage - stats.defense);
    stats.hp = std::max(0, stats.hp - actualDmg);
    return actualDmg;
}