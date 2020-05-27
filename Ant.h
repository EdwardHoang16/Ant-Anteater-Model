/*
Edward Hoang
The question this code responds to is one asking for 30x30 grid of cells modeling the life, death, and reproduction of ants and anteaters.
Both ants and anteaters move, reproduce, and die. Anteaters can also eat ants, but can also starve to death. Ants die by being eaten.
Declares a class representing an ant. The role of the Ant class is to contain functions used by an ant.
*/

#pragma once

#include "Organism.h"

class Ant : public Organism {
private:

public:
	Ant();
	Ant(int rowPosition, int columnPosition);

	void move(std::vector<std::vector<char> >& worldVector);
	void reproduce(std::vector<std::vector<char> >& worldVector);
};