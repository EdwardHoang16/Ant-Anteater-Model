/*
Edward Hoang
The question this code responds to is one asking for 30x30 grid of cells modeling the life, death, and reproduction of ants and anteaters.
Both ants and anteaters move, reproduce, and die. Anteaters can also eat ants, but can also starve to death. Ants die by being eaten.
This program serves as driver code showing the functioning of the World class, the Organism class, the Ant class, and the Anteater class.
*/

#include "Organism.h"
#include "World.h"
#include <iostream>
#include "time.h"
#include <cstdlib>

using namespace std;

int main()
{
	srand(time(NULL));
	World worldObj;
}