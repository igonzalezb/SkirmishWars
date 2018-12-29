#pragma once
#include <iostream>
#include <list>
#include <string>

using namespace std;

typedef enum { WHITE, RED, BLUE, YELLOW, GREEEN } TeamColor;

//#define HQ(x)		"q"#x
//#define CITY(x)		"c"#x
//#define FACTORY(x)	"m"#x

class Building
{
private:
	string cp;
	string name;
	string path;
	string type;
	TeamColor team;
	bool fogOfWar;

public:
	Building();
	Building(string cp, string name, string path, string type, string team);
	~Building();
	void setCp(string cp);
	void setPath(string path);
	void setName(string name);
	string getCp();
	string getPath();
	string getName();
	void setTeam(TeamColor team);
	TeamColor getTeam();
	string getType();
	void setType(string type);
	void removeFog();
};