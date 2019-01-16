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
	Networking();
	~Networking(); //Ver cuando llamarlo
	void sendPackage(genericPackage *Pkg);
	bool receivePackage();
	std::vector<char> getInputPackage();
	//errorCodes getErrorCode();
	//std::string getData();
	//std::string getRequestedFile();
	//std::string getErrorMsg();
	unsigned int getBlockNumber(); //VER si va a haber que usarla o no

	void startConnection();
	bool justConnected = 0;

private:
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::socket* serverSocket;
	boost::asio::ip::tcp::acceptor* serverAcceptor;

	//void packageDecode();

	//std::string fileToTransfer;
	opCodes receivedPackageType;
	//std::string data;	//Se almacena la data en caso de recibir DATA
	//std::string errorMsg;
	//errorCodes errorCode;
	unsigned int blockNumber;

	std::vector<char> inputPackage;
};
#endif // !NETWORKING_H

