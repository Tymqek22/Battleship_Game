#include <iostream>
#include <random>
#include <string>
#include <algorithm>

#include "Computer.h"
#include "Carrier.h"
#include "Battleship.h"
#include "Crusier.h"
#include "Submarine.h"
#include "Destroyer.h"
#include "PositionConverter.h"

Computer::Computer() : Player(), m_hitBox{} {}

bool Computer::ableToPlace(const Coordinates& coords)
{
	if (m_hitBoard.getValue(coords.m_yPosition, coords.m_xPosition) == '*') {
		return true;
	}
	else {
		return false;
	}
}

bool Computer::validateCoordinates(const Coordinates& coords)
{
	if ((coords.m_yPosition < 0 || coords.m_yPosition > 9) || (coords.m_xPosition < 0 || coords.m_xPosition > 9)) {

		return false;
	}
	else {
		return true;
	}
}

void Computer::placeShipsFleet()
{
	Carrier carrier(&m_playerBoard);
	carrier.setOrientationComp();
	carrier.setPositionsComp();
	m_playerBoard.placeShip(&carrier);
	
	Battleship battleship(&m_playerBoard);
	battleship.setOrientationComp();
	battleship.setPositionsComp();
	m_playerBoard.placeShip(&battleship);

	Crusier crusier(&m_playerBoard);
	crusier.setOrientationComp();
	crusier.setPositionsComp();
	m_playerBoard.placeShip(&crusier);

	Submarine submarine(&m_playerBoard);
	submarine.setOrientationComp();
	submarine.setPositionsComp();
	m_playerBoard.placeShip(&submarine);

	Destroyer destroyer(&m_playerBoard);
	destroyer.setOrientationComp();
	destroyer.setPositionsComp();
	m_playerBoard.placeShip(&destroyer);

	m_playerBoard.drawBoard();
}

std::vector<Coordinates> Computer::createClosePositions(const Coordinates& baseCoords, Player* opponent)
{
	//vector to store coordinates, which meet specific criterias (correct index values, free space to fill the position 
	// and position holding the ship's part)
	std::vector<Coordinates> positions;
	positions.reserve(2);

	//creating coordinates, which surround the base coordinates and checking the criterias
	Coordinates upCoords;
	upCoords.m_yPosition = baseCoords.m_yPosition - 1;
	upCoords.m_xPosition = baseCoords.m_xPosition;
	if (this->validateCoordinates(upCoords) && this->ableToPlace(upCoords) &&
		opponent->getBoardValue(upCoords.m_yPosition, upCoords.m_xPosition) != '*') {
		positions.push_back(upCoords);
	}
	Coordinates rightCoords;
	rightCoords.m_yPosition = baseCoords.m_yPosition;
	rightCoords.m_xPosition = baseCoords.m_xPosition + 1;
	if (this->validateCoordinates(rightCoords) && this->ableToPlace(rightCoords) &&
		opponent->getBoardValue(rightCoords.m_yPosition, rightCoords.m_xPosition) != '*') {
		positions.push_back(rightCoords);
	}
	Coordinates downCoords;
	downCoords.m_yPosition = baseCoords.m_yPosition + 1;
	downCoords.m_xPosition = baseCoords.m_xPosition;
	if (this->validateCoordinates(downCoords) && this->ableToPlace(downCoords) && 
		opponent->getBoardValue(downCoords.m_yPosition, downCoords.m_xPosition) != '*') {
		positions.push_back(downCoords);
	}
	Coordinates leftCoords;
	leftCoords.m_yPosition = baseCoords.m_yPosition;
	leftCoords.m_xPosition = baseCoords.m_xPosition - 1;
	if (this->validateCoordinates(leftCoords) && this->ableToPlace(leftCoords) && 
		opponent->getBoardValue(leftCoords.m_yPosition, leftCoords.m_xPosition) != '*') {
		positions.push_back(leftCoords);
	}

	return positions;
}

void Computer::hit(Player* opponent)
{
	constexpr int y = 0;
	constexpr int x = 1;
	Coordinates chosenCoords;
	
	if ((!m_hitBox.empty()) && m_hitBox.back().second == 'X') {

		std::vector<Coordinates> positions;
		positions.reserve(2);
		
		if (m_hitBox.back().second == 'X') {

			Coordinates baseCoords = m_hitBox.back().first;
			positions = createClosePositions(baseCoords, opponent);
		}
		
		//if none of the positions was valid choose the random coordinates
		if (positions.empty()) {
			goto m;
		}

		//choosing the random position from the vector of valid coordinates
		int positionsSize = static_cast<int>(positions.size() - 1);
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution range{ 0, positionsSize };

		do {
			chosenCoords = positions[range(mt)];

		} while (m_hitBoard.getValue(chosenCoords.m_yPosition, chosenCoords.m_xPosition) != '*');

	}
	else {
		m:
		std::array<int, 10> numbers{ 0,1,2,3,4,5,6,7,8,9 };

		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution range{ 0,9 };

		do {
			chosenCoords.m_yPosition = numbers[range(mt)];
			chosenCoords.m_xPosition = numbers[range(mt)];

		} while (m_hitBoard.getValue(chosenCoords.m_yPosition, chosenCoords.m_xPosition) != '*');
	}

	//check what is located on a guessed position on the opponent's board
	char positionValue = opponent->getBoardValue(chosenCoords.m_yPosition, chosenCoords.m_xPosition);

	if (positionValue != '*') {
		opponent->decreaseLivesNo();
		m_hitBoard.uploadPosition(chosenCoords.m_yPosition, chosenCoords.m_xPosition, 'X');
		m_hitBox.push_back(std::pair<Coordinates, char>(chosenCoords, 'X'));
	}
	else {
		m_hitBoard.uploadPosition(chosenCoords.m_yPosition, chosenCoords.m_xPosition, 'O');
		m_hitBox.push_back(std::pair<Coordinates, char>(chosenCoords, 'O'));
	}
}