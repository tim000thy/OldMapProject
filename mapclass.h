#pragma once
#include "stackP.h"
#include <iostream>
#include <iomanip>

using namespace std;

struct cityNode {
	char cityName;
	bool visited;
	bool isOrigin;
	cityNode *next;
};

struct fpNode {
	flight nodeFlight;
	fpNode *next;
};

class mapclass
{
public:
	//linked list of all cities in flightmap
	cityNode *cityHead;

	//linked list of all flights in flightmap
	fpNode *fpHead;

	//stack which holds flights during flightmap search
	stackP currentFlightPath;

	mapclass(void);

	~mapclass(void);

	int getRoutePrice(char a1[]);

	// Add a Flight to the list of all flights
	void addFlight( char start, char end, int price );

	// Add a City to the list of all cities
	void addCity( char cityName, bool isOrigin );

	// Determine whether a city has been already visited
	bool visitedCity( char cityName );

	// Marks city as visited
	void markVisited( char cityName, bool visited );

	//sets the current city's name to current city
	void setCurrentCity( char cityName );
	// Prepares the class to be used for another search.
	void clear();

	// Find a flight path to a destination from currentCity
	bool search( char start, char destination);

private:
	char currentCity;
	int currentPrice;
	fpNode *fpCurrent;
	cityNode *cityCurrent;
}
;