/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "weapon.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(BattleAction, spBattleAction);

class BattleAction : public Actor
{
  public:
    BattleAction();

    void init(spWeapon weapon, spItem target);
    void init(spItem item, spItem target);

    //SETTERS
    void setPrevious(spBattleAction previous);
    void setNext(spBattleAction next);

    //GETTERS
    spBattleAction getPrevious();
    spBattleAction getNext();

    bool hasNext();
    bool hasPrevious();

  private:
    spBattleAction _prev;
    spBattleAction _next;
};