/*
Author: Alexander Mastryukov
License: http://creativecommons.org/licenses/by-nc-nd/4.0/legalcode
*/

#include "resources.h"

/*
For now this serves as an example, but later will include all resources
*/
namespace resources
{
	Resources battle_ui;
  Resources equipment;

	void load()
	{
		//load UI resources
		battle_ui.loadXML("xml/battle_ui.xml");
    equipment.loadXML("xml/equipment.xml");
	}

	void free()
	{
		//unload
    battle_ui.free();
    equipment.free();
	}
}