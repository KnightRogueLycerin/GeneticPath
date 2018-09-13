#include <algorithm>
#include <iostream>

#include "Generation.h"
#include "RNG.h"

static const int MUTACHANSE = 1000;	// Chase to mutate, as in 1 in MUTAGEN
static const int MUTASTRENGTH = 3;		// Strenght of mutation, how far gene can drift
static const int STEPS = 6;				// Steps of coordinates between start and goal

Generation::Generation(Chart* chart){
	charter = chart;
}

Generation::~Generation(){
}

Individuals Generation::freshBatch(int size, int topCount){
	purge();
	// Create generation
	std::cout << " Generating Population (rows of 100's):";
	for (int i = 0; i < size; i++) {
		Individual pop(
			charter->getStart(), 
			charter->getGoal(),
			STEPS,
			charter->getWidth() - 1,
			charter->getHeight() - 1);
		// Mutate
		if (mutagen()) {
			pop.mutate(MUTASTRENGTH);
		}
		// Heard
		population.push_back(pop);
		if (i % 100 == 0)
			std::cout << std::endl;
		if(i % 2 == 0)
			std::cout << char(223);
		else
			std::cout << char(254);
	}// Evaluate generation
	std::cout << std::endl << " Grading Generation";
	gradePopulation();
	// Send back the best stock
	std::cout << " Sending the best for breeding" << std::endl;
	return findBreeders(topCount);
}

Individuals Generation::breedingBatch(int size, int topCount, Individuals breedingStock){
	purge();
	// Create generation
	std::cout << " Generating Population From Stock (rows of 100):";
	for (int i = 0; i < size; i++) {	// Change to use breedninStock!
		Individual pop(
			breed(
				breedingStock[rng::generateNumber(breedingStock.size())],
				breedingStock[rng::generateNumber(breedingStock.size())]),
			charter->getWidth() - 1,
			charter->getHeight() - 1);
		// Mutate
		if (mutagen()) {
			pop.mutate(MUTASTRENGTH);
		}
		// Heard
		population.push_back(pop);
		if (i % 100 == 0)
			std::cout << std::endl;
		if (i % 2 == 0)
			std::cout << char(223);
		else
			std::cout << char(254);
	}// Evaluate generation
	std::cout << std::endl << " Grading Generation";
	gradePopulation();
	// Send back the best stock
	std::cout << " Sending the best for breeding" << std::endl;
	return findBreeders(topCount);
}
void Generation::purge(){
	population.clear();
	population = Individuals();
}
// Help functions
void Generation::gradePopulation(){
	for (auto i = 0; i < population.size(); i++) {
		std::vector<Coordinates> strand = population[i].getDNA();
		population[i].fitness = charter->evaluatePath(charter->createPath(strand));
		// Output for showing progress
		if (i % 100 == 0)
			std::cout << std::endl;
		std::cout << "|";
	}
	std::cout << std::endl;
}
// Need to have been evaluated prior to this!
bool comp(const Individual& a, const Individual& b) { return (a.fitness < b.fitness); }
Individuals Generation::findBreeders(int count){
	// Sort the stock
	Individuals stock;
	for (auto i = 0; i < population.size(); i++) {
		int value = 0; auto index = 0; bool found = false;
		for (auto j = 0; j < population.size(); j++) {
			if (population[j].fitness > value) {
				value = population[j].fitness;
				index = j;
				found = true;
			}
		}
		if (found) {
			stock.push_back(population[index]);
			population[index].fitness = -1;	// Will not be "found" again
		}
	}
	std::reverse(stock.begin(), stock.end());
	population = stock;
	// Pick the top of the stock
	Individuals picks;
	for (int i = 0; i < count; i++) {
		picks.push_back(population[i]);
	}
	for (int i = 0; i < picks.size(); i++) {
		std::cout << " Fittness " << picks[i].fitness << ": ";
		std::cout << "{ ";
		for each(Coordinates c in picks[i].getDNA()) {
			std::cout << "[" << c.column << "," << c.row << "] ";
		}
		std::cout << "}" << std::endl;
		charter->printPathToPrompt(charter->createPath(picks[i].getDNA()));
	}
	return picks;
}
// Mutation
bool Generation::mutagen() {
	return rng::generateNumber(MUTACHANSE) + 1 == 1;
}
// Breeding
int Generation::middlepoint(int a, int b) {
	if (a > b) {
		return int(b + ((a - b) / 2));
	}
	else if (a == b) {
		return a;
	}
	return middlepoint(b, a);
}
Coordinates Generation::mixGenes(Coordinates a, Coordinates b) {
	Coordinates c;
	// Gene mixing
	c.column = middlepoint(a.column, b.column);
	c.row = middlepoint(a.row, b.row);
	// Shift genes (random element)
	int n = rng::generateNumber(2) - 1;	// Range -1 to 1
	c.column += n;
	if (c.column < 0)
		c.column = 0;
	else if (c.column > charter->getWidth() - 1)
		c.column = charter->getWidth() - 1;
	n = rng::generateNumber(2) - 1;	// Range -1 to 1
	c.row += n;
	if (c.row < 0)
		c.row = 0;
	else if (c.row > charter->getHeight() - 1)
		c.row = charter->getHeight() - 1;
	return c;
}
std::vector<Coordinates> Generation::breed(Individual a, Individual b) {
	std::vector<Coordinates> offspring;
	std::vector<Coordinates> strandA = a.getDNA();
	std::vector<Coordinates> strandB = b.getDNA();
	// Asume uniformity of genes
	offspring.push_back(strandA[0]);
	for (unsigned int index = 1; index < strandA.size() - 1; ++index) {
		// For each "pair", mix
		offspring.push_back(mixGenes(strandA[index], strandA[index]));
	}
	offspring.push_back(strandA.back());
	return offspring;
}