/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "damage.h"
#include "damageable.h"

//declare smart pointer
DECLARE_SMART(Armor, spArmor);

using namespace oxygine;

class Armor : public Item, public Damageable
{
  public:
    Armor();

    void init(
      int ballistic_res, 
      int electrical_res, 
      int chemical_ress
      );

    void init(std::string ID);

  private:

};