#pragma once

#include <ydwe/config.h>
#include <cstdint>

_BASE_BEGIN namespace hook {
	_BASE_API bool inline_install(uintptr_t* pointer_ptr, uintptr_t detour);
	_BASE_API bool inline_uninstall(uintptr_t* pointer_ptr, uintptr_t detour);	
	_BASE_API uintptr_t replace_pointer(uintptr_t address, uintptr_t new_value);
}}
