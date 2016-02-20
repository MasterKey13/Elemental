#include "setup.h"
#include "TravelBar.h"

TravelBar::TravelBar()
{

}

void TravelBar::init()
{
	//initialize the travel bar
	_bar = new ColorRectSprite;
	_bar->setSize(500, 50);
	_bar->attachTo(this);
	_bar->setColor(Color::Green);
	_bar->setPosition(getStage()->getWidth() / 2 - _bar->getWidth() / 2, getStage()->getHeight() - _bar->getHeight());
}