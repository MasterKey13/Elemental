/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "armor.h"
#include "damageable.h"

//declare smart pointer
DECLARE_SMART(Engine, spEngine);
DECLARE_SMART(Armor, spArmor);

using namespace oxygine;

class Engine : public Item, public Damageable
{
  public:
    Engine();

    void init(int evasion, float max_weight);

    void setEvasion(int evasion);
    void setArmorPiece(spArmor armor);
    void setMaxWeight(float weight);

    void init(std::string ID);

    int getEvasion();
    spArmor getArmorPiece();
    float getMaxWeight();

  private:
    spArmor _armor_piece;
    int _evasion;
    float _max_weight;
};