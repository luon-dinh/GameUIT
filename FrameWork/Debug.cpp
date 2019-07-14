#pragma once
#include "Debug.h"
#include <locale>
#include <codecvt>
#include <string>
#include <Windows.h>

void PrintDebug(const char* c)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	std::wstring wide = converter.from_bytes(c);
	DebugOut(wide.c_str());
}

void DebugOut(const wchar_t *fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugStringW(dbg_out);
}

void PrintDebugNumber(int num)
{
	std::string s = std::to_string(num);
	char const * chararr = s.c_str();
	PrintDebug(chararr);
}
