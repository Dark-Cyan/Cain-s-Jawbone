#include <iostream>
#include <cstdlib>
#include "list.h"

//default node constructor with no parameters passed
lnode::lnode(){
	
	//sets data to 0 and next and prev to null
	data = "";
	next = NULL;
	prev = NULL;
}

//node constructor with two node pointers passed
lnode::lnode(lnode* p, lnode* n){

	//sets data to 0 and next and prev to respective parameters
	data = "";
	next = n;
	prev = p;
}

//node constructor with two node pointers and a value passed
lnode::lnode(lnode* p, const ldata & d, lnode * n){

	//sets data to the value passed and next and prev to respective parameters
	data = d;
	next = n;
	prev = p;
}

//returns the effective non-negative index
size_t list::_computeIndex(int index) const{

	if (index >= 0){ //if the index is 0 and up return the index
		return index;
	} else { //if the index is negative return the size + the index
		return _size + index;
	}
}

//initializes the list with size 0 and two sentinel nodes
void list::_init(){

	//sets size to zero
	_size = 0;

	//creates two sentinel nodes
	head = new lnode;
	tail = new lnode;

	//makes it so the sentinel nodes point to eachother
	head -> next = tail;
	tail -> prev = head;
}             

//will copy the values of the passed list into this one
void list::_copy(const list & orig){

	//repeats for all non-sentinel nodes of the passed list
	for (int i = 0; i < orig.size(); i++){

		//adds the value at i of the passed list to the end of this list
		add(orig.get(i),-1);
	}
}

//will delete all held memory
void list::_destroy(){

	//repeats for all non-sentinel nodes in the list
	for (int i = _size - 1; i >= 0; i--){

		//removes the current first non-sentinel node and deletes its memory
		removeAt(0);
	}

	//deletes the two sentinel nodes
	delete head;
	delete tail;
}

//default list constructor which creates the two sentinel nodes and points them at eachother
list::list(){

	//creates a blank list
	_init();
}

//list constructor that copies an already existing list
list::list(const list & orig){

	//creates a blank list
	_init();

	//adds all values from the passed list into the blank list
	_copy(orig);
}

//overrides the '=' operator to create a deep copy of one list                    
list & list::operator=(const list & rhs){

	//creates a blank list
	_init();

	//adds all values from the passed list into the blank list
	_copy(rhs);

	//returns a pointer to this list that was created
	return * this;
}

//destructor for the list
list::~list(){

	//deletes all occupied memory
	_destroy();
}

//adds a node with data ldata at the effective non-negative index
void list::add(const ldata & item, int index){

	//increments size
	_size++;

	//creates a temp pointer that points to head
	lnode * temp;
	temp = head;

	//moves the temp pointer to the node before insertion based on the effective non-negative index
	for (int i = 0; i < _computeIndex(index); i++){
		temp = temp -> next;
	}

	//creates a new node and properly links it
	lnode * l = new lnode(temp, item, temp->next);
	l -> prev -> next = l;
	l -> next -> prev = l;
}

//deletes a node at the effective non-negative index
void list::removeAt(int index){

	//decrements size
	_size--;

	//creates a temp pointer that points to the node after head;
	lnode * temp;
	temp = head -> next;

	//moves the temp pointer to the node that needs to be removed based on the effective non-negative index
	for (int i = 0; i < _computeIndex(index); i++){
		temp = temp -> next;
	}

	//makes the nodes around the one that needs to be removed point to eachother
	temp -> prev -> next = temp -> next;
	temp -> next -> prev = temp -> prev;

	//deletes the targeted node
	delete temp;
}

//removes the first node containing a given value if it exists
void list::remove(const ldata & item){

	//finds the first node containing a given value if it exists
	size_t location = find(item);

	//if it did exist remove it
	if (location != _size){
		removeAt((int)location);
	}
}

//finds the first node containing a given value if it exists
size_t list::find(const ldata & item) const{

	//creates a temp pointer that points to head
	lnode * temp; 
	temp = head;

	//progresses through all non-sentinel nodes in the list
	for (int i = 0; i < _size; i++){

		//progresses temp to the current index
		temp = temp -> next;

		//if the value in the node temp is on equals the given value return the index
		if (temp -> data == item){
			return i;
		}
	}

	//if the value was not found return the size of the list
	return _size;
}

//returns the value at a given index
ldata list::get(int index) const{

	//creates a temp pointer that points to head
	lnode * temp; 
	temp = head -> next;

	//moves the temp pointer to the node at the effective non-negative index
	for (int i = 0; i < _computeIndex(index); i++){
		temp = temp -> next;
	}

	//returns the data from the current node
	return temp -> data;
}

//returns the size of the list
size_t list::size() const{
	return _size;
}

//prints the list to cout
void list::output() const{

	//creates a temp pointer that points to head
	lnode * temp; 
	temp = head;

	//prints starting bracket
	std::cout << "<";

	//prints the value of every non-sentinel node
	for (int i = 0; i < _size; i++){

		//makes temp point to the next node in the list and prints the data of the new node
		temp = temp -> next;
		std::cout << temp -> data;

		//if this isn't the last loop put a comma and space to seperate the printed values
		if (i != _size - 1){
			std::cout << ", ";
		}
	}

	//prints the ending bracket
	std::cout << ">";
}