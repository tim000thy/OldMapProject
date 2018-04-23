#include <iostream>
#include <fstream>
#include <sstream>
#include "mapclass.h"
#include <iomanip>
using namespace std;

//main method.
//calls and writes files using
// methods of mapclass and other classes
int main (int argc, char *argv[])
{
	ifstream file(argv[1]);
	ofstream outfile;
	char start, city1, city2;
	int cost;
	file >> start;
	cout << start << "\n";
	mapclass *m = new mapclass();
	m -> addCity(start, true);
	
	//read in flights and cities to list
	while(!file.eof())
	{
		file >> city1 >> city2 >> cost;
		m -> addFlight(city1, city2, cost);
		m -> addCity(city2, false);
	}

	cityNode *temp;

	outfile.open(argv[2]);
	outfile << "Destination Flight Route from " << start << " Total Cost" << "\n";
	for (temp = m-> cityHead; temp != NULL; temp = temp->next)
	{
		//print destinations to file
		m-> search(start, temp->cityName);
		int SIZE = m -> currentFlightPath.getCount();
		char *a1 = new char[SIZE];
		int cost = m-> getRoutePrice(a1);
		outfile << temp ->cityName << setw(13);

		//print flight paths to file
		for (int i = 0; i < SIZE; i++)
		{
			outfile << a1[i] << ", ";
		}
		outfile << right << setw(19 - SIZE);
		//print route costs to file
		outfile << "$" << cost;
		outfile << "\n";
		m -> clear();
	}

	file.close();
}