#pragma once

#include <ydwe/config.h>
#include <ydwe/util/unicode.h>
#include <ydwe/util/string_ref.h>
#include <locale>
#include <string>

_BASE_BEGIN 
namespace util { namespace detail {
	typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_type;

	void convert(const char* from, const char* from_end, std::wstring& to, const codecvt_type& cvt, conv_method how);
	void convert(const wchar_t* from, const wchar_t* from_end, std::string& to, const codecvt_type& cvt, conv_method how);

	template<class FromChar, class ToChar> 
	std::basic_string<ToChar> convert(std::basic_string<FromChar> const& from, const codecvt_type& cvt, conv_method how)
	{
		std::basic_string<ToChar> to;
		if (from.size())
		{
			convert(&*from.begin(), &*from.begin() + from.size(), to, cvt, how);
		}
		return std::move(to);
	}

	template<class FromChar, class ToChar> 
	std::basic_string<ToChar> convert(boost::basic_string_ref<FromChar> const& from, const codecvt_type& cvt, conv_method how)
	{
		std::basic_string<ToChar> to;
		if (from.size())
		{
			convert(&*from.begin(), &*from.begin() + from.size(), to, cvt, how);
		}
		return std::move(to);
	}
}}
_BASE_END
