#include <algorithm>
#include <iostream>

#include "Chart.h"
#include "RNG.h"

const static int DEAFULTVALUE = 5;

using namespace std;

void print(string message) {
	cout << message << endl;
}

Chart::Chart(){
}
Chart::~Chart(){
}
// Manadgment
void Chart::generateMap() {
	generateMap(DEAFULTVALUE, DEAFULTVALUE, DEAFULTVALUE);
}
void Chart::generateMap(int width, int height) {
	generateMap(width, height, DEAFULTVALUE);
}
void Chart::generateMap(int width, int height, int range) {
	chartWidth = width;
	chartHeight = height;
	// Deafult start-goal: From top-left to bottom-right
	Coordinates co;
	co.column = (width - 1) / 2; co.row = 0; startPos = co;
	co.column = (width - 1) / 2; co.row = height - 1; goalPos = co;
	// RNG
	for (int column = 0; column < width; column++) {
		for (int row = 0; row < height; row++) {
			// Create node
			Node n;
			n.coordinates.column = column;
			n.coordinates.row = row;
			n.cost = rng::generateNumber(range) + 1;
			// Archive node
			charter[column][row] = n;
		}
	}
	return;
}
void Chart::setStartGoal(Coordinates start, Coordinates goal){
	startPos = start;
	goalPos = goal;
}
// Data fetching
int Chart::getWidth() const{
	return chartWidth;
}
int Chart::getHeight() const{
	return chartHeight;
}
Coordinates Chart::getStart() const{
	return startPos;
}
Coordinates Chart::getGoal() const{
	return goalPos;
}
// Evaluation
void bresenhamLine(Coordinates start, Coordinates end, vector<Coordinates>& path) {
	/* Bresenham's line algorithm */
	// https://gist.github.com/bert/1085538
	int x = start.column;
	int y = start.row;

	int dx = abs(end.column - start.column), sx = start.column < end.column ? 1 : -1;
	int dy = -abs(end.row - start.row), sy = start.row < end.row ? 1 : -1;
	int err = dx + dy, e2; /* error value e_xy */

	for (;;) {  /* loop */
		Coordinates c;
		c.column = x;
		c.row = y;
		path.push_back(c);

		if (x == end.column && y == end.row) break;
		e2 = 2 * err;
		if (e2 >= dy) { err += dy; x += sx; } /* e_xy+e_x > 0 */
		if (e2 <= dx) { err += dx; y += sy; } /* e_xy+e_y < 0 */
	}
}
vector<Coordinates> Chart::createPath(vector<Coordinates>& nodes){
	vector<Coordinates> path;
	Coordinates end;
	Coordinates start = nodes[0];
	for (int i = 1; i < nodes.size(); i++) {
		end = nodes[i];

		bresenhamLine(start, end, path);

		start = end;
	}
	return path;
}
int Chart::evaluatePath(std::vector<Coordinates>& path){
	int value = 0;
	// Going though all listet coordinates
	for each (Coordinates c in path){	
		value += fetchCost(c);
	}
	return value;
}

// I/O commands
void Chart::printChartToPrompt() {
	if (printPrerequisite()) {
		for (int i = 0; i < chartWidth - 1; i++) {
			cout << "=";
		}
		cout << " Map ";
		for (int i = 0; i < chartWidth - 1; i++) {
			cout << "=";
		}
		cout << endl;
		for (int column = 0; column < chartWidth; column++) {
			cout << "|";
			for (int row = 0; row < chartHeight; row++) {
				// Fetch node
				Coordinates c;
				c.column = column;
				c.row = row;
				cout << " " << fetchCost(c);
			}
			cout << " |" << endl;
		}
		for (int i = 0; i < chartWidth*2+3; i++) {
			cout << "=";
		}
		cout << endl << " W: " << chartWidth << " H: " << chartHeight << endl;
	}
	else {
		cout << "Ops, prerequisite to printing path not met;" << endl;
		return;
	}
}
void Chart::printChartToFile(string destination) {
	if (printPrerequisite()) {
		
	}
	else {
		cout << "Ops, prerequisite to printing chart not met;" << endl;
		return;
	}
}
// Create empty "screen buffer"
map<int, map<int, string>> emptyBuffer(int width, int height) {
	map<int, map<int, string>> buffer;
	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			buffer[i][j] = "[_]";
		}
	}
	return buffer;
}
void Chart::printPathToPrompt(vector<Coordinates>& path){
	if (printPrerequisite()) {
		map<int, map<int, string>> buffer = emptyBuffer(chartWidth, chartHeight);
		for each(Coordinates c in path) {
			buffer[c.row][c.column] = "[#]";	// Rotating representation
		}										// so it looks "right"
		// START \ GOAL
		buffer[startPos.row][startPos.column] = "[S]";
		buffer[goalPos.row][goalPos.column] = "[G]";
		// print out path
		for (int i = 0; i < chartWidth; i++) {
			cout << " ";
			for (int j = 0; j < chartHeight; j++) {
				cout << buffer[i][j];
			}
			cout << endl;
		}
	}
	else {
		cout << "Ops, prerequisite to printing path not met;" << endl;
		return;
	}
}
void Chart::printPathToFile(vector<Coordinates>& path, string destination) {
	if (printPrerequisite()) {

	}
	else {
		cout << "Ops, prerequisite to printing path not met;" << endl;
		return;
	}
}
// Help functions
bool Chart::printPrerequisite(){
	if (!charter.empty())
		return true;
	else
		return false;
}

void Chart::clearCharter(){
	charter.clear();
}

int Chart::fetchCost(Coordinates coords){
	return charter[coords.column][coords.row].cost;
}