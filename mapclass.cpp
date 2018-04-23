#include "mapclass.h"

//constructor
mapclass::mapclass(void)
{
	//setting all pointers to null
	fpHead = NULL; 
	fpCurrent = NULL;  
	cityHead = NULL;
	cityCurrent = NULL;
}

//destructor
//deletes both linked lists
mapclass:: ~mapclass(void)
{
	cityNode *head;
	cityNode *temp;

	head = (*this).cityHead;
	temp = (*this).cityHead;
	while(head != NULL)
	{
		temp = head->next;
		delete head;
		head = temp;
	}

	fpNode *head1;
	fpNode *temp1;
	temp1 = fpHead;
	head1 = fpHead;
	while(temp1 != NULL)
	{
		head1 = temp1->next;
		delete temp1;
		temp1 = head1;
	}
}

//adds a flight to the linked list of all flights
void mapclass::addFlight( char start, char end, int price)
{
	try
	{
		fpNode *newFlight = new fpNode;
		if ( newFlight <= 0)
			throw 1;
		if ( newFlight == NULL)
			throw 2;
		if ( fpCurrent == NULL)
		{
			fpCurrent = newFlight;
			fpHead = newFlight;
			newFlight -> nodeFlight.parentCity = start;
			newFlight -> nodeFlight.City = end;
			newFlight -> nodeFlight.price = price;
			newFlight -> next = NULL;
		}
		else
		{
			newFlight->nodeFlight.parentCity = start;
			newFlight->nodeFlight.City = end;
			newFlight->nodeFlight.price = price;
			newFlight->next = NULL;
			fpCurrent->next = newFlight;
			fpCurrent = newFlight;
		}
	}

	catch(int err)
	{
		if (err == 1)
			cerr << "ERROR! Price needs to be larger than 0! " << endl;
		if (err == 2)
			cerr << "ERROR! there is no price gvien in the input! " << endl;
	}
}

//adds a city to the list of all cities
void mapclass::addCity( char cityName, bool isOrigin)
{
	cityNode *newCity = new cityNode;
	cityNode *tempPtr = new cityNode;
	newCity->cityName = cityName;
	newCity->isOrigin = isOrigin;
	newCity->visited = false;
	//if the city is the first added to the class
	//the city list pointer and current city pointer
	//are set to point to it
	if ((cityHead == NULL) && (isOrigin == true)) 
	{
		cityHead = newCity;
		cityCurrent = newCity;
		newCity->visited = true;
		newCity->next = NULL;
	}
	else
	{
		tempPtr = cityHead;
		while (tempPtr != NULL)
		{
			if (tempPtr->cityName == cityName)
				return;
			tempPtr = tempPtr->next;
		}
		cityCurrent->next = newCity;
		newCity->next = NULL;
		cityCurrent = newCity;
	}
}

//checks if the city has been visited
//if visited it is marked as visited
bool mapclass::visitedCity( char cityName)
{
	try
	{
		cityNode *tmpPtr;
		tmpPtr = cityHead;
		while (tmpPtr != NULL)
		{
			if(tmpPtr->cityName == cityName)
			{
				return tmpPtr->visited;
			}
			tmpPtr= tmpPtr->next;
		}
		if (tmpPtr == NULL)
		{
			throw 1;
			return false;
		}
	}
	catch(int e)
	{
		if(e == 1)
			cout << "Error! The map is empty!" << endl;
	}
}

//marks city as visited or not visited
void mapclass::markVisited( char cityName, bool visited )
{
	try
	{
		cityNode *tmpPtr;
		tmpPtr = cityHead;
		while(tmpPtr != NULL)
		{
			if(tmpPtr->cityName == cityName)
			{
				tmpPtr->visited = visited;
				return;
			}
			tmpPtr = tmpPtr->next;
		}
		if (tmpPtr == NULL)
		{
			throw 1;
		}
	}
	catch(int e)
	{
		cout << "Error, city doesn't exist." << endl;
	}
}

//sets current city to city name
void mapclass::setCurrentCity(char cityName)
{
	currentCity = cityName;
}

//this method searches cities using recursion.
//It finds a flight path to the destination
//from the current city
bool mapclass::search(char start, char destination)
{
	fpNode *flightPtr = fpHead;
	markVisited(start, true);
	currentFlightPath.push(start);
	char x = start;

	//check if parent city is visited
	while (flightPtr != NULL)
	{
		if ( x == flightPtr -> nodeFlight.parentCity )
		{
			x = flightPtr -> nodeFlight.City;
			if (visitedCity( x ) == false)
			{
				if ( x == destination)
				{
					markVisited( x, true);
					currentFlightPath.push(x);
					return true;
				}
				else
				{
					search(x, destination);//recursion
				}
			}
			else
			{
				currentFlightPath.push(x);
			}
		}
		flightPtr = flightPtr -> next;
	}
	//remove flights from stack
	for (int i = 1; i < currentFlightPath.getCount(); i++)
	{
		currentFlightPath.pop();
	}

	flightPtr = fpHead;
	x = start;
	//check for flight path to destination
	while ( flightPtr != NULL)
	{
		if ( x ==  flightPtr -> nodeFlight.parentCity && 
			visitedCity( flightPtr -> nodeFlight.City) == false)
		{
			x = flightPtr -> nodeFlight.City;
			if ( x == destination)
			{
				markVisited( x, false);
				currentFlightPath.push(x);
				return true;
			}
			else
			{
				search(x, destination);
			}
			flightPtr = flightPtr -> next;
		}
		else
		{
			flightPtr = flightPtr -> next;
		}
	}
}

//this method gets the price of a flight path
//And an array with all the flights in the path
int mapclass::getRoutePrice(char a1[])
{
	int TotalCost = 0;
	const int SIZE = currentFlightPath.getCount();
	char *temp_array = new char[SIZE];
	int count = 0;

	while(currentFlightPath.getCount() > 0)
	{
		temp_array[count] = currentFlightPath.peek();
		currentFlightPath.pop();
		count++;
	}
	
	for(int i=0; i<count-1; i++)
	{
		char origin = temp_array[i];
		char destination = temp_array[i+1];
		for(fpNode *temp = fpHead; temp != NULL; temp = temp->next)
		{
			currentPrice = temp->nodeFlight.price;
			if (origin == temp->nodeFlight.City && destination == temp->nodeFlight.parentCity)
			{
				TotalCost = TotalCost + currentPrice;
				break;
			}
		}
	}
	for(int j=0; j<SIZE; j++)
	{
		a1[j] = temp_array[j];
	}
	delete temp_array;
	return TotalCost;
}

//removes all elements from the stack
//to prepare for another search
void mapclass::clear()
{
	cityNode *temp;
	temp = cityHead;
	while (currentFlightPath.getCount() != 0)
	{
		currentFlightPath.pop();
	}
	while(temp != NULL)
	{
		temp->visited = false;
		temp=temp->next;
	} 
}