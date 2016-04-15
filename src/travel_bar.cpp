/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "travel_bar.h"

TravelBar::TravelBar()
{

}

void TravelBar::init()
{
  //test bar for now for debugging
	_bar = new ColorRectSprite;
	_bar->setSize(500, 50);
	_bar->attachTo(this);
	_bar->setColor(Color::Green);
	_bar->setPosition(getStage()->getWidth() / 2 - _bar->getWidth() / 2, getStage()->getHeight() - _bar->getHeight());
}