//name: Brian Frempa-Dekyi
//filename: DBList.cpp

#include <iostream>
#include <string>
#include <fstream>
#include "DBList.h"

using namespace std;

DBList::DBList() {
	Head = NULL;
	Tail = NULL;
	Current = NULL;
}
/////////////////////////////////////////////////////
/**
* InsertFront
*     Inserts a value at the front of the list 
* Params: string : animal to be inserted 
*/
////////////////////////////////////////////////////
void DBList::InsertFront(string Data) {
	Node* Temp = new Node(Data);
	InsertFront(Temp);

}
/////////////////////////////////////////////////////////////////
/*
* InsertFront
*     Inserts a value at the front of the list 
* Params: Node* &Temp : allows formation of the node and
*     linkage to the other possible nodes
*/

/////////////////////////////////////////////////////////////////
void DBList::InsertFront(Node* &Temp) {
	if (!Head) 
		Head = Temp;
		Tail = Temp;
		Tail->Next = Head
		Current = Temp;
		Head->Prev = Tail;
	}
	else {
		Temp->Next = Head;
		Temp->Prev = Tail;
		Head->Prev = Temp;
		Tail->Next = Temp;
		Head = Temp;
		Current = Head;
	}
}
/////////////////////////////////////////////////////////////
/**
* InsertRear
*     Inserts a value at the rear of the list 
* Params: Node* &Temp : allows formation of the node and
*      linking to the other nodes
*
*/
/////////////////////////////////////////////////////////////
void DBList::InsertRear(Node* &Temp) {
	if (!Head) {
		DBList::InsertFront(Temp);
	}
	else {
		Tail->Next = Temp;
		Temp->Prev = Tail;
		Tail = Temp;
		Temp->Next = Head;
		Head->Prev = Tail;
		Current = Tail;
	}
}
////////////////////////////////////////////////////////
/**
* InsertRear
*     Inserts a value at the rear of the list 
* Params: string: animal to be stored 
*
*/
///////////////////////////////////////////////////////
void DBList::InsertRear(string Data) {
	if (!Head) {
		DBList::InsertFront(Data);
	}
	else {
		Node* Temp = new Node(Data);
		InsertRear(Temp);
	}
}
///////////////////////////////////////////////////////////////
/**
* Delete:
*     checks to see if you can possibly delete node 
* Params: string x: checks to see if the string passed in
*      is available for deletion, if not returns false. 
* Returns: boolean
*
*/
///////////////////////////////////////////////////////////////

bool DBList::Delete(string x) {
	if (Head == Tail && Head->Data == x) {
		delete Head;
		Head = NULL;
		Tail = NULL;
		Current = NULL;
		return true;
	}
	else if (Head->Data == x) {
		Head = Head->Next;
		Current = Head;
		delete Head->Prev;
		Head->Prev = Tail;
		return true;
	}
	else if (Tail->Data == x) {
		Tail = Tail->Prev;
		delete Tail->Next;
		Tail->Next = Head;
		Current = Tail;
		return true;
	}
	else {
		Node* Location = DBList::_Search(x);
		if (Location) {
			Location->Prev->Next = Location->Next;
			Location->Next->Prev = Location->Prev;
			Current = Location->Next;
			delete Location;
			return true;
		}
	}
	return false;
}

/////////////////////////////////////////////////////////////////

/**
* Search: searches for a string
* Params
* string x- in order to check if the string exists
* Returns
* false
*/

////////////////////////////////////////////////////////////////
bool DBList::Search(string x) {
	return false;
}


///////////////////////////////////////////////////////////////

/**
* Print
* Prints out the survivor
* Params: int column and ofstream &outfile:
*    allows the program to print out the survivor
*/

//////////////////////////////////////////////////////////////

void DBList::Print(int column, ofstream &outfile) {
	Node *Temp = Head;
	int count = 1;
	while (Temp != Tail) {
		Temp = Temp->Next;
		if (column && count % column == 0)
			count++;
	}
	outfile << "WINNER: " << Tail->Data << "!!" << endl;
}

//////////////////////////////////////////////////////

/**
* Print
* allows the print function to be called 
* Params: Node* &Temp :
* ofstream &outfile : allows outfiling to txt.
*
*/
//////////////////////////////////////////////////////

void DBList::Print(ofstream &outfile) {
	DBList::Print(0, outfile);
}

///////////////////////////////////////////////////////
/**
* _Search
*     Searches for a key string
* Params: string key: the key string method will
* search for
*
*/
///////////////////////////////////////////////////////
Node* DBList::_Search(string key) {
	Node* Temp = Head;
	while (Temp) {
		if (Temp->Data == key) {
			return Temp;
		}
		Temp = Temp->Next;
	}
	return NULL;
}
/**
* checkifEvenorOdd
*     checks if the number is even or odd to determine
*  if the list will go left or right
* Params: int check: the integer that is used to
* determine the direction
*
* Returns : DeleteNode(temp)
*
*/
string DBList::checkifEvenorOdd(int var) {
	Node *temp = Current;
	if (var % 2 == 0)
	{
		for (int i = 0; i < var; i++)
		{
			Current = Current->Next;
		}
		temp = Current;
	}
	else
	{
		for (int i = 0; i < var; i++)
		{
			Current = Current->Prev;
		}
		temp = Current;
	}
	Current = Current->Next;
	return deleteNode(temp);
}
//////////////////////////////////////////////////////////////
/**
* deleteNode
* deletes a node to eliminate the animals
* Params: Node* temp : allows for traversal and deletion
*
*/
//////////////////////////////////////////////////////////////

string DBList::deleteNode(Node* temp) {
	if (temp == Head)
	{
	Head = Head->Next;
	}
	if (temp == Tail)
	{
	Tail = Tail->Prev;
	}
	
	temp->Prev->Next = temp->Next;
	temp->Next->Prev = temp->Prev;
	return temp->Data;
	delete temp;
}
