#include "Service.h"
#include <fstream>
#include <sstream>
#include <algorithm>

void Service::load_from_file()
{
	ifstream f1("Astronomers.txt");
	string line;
	while (getline(f1, line))
	{
		string name;
		string constellation;
		string current;
		stringstream linestream(line);
		int nr = 0;
		while (getline(linestream, current, ' '))
		{
			if (nr == 0)
				name = current;
			else
				constellation = current;
			nr++;
		}
		Astronomer a(name, constellation);
		astronomers.push_back(a);
	}

	ifstream f2("Stars.txt");
	while (getline(f2, line))
	{
		string name;
		string constellation;
		int RA = 0;
		int Dec = 0;
		int diameter = 0;
		string current;
		stringstream linestream(line);
		int nr = 0;
		while (getline(linestream, current, ' '))
		{
			if (nr == 0)
				name = current;
			if(nr == 1)
				constellation = current;
			if (nr == 2)
				RA = stoi(current);
			if(nr == 3)
				Dec = stoi(current);
			if(nr == 4)
				diameter = stoi(current);
			nr++;
		}
		Star s(name, constellation, RA, Dec, diameter);
		stars.push_back(s);
	}
}

bool cmpConstellation(Star s1, Star s2)
{
	return s1.getConstellation() < s2.getConstellation();
}

bool cmpDiameter(Star s1, Star s2)
{
	return s1.getDiameter() < s2.getDiameter();
}

vector<Star> Service::sortByConstellation()
{
	vector<Star> v = stars;
	sort(v.begin(), v.end(), cmpConstellation);
	return v;
}

vector<Star> Service::showConstellation(string constellation)
{
	vector<Star> v;
	for (auto s : stars)
	{
		if (s.getConstellation() == constellation)
			v.push_back(s);
	}
	return v;
}

void Service::addStar(string name, string constellation, int RA, int Dec, int diameter)
{
	if (name == "")
		throw(1);
	for (auto s : stars)
		if (s.getName() == name)
			throw(1);
	Star s(name, constellation, RA, Dec, diameter);
	stars.push_back(s);
}

void Service::updateName(string newName, string oldName)
{
	if (newName == "")
		throw(1);
	for (auto s : stars)
		if (s.getName() == newName)
			throw(1);
	for (int i = 0; i < stars.size(); i++)
		if (stars[i].getName() == oldName)
			stars[i].setName(newName);
}

void Service::updateRa(int newRa, string name)
{
	for (int i = 0; i < stars.size(); i++)
		if (stars[i].getName() == name)
			stars[i].setRa(newRa);
}

void Service::updateDec(int newDec, string name)
{
	for (int i = 0; i < stars.size(); i++)
		if (stars[i].getName() == name)
			stars[i].setDec(newDec);
}

void Service::updateDiameter(int newDiam, string name)
{
	if (newDiam <= 10)
		throw(1);
	for (int i = 0; i < stars.size(); i++)
		if (stars[i].getName() == name)
			stars[i].setDiam(newDiam);
}

vector<Star> Service::sortByConstellationAndDiameter()
{
	vector<Star> v = stars;
	sort(v.begin(), v.end(), cmpConstellation);
	sort(v.begin(), v.end(), cmpDiameter);
	return v;
}

void Service::save_to_file()
{
	vector<Star> v = sortByConstellationAndDiameter();
	ofstream f("Stars.txt");
	for (auto s : v)
	{
		f << s.toStd() << endl;
	}
}
