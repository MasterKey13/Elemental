/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include <string>
#include "json/json.h"
#include "item.h"

//declare smart pointer
DECLARE_SMART(Item, spItem);

using namespace oxygine;

class Engine : public Item
{
  public:
    Engine();

    void setEvasion(int evasion);
    void setArmorPiece(spItem armor);

    int getEvasion();
    spItem getArmorPiece();

  private:
    spItem _armor_piece;
    int _evasion;
};