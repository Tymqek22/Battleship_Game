#pragma once

#include <iostream>
#include <utility>
#include <vector>

#include "Player.h"

struct Coordinates
{
	int m_yPosition;
	int m_xPosition;
};

class Computer : public Player
{
private:
	std::vector<std::pair<Coordinates, char>> m_hitBox;

public:
	Computer();

	bool ableToPlace(const Coordinates& coords);
	bool validateCoordinates(const Coordinates& coords);
	void placeShipsFleet();
	std::vector<Coordinates> createClosePositions(const Coordinates& baseCoords, Player* opponent);
	void hit(Player* opponent);
};