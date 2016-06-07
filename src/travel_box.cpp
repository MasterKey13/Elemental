/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "setup.h"
#include "travel_box.h"

TravelBox::TravelBox()
{

}

/*
Initialize a TravelBox (grid with location stuff)
*/
void TravelBox::init(int grid)
{
  grid_size = grid;

  _boxSetUp();
  _gridSetUp();
  _navButtonSetUp();
}

//set up the background box
void TravelBox::_boxSetUp()
{
  _box = new ColorRectSprite;
  _box->setSize(grid_size * 12 + 13, grid_size * 12 + 13);
  _box->setColor(Color::Gray);

  addChild(_box);
}

//set up the grid of locations
void TravelBox::_gridSetUp()
{
  int offset_x = grid_size + 2;
  int offset_y = grid_size + 2;

  //fill up the grids with gray box sprites
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      _grid[i][j] = new Sprite;
      _grid[i][j]->setResAnim(resources::ui.getResAnim("nav_grid"));
      _grid[i][j]->setScale(1.0f);
      _grid[i][j]->setPosition(offset_x, offset_y);

      addChild(_grid[i][j]);

      offset_x += grid_size + 1;
    }

    offset_x = grid_size + 2;
    offset_y += grid_size + 1;
  }
}

//set up the navigation buttons on each side
void TravelBox::_navButtonSetUp()
{
  for (int i = 0; i < 4; i++)
  {
    _nav_buttons[i] = new ColorRectSprite;
    _nav_buttons[i]->setColor(Color::DarkGray);
    
    addChild(_nav_buttons[i]);
  }

  _nav_buttons[0]->setSize(grid_size, grid_size * 10 + 9); //left nav button
  _nav_buttons[1]->setSize(grid_size * 10 + 9, grid_size); //top nav button
  _nav_buttons[2]->setSize(grid_size, grid_size * 10 + 9); //right nav button
  _nav_buttons[3]->setSize(grid_size * 10 + 9, grid_size); //bottom nav button

  _nav_buttons[0]->setPosition(1, grid_size + 2);
  _nav_buttons[1]->setPosition(grid_size + 2, 1);
  _nav_buttons[2]->setPosition(grid_size * 11 + 12, grid_size + 2);
  _nav_buttons[3]->setPosition(grid_size + 2, grid_size * 11 + 12);
}