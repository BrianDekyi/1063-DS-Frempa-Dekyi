/*
*@ProgramName - ProrityListBasedQueue
*@Author - Brian Frempa-Dekyi
*@E-mail - brian.dekyi@yahoo.com

*@Files
*      main.cpp
*      animals.txt
*      priority_out.txt
*
*@Description
*      This program takes in a list of animals and stores the data in a Queue
*      the queue is organized in the prority of the number of the number of
*      chararcters
*      if there is a tie,the queue will be organized in the prority of
*      alphabetical order

*@Course - 1063 Data Structure
*@Semester - Spring 2018
*@Date - 04 02 2018
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
*Struct to  holds the Node
*/
struct Node {
	string val;
	Node *next;
	Node() {
		val = " ";
		next = NULL;
	}
	Node(string v) {
		val = v;
		next = NULL;
	}
};

/*@className - Queue
*
* Methods:
*   void Queue()
*   void readFile()
*   string pop()
*   void push(string v)
*   bool empty()
*   void print()

*/
class Queue {
private:
	Node *Front;
	Node *Rear;
	string cmd;
	string word;
	ifstream fin;
	ofstream fout;

public:
	/*
	* @FunctionName :Queue
	*
	* @Description:
	*       This is the constructor
	* @Params:
	*       None
	* @Returns:
	*      None
	*/
	Queue() {
		Front = Rear = NULL;
		cmd = " ";
		word = " ";
		fin.open("input_data.txt");
		fout.open("priority_out.txt");
	}

	/*
	* @FunctionName :readFile
	*
	* @Description:
	*       Reads commands and either performs a push or pop method
	* @Params:
	*      None
	* @Returns:
	*      The item removed
	*/
	void readFile() {
		int i = 1;

		fout << "Animals Popped off the Queue : " << endl << endl;

		while (!fin.eof()) {
			fin >> cmd >> word;

			if (!cmd.compare("push")) {
				push(word);
			}
			if (!cmd.compare("pop")) {
				fout << i << " " << pop() << endl;
				i++;

			}
		}

		fout << endl;
	}

	/*
	* @FunctionName :pop
	*
	* @Description:
	*       This method removes an item from the list
	* @Params:
	*      None
	* @Returns:
	*      The item removed
	*/
	string pop() {
		if (!empty()) {
			Node *temp = Front;   // temp pointer so we can delete node
			string v = temp->val; // grab value out of node
			Front = Front->next;  // move pointer to next node
			delete temp;		  // give mem back to system
			return v;
		}
		else {
			fout << "error: cannot pop off empty queue." << endl;
			return " ";
		}
	}

	/*
	* @FunctionName : push
	*
	* @Description:
	*       This method adds an item to the list and begins to sort the
	*       list everytime a new item is added via the sort method
	* @Params:
	*       string v - the item to be added
	* @Returns:
	*       none
	*/
	void push(string v) {
		Node *n = new Node(v);

		// handle the empty case
		if (empty()) {
			Front = n;
			Rear = n;
		}
		else {
			// not empty add to rear
			Rear->next = n;
			Rear = n;
			sort();
		}
	}

	/*
	* @FunctionName : sort
	*
	* @Description:
	*       sorts each item in the queue in terms of  priority
	* @Params:
	*       none
	* @Returns:
	*       none
	*/
	void sort() {
		string tWord = " ";
		Node *temp = Front;
		Node *i;
		Node *j;

		for (i = Front; i != NULL; i = i->next) {
			for (j = i->next; j != NULL; j = j->next) {
				// This handles the priority of number of character
				if (j->val.length() < i->val.length()) {
					tWord = j->val;
					j->val = i->val;
					i->val = tWord;
				}

				// This handles when there are ties
				else if (j->val.length() == i->val.length()) {
					for (int k = 0; k < j->val.length(); k++) {
						if ((int)j->val[k] < (int)i->val[k]) {
							tWord = j->val;
							j->val = i->val;
							i->val = tWord;
						}
						break;
					}
				}
			}
		}
	}

	/*
	* @FunctionName :empty
	*
	* @Description:
	*       Checks wheter the list empty or not
	* @Params:
	*       none
	* @Returns:
	*      returns true or false
	*/
	bool empty() {
		return (Front == NULL);
	}

	/*
	* @FunctionName : print
	*
	* @Description:
	*       Prints all the items currently in the queue
	* @Params:
	*      none
	* @Returns:
	*    none
	*/

	void print() {

　
		fout << "Animals Remaining on the Queue (in order of priority) : " << endl << endl;
		Node *temp = Front;
		int i = 1;
		while (temp) {
			fout << i << " " << temp->val << "\n";
			temp = temp->next;
			i++;
		}
		fout << endl;
		fout.close();
	}
};
int main() {
	Queue Q;
	Q.readFile();
	Q.print();
}
