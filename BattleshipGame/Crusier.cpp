#include <iostream>

#include "Board.h"
#include "Crusier.h"

Crusier::Crusier(Board* board) : Ship({ 0,0 }, { 0,0 }, 3, '0', 'c', board) {}