/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "item.h"
#include "hull.h"

Hull::Hull()
{

}

void Hull::setArmorPiece(spItem armor)
{
  _armor_piece = armor;
}