#include "pch.h"
#include "abstract_window.h"

abstract_window::abstract_window () :
	active_ (false)
{
}

void abstract_window::activate ()
{
	active_ = true;
}

void abstract_window::deactivate ()
{
	active_ = false;
}
