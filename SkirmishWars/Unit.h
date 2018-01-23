#pragma once

#include "Map.h"


#include <string>
using namespace std;


//----- UNIT TYPE [CODES] -----
#define INFANTRIES	"in"#x
#define MECHS		"me"#x
#define ROCKETS		"ro"#x
#define RECONS		"re"#x
#define APCS		"ap"#x
#define ANTIAIR		"aa"#x
#define ARTILLERY	"ar"#x
#define TANKS		"ta"#x
#define MEDTANKS	"mt"#x

//enum unit{infantry, mech, rocket, recon, APC, antiair, artillery, tank, medtank }unitType;

// Tabla de terrein defense modifiers!!!!!!!


struct shape{
	int moon;
	int star;
	int square;
	int triangle;
	int circle;
};
//moverse sobre HQ y buildings cuesta 1MP... 
struct terrein {
	int grass;
	int street;
	int tree;
	int water;
	int mountain;
};

class Unit
{
public:
	Unit();
	~Unit();

	//Attack Unit
	//Attack Building
	//Move
	//Defend

private:

	shape unitShape;	// moon, star, square, triangle, circle
	string unitType;   // foot, wheel, tread  
	TeamColor team;

	int cost;

	int HP;  // HealthPoints 
	//int attackDamage;
	int defense; // Puntos de defensa de la unidad

	int MP;  // Movement Points
	int Range; // Rango de alcance para el ataque

	shape FP; // FirePoints para la unidad SIN reducir
	shape FPreduced; // FirePoints para la unidad reducida (si HP<5 la unidad esta reducida)

	terrein terreinMovementCost;


};