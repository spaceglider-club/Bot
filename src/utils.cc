// This file has function definitions for utils.h

#include "utils.h"
#include "interface.h"

#include <Windows.h>
#include <string>
#include <random>
#include <xorstr.hpp>
#include <locale>
#include <codecvt>
#include <sstream>

bool cUtils::IsLeagueForeGround()
{
	HWND handle = GetForegroundWindow();
	DWORD pid;
	GetWindowThreadProcessId(handle, &pid);
	if (Interface->process_id != pid)
	{
		CloseHandle(handle);
		return false;
	}
	return true;
}

bool cUtils::IsScriptForeGround()
{
	HWND handle = GetForegroundWindow();
	DWORD pid;
	GetWindowThreadProcessId(handle, &pid);
	if (GetCurrentProcessId() != pid)
	{
		return false;
	}
	return true;
}

std::string cUtils::wtos(std::wstring wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	try
	{
		return converter.to_bytes(wstr);
	}
	catch (std::range_error)
	{
		return xorstr_("range_error");
	}
}

std::wstring cUtils::stow(std::string str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;

	try
	{
		return converter.from_bytes(str);
	}
	catch (std::range_error)
	{
		std::wostringstream s;
		s << str.c_str();
		return s.str();
	}
}

std::string cUtils::RandomString(int size)
{
	std::string str = xorstr_("");

	for (int i = 0; i < size; i++)
		str += RandomInt(0, 1) ? RandomInt(48, 57) : RandomInt(97, 122);

	return str;
}

int cUtils::RandomInt(int a, int b)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(a, b); 
	return dist6(rng);
}

bool cUtils::RenameApp()
{
	char szExeFileName[MAX_PATH];
	GetModuleFileNameA(NULL, szExeFileName, MAX_PATH);
	std::string path = std::string(szExeFileName);
	std::string exe = path.substr(path.find_last_of("\\") + 1, path.size());
	std::string newname;
	newname = RandomString(RandomInt(5, 10));
	newname += xorstr_(".exe");
	if (!rename(exe.c_str(), newname.c_str()))
		return true;
	else return false;
}

cUtils* Utils = new cUtils();