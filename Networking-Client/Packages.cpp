
//////////////// !!!!!!!!!!!!!!!!!!
//agregar las cosas que se tienen que recibir, por ejemplo el nombre, las coordenadas, etc


#include "Packages.h"
#include "Networking.h"
#include <fstream>

#include <string>		//VER que hacer con todos estos includes (si dejar aca o no)
#include <sstream>
#include <vector>
#include <iostream>
#include "windows.h"
#include <iterator>



void Ack::setPackage()
{
	//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)ACK); //en vez de ACK podria poner code. (idem para los otros packages)
}

void Name::setPackage()
{
	//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)NAME); //en vez de NAME podria poner code.
}

void NameIs::setPackage()
{
	string myName = "Malena0123456789w"; //RECIBIR NOMBRE!!!

										 //std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)NAME_IS); //sin el (MYBYTE) anda igual que con.my 
	package.push_back((unsigned char)myName.size());
#ifdef DEBUG
	std::cout << myName.size() << std::endl;
#endif // DEBUG
	//la siguiente linea equivale a la de arriba, pero dejo la de arriba para asegurarme el unsigned char (aunque se cumple en la de abajo)
	//package.push_back(myName.size());//guarda el tamaño en asci (lo lee como en hexa) ej:41 int lo toma como 0x29
	std::copy(myName.begin(), myName.end(), std::back_inserter(package));
}

void MapIs::setPackage()
{ //ANDA
	string myMapsName = "hola_soy_el_mapa_soy_el_mapa"; //RECIBIR NOMBRE!!! sin extension.csv
	unsigned int checksum = 41; //RECIBIR VALOR!!! es un int (contador) que se guarda con la linea de abajo como un char para que este en hexa.

								//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)MAP_IS); //1 byte con el encabezado MAP_IS en hexa
	package.push_back((unsigned char)myMapsName.size()); //tamaño del nombre del mapa
	std::copy(myMapsName.begin(), myMapsName.end(), std::back_inserter(package));
	package.push_back((unsigned char)checksum);
}

void YouStart::setPackage()
{
	//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)YOU_START);
}

void IStart::setPackage()
{
	//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)I_START);
}

void Move::setPackage()
{
	//ejemplos de valores en variables:
	MYBYTE filaOrigen = 0x00; //RECIBIR FILA DE ORIGEN (entre 0x00 y 0x0C)
	MYBYTE columnaOrigen = 0x42; //RECIBIR COLUMNA  (entre 0x41 y 0x50)
	MYBYTE filaDestino = 0x0C; //RECIBIR FILA DESTINO (entre 0x00 y 0x0C)
	MYBYTE columnaDestino = 0x041; //RECIBIR (entre 0x41 y 0x50)

								   //std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)MOVE);			//byte 1
	package.push_back((MYBYTE)filaOrigen);		//byte 2
	package.push_back((MYBYTE)columnaOrigen);	//byte 3
	package.push_back((MYBYTE)filaDestino);		//byte 4
	package.push_back((MYBYTE)columnaDestino);	//byte 5
}

void Purchase::setPackage()//ANDA
{
	string unidad = "infantry"; //RECIBIR EN MINUSCULA nombre de unidad que compro
	MYBYTE fila = 0x0C;			//RECIBIR fila donde quiero poner la unidad (entre 0x00 y 0x0C)
	MYBYTE columna = 0x41;		//RECIBIR columna donde quiero poner la unidad (entre 0x41 y 0x50)

	string unidadLetras1y2 = unidad.substr(0, 2); //agarro las dos primeras letras del nombre de la unidad
												  //std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)PURCHASE);			//byte 1
	std::copy(unidadLetras1y2.begin(), unidadLetras1y2.end(), std::back_inserter(package));	//bytes 2 y 3 (2 primeras letras de unidad)
	package.push_back((MYBYTE)fila);				//byte 4
	package.push_back((MYBYTE)columna);				//byte 5
}

void Attack::setPackage()
{	//ejemplos de valores en variables:
	MYBYTE filaOrigen = 0x00; //RECIBIR FILA DE unidad atacante (entre 0x00 y 0x0C)
	MYBYTE columnaOrigen = 0x42; //RECIBIR COLUMNA de unidad atacante  (entre 0x41 y 0x50)
	MYBYTE filaDestino = 0x0C; //RECIBIR FILA DESTINO unidad atacada (entre 0x00 y 0x0C)
	MYBYTE columnaDestino = 0x041; //RECIBIR columna atacada(entre 0x41 y 0x50)
	MYBYTE dado = 0x03;	//RECIBIR valor del dado (entre 00x0 y 00x6)

						//std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)ATTACK);			//byte 1: encabezado
	package.push_back((MYBYTE)filaOrigen);		//byte 2
	package.push_back((MYBYTE)columnaOrigen);	//byte 3
	package.push_back((MYBYTE)filaDestino);		//byte 4
	package.push_back((MYBYTE)columnaDestino);	//byte 5
}

void Pass::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)PASS);			//byte 1: encabezado
}

void YouWon::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)YOU_WON);			//byte 1: encabezado
}

void PlayAgain::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)PLAY_AGAIN);		//byte 1: encabezado
}

void GameOver::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)GAME_OVER);		//byte 1: encabezado
}

void Error_::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)ERROR_);			//byte 1: encabezado
}

void Quit::setPackage()
{
	std::vector<char> package;
	package.clear();
	package.push_back((MYBYTE)QUIT);			//byte 1: encabezado
}
