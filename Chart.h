#pragma once

#include <vector>
#include <string>
#include <map>

struct Coordinates {
	int column;
	int row;
};
struct Node {
	Coordinates coordinates;
	int cost;
};

/* Only suport NxN matrices with only one int for each position */
class Chart {
public:
	Chart();
	~Chart();
	// Manadgment
	void generateMap();
	void generateMap(int width, int height);
	void generateMap(int width, int height, int range);
	void setStartGoal(Coordinates start, Coordinates goal);
	// Data fetching
	int getWidth() const;
	int getHeight() const;
	Coordinates getStart() const;
	Coordinates getGoal() const;
	// Evaluation
	std::vector<Coordinates> createPath(std::vector<Coordinates>& nodes);
	int evaluatePath(std::vector<Coordinates>& path);
	// I/O commands
	void printChartToPrompt();
	void printChartToFile(std::string destination);
	void printPathToPrompt(std::vector<Coordinates>& path);
	void printPathToFile(std::vector<Coordinates>& path, std::string destination);
private:
	// Chart[x][y] coordinate to find spesific node
	std::map<int, std::map<int, Node>> charter;
	int chartWidth;
	int chartHeight;
	Coordinates startPos;
	Coordinates goalPos;
	// help functions
	bool printPrerequisite();
	void clearCharter();
	int fetchCost(Coordinates coords);
};

