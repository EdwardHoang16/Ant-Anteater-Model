/*
Edward Hoang
The question this code responds to is one asking for 30x30 grid of cells modeling the life, death, and reproduction of ants and anteaters.
Both ants and anteaters move, reproduce, and die. Anteaters can also eat ants, but can also starve to death. Ants die by being eaten.
Declares a class representing the 30x30 grid of cells that represents the world. The role of the World class is to represent the ants and
anteaters and their actions on a grid of cells that can be viewed by the user.
*/

#pragma once

#include "Anteater.h"
#include "Ant.h"
#include <vector>

class Organism;
class World {
private:
	const int NORTH = 1;
	const int EAST = 2;
	const int SOUTH = 3;
	const int WEST = 4;
	const int WORLD_ROWS = 30;
	const int WORLD_COLUMNS = 30;

	std::vector<std::vector<char> > worldVector;
	int time;

	Anteater* pointerToAnteater;
	std::vector<Anteater*> vectorOfAnteaters;

	Ant* pointerToAnt;
	std::vector<Ant*> vectorOfAnts;

public:
	World();
	~World();

	int getWorldRows() const;
	int getWorldColumns() const;
	std::vector<std::vector<char> >& getWorldVector();
	int getNorth() const;
	int getEast() const;
	int getSouth() const;
	int getWest() const;

	void setWorldVector(std::vector<std::vector<char> > worldVector);

	void buildWalls();
	std::vector<int> generateNonRepeatingRandomNumbers();
	void setUpInitialAnteaters();
	void setUpInitialAnts();
	void displayWorld() const;

	void worldLoop();
	void timePasses();
	void anteatersMove();
	void anteatersEat();
	void oneAnteaterEats(Anteater* pointerToAnteater);
	void oneAnteaterEatsNorth(Anteater* pointerToAnteater);
	void oneAnteaterEatsEast(Anteater* pointerToAnteater);
	void oneAnteaterEatsSouth(Anteater* pointerToAnteater);
	void oneAnteaterEatsWest(Anteater* pointerToAnteater);
	void antsMove();
	void antsReproduce();
	void anteatersReproduce();
	void anteatersStarve();
};