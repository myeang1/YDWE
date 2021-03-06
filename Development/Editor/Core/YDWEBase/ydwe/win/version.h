#pragma once

#include <ydwe/config.h>

_BASE_BEGIN
namespace win {
	enum Version 
	{
		VERSION_PRE_XP = 0,
		VERSION_XP,
		VERSION_SERVER_2003,
		VERSION_VISTA,
		VERSION_WIN7,
		VERSION_WIN8,
		VERSION_WIN_LAST,
	};

	Version _BASE_API version();
}
_BASE_END
