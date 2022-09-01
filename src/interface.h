#ifndef SPACEGLIDER_SRC_INTERFACE_H_
#define SPACEGLIDER_SRC_INTERFACE_H_

#pragma once

#include "macro.h"

#include <windows.h>
#include <string>

class cInterface
{
public:
	template <class T>
	__inline T ReadMemory(PTR read_address) noexcept
	{
		T buffer;
		ReadProcessMemory(this->process_handle, (PVOID)read_address, &buffer, sizeof(buffer), NULL);
		return buffer;
	}

	template <class T>
	__inline void WriteMemory(PTR write_address, T value_to_write) noexcept
	{
		WriteProcessMemory(this->process_handle, (PVOID)write_address, value_to_write, sizeof(value_to_write), NULL);
	}

	std::string ReadCharPointer(PTR read_address);
	std::string ReadCharArray(PTR read_address);

	void GetProcessId();
	void OpenProcessHandle();
	void GetProcessAddress();

	void Setup();

	HANDLE	process_handle = {0};
	INT		process_id = {0};
	INT		process_address = {0};
};
extern cInterface * Interface;




#endif