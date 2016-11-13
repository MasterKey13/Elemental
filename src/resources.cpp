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

	void load()
	{
		//load UI resources
		battle_ui.loadXML("battle_ui.xml");
	}

	void free()
	{
		//unload
    battle_ui.free();
	}
}