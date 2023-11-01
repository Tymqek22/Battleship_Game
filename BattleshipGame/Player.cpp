#include <iostream>
#include <array>

#include "Player.h"
#include "Carrier.h"
#include "Battleship.h"
#include "Crusier.h"
#include "Submarine.h"
#include "Destroyer.h"
#include "PositionConverter.h"

Player::Player() : m_totalLives{ 17 }, m_playerBoard{ Board() }, m_hitBoard{Board()} {}

bool Player::ableToPlace(const Coordinates& coords)
{
	if (m_hitBoard.getValue(coords.yPosition, coords.xPosition) == '*') {
		return true;
	}
	else {
		return false;
	}
}

void Player::showPlayersHitBoard()
{
	m_hitBoard.drawBoard();
}

void Player::showPlayersBoard()
{
	m_playerBoard.drawBoard();
}

void Player::decreaseLivesNo()
{
	m_totalLives--;
}

void Player::hit(Player* opponent)
{
	constexpr int y = 0;
	constexpr int x = 1;

	Coordinates finalCoords = { 0,0 };
	std::string rawPosition;

	std::cout << "Enter the position to hit: ";
	do {
		std::cin >> rawPosition;

		if (positionValidator(rawPosition)) {

			finalCoords.yPosition = convertLetterToInt(std::toupper(rawPosition[y]));
			finalCoords.xPosition = static_cast<int>(rawPosition[x] - 48);
		}
		else {
			std::cout << "Wrong position entered!\n";
		}

		if (!this->ableToPlace(finalCoords)) {
			std::cout << "This position is occupied.\n";
		}

	} while (!positionValidator(rawPosition) || !this->ableToPlace(finalCoords));

	if (opponent->getBoardValue(finalCoords.yPosition, finalCoords.xPosition) != '*') {
		m_hitBoard.uploadPosition(finalCoords.yPosition, finalCoords.xPosition, 'X');
		opponent->decreaseLivesNo();
	}
	else {
		m_hitBoard.uploadPosition(finalCoords.yPosition, finalCoords.xPosition, 'O');
	}
}

void Player::placeShipsFleet()
{
	m_playerBoard.drawBoard();

	std::cout << "Place carrier in 5 holes.\n";
	Carrier carrier(&m_playerBoard);
	carrier.setOrientation();
	carrier.setBothPositions();
	m_playerBoard.placeShip(&carrier);
	system("cls");
	m_playerBoard.drawBoard();

	std::cout << "Place battleship in 4 holes.\n";
	Battleship battleship(&m_playerBoard);
	battleship.setOrientation();
	battleship.setBothPositions();
	m_playerBoard.placeShip(&battleship);
	system("cls");
	m_playerBoard.drawBoard();

	std::cout << "Place crusier in 3 holes.\n";
	Crusier crusier(&m_playerBoard);
	crusier.setOrientation();
	crusier.setBothPositions();
	m_playerBoard.placeShip(&crusier);
	system("cls");
	m_playerBoard.drawBoard();

	std::cout << "Place submarine in 3 holes.\n";
	Submarine submarine(&m_playerBoard);
	submarine.setOrientation();
	submarine.setBothPositions();
	m_playerBoard.placeShip(&submarine);
	system("cls");
	m_playerBoard.drawBoard();

	std::cout << "Place destroyer in 2 holes.\n";
	Destroyer destroyer(&m_playerBoard);
	destroyer.setOrientation();
	destroyer.setBothPositions();
	m_playerBoard.placeShip(&destroyer);
	system("cls");
	m_playerBoard.drawBoard();
}

void Player::signHitShipsSegment(int yPos, int xPos)
{
	m_playerBoard.uploadPosition(yPos, xPos, '#');
}