#pragma once

#include "Board.h"

class Player
{
protected:
	int m_totalLives;
	Board m_playerBoard;
	Board m_hitBoard;
public:
	Player();

	int getLivesCount() const { return m_totalLives; }
	char getBoardValue(int yPos, int xPos) const { return m_playerBoard.getValue(yPos, xPos); }

	void showPlayersHitBoard();
	void decreaseLivesNo();
	void hit(Player* opponent);
	void placeShipsFleet();
};