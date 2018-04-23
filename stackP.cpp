#include "stackP.h"


stackP:: stackP(void)
{
	top = NULL;
}

stackP:: stackP( const stackP &toCopy )
{
	if (toCopy.top == NULL)
		top = NULL;
	else {
		//copy first node
		top = new stackNode;
		top-> item = toCopy.top->item;

		//deep copy
		stackNode *newPtr = top; //new list pointer
		for ( stackNode *origPtr = toCopy.top->next; origPtr != NULL;
			origPtr = origPtr ->next)
		{
			newPtr -> next = new stackNode;
			newPtr = newPtr -> next;
			newPtr -> item = origPtr -> item;
		}
		newPtr-> next = NULL;
	}
}

void stackP:: push (const StackItemType newItem)
{
	try
	{
		stackNode *newPtr = new stackNode;
		if(newPtr==NULL)
		{
			throw 1;
		}
		else{
			newPtr->item = newItem;
			newPtr->next = top;
			top = newPtr;
		}
	}
	catch(int e)
	{
		cout << "Error, the stack is out of memory" << endl;
	}
}

void stackP:: pop()
{
	try
	{
		if(isEmpty())
		{
			throw 1;
		}
		else
		{
			//stack not empty, delete top
			stackNode *tmpPtr = top;
			top = top->next;

			//delete node
			tmpPtr -> next = NULL;
			delete tmpPtr;
		}
	}
	catch(int e)
	{
		if (e == 1)
			cout << "Error, the stack is empty." << endl;
	}
}

bool stackP::isEmpty() const
{
	return ( top == NULL);
}

stackP::~stackP(void)
{
	while( !isEmpty())
	{
		pop();
	}
}

StackItemType stackP:: peek()
{
	try
	{
		if (isEmpty())
		{
			throw 1;
			return NULL;
		}
		else
		{
			return top -> item;
		}
	}
	catch (int e)
	{
		if (e == 1)
			cout << "Error, the stack is empty." << endl;
	}
}

int stackP::getCount()
{
	int count = 0;
	if( isEmpty())
	{
		count = 0;
	}
	stackNode *tmpPtr;
	tmpPtr = top;
	while (tmpPtr != NULL)
	{
		count++;
		tmpPtr=  tmpPtr -> next;
	}
	return count;
}

