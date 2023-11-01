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

bool Computer::validateCoordinates(const Coordinates& coords)
{
	if ((coords.yPosition < 0 || coords.yPosition > 9) || (coords.xPosition < 0 || coords.xPosition > 9)) {

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
	// and position holding the ship's segment.
	std::vector<Coordinates> positions;
	positions.reserve(2);

	//creating coordinates, which surround the base coordinates and checking the criterias
	Coordinates upCoords;
	upCoords.yPosition = baseCoords.yPosition - 1;
	upCoords.xPosition = baseCoords.xPosition;
	if (this->validateCoordinates(upCoords) && this->ableToPlace(upCoords) &&
		opponent->getBoardValue(upCoords.yPosition, upCoords.xPosition) != '*') {
		positions.push_back(upCoords);
	}
	Coordinates rightCoords;
	rightCoords.yPosition = baseCoords.yPosition;
	rightCoords.xPosition = baseCoords.xPosition + 1;
	if (this->validateCoordinates(rightCoords) && this->ableToPlace(rightCoords) &&
		opponent->getBoardValue(rightCoords.yPosition, rightCoords.xPosition) != '*') {
		positions.push_back(rightCoords);
	}
	Coordinates downCoords;
	downCoords.yPosition = baseCoords.yPosition + 1;
	downCoords.xPosition = baseCoords.xPosition;
	if (this->validateCoordinates(downCoords) && this->ableToPlace(downCoords) && 
		opponent->getBoardValue(downCoords.yPosition, downCoords.xPosition) != '*') {
		positions.push_back(downCoords);
	}
	Coordinates leftCoords;
	leftCoords.yPosition = baseCoords.yPosition;
	leftCoords.xPosition = baseCoords.xPosition - 1;
	if (this->validateCoordinates(leftCoords) && this->ableToPlace(leftCoords) && 
		opponent->getBoardValue(leftCoords.yPosition, leftCoords.xPosition) != '*') {
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
		
		//if none of the positions are valid choose the random coordinates
		if (positions.empty()) {
			goto m;
		}

		//choosing the random position from the vector of valid coordinates
		int positionsSize = static_cast<int>(positions.size() - 1);
		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution range{ 0, positionsSize };

		do {
			chosenCoords = positions[range(mt)];

		} while (m_hitBoard.getValue(chosenCoords.yPosition, chosenCoords.xPosition) != '*');

	}
	else {
		m:
		std::array<int, 10> numbers{ 0,1,2,3,4,5,6,7,8,9 };

		std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution range{ 0,9 };

		do {
			chosenCoords.yPosition = numbers[range(mt)];
			chosenCoords.xPosition = numbers[range(mt)];

		} while (m_hitBoard.getValue(chosenCoords.yPosition, chosenCoords.xPosition) != '*');
	}

	//check what is located on a guessed position on the opponent's board
	char positionValue = opponent->getBoardValue(chosenCoords.yPosition, chosenCoords.xPosition);

	if (positionValue != '*') {
		opponent->decreaseLivesNo();
		m_hitBoard.uploadPosition(chosenCoords.yPosition, chosenCoords.xPosition, 'X');
		opponent->signHitShipsSegment(chosenCoords.yPosition, chosenCoords.xPosition);
		m_hitBox.push_back(std::pair<Coordinates, char>(chosenCoords, 'X'));
	}
	else {
		m_hitBoard.uploadPosition(chosenCoords.yPosition, chosenCoords.xPosition, 'O');
		m_hitBox.push_back(std::pair<Coordinates, char>(chosenCoords, 'O'));
	}
}