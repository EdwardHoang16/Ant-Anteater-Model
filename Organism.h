/*
Edward Hoang
The question this code responds to is one asking for 30x30 grid of cells modeling the life, death, and reproduction of ants and anteaters.
Both ants and anteaters move, reproduce, and die. Anteaters can also eat ants, but can also starve to death. Ants die by being eaten.
Declares an abstract class representing an organism. The role of the Organism class is to contain variables and functions used by both
ants and anteaters.
*/

#pragma once

#include <vector>

class World;
class Organism {
private:
	const int NORTH = 1;
	const int EAST = 2;
	const int SOUTH = 3;
	const int WEST = 4;
	const int WORLD_ROWS = 30;
	const int WORLD_COLUMNS = 30;

	int rowPosition;
	int columnPosition;
	int direction;
	int timeToReproduce;

public:
	int getNorth() const;
	int getEast() const;
	int getSouth() const;
	int getWest() const;
	int getWorldRows() const;
	int getWorldColumns() const;

	int& getRowPosition();
	int& getColumnPosition();
	int& getDirection();
	int& getTimeToReproduce();

	void setRowPosition(int rowPosition);
	void setColumnPosition(int columnPosition);

	bool isNorthClear(std::vector<std::vector<char> >& worldVector);
	bool isEastClear(std::vector<std::vector<char> >& worldVector);
	bool isSouthClear(std::vector<std::vector<char> >& worldVector);
	bool isWestClear(std::vector<std::vector<char> >& worldVector);
	int chooseRandomDirection(std::vector<std::vector<char> >& worldVector);

	virtual void move(std::vector<std::vector<char> >& worldVector) = 0;
	virtual void reproduce(std::vector<std::vector<char> >& worldVector) = 0;
};