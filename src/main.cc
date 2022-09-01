// Using the Google C++ Style Guide
// https://google.github.io/styleguide/cppguide.html
// Start Date: 30.08.2022 (5:11 am)
// Author: souljah#7777 @ spaceglider.club
// Sharing, modification of this source code is strictly forbidden unless given permission by the Author.

#include "interface.h"
#include "offsets.h"
#include "vector.h"
#include "cobject.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string_view>

int __cdecl main(void*)
{
	Interface->Setup();

	CObject->GetAttackSpeedOffset();
	printf("0x%x\n", CObject->kAttackSpeedOffset);
}