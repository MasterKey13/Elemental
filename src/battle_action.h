/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(BattleAction, spBattleAction);
DECLARE_SMART(Item, spItem);

class BattleAction : public Actor
{
  public:
    BattleAction();

    void process(spItem item, spItem target, spItem armor);

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