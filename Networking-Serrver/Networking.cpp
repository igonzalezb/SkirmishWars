
#include "Networking.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <conio.h>


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

}

unsigned int Networking::getBlockNumber()
{
	return blockNumber;
}

//VER CUANDO SE USA ESTA FUNCION (SI ES QUE SE USA)!!!!!!!!!!!!!
/*
void Networking::packageDecode() //CAMBIAR
{
//std::string receivedFile;
receivedPackageType = (opCodes)inputPackage[0]; //Agarro el opCode del paquete recibido
switch (receivedPackageType)
{
case ACK:
//adentro de cada uno de estos casos, GENERAR EL EVENTO R_ACK, o R_ALGO correspondiente a cada caso
//tmb se podria validar aca mismo el resto del mensaje recibido. (o ver donde)
break;
case NAME:
break;
case NAME_IS:
break;
case MAP_IS:
break;
case YOU_START:
break;
case I_START:
break;
case PASS:
break;
case MOVE:
break;
case PURCHASE:
break;
case ATTACK:
break;
case YOU_WON:
break;
case PLAY_AGAIN:
break;
case GAME_OVER:
break;
case ERROR_:
break;
case QUIT:
break;
*/

/*
case WRQ_OP:
fileToTransfer = std::string(inputPackage.begin() + 2, inputPackage.end());
break;
case RRQ_OP:
fileToTransfer = std::string(inputPackage.begin() + 2, inputPackage.end());
break;
case DATA_OP:
blockNumber = (inputPackage[2] << 8) + inputPackage[3];
data = inputPackage[4];
break;
case ACK_OP:
blockNumber = (inputPackage[2] << 8) + inputPackage[3];
break;
case ERROR_OP:
errorCode = (errorCodes)inputPackage[3];
errorMsg = inputPackage[4];
break;

default:
break;
}
}
*/

/*
errorCodes Networking::getErrorCode()
{
return errorCode;
}

std::string Networking::getErrorMsg()
{
return errorMsg;
}

std::string Networking::getData()
{
return data;
}


std::string Networking::getRequestedFile()
{
return fileToTransfer;
}
*/


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
		len = serverSocket->write_some(boost::asio::buffer(Pkg->package, Pkg->package.size()), error);
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
		len = serverSocket->read_some(boost::asio::buffer(buf), error);

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
		std::cout << std::endl << "Client says: " << str << std::endl;
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
