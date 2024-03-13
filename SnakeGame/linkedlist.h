#pragma once
class SnakeLinkedList
{
private:
	struct Node
	{
		int x, y;
		Node* nextUp;

		Node(int val = 0) :x(val), y(val), nextUp(nullptr) {}
		// Everytime you add a node you want the pointer nextUp to be the last linked node
		Node(int valx, int valy,Node* tempnextUp) :x(valx), y(valy), nextUp(tempnextUp) {}
	};
	Node* head;
public:
	SnakeLinkedList():head(nullptr) {}
	~SnakeLinkedList();
	void insert(int val);

};

