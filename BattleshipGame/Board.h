#pragma once

#include "Ship.h"

class Board
{
private:
	char m_board[10][10];

public:
	Board();

	char getValue(int yPos, int xPos) const;

	void uploadPosition(int yPos, int xPos, char symbol);
	void placeShip(Ship* ship);
	void drawBoard();
};
