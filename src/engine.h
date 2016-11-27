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

    void init(int evasion);

    void setEvasion(int evasion);
    void setArmorPiece(spArmor armor);

    void init(std::string ID);

    int getEvasion();
    spArmor getArmorPiece();

  private:
    spArmor _armor_piece;
    int _evasion;
};