#pragma once

#include <iostream>
#include <array>

class Board;

struct Coordinates 
{
	int yPosition;
	int xPosition;
};

class Ship
{
protected:
	Coordinates m_firstPos;
	Coordinates m_secondPos;
	int m_length;
	char m_orientation;
	char m_symbol;
	Board* m_boardOperations;

public:
	//setters
	Ship(const Coordinates& startPos = { 0,0 }, const Coordinates& endPos = { 0,0 }, int length = 0,
		char orientation = '0', char symbol = '0', Board* boardOperator = nullptr);
	void setOrientation();
	void setOnePosition(Coordinates& coords);
	void setBothPositions();

	//computer methods
	void setOrientationComp();
	void setPositionsComp();

	//checking methods
	bool checkLengthAndOrientation(const Coordinates& coords1, const Coordinates& coords2);
	bool validatePosition(const Coordinates& coords1, const Coordinates& coords2);

	//getters
	Coordinates getFirstPos() const { return m_firstPos; }
	Coordinates getSecondPos() const { return m_secondPos; }
	int getLength() const { return m_length; }
	char getOrientation() const { return m_orientation; }
	char getSymbol() const { return m_symbol; }
};