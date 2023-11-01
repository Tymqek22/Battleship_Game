#pragma once

#include <iostream>
#include <utility>
#include <vector>

#include "Player.h"

struct Coordinates;

class Computer : public Player
{
private:
	std::vector<std::pair<Coordinates, char>> m_hitBox;

public:
	Computer();

	bool validateCoordinates(const Coordinates& coords);
	void placeShipsFleet();
	std::vector<Coordinates> createClosePositions(const Coordinates& baseCoords, Player* opponent);
	void hit(Player* opponent);
};