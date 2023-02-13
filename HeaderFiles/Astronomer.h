#pragma once
#include <string>
using namespace std;

class Astronomer
{
private:
	string name;
	string constellation;
public:
	Astronomer(const string& name_, const string& constellation_): name{name_}, constellation{constellation_}{}
	~Astronomer() {}

	string getName() { return name; }
	string getConstellation() { return constellation; }
	string toStd() { return name + " " + constellation; }
};
