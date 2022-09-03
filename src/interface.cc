// this file has function definitions for interface.h

#include "interface.h"

#include <windows.h>
#include <tlhelp32.h>
#include <comdef.h>
#include <xorstr.hpp>

void cInterface::Setup()
{
	this->GetProcessId();
	this->OpenProcessHandle();
	this->GetProcessAddress();
}

void cInterface::GetProcessId()
{
	PROCESSENTRY32 entry;
	entry.dwSize = sizeof(PROCESSENTRY32);

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

	if (Process32First(snapshot, &entry) == TRUE)
	{
		while (Process32Next(snapshot, &entry) == TRUE)
		{
			if (_stricmp(_bstr_t(entry.szExeFile), xorstr_("League of Legends.exe")) == 0)
			{
				this->process_id = entry.th32ProcessID;
			}

		}
	}
	CloseHandle(snapshot);
}

void cInterface::OpenProcessHandle()
{
	this->process_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_READ | PROCESS_ALL_ACCESS, FALSE, this->process_id);
}

void cInterface::GetProcessAddress()
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, this->process_id);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				this->process_address = (uintptr_t)modEntry.modBaseAddr;
				break;

			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
}

std::string cInterface::ReadCharPointer(PTR read_address)
{
	char buffer[256];
	ReadProcessMemory(this->process_handle, (PVOID)this->ReadMemory<PTR>(read_address), &buffer, 256, 0);
#pragma warning( push )
#pragma warning( disable : 6054 )
	return buffer;
#pragma warning ( pop )
}

std::string cInterface::ReadCharArray(PTR read_address)
{
	char buffer[256];
	ZeroMemory(buffer, 256);
	ReadProcessMemory(this->process_handle, (PVOID)read_address, &buffer, 256, 0);
#pragma warning( push )
#pragma warning( disable : 6054 )
	return buffer;
#pragma warning ( pop )
}

cInterface * Interface = new cInterface();