/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

namespace resources
{
	extern Resources battle_ui;
  extern Resources equipment;
  extern Resources hulls;
  extern Resources engines;
  extern Resources batteries;
  extern Resources game_ui;

	void load();
	void free();
}