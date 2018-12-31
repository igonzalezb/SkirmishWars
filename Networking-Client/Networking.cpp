
#include "Networking.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <conio.h>

Networking::Networking(std::string _serverAddress) : serverAddress(_serverAddress)
{
	IO_handler = new boost::asio::io_service();
	clientSocket = new boost::asio::ip::tcp::socket(*IO_handler);
	clientResolver = new boost::asio::ip::tcp::resolver(*IO_handler);
}

Networking::~Networking()
{
	clientSocket->close();

	delete clientResolver;
	delete clientSocket;
	delete IO_handler;
}

/*
void Networking::startConnection(const char* host) {
endpoint = clientResolver->resolve(
boost::asio::ip::tcp::resolver::query(host, CONNECTION_PORT));
boost::asio::connect(*clientSocket, endpoint);
}
*/

//ESTA ES LA START CONNECTION QUE VA A IR PERO FALTA CORREGIR LA LINEA DE RESOLVER
void Networking::startConnection()
{
	bool exit;

	endpoint = clientResolver->resolve(
		boost::asio::ip::tcp::resolver::query(serverAddress.c_str(), CONNECTION_PORT));
	do
	{
		exit = true;
		try
		{
			boost::asio::connect(*clientSocket, endpoint);
		}
		catch (const std::exception& e)
		{
			exit = false;
		}
		cout << "HOLA" << endl;
	} while (!exit);
	clientSocket->non_blocking(true);

}


std::string Networking::getServerAddres()
{
	return serverAddress;
}
/*
Networking::Networking()
{
IO_handler = new boost::asio::io_service();
serverSocket = new boost::asio::ip::tcp::socket(*IO_handler);
serverAcceptor = new boost::asio::ip::tcp::acceptor(*IO_handler,
boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), CONNECTION_PORT));
}

Networking::~Networking()
{
serverAcceptor->close();
serverSocket->close();
delete serverSocket;
delete IO_handler;
}

void Networking::startConnection()
{
serverAcceptor->accept(*serverSocket);
serverSocket->non_blocking(true);
cout << "connected" << endl;
}*/

unsigned int Networking::getBlockNumber()
{
	return blockNumber;
}


void Networking::sendPackage(genericPackage *Pkg)
{
	Pkg->setPackage();

	size_t len;
	boost::system::error_code error;
#ifdef DEBUG
	cout << "entra 8: funcion send Package" << endl;
#endif // DEBUG
	do
	{
		len = clientSocket->write_some(boost::asio::buffer(Pkg->package, Pkg->package.size()), error);
#ifdef DEBUG
		cout << "len: " << len << endl;
#endif // DEBUG
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
	{
		/*std::cout << "Error while trying to connect to server " << error.message() << std::endl;*/
#ifdef DEBUG
		cout << "error al querer enviar" << endl;
#endif // DEBUG
	}
#ifdef DEBUG
	cout << "entra 9: termino de enviar" << endl;
#endif // DEBUG

}

bool Networking::receivePackage()
{
	bool ret = false;
	boost::system::error_code error;
	char buf[PACKAGE_MAX_SIZE];
	size_t len = 0;
	//len = serverSocket->read_some(boost::asio::buffer(buf), error); //VER EL LEN QUE ONDA, EN MI CASO

	//pruebo esto en lugar de la linea de arriba. DE ACA
	do
	{
		len = clientSocket->read_some(boost::asio::buffer(buf), error);

		if (!error)
		{
			std::cout << '|';
			buf[len] = '\0';
		}

	} while (error); //cambio por error en lugar de !error
					 // HASTA ACA

	if (!error)
	{
		inputPackage.clear();
		//inputPackage.insert(inputPackage.end(), buf, buf + len); //VER insert
		inputPackage.insert(inputPackage.end(), buf, buf + len);

#ifdef DEBUG	
		std::cout << "len del recibido: " << len << std::endl;
		//Paso el vector a string:
		/*
		for (int i = 0; i < 10; ++i)
		inputPackage.push_back('A' + i);*/

		string str(inputPackage.begin(), inputPackage.end());
		//str.c_str();
		cout << "Here is strC, which is constructed from a vector:\n";
		cout << str << endl;

		//------------
		//int n = str.length();
		//char char_array[n + 1];
		// copying the contents of the 
		// string to char array
		//strcpy_s(char_array, str.c_str());

		//for (int i = 0; i<n; i++)
		//	cout << char_array;
		//-------------

		//imprimo el str:
		std::cout << std::endl << "Server says: " << str << std::endl;
		char recibi = (char)buf[1];
		char recibi2 = (char)str[2];
		std::cout << "message lenght (-2) (recibi): " << recibi << std::endl;
		std::cout << "recibi2: " << recibi2 << std::endl;
#endif // DEBUG

		ret = true;
	}
	else
	{
		ret = false;
	}
	return ret;
}

std::vector<char> Networking::getInputPackage()
{
	return inputPackage;
}