#pragma once
#include "Astronomer.h"
#include "Star.h"
#include <vector>
#include <string>
using namespace std;

class Service
{
private:
	vector<Astronomer> astronomers;
	vector<Star> stars;
	void load_from_file();
public:
	Service() { load_from_file(); }
	~Service(){}

	vector<Astronomer> getAstronomers() { return astronomers; }
	vector<Star> getStars() { return stars; }
	vector<Star> sortByConstellation();
	vector<Star> showConstellation(string constellation);
	void addStar(string name, string constellation, int RA, int Dec, int diameter);
	void updateName(string newName, string oldName);
	void updateRa(int newRa, string name);
	void updateDec(int newDec, string name);
	void updateDiameter(int newDiam, string name);
	vector<Star> sortByConstellationAndDiameter();
	void save_to_file();
};