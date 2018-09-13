#include <algorithm>
#include <iostream>

#include "Individual.h"
#include "RNG.h" 

Individual::Individual(Coordinates start, Coordinates goal, int steps, int width, int height){
	DNA = std::vector<Coordinates>();
	DNA.push_back(start);
	worldWidth = width;
	worldHeight = height;
	for (int i = 0; i < steps; i++) {
		Coordinates c;
		c.column = rng::generateNumber(width);
		c.row = rng::generateNumber(height);
		DNA.push_back(c);
	}
	DNA.push_back(goal);
}

Individual::Individual(std::vector<Coordinates> dna, int width, int height){
	DNA = dna;
	worldWidth = width;
	worldHeight = height;
}

Individual::~Individual(){
}

std::vector<Coordinates> Individual::getDNA(){
	return DNA;
}

bool Individual::isEmpty(){
	return DNA.empty();
}

void Individual::mutate(int range){
	int verticalDirection, horisontalDirection;
	int verticalShift, horisontalShift;
	Coordinates start = DNA[0];
	Coordinates goal = DNA[DNA.size() - 1];
	for each(Coordinates c in DNA) {
		verticalDirection = rng::generateNumber(2) - 1;
		verticalShift = rng::generateNumber(range);

		horisontalDirection = rng::generateNumber(2) - 1;
		horisontalShift = rng::generateNumber(range);
		// Mutating horisontaly , columns
		if (horisontalDirection == 0) {
			// up
			c.column -= horisontalShift;
			if (c.column < 0)
				c.column = 0;
		}
		else {
			// down
			c.column += horisontalShift;
			if (c.column > worldWidth - 1)
				c.column = worldWidth - 1;
		}
		// Mutating vertically, rows
		if (verticalDirection == 0) {
			// left
			c.row -= verticalShift;
			if (c.row < 0)
				c.row = 0;
		}
		else {
			// right
			c.row -= verticalShift;
			if (c.row > worldHeight - 1)
				c.row = worldHeight - 1;
		}
	}
	// May not change start/goal!
	DNA[0] = start;
	DNA[DNA.size() - 1] = goal;
}