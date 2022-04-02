
#include "pch.h"


//Test 1
/*
#include "game.h"
#include "game.h"
#include "world.h"
#include "world.h" 
#include "life.h" 
#include "life.h"
#include "toad.h"
#include "toad.h" 
#include "glider.h"
#include "glider.h" 
#include "globals.h"
#include "globals.h"
int main(){}*/
 //Test 1 Passed

//Test 2
/*
#include"game.h" 
int main() {       
	World w;       
	Game g(nullptr, 0); 
} */ //Test 2 Passed

//Test 3
/*
#include"game.h" 
int main() { 
	Life l; 
} */

//Main


#include "globals.h"
#include "Life.h"
#include "toad.h"
#include "glider.h"
#include "world.h"
#include "game.h"

int main() {

	Life **population = new Life*[2];

	//population[0] = new Toad(4, 5); //toad alone
	//int numLife = 1;

	//population[0] = new Glider(0,0); //glider alone
	//int numLife = 1;


	population[0] = new Glider(0, 0); // Toad and Glider
	population[1] = new Toad(4, 5);
	int numLife = 2;

	// Create the game
	Game g(population, numLife);

	// Run the game
	g.play();

	// Report
	report();

	// Clean up
	delete population[0];
	delete population[1];
	delete[] population;

}