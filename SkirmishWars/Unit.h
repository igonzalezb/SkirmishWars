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

//CREO QUE NO ES LA MANERA MAS EFICIENTE... POR LAS DUDAS NO LO TERMINE DE COMPLETAR


//struct terreinModifier {
//	int dice;
//	int initialDamage;
//
//};
//enum terreinType{mountain, building, tree, grass, streetORwater};
//
//terreinModifier InitialDamage(int FP, int defense, terreinType terrein)
//{
//	terreinModifier r;
//
//	switch (FP - defense) {
//	case 13: {
//		switch (terrein) {
//		case(mountain): {r.initialDamage = 8;		r.dice = false;		break;}
//		}
//	}
//	case 12: {
//		switch (terrein) {
//		case(mountain): {r.initialDamage = 7;		r.dice = 3;			break;}
//		}
//	}
//	case 11: {
//		switch (terrein) {
//		case(mountain): {r.initialDamage = 6;		r.dice = 5;			break;}
//		case(building): {r.initialDamage = 8;		r.dice = false;		break;}
//		}
//	}
//	case 10: {
//		switch (terrein) {
//		case(mountain): {r.initialDamage = 6;		r.dice = 2;			break;}
//		case(building): {r.initialDamage = 7;		r.dice = 2;			break;}
//		case(tree): {r.initialDamage = 8;		r.dice = false;		break;}
//		}
//	}
//	case 9: {
//		switch (terrein) {
//		case(mountain): {r.initialDamage = 5;		r.dice = 4;			break;}
//		case(building): {r.initialDamage = 6;		r.dice = 4;			break;}
//		case(tree): {r.initialDamage = 7;		r.dice = 4;			break;}
//		case(grass): {r.initialDamage = 8;		r.dice = false;		break;}
//		}
//	}
//	case 8: {
//		switch (terrein) {
//		case(mountain): {r.initialDamage = 5;		r.dice = 1;			break;}
//		case(building): {r.initialDamage = 5;		r.dice = 5;			break;}
//		case(tree): {r.initialDamage = 6;		r.dice = 5;			break;}
//		case(grass): {r.initialDamage = 7;		r.dice = 4;		break;}
//		case(streetORwater): {r.initialDamage = 8;		r.dice = false;		break;}
//		}
//	}
//	default: {r.initialDamage = false;		r.dice = false;		break;}
//	}
//
//	return r;
//}
