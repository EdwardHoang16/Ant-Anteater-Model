/*
Edward Hoang
The question this code responds to is one asking for 30x30 grid of cells modeling the life, death, and reproduction of ants and anteaters.
Both ants and anteaters move, reproduce, and die. Anteaters can also eat ants, but can also starve to death. Ants die by being eaten.
Defines a class representing an anteater.
*/

#include "World.h"
#include "Organism.h"
#include "Anteater.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <cmath>
#include <limits>

using namespace std;

Anteater::Anteater() {
	setRowPosition(0);
	setColumnPosition(0);
	getDirection() = 0;
	distance = numeric_limits<int>::max();
	timeToStarve = 0;
	antWithinFiveSquares = false;
	directionToEatAnts = 0;
}

Anteater::Anteater(int rowPosition, int columnPosition) {
	setRowPosition(rowPosition);
	setColumnPosition(columnPosition);
	getDirection() = 0;
	distance = numeric_limits<int>::max();
	timeToStarve = 0;
	antWithinFiveSquares = false;
	directionToEatAnts = 0;

}

int Anteater::getDirectionToEatAnts() {
	return directionToEatAnts;
}

bool Anteater::getAntWithinFiveSquares() {
	return antWithinFiveSquares;
}

int& Anteater::getTimeToStarve() {
	return timeToStarve;
}

//This function causes an anteater to determine if an ant is within five squares of it north, east, south, and west.
bool Anteater::findIfAntIsWithinFiveSquares(std::vector<std::vector<char> > worldVector) {
	bool antWithinFiveSquaresNorth = false;
	bool antWithinFiveSquaresEast = false;
	bool antWithinFiveSquaresSouth = false;
	bool antWithinFiveSquaresWest = false;

	if (!(getRowPosition() == 0)) {
		antWithinFiveSquaresNorth = findIfAntIsWithinFiveSquaresNorth(worldVector);
		if (antWithinFiveSquaresNorth == true) {
			return true;
		}
	}
	if (!(getColumnPosition() == 29)) {
		antWithinFiveSquaresEast = findIfAntIsWithinFiveSquaresEast(worldVector);
		if (antWithinFiveSquaresEast == true) {
			return true;
		}
	}
	if (!(getRowPosition() == 29)) {
		antWithinFiveSquaresSouth = findIfAntIsWithinFiveSquaresSouth(worldVector);
		if (antWithinFiveSquaresSouth == true) {
			return true;
		}
	}
	if (!(getColumnPosition() == 0)) {
		antWithinFiveSquaresWest = findIfAntIsWithinFiveSquaresWest(worldVector);
		if (antWithinFiveSquaresWest == true) {
			return true;
		}
	}
	return false;
}

//This function causes an anteater to determine if an ant is within five squares of it north.
bool Anteater::findIfAntIsWithinFiveSquaresNorth(std::vector<std::vector<char> >& worldVector) {
	int index = 0;
	bool keepLookingNorth = true;

	if (getRowPosition() < 5) {
		index = getRowPosition();
	}
	else {
		index = 5;
	}
	while (keepLookingNorth == true && index <= 5 && index >= 0) {
		if (worldVector[getRowPosition() - index][getColumnPosition()] == '#' && keepLookingNorth == true) {
			keepLookingNorth = false;
		}
		if (worldVector[getRowPosition() - index][getColumnPosition()] == 'a' && keepLookingNorth == true) {
			directionToEatAnts = getNorth();
			return true;
		}
		index--;
	}
	return false;
}

//This function causes an anteater to determine if an ant is within five squares of it east.
bool Anteater::findIfAntIsWithinFiveSquaresEast(std::vector<std::vector<char> >& worldVector) {
	int index = 0;
	bool keepLookingEast = true;

	if (getColumnPosition() > 24) {
		index = 29 - getColumnPosition();
	}
	else {
		index = 5;
	}
	while (keepLookingEast == true && index <= 5 && index >= 0) {
		if (worldVector[getRowPosition()][getColumnPosition() + index] == '#' && keepLookingEast == true) {
			keepLookingEast = false;
		}
		if (worldVector[getRowPosition()][getColumnPosition() + index] == 'a' && keepLookingEast == true) {
			directionToEatAnts = getEast();
			return true;
		}
		index--;
	}
	return false;
}

//This function causes an anteater to determine if an ant is within five squares of it south.
bool Anteater::findIfAntIsWithinFiveSquaresSouth(std::vector<std::vector<char> >& worldVector) {
	int index = 0;
	bool keepLookingSouth = true;

	if (getRowPosition() > 24) {
		index = 29 - getRowPosition();
	}
	else {
		index = 5;
	}
	while (keepLookingSouth == true && index <= 5 && index >= 0) {
		if (worldVector[getRowPosition() + index][getColumnPosition()] == '#' && keepLookingSouth == true) {
			keepLookingSouth = false;
		}
		if (worldVector[getRowPosition() + index][getColumnPosition()] == 'a' && keepLookingSouth == true) {
			directionToEatAnts = getSouth();
			return true;
		}
		index--;
	}
	return false;
}

//This function causes an anteater to determine if an ant is within five squares of it west.
bool Anteater::findIfAntIsWithinFiveSquaresWest(std::vector<std::vector<char> >& worldVector) {
	int index = 0;
	bool keepLookingWest = true;

	if (getColumnPosition() < 5) {
		index = getColumnPosition();
	}
	else {
		index = 5;
	}
	while (keepLookingWest == true && index <= 5 && index >= 0) {
		if (worldVector[getRowPosition()][getColumnPosition() - index] == '#' && keepLookingWest == true) {
			keepLookingWest = false;
		}
		if (worldVector[getRowPosition()][getColumnPosition() - index] == 'a' && keepLookingWest == true) {
			directionToEatAnts = getWest();
			return true;
		}
		index--;
	}
	return false;
}

//This function causes an anteater to find the nearest ant. 
int Anteater::lookForAntsThroughoutWorld(std::vector<std::vector<char> > worldVector) {
	vector<float> vectorOfDistances;
	vector<int> vectorOfXValues;
	vector<int> vectorOfYValues;
	int minimumDistanceX = 0;
	int minimumDistanceY = 0;
	antWithinFiveSquares = findIfAntIsWithinFiveSquares(worldVector);

	if (antWithinFiveSquares == false) {
		for (int rowIndex = 0; rowIndex <= getWorldRows() - 1; ++rowIndex) {
			for (int columnIndex = 0; columnIndex <= getWorldColumns() - 1; ++columnIndex) {
				if (worldVector[rowIndex][columnIndex] == 'a') {
					vectorOfDistances.push_back(findDistance(getRowPosition(), getColumnPosition(), rowIndex, columnIndex));
					vectorOfXValues.push_back(rowIndex);
					vectorOfYValues.push_back(columnIndex);
				}
			}
		}

		distance = numeric_limits<int>::max();

		for (int index = 0; index < vectorOfDistances.size(); index++) {
			if (vectorOfDistances.at(index) < distance) {
				distance = vectorOfDistances.at(index);
				minimumDistanceX = vectorOfXValues.at(index);
				minimumDistanceY = vectorOfYValues.at(index);
			}
		}
		getDirection() = findDirection(minimumDistanceX, minimumDistanceY);
	}
	return getDirection();
}

//This function calculates distance.
float Anteater::findDistance(int x1, int y1, int x2, int y2) {
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

//This function determines which direction an anteater should go toward the nearest ant.
int Anteater::findDirection(int minimumDistanceX, int minimumDistanceY) {
	if (getRowPosition() > minimumDistanceX) {
		return getNorth();
	}
	else if (getRowPosition() < minimumDistanceX) {
		return getSouth();
	}
	else if (getColumnPosition() > minimumDistanceY) {
		return getWest();
	}
	else if (getColumnPosition() < minimumDistanceY) {
		return getEast();
	}
	return -1;
}

//This function causes an anteater to move.
void Anteater::move(std::vector<std::vector<char> >& worldVector) {
	getDirection() = lookForAntsThroughoutWorld(worldVector);

	if (antWithinFiveSquares == false) {
		if (getDirection() == getNorth() && isNorthClear(worldVector) == true) {
			getRowPosition()--;
			worldVector[getRowPosition()][getColumnPosition()] = '@';
			worldVector[getRowPosition() + 1][getColumnPosition()] = '-';
		}
		else if (getDirection() == getEast() && isEastClear(worldVector) == true) {
			getColumnPosition()++;
			worldVector[getRowPosition()][getColumnPosition()] = '@';
			worldVector[getRowPosition()][getColumnPosition() - 1] = '-';
		}
		else if (getDirection() == getSouth() && isSouthClear(worldVector) == true) {
			getRowPosition()++;
			worldVector[getRowPosition()][getColumnPosition()] = '@';
			worldVector[getRowPosition() - 1][getColumnPosition()] = '-';
		}
		else if (getDirection() == getWest() && isWestClear(worldVector) == true) {
			getColumnPosition()--;
			worldVector[getRowPosition()][getColumnPosition()] = '@';
			worldVector[getRowPosition()][getColumnPosition() + 1] = '-';
		}
	}
}

//This function determines whether an anteater is able to eat an ant. 
bool Anteater::canEat(std::vector<std::vector<char> >& worldVector) {
	if (directionToEatAnts == getNorth() && isNorthClearRegardlessOfAnts(worldVector) == true) {
		for (int index = 1; index < 5; index++) {
			if (getRowPosition() - 5 < 0 || worldVector[getRowPosition() - index][getColumnPosition()] == '@' ||
				worldVector[getRowPosition() - index][getColumnPosition()] == '#') {
				return false;
			}
		}
		return true;
	}
	else if (directionToEatAnts == getEast() && isEastClearRegardlessOfAnts(worldVector)) {
		for (int index = 1; index < 5; index++) {
			if (getColumnPosition() + 5 > getWorldColumns() - 1 ||
				worldVector[getRowPosition()][getColumnPosition() + index] == '@' ||
				worldVector[getRowPosition()][getColumnPosition() + index] == '#') {
				return false;
			}
		}
		return true;
	}
	else if (directionToEatAnts == getSouth() && isSouthClearRegardlessOfAnts(worldVector)) {
		for (int index = 1; index < 5; index++) {
			if (getRowPosition() + 5 > getWorldRows() - 1 ||
				worldVector[getRowPosition() + index][getColumnPosition()] == '@' ||
				worldVector[getRowPosition() + index][getColumnPosition()] == '#') {
				return false;
			}
		}
		return true;
	}
	else if (directionToEatAnts == getWest() && isWestClearRegardlessOfAnts(worldVector)) {
		for (int index = 1; index < 5; index++) {
			if (getRowPosition() - 5 < 0 ||
				worldVector[getRowPosition()][getColumnPosition() - index] == '@' ||
				worldVector[getRowPosition()][getColumnPosition() - index] == '#') {
				return false;
			}
		}
		return true;
	}
}

//This function determines the direction in which an anteater produces another anteater.
void Anteater::reproduce(std::vector<std::vector<char> >& worldVector) {
	getDirection() = chooseRandomDirection(worldVector);
}

//This function determines the direction in which an anteater produces another anteater, taking over an ant's spot if needed.
void Anteater::reproduceRegardlessOfAnts(std::vector<std::vector<char> >& worldVector) {
	getDirection() = chooseRandomDirectionRegardlessOfAnts(worldVector);
}

//This function causes an anteater to choose a direction to reproduce without regard to if ants are there.
int Anteater::chooseRandomDirectionRegardlessOfAnts(std::vector<std::vector<char> >& worldVector) {
	vector<int> vectorOfDirections;
	bool matchFound = false;

	if (isNorthClearRegardlessOfAnts(worldVector) == true) {
		vectorOfDirections.push_back(getNorth());
	}
	if (isEastClearRegardlessOfAnts(worldVector) == true) {
		vectorOfDirections.push_back(getEast());
	}
	if (isSouthClearRegardlessOfAnts(worldVector) == true) {
		vectorOfDirections.push_back(getSouth());
	}
	if (isWestClearRegardlessOfAnts(worldVector) == true) {
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

//This function causes an anteater to check if another anteater can be placed to its north without regard to whether an ant is there.
bool Anteater::isNorthClearRegardlessOfAnts(std::vector<std::vector<char> >& worldVector) {
	if (!(getRowPosition() == 0)) {
		if (worldVector[getRowPosition()][getColumnPosition()] == '#' && getRowPosition() - 1 < 0) {
			return false;
		}
		else if (worldVector[getRowPosition() - 1][getColumnPosition()] == '@') {
			return false;
		}
		return true;
	}
	return false;
}

//This function causes an anteater to check if another anteater can be placed to its east without regard to whether an ant is there.
bool Anteater::isEastClearRegardlessOfAnts(std::vector<std::vector<char> >& worldVector) {
	if (!(getColumnPosition() == 29)) {
		if (worldVector[getRowPosition()][getColumnPosition()] == '#' && getColumnPosition() + 1 > 29) {
			return false;
		}
		else if (worldVector[getRowPosition()][getColumnPosition() + 1] == '@') {
			return false;
		}
		return true;
	}
	return false;
}

//This function causes an anteater to check if another anteater can be placed to its south without regard to whether an ant is there.
bool Anteater::isSouthClearRegardlessOfAnts(std::vector<std::vector<char> >& worldVector) {
	if (!(getRowPosition() == 29)) {
		if (worldVector[getRowPosition()][getColumnPosition()] == '#' && getRowPosition() + 1 > 29) {
			return false;
		}
		else if (worldVector[getRowPosition() + 1][getColumnPosition()] == '@') {
			return false;
		}
		return true;
	}
	return false;
}

//This function causes an anteater to check if another anteater can be placed to its west without regard to whether an ant is there.
bool Anteater::isWestClearRegardlessOfAnts(std::vector<std::vector<char> >& worldVector) {
	if (!(getColumnPosition() == 0)) {
		if (worldVector[getRowPosition()][getColumnPosition()] == '#' && getColumnPosition() - 1 < 0) {
			return false;
		}
		else if (worldVector[getRowPosition()][getColumnPosition() - 1] == '@') {
			return false;
		}
		return true;
	}
	return false;
}