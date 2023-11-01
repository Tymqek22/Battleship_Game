#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <string>
#include <sstream>

#include "Ship.h"
#include "Board.h"
#include "PositionConverter.h"

Ship::Ship(const Coordinates& startPos, const Coordinates& endPos, int length,
	char orientation, char symbol, Board* boardOperator)
	: m_firstPos{ startPos }, m_secondPos{ endPos }, m_length{ length }, m_orientation{ orientation },
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

void Ship::setOnePosition(Coordinates& coords)
{
	std::string position;

	do {
		std::cin >> position;

		if (!positionValidator(position)) {
			std::cout << "Invalid position entered.\n";
		}
		else {

			coords.yPosition = convertLetterToInt(std::toupper(position[0]));
			coords.xPosition = static_cast<int>(position[1] - 48);
		}
	} while (!positionValidator(position));
}

void Ship::setBothPositions()
{
	constexpr int x = 1;
	constexpr int y = 0;

	do {
		std::cout << "Enter first position: ";
		this->setOnePosition(m_firstPos);
		std::cout << "Enter second position: ";
		do {
			this->setOnePosition(m_secondPos);

			if (!this->checkLengthAndOrientation(m_firstPos, m_secondPos))
				std::cout << "Wrong position assigned.\n";

		} while (!this->checkLengthAndOrientation(m_firstPos, m_secondPos));

		if (!this->validatePosition(m_firstPos, m_secondPos))
			std::cout << "You can't place a ship in this position.\n";

	} while (!this->validatePosition(m_firstPos, m_secondPos));
	
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

	std::array<char, 10> letters{ 'A','B','C','D','E','F','G','H','I','J' };
	std::array<int, 10> numbers{ 0,1,2,3,4,5,6,7,8,9 };

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution range{ 0,9 };

	do {
		if (m_orientation == 'H') {
			//setting first position
			m_firstPos.yPosition = convertLetterToInt(letters[range(mt)]);
			m_firstPos.xPosition = numbers[range(mt)];

			//setting second position
			m_secondPos.yPosition = m_firstPos.yPosition;
			int secondXPos = m_firstPos.xPosition;
			secondXPos += m_length - 1;

			if (secondXPos > 9) {

				secondXPos = m_firstPos.xPosition;
				secondXPos -= m_length - 1;
			}

			m_secondPos.xPosition = secondXPos;
		}
		else if (m_orientation == 'V') {
			//first
			m_firstPos.yPosition = convertLetterToInt(letters[range(mt)]);
			m_firstPos.xPosition = numbers[range(mt)];

			//second
			m_secondPos.xPosition = m_firstPos.xPosition;
			int secondYPos = m_firstPos.yPosition;
			secondYPos += m_length - 1;

			if (secondYPos > 9) {
				secondYPos = m_firstPos.yPosition;
				secondYPos -= m_length - 1;
			}

			m_secondPos.yPosition = secondYPos;
		}
	} while (!this->validatePosition(m_firstPos, m_secondPos));
}

bool Ship::checkLengthAndOrientation(const Coordinates& coords1, const Coordinates& coords2)
{
	if (m_orientation == 'H') {

		std::array<int, 2> values{ coords1.xPosition, coords2.xPosition };

		auto max = std::max_element(values.begin(), values.end());
		auto min = std::min_element(values.begin(), values.end());

		//checking proper length and equality of the orientation indexes
		if ((*max - *min == m_length - 1) && (coords1.yPosition == coords2.yPosition)) {
			return true;
		}
	}
	else if (m_orientation == 'V') {

		std::array<int, 2> values{ coords1.yPosition, coords2.yPosition };

		auto max = std::max_element(values.begin(), values.end());
		auto min = std::min_element(values.begin(), values.end());

		if ((*max - *min == m_length - 1) && (coords1.xPosition == coords2.xPosition)) {
			return true;
		}
	}

	return false;
}

bool Ship::validatePosition(const Coordinates& coords1, const Coordinates& coords2)
{
	constexpr int x = 1;
	constexpr int y = 0;
	std::array<int, 2> yPositions{ coords1.yPosition, coords2.yPosition };
	std::array<int, 2> xPositions{ coords1.xPosition, coords2.xPosition };


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
				for (int j = coords1.xPosition - 1; j <= coords1.xPosition + 1; ++j) {

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

		for (int i = coords1.yPosition - 1; i <= coords1.yPosition + 1; ++i) {

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