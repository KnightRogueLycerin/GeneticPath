#pragma once

#include <vector>

#include "Chart.h"

class Individual{
public:
	Individual(Coordinates start, Coordinates goal, int steps, int width, int height);
	Individual(std::vector<Coordinates> dna, int width, int height);
	~Individual();
	// Fitness value to evaluate
	int fitness = 0;
	// Data access
	std::vector<Coordinates> getDNA();
	bool isEmpty();
	// Data Manupulation
	void mutate(int range);
private:
	std::vector<Coordinates> DNA;
	int worldWidth;
	int worldHeight;
};