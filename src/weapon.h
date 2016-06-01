/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(Weapon, spWeapon);

class Weapon : public Item
{
  public:
    Weapon();

  private:

};