

#include "Packages.h"
#include "Networking.h"
#include <fstream>
#include <string>		
#include <sstream>
#include <vector>
#include <iostream>
#include <iterator>



void Ack::setPackage()
{
	package.clear();
	package.push_back((MYBYTE)OP_ACK); 
}

void Name::setPackage()
{
	package.clear();
	package.push_back((MYBYTE)OP_NAME);
}

 NameIs::NameIs(string nameIs) 
 { 
	 code = OP_NAME_IS; 
	 this->nameIs = nameIs; 
 }

void NameIs::setPackage()
{
	package.clear();
	package.push_back((MYBYTE)OP_NAME_IS); //sin el (MYBYTE) anda igual que con.my 
	package.push_back((unsigned char)nameIs.size());
#ifdef DEBUG
	std::cout << nameIs.size() << std::endl;
#endif // DEBUG
	std::copy(nameIs.begin(), nameIs.end(), std::back_inserter(package));
}

MapIs::MapIs(string mapName,char checksum)
{
	code = OP_MAP_IS; 
	this->mapName = mapName; 

	this->checksum = checksum;
}

void MapIs::setPackage()
{ 
	package.clear();
	package.push_back((MYBYTE)OP_MAP_IS);					 //1 byte con el encabezado MAP_IS en hexa
	package.push_back((unsigned char)mapName.size());		 //tamaño del nombre del mapa
	std::copy(mapName.begin(), mapName.end(), std::back_inserter(package));
	package.push_back((unsigned char)checksum);
}

void YouStart::setPackage()
{
	package.clear();
	package.push_back((MYBYTE)OP_YOU_START);
}

void IStart::setPackage()
{
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
	MYBYTE filaOrigen = (MYBYTE)attacker_i;
	MYBYTE columnaOrigen = ((MYBYTE)attacker_j)+ 0x41;
	MYBYTE filaDestino = (MYBYTE)defender_i;
	MYBYTE columnaDestino = ((MYBYTE)defender_j) + 0x41;

	package.clear();
	package.push_back((MYBYTE)OP_MOVE);			//byte 1
	
	package.push_back((MYBYTE)filaOrigen);		//byte 2
	package.push_back((MYBYTE)columnaOrigen);	//byte 3
	package.push_back((MYBYTE)filaDestino);		//byte 4
	package.push_back((MYBYTE)columnaDestino);	//byte 5
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
	string unidad = unit;
	MYBYTE fila = (MYBYTE)defender_i;
	MYBYTE columna = ((MYBYTE)defender_j) + 0x41;

	string unidadLetras1y2 = unidad.substr(0, 2);	//agarro las dos primeras letras del nombre de la unidad

	package.clear();
	package.push_back((MYBYTE)OP_PURCHASE);			//byte 1
	std::copy(unidadLetras1y2.begin(), unidadLetras1y2.end(), std::back_inserter(package));	//bytes 2 y 3 (2 primeras letras de unidad)

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
		
	MYBYTE _dado = (MYBYTE)dado;	//RECIBE valor del dado (entre 00x0 y 00x6)

	package.clear();
	package.push_back((MYBYTE)OP_ATTACK);		//byte 1: encabezado
	package.push_back((MYBYTE)filaOrigen);		//byte 2
	package.push_back((MYBYTE)columnaOrigen);	//byte 3
	package.push_back((MYBYTE)filaDestino);		//byte 4
	package.push_back((MYBYTE)columnaDestino);	//byte 5
	package.push_back((MYBYTE)_dado);
}

void Pass::setPackage()
{
	cout << "envia paquete PASS" << endl;
	package.clear();
	package.push_back((MYBYTE)OP_PASS);			//byte 1: encabezado
	cout << "OPPPPPCODE PASS:"<<OP_PASS << endl;
}

void YouWon::setPackage()
{
	cout << "se envioo el paquete you won" << endl;
	package.clear();
	package.push_back((MYBYTE)OP_YOU_WON);			//byte 1: encabezado
}

void PlayAgain::setPackage()
{
	cout << "se envioo el paquete play again" << endl;
	package.clear();
	package.push_back((MYBYTE)OP_PLAY_AGAIN);		//byte 1: encabezado
}

void GameOver::setPackage()
{
	cout << "se envioo el paquete gameover" << endl;
	package.clear();
	package.push_back((MYBYTE)OP_GAME_OVER);		//byte 1: encabezado
}

void Error_::setPackage()
{
	cout << "envio paquete de error!!!!!!!!!" << endl;
	package.clear();
	package.push_back((MYBYTE)OP_ERROR);			//byte 1: encabezado
}

void Quit::setPackage()
{
	package.clear();
	package.push_back((MYBYTE)OP_QUIT);				//byte 1: encabezado
}

genericPackage::genericPackage()
{
}

genericPackage::~genericPackage()
{
}