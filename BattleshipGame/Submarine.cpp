#include <iostream>

#include "Board.h"
#include "Submarine.h"

Submarine::Submarine(Board* board) : Ship({0,0}, {0,0}, 3, '0', 'S', board) {}