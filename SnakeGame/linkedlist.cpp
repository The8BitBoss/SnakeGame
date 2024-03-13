#include "linkedlist.h"
#include <iostream>

SnakeLinkedList::SnakeLinkedList(sf::Vector2f headpos)
{
	head = new Node(headpos);
	if (!t.loadFromFile("Assets/t.png"))
		std::cout << "Error:Texture not loaded";
	s = sf::Sprite(t);
	s.setColor(sf::Color::Red);
}
void SnakeLinkedList::Move(int dir)
{
	sf::Vector2f tempPos = head->position;

	/*if (dir == (lastDir + 2) % 4)
	{
		dir = lastDir;
	}*/
	switch (dir)
	{
	case EDirection::eUp:
		head->position.y -= 1;
		break;
	case EDirection::eLeft:
		head->position.x -= 1;
		break;
	case EDirection::eRight:
		head->position.x += 1;
		break;
	case EDirection::eDown:
		head->position.y += 1;
		break;
	}
	Node* temp = head;
	while (temp->nextUp != nullptr)
	{
		tempPos = temp->nextUp->position;
		temp->nextUp->position = temp->position;
		temp->position = tempPos;
		temp->nextUp = temp->nextUp->nextUp;
		//Move along the snake, keep record of where the next pos was when you move it

	}
}
void SnakeLinkedList::insert(sf::Vector2f pos)
{
	Node* Endoflist = head;
	//set the end of the list to be the head
	while (Endoflist->nextUp != nullptr)
	{
		//set the end of the list to be the next *nextUp along
		Endoflist = Endoflist->nextUp;
	}//once it reachs the end of the snake it'll be set to nullPtr
		Endoflist->nextUp = new Node(pos);
}

void SnakeLinkedList::Draw(sf::RenderWindow& window)
{
	Node* drawNode = head;
	while (drawNode != nullptr)
	{
		s.setPosition(drawNode->position.x*16, drawNode->position.y*16);
		window.draw(s);
		drawNode = drawNode->nextUp;
	}
}
