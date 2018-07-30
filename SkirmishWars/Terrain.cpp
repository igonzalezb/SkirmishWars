#include "Terrain.h"

Terrain::Terrain()
{
	fogOfWar = true;
	connections = { false, false, false, false };
}

Terrain::Terrain(string name, string path, string type)
{
	fogOfWar = true;
	connections = { false, false, false, false };
	this->name = name;
	this->path = path;
	this->type = type;
}

Terrain::~Terrain()
{
}

void Terrain::setName(string name)
{
	this->name = name;
}

void Terrain::setType(string type)
{
	this->type = type;
}

void Terrain::setPath(string path)
{
	this->path = path;
}

string Terrain::getPath()
{
	return path;
}

string Terrain::getName()
{
	return name;
}

string Terrain::getType()
{
	return type;
}


void Terrain::setConnections(int i, int j, string matrix[FILA][COLUMNA])
{
	if (!(matrix[i][j].compare("r")) || !(matrix[i][j].compare("a"))) {
		
		if ((i - 1 >= 0) && !(matrix[i][j].compare(matrix[i - 1][j])))
		{
			connections.up = true;
		}
		if ((i + 1 < FILA) && !(matrix[i][j].compare(matrix[i + 1][j])))
		{
			connections.down = true;
		}
		if (((j - 1) >= 0) && !(matrix[i][j].compare(matrix[i][j-1])))
		{
			connections.left = true;
		}
		if (((j + 1) < COLUMNA) && !(matrix[i][j].compare(matrix[i][j+1])))
		{
			connections.right = true;
		}

		if (connections.up && connections.down && connections.right && connections.left) {
			path = path + "x.png";
		}
		else if ((!connections.up && connections.down) && (connections.right && connections.left)) {
			path = path + "t1.png";
		}
		else if ((connections.up && connections.down) && (!connections.right && connections.left)) {
			path = path + "t2.png";
		}
		else if ((connections.up && !connections.down) && (connections.right && connections.left)) {
			path = path + "t3.png";
		}
		else if ((connections.up && connections.down) && (connections.right && !connections.left)) {
			path = path + "t4.png";
		}
		else if ((connections.up && connections.down) && !(connections.right && connections.left)) {
			path = path + "i1.png";
		}
		else if (!(connections.up && connections.down) && (connections.right && connections.left)) {
			path = path + "i2.png";
		}
		
		else if ((!connections.up && connections.down) && (connections.right && !connections.left)) {
			path = path + "l1.png";
		}
		else if ((!connections.up && connections.down) && (!connections.right && connections.left)) {
			path = path + "l2.png";
		}
		else if ((connections.up && !connections.down) && (!connections.right && connections.left)) {
			path = path + "l3.png";
		}
		else if ((connections.up && !connections.down) && (connections.right && !connections.left)) {
			path = path + "l4.png";
		}

		else if ((connections.up || connections.down) && (!connections.right && !connections.left)) {
			path = path + "i1.png";
		}
		else if ((!connections.up && !connections.down) && (connections.right || connections.left)) {
			path = path + "i2.png";
		}
		else {						
			path = path + "x.png";
		}

	}

}


void Terrain::removeFog()
{
	fogOfWar = false;
}