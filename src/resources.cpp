#include "resources.h"

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