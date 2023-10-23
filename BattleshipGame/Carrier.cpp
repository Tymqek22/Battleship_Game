#include <iostream>

#include "Carrier.h"
#include "PositionConverter.h"

Carrier::Carrier(Board* board) : Ship({0,0}, {0,0}, 5, '0', 'C', board) {}
