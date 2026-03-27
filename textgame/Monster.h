#pragma once
// Monster.h
#pragma once
#include <string>
#include "Types.h"

class Monster {
private:
    std::string name;
    Element element;
    Stats stats;
    int dropExp;
public:
    Monster(std::string n, Element e, Stats s, int exp);

    std::string GetName() const;
    Element GetElement() const;
    int GetAttack() const;
    int GetHp() const;
    int GetMaxHp() const;
    int GetDropExp() const;
    bool IsDead() const;

    int TakeDamage(int damage);
};