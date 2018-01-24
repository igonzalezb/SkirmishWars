#pragma once
#include <iostream>
#include <list>
#include <string>

using namespace std;


class Building
{
private:
	string hp;
	string name;
	string path;
public:
	Building();
	~Building();
	void setHp(string hp);
	void setPath(string path);
	void setName(string name);
	string getHp();
	string getPath();
	string getName();
};