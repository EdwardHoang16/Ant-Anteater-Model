/*
Edward Hoang
The question this code responds to is one asking for 30x30 grid of cells modeling the life, death, and reproduction of ants and anteaters.
Both ants and anteaters move, reproduce, and die. Anteaters can also eat ants, but can also starve to death. Ants die by being eaten.
Defines a class representing the 30x30 grid of cells that represents the world.
*/

#include "World.h"
#include "Organism.h"
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

World::World() {
	vector<vector<char> > worldVector(WORLD_ROWS, vector<char>(WORLD_COLUMNS, '-'));
	setWorldVector(worldVector);
	time = 0;

	buildWalls();
	setUpInitialAnteaters();
	setUpInitialAnts();
	cout << "Time Step: " << time << endl;
	displayWorld();

	worldLoop();
}

World::~World() {
	for (vector<Anteater*>::iterator index = vectorOfAnteaters.begin(); index != vectorOfAnteaters.end(); ++index) {
		Anteater* anteaterObj = *index;
		delete anteaterObj;
		anteaterObj = nullptr;
	}
	for (vector<Ant*>::iterator index = vectorOfAnts.begin(); index != vectorOfAnts.end(); ++index) {
		Ant* antObj = *index;
		delete antObj;
		antObj = nullptr;
	}
}

int World::getWorldRows() const {
	return WORLD_ROWS;
}

int World::getWorldColumns() const {
	return WORLD_COLUMNS;
}

vector<vector<char> >& World::getWorldVector() {
	return worldVector;
}

int World::getNorth() const {
	return NORTH;
}

int World::getEast() const {
	return EAST;
}

int World::getSouth() const {
	return SOUTH;
}

int World::getWest() const {
	return WEST;
}

void World::setWorldVector(vector<vector<char> > worldVector) {
	this->worldVector = worldVector;
}

//This function places the '#' character representing the edge of the world along the edges of the grid.
void World::buildWalls() {
	for (int index = 0; index < 30; ++index) {
		if (worldVector[0][index] == '-') {
			worldVector[0][index] = '#';
		}
		if (worldVector[index][0] == '-') {
			worldVector[index][0] = '#';
		}
		if (worldVector[WORLD_ROWS - 1][index] == '-') {
			worldVector[WORLD_ROWS - 1][index] = '#';
		}
		if (worldVector[index][WORLD_COLUMNS - 1] == '-') {
			worldVector[index][WORLD_COLUMNS - 1] = '#';
		}
	}
}

//This function returns a vector of non-repeating randomly generated numbers from 0 to 29.
vector<int> World::generateNonRepeatingRandomNumbers() {
	vector<int> vectorOfRandomNumbers;

	for (int index = 0; index < 30; ++index) {
		vectorOfRandomNumbers.push_back(index);
	}

	random_shuffle(vectorOfRandomNumbers.begin(), vectorOfRandomNumbers.end());
	return vectorOfRandomNumbers;
}

//This function sets up 10 anteaters and their representations on the grid. 
void World::setUpInitialAnteaters() {
	vector<int> vectorOfRandomNumbers1 = generateNonRepeatingRandomNumbers();
	vector<int> vectorOfRandomNumbers2 = generateNonRepeatingRandomNumbers();

	for (int index = 0; index < 10; index++) {
		int randomRowPosition = vectorOfRandomNumbers1.at(index);
		int randomColumnPosition = vectorOfRandomNumbers2.at(index);

		Anteater* pointerToAnteater = new Anteater(randomRowPosition, randomColumnPosition);
		vectorOfAnteaters.push_back(pointerToAnteater);
		worldVector[randomRowPosition][randomColumnPosition] = '@';
	}
}

//This function sets up 15 ants and their representations on the grid.
void World::setUpInitialAnts() {
	vector<int> vectorOfRandomNumbers1 = generateNonRepeatingRandomNumbers();
	vector<int> vectorOfRandomNumbers2 = generateNonRepeatingRandomNumbers();

	for (int index = 0; index < 15; index++) {
		int randomRowPosition = vectorOfRandomNumbers1.at(index);
		int randomColumnPosition = vectorOfRandomNumbers2.at(index);

		Ant* pointerToAnt = new Ant(randomRowPosition, randomColumnPosition);
		vectorOfAnts.push_back(pointerToAnt);
		worldVector[randomRowPosition][randomColumnPosition] = 'a';
	}
}

//This function displays the current state of the game board.
void World::displayWorld() const {
	for (unsigned int displayRows = 0; displayRows < worldVector.size(); ++displayRows) {
		for (unsigned int displayColumns = 0; displayColumns < worldVector[displayRows].size(); ++displayColumns) {
			cout << worldVector[displayRows][displayColumns];
		}
		cout << endl;
	}
}

//This function serves as the loop to advance the time step of the world by one each time the user presses the enter key.
void World::worldLoop() {
	string inputToMaintainLoop;
	cout << "Press Enter to Continue . . . ";

	while (cin.ignore(numeric_limits<streamsize>::max(), '\n')) {
		timePasses();
		cout << "\nTime Step: " << time << endl;
		displayWorld();
		cout << "Press Enter to Continue . . . ";
	}
}

//This function calls the functions representing the various actions each animal takes for each time step.
void World::timePasses() {
	time++;

	anteatersMove();
	anteatersEat();
	antsMove();
	antsReproduce();
	anteatersReproduce();
	anteatersStarve();
}

//This function causes the anteaters to move on the grid. 
void World::anteatersMove() {
	for (int index = 0; index < vectorOfAnteaters.size(); index++) {
		vectorOfAnteaters.at(index)->move(worldVector);
		vectorOfAnteaters.at(index)->getDirection() = 0;
	}

	buildWalls();
}

//This function causes the anteaters to eat ants on the grid. 
void World::anteatersEat() {
	for (int index = 0; index < vectorOfAnteaters.size(); index++) {
		if (vectorOfAnteaters.at(index)->findIfAntIsWithinFiveSquares(worldVector) == true && vectorOfAnteaters.at(index)->canEat(worldVector) == true) {
			oneAnteaterEats(vectorOfAnteaters.at(index));
			vectorOfAnteaters.at(index)->getTimeToStarve() = 0;
		}
	}
}

//This function causes one anteater to eat ants on the grid.
void World::oneAnteaterEats(Anteater* pointerToAnteater) {
	if (pointerToAnteater->getDirectionToEatAnts() == pointerToAnteater->getNorth()) {
		oneAnteaterEatsNorth(pointerToAnteater);
	}
	else if (pointerToAnteater->getDirectionToEatAnts() == pointerToAnteater->getEast()) {
		oneAnteaterEatsEast(pointerToAnteater);
	}
	else if (pointerToAnteater->getDirectionToEatAnts() == pointerToAnteater->getSouth()) {
		oneAnteaterEatsSouth(pointerToAnteater);
	}
	else if (pointerToAnteater->getDirectionToEatAnts() == pointerToAnteater->getWest()) {
		oneAnteaterEatsWest(pointerToAnteater);
	}
}

//This function causes one anteater to eat ants to the north.
void World::oneAnteaterEatsNorth(Anteater* pointerToAnteater) {
	for (int anteaterIndex = 1; anteaterIndex <= 5; anteaterIndex++) {
		if (worldVector[pointerToAnteater->getRowPosition() - anteaterIndex][pointerToAnteater->getColumnPosition()] == 'a') {
			for (int index = 0; index < vectorOfAnts.size(); index++) {
				if (vectorOfAnts.at(index)->getRowPosition() == pointerToAnteater->getRowPosition() - anteaterIndex &&
					vectorOfAnts.at(index)->getColumnPosition() == pointerToAnteater->getColumnPosition()) {
					worldVector[vectorOfAnts.at(index)->getRowPosition()][vectorOfAnts.at(index)->getColumnPosition()] = '-';
					delete vectorOfAnts.at(index);
					vectorOfAnts.at(index) = nullptr;
					vectorOfAnts.erase(vectorOfAnts.begin() + index);

				}
			}
		}
	}
}

//This function causes one anteater to eat ants to the east.
void World::oneAnteaterEatsEast(Anteater* pointerToAnteater) {
	for (int anteaterIndex = 1; anteaterIndex <= 5; anteaterIndex++) {
		if (worldVector[pointerToAnteater->getRowPosition()][pointerToAnteater->getColumnPosition() + anteaterIndex] == 'a') {
			for (int index = 0; index < vectorOfAnts.size(); index++) {
				if (vectorOfAnts.at(index)->getRowPosition() == pointerToAnteater->getRowPosition() &&
					vectorOfAnts.at(index)->getColumnPosition() == pointerToAnteater->getColumnPosition() + anteaterIndex) {
					worldVector[vectorOfAnts.at(index)->getRowPosition()][vectorOfAnts.at(index)->getColumnPosition()] = '-';
					delete vectorOfAnts.at(index);
					vectorOfAnts.at(index) = nullptr;
					vectorOfAnts.erase(vectorOfAnts.begin() + index);
				}
			}
		}
	}
}

//This function causes one anteater to eat ants to the south.
void World::oneAnteaterEatsSouth(Anteater* pointerToAnteater) {
	for (int anteaterIndex = 1; anteaterIndex <= 5; anteaterIndex++) {
		if (worldVector[pointerToAnteater->getRowPosition() + anteaterIndex][pointerToAnteater->getColumnPosition()] == 'a') {
			for (int index = 0; index < vectorOfAnts.size(); index++) {
				if (vectorOfAnts.at(index)->getRowPosition() == pointerToAnteater->getRowPosition() + anteaterIndex &&
					vectorOfAnts.at(index)->getColumnPosition() == pointerToAnteater->getColumnPosition()) {
					worldVector[vectorOfAnts.at(index)->getRowPosition()][vectorOfAnts.at(index)->getColumnPosition()] = '-';
					delete vectorOfAnts.at(index);
					vectorOfAnts.at(index) = nullptr;
					vectorOfAnts.erase(vectorOfAnts.begin() + index);
				}
			}
		}
	}
}

//This function causes one anteater to eat ants to the west.
void World::oneAnteaterEatsWest(Anteater* pointerToAnteater) {
	for (int anteaterIndex = 1; anteaterIndex <= 5; anteaterIndex++) {
		if (worldVector[pointerToAnteater->getRowPosition()][pointerToAnteater->getColumnPosition() - anteaterIndex] == 'a') {
			for (int index = 0; index < vectorOfAnts.size(); index++) {
				if (vectorOfAnts.at(index)->getRowPosition() == pointerToAnteater->getRowPosition() &&
					vectorOfAnts.at(index)->getColumnPosition() == pointerToAnteater->getColumnPosition() - anteaterIndex) {
					worldVector[vectorOfAnts.at(index)->getRowPosition()][vectorOfAnts.at(index)->getColumnPosition()] = '-';
					delete vectorOfAnts.at(index);
					vectorOfAnts.at(index) = nullptr;
					vectorOfAnts.erase(vectorOfAnts.begin() + index);
				}
			}
		}
	}
}

//This function causes the ants to move on the grid.
void World::antsMove() {
	for (int index = 0; index < vectorOfAnts.size(); index++) {
		vectorOfAnts.at(index)->move(getWorldVector());
		vectorOfAnts.at(index)->getDirection() = 0;
	}

	buildWalls();
}

//This function causes the ants to reproduce on the grid.
void World::antsReproduce() {
	for (int index = 0; index < vectorOfAnts.size(); index++) {
		vectorOfAnts.at(index)->getTimeToReproduce()++;

		if (vectorOfAnts.at(index)->getTimeToReproduce() == 3) {
			vectorOfAnts.at(index)->reproduce(worldVector);
			vectorOfAnts.at(index)->getTimeToReproduce() = 0;
			if (vectorOfAnts.at(index)->getDirection() == NORTH) {
				Ant* pointerToAnt = new Ant(vectorOfAnts.at(index)->getRowPosition() - 1,
					vectorOfAnts.at(index)->getColumnPosition());
				vectorOfAnts.push_back(pointerToAnt);
				worldVector[vectorOfAnts.at(index)->getRowPosition() - 1][vectorOfAnts.at(index)->getColumnPosition()] = 'a';
			}
			else if (vectorOfAnts.at(index)->getDirection() == EAST) {
				Ant* pointerToAnt = new Ant(vectorOfAnts.at(index)->getRowPosition(),
					vectorOfAnts.at(index)->getColumnPosition() + 1);
				vectorOfAnts.push_back(pointerToAnt);
				worldVector[vectorOfAnts.at(index)->getRowPosition()][vectorOfAnts.at(index)->getColumnPosition() + 1] = 'a';
			}
			else if (vectorOfAnts.at(index)->getDirection() == SOUTH) {
				Ant* pointerToAnt = new Ant(vectorOfAnts.at(index)->getRowPosition() + 1,
					vectorOfAnts.at(index)->getColumnPosition());
				vectorOfAnts.push_back(pointerToAnt);
				worldVector[vectorOfAnts.at(index)->getRowPosition() + 1][vectorOfAnts.at(index)->getColumnPosition()] = 'a';
			}
			else if (vectorOfAnts.at(index)->getDirection() == WEST) {
				Ant* pointerToAnt = new Ant(vectorOfAnts.at(index)->getRowPosition(),
					vectorOfAnts.at(index)->getColumnPosition() - 1);
				vectorOfAnts.push_back(pointerToAnt);
				worldVector[vectorOfAnts.at(index)->getRowPosition()][vectorOfAnts.at(index)->getColumnPosition() - 1] = 'a';
			}
			vectorOfAnts.at(index)->getDirection() = 0;
		}
	}
}

//This function causes the anteaters to reproduce on the grid.
void World::anteatersReproduce() {
	for (int index = 0; index < vectorOfAnteaters.size(); index++) {
		vectorOfAnteaters.at(index)->getTimeToReproduce()++;

		if (vectorOfAnteaters.at(index)->getTimeToReproduce() == 8) {
			vectorOfAnteaters.at(index)->reproduce(worldVector);
			vectorOfAnteaters.at(index)->getTimeToReproduce() = 0;

			if (vectorOfAnteaters.at(index)->getDirection() == 0) {
				vectorOfAnteaters.at(index)->reproduceRegardlessOfAnts(worldVector);
			}

			if (vectorOfAnteaters.at(index)->getDirection() == NORTH) {
				Anteater* pointerToAnteater = new Anteater(vectorOfAnteaters.at(index)->getRowPosition() - 1,
					vectorOfAnteaters.at(index)->getColumnPosition());
				vectorOfAnteaters.push_back(pointerToAnteater);
				worldVector[vectorOfAnteaters.at(index)->getRowPosition() - 1][vectorOfAnteaters.at(index)->getColumnPosition()] = '@';
			}
			else if (vectorOfAnteaters.at(index)->getDirection() == EAST) {
				Anteater* pointerToAnteater = new Anteater(vectorOfAnteaters.at(index)->getRowPosition(),
					vectorOfAnteaters.at(index)->getColumnPosition() + 1);
				vectorOfAnteaters.push_back(pointerToAnteater);
				worldVector[vectorOfAnteaters.at(index)->getRowPosition()][vectorOfAnteaters.at(index)->getColumnPosition() + 1] = '@';
			}
			else if (vectorOfAnteaters.at(index)->getDirection() == SOUTH) {
				Anteater* pointerToAnteater = new Anteater(vectorOfAnteaters.at(index)->getRowPosition() + 1,
					vectorOfAnteaters.at(index)->getColumnPosition());
				vectorOfAnteaters.push_back(pointerToAnteater);
				worldVector[vectorOfAnteaters.at(index)->getRowPosition() + 1][vectorOfAnteaters.at(index)->getColumnPosition()] = '@';
			}
			else if (vectorOfAnteaters.at(index)->getDirection() == WEST) {
				Anteater* pointerToAnteater = new Anteater(vectorOfAnteaters.at(index)->getRowPosition(),
					vectorOfAnteaters.at(index)->getColumnPosition() - 1);
				vectorOfAnteaters.push_back(pointerToAnteater);
				worldVector[vectorOfAnteaters.at(index)->getRowPosition()][vectorOfAnteaters.at(index)->getColumnPosition() - 1] = '@';
			}
			vectorOfAnts.at(index)->getDirection() = 0;
		}
	}
}

//This function causes the anteaters to starve to death on the grid.
void World::anteatersStarve() {
	for (int index = 0; index < vectorOfAnteaters.size(); index++) {
		vectorOfAnteaters.at(index)->getTimeToStarve()++;
		if (vectorOfAnteaters.at(index)->getTimeToStarve() == 4) {
			worldVector[vectorOfAnteaters.at(index)->getRowPosition()][vectorOfAnteaters.at(index)->getColumnPosition()] = '-';
			delete vectorOfAnteaters.at(index);
			vectorOfAnteaters.at(index) = nullptr;
			vectorOfAnteaters.erase(vectorOfAnteaters.begin() + index);
		}
	}

	buildWalls();
}