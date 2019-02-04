
#include "Networking.h"
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <conio.h>
//#include <boost/asio/ip/basic_endpoint.hpp>

//CONSTRUCTOR PARA CLIENTE
Networking::Networking(std::string _serverAddress) : serverAddress(_serverAddress)
{
	IO_handler = new boost::asio::io_service();
	mySocket = new boost::asio::ip::tcp::socket(*IO_handler);
	clientResolver = new boost::asio::ip::tcp::resolver(*IO_handler);
	
	justConnected = false;
	IamClient = true;
}


Networking::~Networking()//PARA CLIENT
{
	//3 SIGUIENTES LINEAS PARA CLIENT
	if (IamClient)
	{
		mySocket->close();
		delete clientResolver;
		delete mySocket;
		delete IO_handler;
	}
	else
		//3 SIGUIENTES LINEAS PARA SERVER
	{
		serverAcceptor->close();
		serverSocket->close();
		delete serverSocket;
		delete s_IO_handler;
	}
}


//ESTA ES LA START CONNECTION QUE VA A IR PERO FALTA CORREGIR LA LINEA DE RESOLVER
void Networking::startConnection()
{
	bool exit;

	endpoint = clientResolver->resolve(
		boost::asio::ip::tcp::resolver::query(serverAddress.c_str(), CONNECTION_PORT_C));
	int contador = 0; 
	do
	{
		exit = true;
		try
		{
			boost::asio::connect(*mySocket, endpoint);
		}
		catch (const std::exception& e)
		{
			exit = false;
		}

		contador++; 
	} while ((!exit) && (contador <= 5)); 

	if (contador<=5) //NO SE CUMPLIO EL TIEMPO, ES CLIENTE
	{
		mySocket->non_blocking(true);
		IamClient = true;
		cout << "CONNECTED AS CLIENT" << endl;

	}
	else //TIENE QUE SER SERVER
	{
		//Si no anduvo como cliente, destruyo el clientResolver y creo un serverAcceptor:
		IamClient = false;
		mySocket->close();
		delete clientResolver;
		delete mySocket;
		delete IO_handler;
		s_IO_handler = new boost::asio::io_service();
		serverSocket = new boost::asio::ip::tcp::socket(*s_IO_handler);
		serverAcceptor = new boost::asio::ip::tcp::acceptor(*s_IO_handler,
			boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), CONNECTION_PORT_S));

		//serverAcceptor->accept(*mySocket);
		//mySocket->non_blocking(true);
		//try {
			serverAcceptor->accept(*serverSocket);
			serverSocket->non_blocking(true);
		//}
		//catch (boost::exception const&  ex) {}

		cout << "CONNECTED AS SERVER" << endl;
	}
}


std::string Networking::getServerAddres()
{
	return serverAddress;
}


unsigned int Networking::getBlockNumber()
{
	return blockNumber;
}


void Networking::sendPackage(genericPackage *Pkg)
{
#ifdef DEBUG
	//cout << "entra 8: funcion send Package" << endl;
#endif // DEBUG
	Pkg->setPackage();
	cout << "OP CODE ENVIADO: " << (int)(Pkg->code) << endl;
	size_t len;
	boost::system::error_code error;

	do
	{
		if (IamClient)
		{
			len = mySocket->write_some(boost::asio::buffer(Pkg->package, Pkg->package.size()), error);
		}
		else
		{
			len = serverSocket->write_some(boost::asio::buffer(Pkg->package, Pkg->package.size()), error);

		}

#ifdef DEBUG
	//	cout << "len: " << len << endl;
#endif // DEBUG
	} while ((error.value() == WSAEWOULDBLOCK));
	if (error)
	{
		/*std::cout << "Error while trying to connect to server " << error.message() << std::endl;*/
#ifdef DEBUG
	//	cout << "error al querer enviar" << endl;
#endif // DEBUG
	}
#ifdef DEBUG
	//cout << "entra 9: termino de enviar" << endl;
#endif // DEBUG

}

bool Networking::receivePackage()
{
#ifdef DEBUG
	//cout << "entra a Receive Package" << endl;
#endif // DEBUG

	bool ret = false;
	boost::system::error_code error;
	char buf[PACKAGE_MAX_SIZE];
	size_t len = 0;
	//len = serverSocket->read_some(boost::asio::buffer(buf), error); //VER EL LEN QUE ONDA, EN MI CASO

	//pruebo esto en lugar de la linea de arriba. DE ACA
//	do
//	{
#ifdef DEBUG
		//cout << "entra adentro de receive package, a un do while" << endl;
#endif // DEBUG
		if (IamClient)
		{
			len = mySocket->read_some(boost::asio::buffer(buf), error);
			//cout << "BUF:" << buf<< endl;
#ifdef DEBUG
			//cout << "entra adentro de receive package, a un do while CLIENT" << endl;
#endif // DEBUG
		}
		else 
		{
			len = serverSocket->read_some(boost::asio::buffer(buf), error);
			//cout << "BUF:" << buf<< endl;
#ifdef DEBUG
		//	cout << "entra adentro de receive package, a un do while, SERVER" << endl;
#endif // DEBUG
		}

		if (!error)
		//if(error)
		{
			std::cout << '|' << endl;
			buf[len] = '\0';
		}
	//} while (!error);

//	} while (error); //cambio por error en lugar de !error
					 // HASTA ACA

	//	if(error)
	if (!error)
	{
		inputPackage.clear();
		//inputPackage.insert(inputPackage.end(), buf, buf + len); //VER insert
		inputPackage.insert(inputPackage.end(), buf, buf + len);

#ifdef DEBUG	
	//	

		string str(inputPackage.begin(), inputPackage.end());
		
		std::cout << std::endl << "Server says: " << str << std::endl;
		char recibi = (char)buf[1];
	//	char recibi2 = (char)str[2];
		std::cout << "message lenght (-2) (recibi): " << recibi << std::endl;
	//	std::cout << "recibi2: " << recibi2 << std::endl;
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