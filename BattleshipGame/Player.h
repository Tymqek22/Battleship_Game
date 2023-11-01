#pragma once

#include "Board.h"

struct Coordinates;

class Player
{
protected:
	int m_totalLives;
	Board m_playerBoard;
	Board m_hitBoard;
public:
	Player();

	bool ableToPlace(const Coordinates& coords);
	int getLivesCount() const { return m_totalLives; }
	char getBoardValue(int yPos, int xPos) const { return m_playerBoard.getValue(yPos, xPos); }

	void showPlayersHitBoard();
	void showPlayersBoard();
	void decreaseLivesNo();
	void hit(Player* opponent);
	void placeShipsFleet();
	void signHitShipsSegment(int yPos, int xPos);
};