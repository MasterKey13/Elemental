/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
#include "item.h"
#include "ship.h"
#include "container.h"

using namespace oxygine;

#define MAX_ELEMENTS 50

//Declare smart pointers
DECLARE_SMART(Synthesizer, spSynthesizer);
DECLARE_SMART(Container, spContainer);

class Synthesizer : public Item
{
  public:
    Synthesizer();

    void init(int capacity);

    void init(std::string ID);

    void decomposeItem(spItem item);
    void synthesizeItem(std::string ID);

  private:
    spContainer _chem_container;
};