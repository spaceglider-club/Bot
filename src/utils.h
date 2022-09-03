#ifndef SPACEGLIDER_SRC_UTILS_H_
#define SPACEGLIDER_SRC_UTILS_H_

#pragma once

#include <string>



class cUtils
{
public:
	std::string RandomString(int size);
	int RandomInt(int a, int b);
	bool RenameApp();
	std::string wtos(std::wstring wstr);
	std::wstring stow(std::string str);
	bool IsLeagueForeGround();
	bool IsScriptForeGround();
	bool IsLeagueOpen();
	bool HasGameStarted();


};

extern cUtils* Utils;

#endif