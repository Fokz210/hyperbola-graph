#include "pch.h"
#include "cursor_handler.h"
#include <iostream>

cursor::cursor (const cursor::TYPE t)
{
	switch (t)
	{
	case cursor::WAIT:
	{
		Cursor = LoadCursor (NULL, IDC_WAIT);
	}
	break;
	case cursor::HAND:
	{
		Cursor = LoadCursor (NULL, IDC_HAND);
	}
	break;
	case cursor::NORMAL:
	{
		Cursor = LoadCursor (NULL, IDC_ARROW);
	}
	break;
	case cursor::TEXT:
	{
		Cursor = LoadCursor (NULL, IDC_IBEAM);
	}
	break;
	}
}

void cursor::Set (const sf::WindowHandle & aWindowHandle) const
{
	SetClassLongPtr (aWindowHandle, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(Cursor));
}
