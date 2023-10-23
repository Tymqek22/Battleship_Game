#pragma once

#include <iostream>
#include <array>

bool positionValidator(const std::string& position);
int convertLetterToInt(char letter);
std::array<int, 2> recievePositionValues(const std::string& position);