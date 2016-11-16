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

class Hull : public Item
{
  public:
    Hull();

    void setArmorPiece(spItem armor);

    spItem getArmorPiece();

  private:
    spItem _armor_piece;

};