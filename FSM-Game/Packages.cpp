
//////////////// !!!!!!!!!!!!!!!!!!
//agregar las cosas que se tienen que recibir, por ejemplo el nombre, las coordenadas, etc


#include "Packages.h"
#include "Networking.h"
#include <fstream>

#include <string>		//VER que hacer con todos estos includes (si dejar aca o no)
#include <sstream>
#include <vector>
#include <iostream>
//#include "windows.h"
#include <iterator>



void Ack::setPackage()
{
	//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_ACK); //en vez de ACK podria poner code. (idem para los otros packages)
}

void Name::setPackage()
{
	//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_NAME); //en vez de NAME podria poner code.
}

 NameIs::NameIs(string nameIs) 
 { 
	 code = OP_NAME_IS; 
	 this->nameIs = nameIs; 
 }

void NameIs::setPackage()
{
	//string myName = "Malena0123456789w"; //RECIBIR NOMBRE!!!										 //std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_NAME_IS); //sin el (MYBYTE) anda igual que con.my 
	package.push_back((unsigned char)nameIs.size());
#ifdef DEBUG
	std::cout << nameIs.size() << std::endl;
#endif // DEBUG
	//la siguiente linea equivale a la de arriba, pero dejo la de arriba para asegurarme el unsigned char (aunque se cumple en la de abajo)
	//package.push_back(myName.size());//guarda el tamaño en asci (lo lee como en hexa) ej:41 int lo toma como 0x29
	std::copy(nameIs.begin(), nameIs.end(), std::back_inserter(package));
}

MapIs::MapIs(string mapName)
{
	code = OP_MAP_IS; 
	this->mapName = mapName; 
}

void MapIs::setPackage()
{ //ANDA
	//string myMapsName = "hola_soy_el_mapa_soy_el_mapa"; //RECIBIR NOMBRE!!! sin extension.csv
	unsigned int checksum = 41; //RECIBIR VALOR!!! es un int (contador) que se guarda con la linea de abajo como un char para que este en hexa.

								//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_MAP_IS); //1 byte con el encabezado MAP_IS en hexa
	package.push_back((unsigned char)mapName.size()); //tamaño del nombre del mapa
	std::copy(mapName.begin(), mapName.end(), std::back_inserter(package));
	package.push_back((unsigned char)checksum);
}

void YouStart::setPackage()
{
	//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_YOU_START);
}

void IStart::setPackage()
{
	//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_I_START);
}

Move::Move(int attacker_i, int attacker_j, int defender_i, int defender_j)
{ 
	code = OP_MOVE; 
	this->attacker_i = attacker_i;
	this->attacker_j = attacker_j;
	this->defender_i = defender_i;
	this->defender_j = defender_j;
}

void Move::setPackage()
{
	//ejemplos de valores en variables

	//MYBYTE filaOrigen = 0x00; //RECIBIR FILA DE ORIGEN (entre 0x00 y 0x0C)
	//MYBYTE columnaOrigen = 0x42; //RECIBIR COLUMNA  (entre 0x41 y 0x50)
	//MYBYTE filaDestino = 0x0C; //RECIBIR FILA DESTINO (entre 0x00 y 0x0C)
	//MYBYTE columnaDestino = 0x041; //RECIBIR (entre 0x41 y 0x50)

	MYBYTE filaOrigen = (MYBYTE)attacker_i;
	MYBYTE columnaOrigen = ((MYBYTE)attacker_j)+ 0x41;
	MYBYTE filaDestino = (MYBYTE)defender_i;
	MYBYTE columnaDestino = ((MYBYTE)defender_j) + 0x41;

								   //std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_MOVE);			//byte 1
	
	package.push_back((MYBYTE)filaOrigen);		//byte 2
	package.push_back((MYBYTE)columnaOrigen);	//byte 3
	package.push_back((MYBYTE)filaDestino);		//byte 4
	package.push_back((MYBYTE)columnaDestino);	//byte 5
	
	//package.push_back((MYBYTE)//Info->gameInterface->getAttacker().i);		//byte 2
	//package.push_back((MYBYTE)attacker_j);	//byte 3
	//package.push_back((MYBYTE));		//byte 4
	//package.push_back((MYBYTE)columnaDestino);	//byte 5

}

Purchase::Purchase(string typeOfUnit, int defender_i_, int defender_j_)
{
	code = OP_PURCHASE;
	this->unit = typeOfUnit;
	this->defender_i = defender_i_;
	this->defender_j = defender_j_;
}

void Purchase::setPackage()//ANDA
{
	//string unidad = "infantry"; //RECIBIR EN MINUSCULA nombre de unidad que compro
	//MYBYTE fila = 0x0C;			//RECIBIR fila donde quiero poner la unidad (entre 0x00 y 0x0C)
	//MYBYTE columna = 0x41;		//RECIBIR columna donde quiero poner la unidad (entre 0x41 y 0x50)

	string unidad = unit;
	MYBYTE fila = (MYBYTE)defender_i;
	MYBYTE columna = ((MYBYTE)defender_j) + 0x41;

	string unidadLetras1y2 = unidad.substr(0, 2); //agarro las dos primeras letras del nombre de la unidad
												  //std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_PURCHASE);			//byte 1
	std::copy(unidadLetras1y2.begin(), unidadLetras1y2.end(), std::back_inserter(package));	//bytes 2 y 3 (2 primeras letras de unidad)
	//std::copy(unidad.begin(), unidad.end(), std::back_inserter(package));	//bytes 2 y 3 (2 primeras letras de unidad)
	package.push_back((MYBYTE)fila);				//byte 4
	package.push_back((MYBYTE)columna);				//byte 5

	//PARA VER QUE SE MANDA:
	string package_string;
	for (char c : package) {
		package_string.push_back(c);
	}
	cout << "PACKAGE QUE SE ENVIA: " << package_string << endl;
	cout << "HOLA222!! COORDENADA ENVIADA DEL DEFENDER (defender_):  (I=  " << defender_i << "; J=" << defender_j << "  )";
	cout << "HOLA222!! COORDENADA ENVIADA DEL DEFENDER ((MYBYYTE)):  (I=  " << (int)fila << "; J=" << (int)columna << "  )";

}

Attack::Attack(int attacker_i, int attacker_j, int defender_i, int defender_j, int dado) 
{ 
	code = OP_ATTACK;
	this->attacker_i = attacker_i;
	this->attacker_j = attacker_j;
	this->defender_i = defender_i;
	this->defender_j = defender_j;
	this->dado = dado;
}

void Attack::setPackage()
{	
	MYBYTE filaOrigen = (MYBYTE)attacker_i;
	MYBYTE columnaOrigen = ((MYBYTE)attacker_j) + 0x41;
	MYBYTE filaDestino = (MYBYTE)defender_i;
	MYBYTE columnaDestino = ((MYBYTE)defender_j) + 0x41;
		
	MYBYTE _dado = (MYBYTE)dado;	//0x03;	//RECIBIR valor del dado (entre 00x0 y 00x6)

						//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_ATTACK);			//byte 1: encabezado
	package.push_back((MYBYTE)filaOrigen);		//byte 2
	package.push_back((MYBYTE)columnaOrigen);	//byte 3
	package.push_back((MYBYTE)filaDestino);		//byte 4
	package.push_back((MYBYTE)columnaDestino);	//byte 5
	package.push_back((MYBYTE)_dado);
}

void Pass::setPackage()
{
	cout << "envia paquete PASS" << endl;
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_PASS);			//byte 1: encabezado
	cout << "OPPPPPCODE PASS:"<<OP_PASS << endl;
}

void YouWon::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_YOU_WON);			//byte 1: encabezado
}

void PlayAgain::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_PLAY_AGAIN);		//byte 1: encabezado
}

void GameOver::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_GAME_OVER);		//byte 1: encabezado
}

void Error_::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_ERROR);			//byte 1: encabezado
}

void Quit::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)OP_QUIT);			//byte 1: encabezado
}

genericPackage::genericPackage()
{
}

genericPackage::~genericPackage()
{
}