#include <cstdlib>
#include <iostream>

#include "RNG.h"
#include "Chart.h"
#include "Generation.h"

using namespace std;

/*
	TODO: 
*/

int main(void) {
	// Setup
	int size = 1000;
	int prize = 5;
	int generations = 20;

	int mapSize = 30;
	int mapRange = 5;

	rng::initalize();

	cout << endl << " === Start ===" << endl;
	Chart chart;
	Generation gen(&chart);
	// Map generation
	cout << endl << " === Map Generation ===" << endl;
	chart.generateMap(mapSize, mapSize, mapRange);
	chart.printChartToPrompt();

	Individuals stock;
	// Evolution
	cout << endl << " === Generation Test ===" << endl;
	cout << endl << " === Generation 0 ===" << endl;
	stock = gen.freshBatch(size, prize);
	for (int i = 0; i < generations; i++) {
		cout << " === Generation " << i+1 << " ===" << endl;
		stock = gen.breedingBatch(size, prize, stock);
	}
	// Post report
	cout << endl << " === Winner ===" << endl;
	chart.printChartToPrompt();
	cout << " " << generations << " generations of " << size << " individuals" << endl;
	cout << " The top " << prize << " of individuals were picked for futher breeding" << endl;
	Individual winner = stock[0];
	vector<Coordinates> path = chart.createPath(winner.getDNA());
	std::cout << " Fittness " << winner.fitness << ": " << "{ ";
	for each(Coordinates c in winner.getDNA()) {
		std::cout << "[" << c.column << "," << c.row << "] ";
	}
	cout << "}" << endl;
	chart.printPathToPrompt(path);
	cout << endl << " === End ===" << endl;
	cout << endl << " Press any key to terminate promt...";
	getchar();
	return 0;
}