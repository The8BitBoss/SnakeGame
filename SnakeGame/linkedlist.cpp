#include "linkedlist.h"

SnakeLinkedList::~SnakeLinkedList()
{

}
void SnakeLinkedList::insert(int VAL)
{
	Node* Endoflist = head;
	//set the end of the list to be the head
	while (Endoflist != nullptr)
	{
		//set the end of the list to be the next *nextUp along
		Endoflist = Endoflist->nextUp;
	}//once it reachs the end of the snake it'll be set to nullPtr
	Endoflist = new Node(VAL);;
	//Sets the nullpointer to be a new node
}
