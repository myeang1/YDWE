#pragma once

#include <ydwe/win/scoped_handle.h>
#include <Windows.h>
#include <cstdint>

_BASE_BEGIN namespace file {

	class file_handle : public win::scoped_handle<INVALID_HANDLE_VALUE>
	{
		typedef win::scoped_handle<INVALID_HANDLE_VALUE> _Mybase;

	public:
		file_handle(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
		uint64_t get_size();
	};
}}
