#pragma once

#include <iostream>

#include "Ship.h"

class Board;

class Crusier : public Ship
{
public:
	Crusier(Board* board);
};