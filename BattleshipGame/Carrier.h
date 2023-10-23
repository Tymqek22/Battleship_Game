#pragma once

#include <iostream>
#include <array>

#include "Ship.h"

class Board;

class Carrier : public Ship
{
public:
	Carrier(Board* board);
};