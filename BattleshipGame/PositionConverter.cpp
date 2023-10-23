#include <iostream>
#include <string>
#include <array>

#include "PositionConverter.h"

bool positionValidator(const std::string& position)
{
	std::array<int, 10> numbers{ '0','1','2','3','4','5','6','7','8','9' };

	int converted = convertLetterToInt(std::toupper(position[0]));
	
	if (converted != -1 && std::find(numbers.begin(), numbers.end(), position[1]) !=
		numbers.end() && position.size() == 2) {
		return true;
	}
	else {
		return false;
	}
}

int convertLetterToInt(char letter)
{
	switch (letter) {
	case 'A':
		return 0;
		break;
	case 'B':
		return 1;
		break;
	case 'C':
		return 2;
		break;
	case 'D':
		return 3;
		break;
	case 'E':
		return 4;
		break;
	case 'F':
		return 5;
		break;
	case 'G':
		return 6;
		break;
	case 'H':
		return 7;
		break;
	case 'I':
		return 8;
		break;
	case 'J':
		return 9;
		break;
	default:
		return -1;
		break;
	}
}

std::array<int, 2> recievePositionValues(const std::string& position)
{
	int firstPos = convertLetterToInt(std::toupper(position[0]));
	int secondPos = static_cast<int>(position[1] - 48);

	std::array<int, 2> coordinates{ firstPos, secondPos };

	return coordinates;
}