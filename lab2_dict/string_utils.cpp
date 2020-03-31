#include "string_utils.h"
#include <iostream>
#include <string>
#include <codecvt>
#include <locale>

std::string StringToLowerUTF8(const std::string& s)
{
	std::locale::global(std::locale(""));
	std::wcout.imbue(std::locale());
	auto& facet = std::use_facet<std::ctype<wchar_t>>(std::locale());
	std::wstring str = StringToWstring(s);
	facet.tolower(&str[0], &str[0] + str.size());
	return WstringToString(str);
}

std::wstring StringToWstring(const std::string& s)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(s);
}

std::string WstringToString(const std::wstring& s)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().to_bytes(s);
}