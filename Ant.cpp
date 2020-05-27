/*
Edward Hoang
The question this code responds to is one asking for 30x30 grid of cells modeling the life, death, and reproduction of ants and anteaters.
Both ants and anteaters move, reproduce, and die. Anteaters can also eat ants, but can also starve to death. Ants die by being eaten.
Defines a class representing an ant.
*/

#include "Ant.h"

using namespace std;

Ant::Ant() {
	setRowPosition(0);
	setColumnPosition(0);
	getDirection() = 0;
	getTimeToReproduce() = 0;
}

Ant::Ant(int rowPosition, int columnPosition) {
	setRowPosition(rowPosition);
	setColumnPosition(columnPosition);
	getDirection() = 0;
	getTimeToReproduce() = 0;
}

//This function causes one ant to move.
void Ant::move(std::vector<std::vector<char> >& worldVector) {
	getDirection() = chooseRandomDirection(worldVector);

	if (getDirection() == getNorth()) {
		getRowPosition()--;
		worldVector[getRowPosition()][getColumnPosition()] = 'a';
		worldVector[getRowPosition() + 1][getColumnPosition()] = '-';
	}
	else if (getDirection() == getEast()) {
		getColumnPosition()++;
		worldVector[getRowPosition()][getColumnPosition()] = 'a';
		worldVector[getRowPosition()][getColumnPosition() - 1] = '-';
	}
	else if (getDirection() == getSouth()) {
		getRowPosition()++;
		worldVector[getRowPosition()][getColumnPosition()] = 'a';
		worldVector[getRowPosition() - 1][getColumnPosition()] = '-';
	}
	else if (getDirection() == getWest()) {
		getColumnPosition()--;
		worldVector[getRowPosition()][getColumnPosition()] = 'a';
		worldVector[getRowPosition()][getColumnPosition() + 1] = '-';
	}
}

//This function determines the direction in which an ant produces another ant.
void Ant::reproduce(std::vector<std::vector<char> >& worldVector) {
	getDirection() = chooseRandomDirection(worldVector);
}