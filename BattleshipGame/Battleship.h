#pragma once

#include <iostream>

#include "Ship.h"

class Board;

class Battleship : public Ship
{
public:
	Battleship(Board* board);
};