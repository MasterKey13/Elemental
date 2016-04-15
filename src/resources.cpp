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
	Resources ui;

	void load()
	{
		//load our resources
		ui.loadXML("xml/ui.xml");
	}

	void free()
	{
		//unload
		ui.free();
	}
}