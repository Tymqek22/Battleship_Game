#include <iostream>

#include "Board.h"
#include "Destroyer.h"

Destroyer::Destroyer(Board* board) : Ship({0,0}, {0,0}, 2, '0', 'D', board) {}