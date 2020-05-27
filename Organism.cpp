/*
Edward Hoang
The question this code responds to is one asking for 30x30 grid of cells modeling the life, death, and reproduction of ants and anteaters.
Both ants and anteaters move, reproduce, and die. Anteaters can also eat ants, but can also starve to death. Ants die by being eaten.
Defines a class representing an organism.
*/

#include "Organism.h"
#include "World.h"

using namespace std;

int Organism::getNorth() const {
	return NORTH;
}

int Organism::getEast() const {
	return EAST;
}

int Organism::getSouth() const {
	return SOUTH;
}

int Organism::getWest() const {
	return WEST;
}

int Organism::getWorldRows() const {
	return WORLD_ROWS;
}

int Organism::getWorldColumns() const {
	return WORLD_COLUMNS;
}

int& Organism::getRowPosition() {
	return rowPosition;
}

int& Organism::getColumnPosition() {
	return columnPosition;
}

int& Organism::getDirection() {
	return direction;
}

int& Organism::getTimeToReproduce() {
	return timeToReproduce;
}

void Organism::setRowPosition(int rowPosition) {
	this->rowPosition = rowPosition;
}

void Organism::setColumnPosition(int columnPosition) {
	this->columnPosition = columnPosition;
}

//This function causes the organism to check if the first step north is clear.
bool Organism::isNorthClear(std::vector<std::vector<char> >& worldVector) {
	if (!(getRowPosition() == 0)) {
		if (worldVector[getRowPosition()][getColumnPosition()] == '#' && getRowPosition() - 1 < 0) {
			return false;
		}
		else if (worldVector[getRowPosition() - 1][getColumnPosition()] == 'a' ||
			worldVector[getRowPosition() - 1][getColumnPosition()] == '@') {
			return false;
		}
		return true;
	}
	return false;
}

//This function causes the organism to check if the first step east is clear.
bool Organism::isEastClear(std::vector<std::vector<char> >& worldVector) {
	if (!(getColumnPosition() == 29)) {
		if (worldVector[getRowPosition()][getColumnPosition()] == '#' && getColumnPosition() + 1 > 29) {
			return false;
		}
		else if (worldVector[getRowPosition()][getColumnPosition() + 1] == 'a' ||
			worldVector[getRowPosition()][getColumnPosition() + 1] == '@') {
			return false;
		}
		return true;
	}
	return false;
}

//This function causes the organism to check if the first step south is clear.
bool Organism::isSouthClear(std::vector<std::vector<char> >& worldVector) {
	if (!(getRowPosition() == 29)) {
		if (worldVector[getRowPosition()][getColumnPosition()] == '#' && getRowPosition() + 1 > 29) {
			return false;
		}
		else if (worldVector[getRowPosition() + 1][getColumnPosition()] == 'a' ||
			worldVector[getRowPosition() + 1][getColumnPosition()] == '@') {
			return false;
		}
		return true;
	}
	return false;
}

//This function causes the organism to check if the first step west is clear.
bool Organism::isWestClear(std::vector<std::vector<char> >& worldVector) {
	if (!(getColumnPosition() == 0)) {
		if (worldVector[getRowPosition()][getColumnPosition()] == '#' && getColumnPosition() - 1 < 0) {
			return false;
		}
		else if (worldVector[getRowPosition()][getColumnPosition() - 1] == 'a' ||
			worldVector[getRowPosition()][getColumnPosition() - 1] == '@') {
			return false;
		}
		return true;
	}
	return false;
}

//This function causes the organism to randomly choose a direction that is clear.
int Organism::chooseRandomDirection(std::vector<std::vector<char> >& worldVector) {
	vector<int> vectorOfDirections;
	bool matchFound = false;

	if (isNorthClear(worldVector) == true) {
		vectorOfDirections.push_back(getNorth());
	}
	if (isEastClear(worldVector) == true) {
		vectorOfDirections.push_back(getEast());
	}
	if (isSouthClear(worldVector) == true) {
		vectorOfDirections.push_back(getSouth());
	}
	if (isWestClear(worldVector) == true) {
		vectorOfDirections.push_back(getWest());
	}

	while (matchFound == false) {
		int randomDirection = (rand() % 4) + 1;
		for (int index = 0; index < vectorOfDirections.size(); index++) {
			if (vectorOfDirections.at(index) == randomDirection) {
				matchFound = true;
				return randomDirection;
			}
		}
	}
}