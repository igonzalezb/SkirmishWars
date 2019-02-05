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
#include "Packages.h"

#define CONNECTION_PORT_C "13225"	//puerto TFTP
#define CONNECTION_PORT_S 13225	//puerto TFTP
#define PACKAGE_MAX_SIZE 516	

typedef char MYBYTE;



class Networking
{
public:
	Networking(std::string _serverAddress);	//PARA CUANDO ES CLIENTE
	Networking();		//PARA CUANDO ES SERVER
	~Networking(); 
	std::string getServerAddres();//PARA CUANDO ES CLIENTE
	void sendPackage(genericPackage *Pkg);
	bool receivePackage();
	std::vector<char> getInputPackage();
	unsigned int getBlockNumber();

	void startConnection();
	bool justConnected;
	bool IamClient;
private:
	//siguientes 3 lineas son  para server
	boost::asio::io_service*  s_IO_handler;
	boost::asio::ip::tcp::socket* serverSocket;
	boost::asio::ip::tcp::acceptor* serverAcceptor;
	
	boost::asio::ip::tcp::socket* mySocket;
	
	//siguientes 3 lineas son para client
	boost::asio::io_service*  IO_handler;
	boost::asio::ip::tcp::resolver* clientResolver; //PARA CUANDO ES CLIENT!
	boost::asio::ip::tcp::resolver::iterator endpoint; //PARA CUANDO ES CLIENT!

	std::string serverAddress; //PARA CUANDO ES CLIENT
	opCodes receivedPackageType;
	unsigned int blockNumber;
	std::vector<char> inputPackage;


};
#endif // !NETWORKING_H

