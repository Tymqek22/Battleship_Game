#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <string>
#include <sstream>

#include "Ship.h"
#include "Board.h"
#include "PositionConverter.h"

struct Coordinates
{
	int m_yPosition;
	int m_xPosition;
};

Ship::Ship(const std::array<int, 2>& startPos, const std::array<int, 2>& endPos, int length,
	char orientation, char symbol, Board* boardOperator)
	: m_startPos{ startPos }, m_endPos{ endPos }, m_length{ length }, m_orientation{ orientation },
	m_symbol{ symbol }, m_boardOperations{ boardOperator } {}

void Ship::setOrientation()
{
	char orientation;
	std::cout << "Enter the orientation: ";

	do {
		std::cin >> orientation;

		orientation = std::toupper(orientation);

	} while ((orientation != 'H') && (orientation != 'V'));

	m_orientation = orientation;
}

void Ship::setOnePosition(std::array<int, 2>& coordinates)
{
	std::string position;

	do {
		std::cin >> position;

		if (!positionValidator(position)) {
			std::cout << "Wrong position assigned.\n";
		}
		else {
			coordinates = recievePositionValues(position);
		}
	} while (!positionValidator(position));
}

void Ship::setBothPositions()
{
	constexpr int x = 1;
	constexpr int y = 0;

	do {
		if (m_orientation == 'H') {

			std::cout << "Enter first position: ";
			this->setOnePosition(m_startPos);
			std::cout << "Enter second position: ";
			do {
				this->setOnePosition(m_endPos);
			} while (!(this->checkLength(m_startPos[x], m_endPos[x])) || !(m_startPos[y] == m_endPos[y]));
		}
		else if (m_orientation == 'V') {

			std::cout << "Enter first position: ";
			this->setOnePosition(m_startPos);
			std::cout << "Enter second position: ";
			do {
				this->setOnePosition(m_endPos);
			} while (!(this->checkLength(m_startPos[y], m_endPos[y])) || !(m_startPos[x] == m_endPos[x]));
		}
	} while (!(this->validatePosition(m_startPos, m_endPos)));
}

//computer methods
void Ship::setOrientationComp()
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution range{ 0,1 };

	std::array<int, 2> orientations{ 'H','V' };

	m_orientation = orientations[range(mt)];
}

void Ship::setPositionsComp()
{
	constexpr int y = 0;
	constexpr int x = 1;

	std::array<std::string, 10> letters{ "A","B","C","D","E","F","G","H","I","J" };
	std::array<int, 10> numbers{ 0,1,2,3,4,5,6,7,8,9 };

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution range{ 0,9 };

	do {
		if (m_orientation == 'H') {
			//setting first position
			std::string position1 = letters[range(mt)] + std::to_string(numbers[range(mt)]);
			std::array<int, 2> firstPos = recievePositionValues(position1);
			m_startPos = firstPos;

			//setting second position
			int secondX = firstPos[x];
			secondX += m_length - 1;

			if (secondX > 9) {

				secondX = firstPos[x];
				secondX -= m_length - 1;
			}

			std::stringstream ss;
			ss << position1[y] << secondX;

			std::array<int, 2> secondPos = recievePositionValues(ss.str());
			m_endPos = secondPos;
		}
		else if (m_orientation == 'V') {
			//first
			std::string position1 = letters[range(mt)] + std::to_string(numbers[range(mt)]);
			std::array<int, 2> firstPos = recievePositionValues(position1);
			m_startPos = firstPos;

			//second
			int secondY = firstPos[y];
			secondY += m_length - 1;

			if (secondY > 9) {
				secondY = firstPos[y];
				secondY -= m_length - 1;
			}

			std::stringstream ss;
			ss << letters[secondY] << position1[x];
			//std::string position2 = std::to_string(secondY) + std::to_string(position1[x]);
			std::array<int, 2> secondPos = recievePositionValues(ss.str());
			m_endPos = secondPos;
		}
	} while (!this->validatePosition(m_startPos, m_endPos));
}

bool Ship::checkLength(int firstPos, int secondPos)
{
	std::array<int, 2> values{ firstPos, secondPos };

	auto max = std::max_element(values.begin(), values.end());
	auto min = std::min_element(values.begin(), values.end());

	if (*max - *min == m_length - 1) {
		return true;
	}
	else {
		return false;
	}
}

bool Ship::validatePosition(const std::array<int, 2>& firstPos, const std::array<int, 2>& secondPos)
{
	constexpr int x = 1;
	constexpr int y = 0;
	std::array<int, 2> yPositions{ firstPos[0], secondPos[0] };
	std::array<int, 2> xPositions{ firstPos[1], secondPos[1] };


	if (m_orientation == 'V') {

		auto yMin = std::min_element(yPositions.begin(), yPositions.end());
		auto yMax = std::max_element(yPositions.begin(), yPositions.end());

		//iterating through all the 2d indexes which surround the ship including with those where the ship
		//is located

		for (int i = *yMin - 1; i <= *yMax + 1; ++i) {

			//checking the correct 2d array index to prevent accessing the index which is not a part of
			//an array

			if (i < 0 || i > 9) {
				continue;
			}
			else {
				for (int j = firstPos[x] - 1; j <= firstPos[x] + 1; ++j) {

					if (j < 0 || j > 9) {
						continue;
					}
					else {

						if (m_boardOperations->getValue(i, j) != '*') {
							return false;
						}
					}
				}
			}
		}
	}
	else if (m_orientation == 'H') {

		auto xMin = std::min_element(xPositions.begin(), xPositions.end());
		auto xMax = std::max_element(xPositions.begin(), xPositions.end());

		for (int i = firstPos[y] - 1; i <= firstPos[y] + 1; ++i) {

			if (i < 0 || i > 9) {
				continue;
			}
			else {
				for (int j = *xMin - 1; j <= *xMax + 1; ++j) {

					if (j < 0 || j > 9) {
						continue;
					}
					else {
						
						if (m_boardOperations->getValue(i, j) != '*') {
							return false;
						}
					}
				}
			}
		}
	}
	return true;
}