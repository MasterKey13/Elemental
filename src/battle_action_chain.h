/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "battle_action.h"

using namespace oxygine;

//Declare smart pointers
DECLARE_SMART(BattleActionChain, spBattleActionChain);

class BattleActionChain : public Actor
{
  public:
    BattleActionChain();

    void init();

    //SETTERS
    void setHead(spBattleAction head);
    void setTail(spBattleAction tail);
    void setCurrent(spBattleAction curr);

    //GETTERS
    spBattleAction getHead();
    spBattleAction getTail();
    spBattleAction getCurrent();

    void addAction(spBattleAction action);

  private:
    spBattleAction _head;
    spBattleAction _tail;
    spBattleAction _current;
};