// Using the Google C++ Style Guide
// https://google.github.io/styleguide/cppguide.html
// Start Date: 30.08.2022 (5:11 am)
// Author: souljah#7777 @ spaceglider.club

#include "interface.h"
#include "offsets.h"
#include "vector.h"
#include "cobject.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string_view>

int __cdecl main(void*)
{
	Interface->Setup();
	std::cout << CObject->GetChampionName(CObject->GetLocalPlayer());
}