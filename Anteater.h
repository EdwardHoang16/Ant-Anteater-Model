/*
Edward Hoang
The question this code responds to is one asking for 30x30 grid of cells modeling the life, death, and reproduction of ants and anteaters.
Both ants and anteaters move, reproduce, and die. Anteaters can also eat ants, but can also starve to death. Ants die by being eaten.
Declares a class representing an anteater. The role of the Anteater class is to contain the variables and functions used by an anteater.
*/

#pragma once

#include "World.h"
#include "Organism.h"

class Anteater : public Organism {
private:
	float distance;
	int directionToEatAnts;
	bool antWithinFiveSquares;
	int timeToStarve;

public:
	Anteater();
	Anteater(int rowPosition, int columnPosition);

	int getDirectionToEatAnts();
	bool getAntWithinFiveSquares();
	int& getTimeToStarve();

	bool findIfAntIsWithinFiveSquares(std::vector<std::vector<char> > worldVector);
	bool findIfAntIsWithinFiveSquaresNorth(std::vector<std::vector<char> >& worldVector);
	bool findIfAntIsWithinFiveSquaresEast(std::vector<std::vector<char> >& worldVector);
	bool findIfAntIsWithinFiveSquaresSouth(std::vector<std::vector<char> >& worldVector);
	bool findIfAntIsWithinFiveSquaresWest(std::vector<std::vector<char> >& worldVector);
	int lookForAntsThroughoutWorld(std::vector<std::vector<char> > worldVector);
	float findDistance(int x1, int y1, int x2, int y2);
	int findDirection(int xDistance, int yDistance);

	void move(std::vector<std::vector<char> >& worldVector);
	bool canEat(std::vector<std::vector<char> >& worldVector);

	void reproduce(std::vector<std::vector<char> >& worldVector);
	void reproduceRegardlessOfAnts(std::vector<std::vector<char> >& worldVector);
	int chooseRandomDirectionRegardlessOfAnts(std::vector<std::vector<char> >& worldVector);
	bool isNorthClearRegardlessOfAnts(std::vector<std::vector<char> >& worldVector);
	bool isEastClearRegardlessOfAnts(std::vector<std::vector<char> >& worldVector);
	bool isSouthClearRegardlessOfAnts(std::vector<std::vector<char> >& worldVector);
	bool isWestClearRegardlessOfAnts(std::vector<std::vector<char> >& worldVector);
};