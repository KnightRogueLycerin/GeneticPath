#pragma once

#include "Individual.h"

typedef std::vector<Individual> Individuals;

class Generation{	// Needs start and end cords
public:
	Generation(Chart* chart);
	~Generation();
	// Generate generation
	Individuals freshBatch(int size, int topCount);
	Individuals breedingBatch(int size, int topCount, Individuals breedingStock);
	//
	void purge();
private:
	// Data trakers
	Chart * charter;
	Individuals population;
	// Help functions
	void gradePopulation();
	Individuals findBreeders(int count);
	bool mutagen();
	int middlepoint(int a, int b);
	Coordinates mixGenes(Coordinates a, Coordinates b);
	std::vector<Coordinates> breed(Individual a, Individual b);
};