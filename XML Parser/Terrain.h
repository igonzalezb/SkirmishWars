#pragma once
#include <iostream>
#include <list>
#include <string>

using namespace std;

class Terrain
{
private:
	string name;
	string path;
public:
	Terrain();
	~Terrain();
	void setPath(string path);
	void setName(string name);
	string getPath();
	string getName();
};