#pragma once
#include <string>
using namespace std;

class Star
{
private:
	string name;
	string constellation;
	int RA;
	int Dec;
	int diameter;
public:
	Star(string name_, string constellation_, int RA_, int Dec_, int diameter_):
		name{name_}, constellation{constellation_}, RA{RA_}, Dec{Dec_}, diameter{diameter_}{}
	~Star(){}

	string getName() { return name; }
	string getConstellation() { return constellation; }
	int getRA() { return RA; }
	int getDec() { return Dec; }
	int getDiameter() { return diameter; }
	string toStd();
	void setName(string n) { name = n; }
	void setRa(int r) { RA = r; }
	void setDec(int dec) { Dec = dec; }
	void setDiam(int d) { diameter = d; }
};