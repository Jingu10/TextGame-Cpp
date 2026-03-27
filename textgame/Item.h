#pragma once
// Item.h
#pragma once
#include <string>
#include "Types.h"

class Item {
protected:
    std::string name;
    ItemType type;
    int statBonus;
    Element element;
    Rarity rarity;
    ConsumableType consType;
public:
    Item(std::string n, ItemType t, int b, Element e = Element::NORMAL, Rarity r = Rarity::NORMAL, ConsumableType ct = ConsumableType::NONE);
    virtual ~Item() = default;

    std::string GetName() const;
    ItemType GetType() const;
    int GetBonus() const;
    Element GetElement() const;
    Rarity GetRarity() const;
    ConsumableType GetConsType() const;
};


    