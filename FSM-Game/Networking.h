#ifndef NETWORKING_H
#define NETWORKING_H

#define DEBUG true

#include <iostream>
#include <string>
#include <exception>
#include <array>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <Windows.h> //ver si sacar
#include "Packages.h"

#define CONNECTION_PORT 69	//puerto TFTP
#define PACKAGE_MAX_SIZE 516	

typedef char MYBYTE;



class Networking
{
public:
	Networking(std::string _serverAddress);//PARA CUANDO ES CLIENTE!!!
	Networking();//PARA CUANDO ES SERVER!!!
	~Networking(); //Ver cuando llamarlo
	std::string getServerAddres();//PARA CUANDO ES CLIENTE
	void sendPackage(genericPackage *Pkg);
	bool receivePackage();
	std::vector<char> getInputPackage();
	unsigned int getBlockNumber(); //VER si va a haber que usarla o no

	void startConnection();
	bool justConnected = 0;

private:
	//siguientes 3 lineas son  para server
	boost::asio::io_service*  IO_handler;
	//boost::asio::ip::tcp::socket* serverSocket;//PARA SERVER PERO IGUAL AL DEL CLIENT. PONER NOMBRE EN COMUN
	boost::asio::ip::tcp::acceptor* serverAcceptor;//PARA SERVER!!!
	
	boost::asio::ip::tcp::socket* mySocket;
	
	//siguientes 3 lineas son para client
	//boost::asio::ip::tcp::socket* clientSocket; //PARA CLIENT PERO ES IGUAL AL DE DOS LINEAS MAS ARRIBA (SE PUEDE SACAR Y PONER NOMBRE EN COMUN)
	boost::asio::ip::tcp::resolver* clientResolver; //PARA CUANDO ES CLIENT!!!
	boost::asio::ip::tcp::resolver::iterator endpoint; //PARA CUANDO ES CLIENT!!!

	std::string serverAddress; //PARA CUANDO ES CLIENT
	opCodes receivedPackageType;
	unsigned int blockNumber;
	std::vector<char> inputPackage;

	bool IamClient;
};
#endif // !NETWORKING_H

