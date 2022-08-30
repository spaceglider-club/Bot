#ifndef SPACEGLIDER_SRC_INTERFACE_H_
#define SPACEGLIDER_SRC_INTERFACE_H_

#pragma once

#include "macro.h"

#include <windows.h>

class Interface
{
public:
	template <class T>
	__inline T ReadMemory(PTR read_address) noexcept
	{
		T buffer;
		ReadProcessMemory(NULL, (PVOID)read_address, &buffer, sizeof(buffer), NULL);
		return buffer;
	}

	template <class T>
	__inline void WriteMemory(PTR write_address, T value_to_write) noexcept
	{
		WriteProcessMemory(NULL, (PVOID)write_address, value_to_write, sizeof(value_to_write), NULL);
	}

	void GetProcessId();
	void OpenProcessHandle();
	void GetProcessAddress();

	void Setup();

	HANDLE	process_handle = {0};
	INT		process_id = {0};
	INT		process_address = {0};


};




#endif