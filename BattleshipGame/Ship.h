#pragma once

#include <iostream>
#include <array>

class Board;

class Ship
{
protected:
	//array of two elements to store two indexes, first element stores y arguments and second x arguments
	std::array<int, 2> m_startPos;
	std::array<int, 2> m_endPos;
	int m_length;
	char m_orientation;
	char m_symbol;
	Board* m_boardOperations;

public:
	//setters
	Ship(const std::array<int, 2>& startPos = {0,0}, const std::array<int, 2>& endPos = {0,0}, int length = 0,
		char orientation = '0', char symbol = '0', Board* boardOperator = nullptr);
	void setOrientation();
	void setOnePosition(std::array<int, 2>& coordinates);
	void setBothPositions();

	//computer methods
	void setOrientationComp();
	void setPositionsComp();

	//checking methods
	bool checkLength(int firstPos, int secondPos);
	bool validatePosition(const std::array<int, 2>& firstPos, const std::array<int, 2>& secondPos);

	//getters
	std::array<int, 2> getFirstPos() const { return m_startPos; }
	std::array<int, 2> getSecondPos() const { return m_endPos; }
	int getLength() const { return m_length; }
	char getOrientation() const { return m_orientation; }
	char getSymbol() const { return m_symbol; }
};