// this file has function definitions for cobject.h

#include "cobject.h"
#include "interface.h"
#include "macro.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// search through memory blocks until found the pointer combination (takes about 2-10 seconds depending on PC)
void cCObject::GetPingOffset()
{
	for (int i = 0x0; i < 0xBFFFFFF; i += 0x4000)
	{
		// init static buffer, else compiler complains
		static PTR buffer[0x4000];
		
		// set buffer to null
		ZeroMemory(buffer, sizeof(buffer));

		// read next 0x4000 addresses from i
		ReadProcessMemory(Interface->process_handle, (PVOID)i, &buffer, sizeof(buffer), NULL);

		for (int j = 0; j < 0x4000; j++)
		{
			// check if address ends with DB0 and the one after it with DC4
			if (static_cast<int>(buffer[j] & 0x0fff) == 3504 && static_cast<int>(buffer[j + 1] & 0x0fff) == 3524)
			{
				// if it does we got the ping offset (ofc - 0x24 cuz dats where i was first found)
				this->kPingOffset = (i + (j * 4)) - 0x24;
				return;
			}
		}
	}
}

// search through memory blocks until found the pointer combination (takes about 2-10 seconds depending on PC)
void cCObject::GetAttackSpeedOffset()
{
    for (int i = 0x00000000; i < 0xFFFFFFFF; i += 0x4000)
    {
        static PTR buffer[16384];
		ZeroMemory(buffer, 0x4000);
        ReadProcessMemory(Interface->process_handle, (PVOID)i, &buffer, 16384, 0);

        for (int j = 0; j < 0x4000; j++)
        {
            if (static_cast<int>(buffer[j] & 0x0ff) == 186)
            {
				if (strcmp(Interface->ReadCharPointer((i + ((j - 3) * 4))).c_str(), "game_DynamicMenuText_[Attributes]_AttackSpeedWithRatio") == 0)
				{
					if (strcmp(Interface->ReadCharPointer((i + ((j + 62) * 4))).c_str(), "game_DynamicMenuText_[Attributes]_LifeSteal") == 0)
					{
						this->kAttackSpeedOffset = (i + (j * 4)) - 0x14;
						return;
					}
				}
            }
        }
    }
}

cCObject* CObject = new cCObject();