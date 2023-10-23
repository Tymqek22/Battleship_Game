#include <iostream>

#include "Battleship.h"
#include "Board.h"

Battleship::Battleship(Board* board) : Ship({0,0}, {0,0}, 4, '0', 'B', board) {}