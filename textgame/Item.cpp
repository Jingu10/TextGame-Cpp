// Item.cpp
#include "Item.h"

Item::Item(std::string n, ItemType t, int b, Element e, Rarity r, ConsumableType ct)
    : name(n), type(t), statBonus(b), element(e), rarity(r), consType(ct) {}

std::string Item::GetName() const { return name; }
ItemType Item::GetType() const { return type; }
int Item::GetBonus() const { return statBonus; }
Element Item::GetElement() const { return element; }
Rarity Item::GetRarity() const { return rarity; }
ConsumableType Item::GetConsType() const { return consType; }
