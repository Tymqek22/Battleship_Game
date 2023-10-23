#include <iostream>

#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 10; ++i) {

		for (int j = 0; j < 10; ++j) {

			m_board[i][j] = '*';
		}
	}
}

char Board::getValue(int yPos, int xPos) const
{
	return m_board[yPos][xPos];
}

void Board::uploadPosition(int yPos, int xPos, char symbol)
{
	m_board[yPos][xPos] = symbol;
}

void Board::placeShip(Ship* ship)
{
	std::array<int, 2> position1 = ship->getFirstPos();
	std::array<int, 2> position2 = ship->getSecondPos();
	
	//arrays to store x and y positions from both positions separately to find min and max x and y

	std::array<int, 2> yPositions{ position1[0], position2[0] };
	std::array<int, 2> xPositions{ position1[1], position2[1] };

	constexpr int x = 1;
	constexpr int y = 0;

	if (ship->getOrientation() == 'V') {

		auto yMin = std::min_element(yPositions.begin(), yPositions.end());
		auto yMax = std::max_element(yPositions.begin(), yPositions.end());

		for (int i = *yMin; i <= *yMax; ++i) {

			m_board[i][position1[x]] = ship->getSymbol();
		}
	}
	else if (ship->getOrientation() == 'H') {

		auto xMin = std::min_element(xPositions.begin(), xPositions.end());
		auto xMax = std::max_element(xPositions.begin(), xPositions.end());

		for (int i = *xMin; i <= *xMax; ++i) {

			m_board[position1[y]][i] = ship->getSymbol();
		}
	}
}

void Board::drawBoard()
{
	std::cout << "  0 1 2 3 4 5 6 7 8 9\n";
	std::array<char, 10> letters{ 'A','B','C','D','E','F','G','H','I','J' };
	
	for (int i = 0; i < 10; ++i) {

		std::cout << letters[i] << ' ';

		for (int j = 0; j < 10; ++j) {
			
			if (j == 9) {
				std::cout << m_board[i][j] << '\n';
			}
			else {
				std::cout << m_board[i][j] << ' ';
			}
			
		}
	}
}