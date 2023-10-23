#pragma once

#include <iostream>

#include "Ship.h"

class Board;

class Submarine : public Ship
{
public:
	Submarine(Board* board);
};