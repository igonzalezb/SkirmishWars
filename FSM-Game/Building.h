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
	//string cp;
			//HACER: el parser que lee la info del xml tiene quqe guardar el cp como int (con stoi)
	string cp; //HACER que arranque el del HQ en 8 y el de los demas en 4!! (puede ser que ya este hecho al parsear el XML)
	string name;
	string path;
	string type;
	TeamColor team;
	bool fogOfWar;	//FIJARSE DONDE METERLO

public:
	Building();
	//Building(string cp, string name, string path, string type, string team);
	Building(int cp, string name, string path, string type, string team);
	~Building();
	//void setCp(string cp);
	void setCp(int cp);
	void setPath(string path);
	void setName(string name);
	//string getCp();
	int getCp();
	string getPath();
	string getName();
	void setTeam(TeamColor team);
	TeamColor getTeam();
	string getType();
	void setType(string type);
	void removeFog();
};