#include "linkedlist.h"
#include <iostream>

SnakeLinkedList::SnakeLinkedList(sf::Vector2f headpos) //Constructor//
{
	head = new Node(headpos);
	if (!t.loadFromFile("Assets/t.png"))
		std::cout << "Error:Texture not loaded";
	s = sf::Sprite(t);
	s.setColor(sf::Color::Red);
}
int SnakeLinkedList::Size()
{
	int s = 0;
	Node* node = head;
	while (node != nullptr)
	{
		s++;
		node = node->nextUp;
	}
	return s;
}
void SnakeLinkedList::PushFront(sf::Vector2f headPos)
{
	Node* tmp = head;
	head = new Node(headPos);
	head->nextUp = tmp;
}
void SnakeLinkedList::PushBack(sf::Vector2f pos)
{
	Node* Endoflist = head;

	while (Endoflist->nextUp != nullptr) {
		Endoflist = Endoflist->nextUp;
	}
	Endoflist->nextUp = new Node(pos);
}

void SnakeLinkedList::PopBack()
{
	Node* tmp = head;
	Node* prev = nullptr;
	while (tmp->nextUp != nullptr)
	{
		prev = tmp;
		tmp = tmp->nextUp;
	}
	if (prev != nullptr) {
	prev->nextUp = nullptr;
	}
		delete tmp;
}
bool SnakeLinkedList::DataCheck(int x, int y)
{
	Node* node = head;
	while (node != nullptr)
	{
		if (node->position.x == x && node->position.y == y)
		{
			return true;
		}
		node = node->nextUp;
	}
	return false;
}

std::unordered_set<int> SnakeLinkedList::CreateHash()
{
	std::unordered_set<int> hashSet;
	Node* node = head;
	while (node != nullptr) {
		// Hash the coordinates to a single integer
		int hash = node->position.x * 100 + node->position.y;
		hashSet.insert(hash);
		node = node->nextUp;
	}
	return hashSet;
}

void SnakeLinkedList::Move(int dir)
{
	sf::Vector2f tempPos = head->position;
	if (dir == (lastDir + 2) % 4)
	{
		dir = lastDir;
	}
	switch (dir)
	{
	case EDirection::eRight:
		tempPos.x += 1;
		break;
	case EDirection::eDown:
		tempPos.y += 1;
		break;
	case EDirection::eLeft:
		tempPos.x -= 1;
		break;
	case EDirection::eUp:
		tempPos.y -= 1;
		break;
	}
	lastDir = dir;
	PushFront(tempPos);
	if (segDebt)
	{
		segDebt--;
	}
	else
	{
		PopBack();
	}
}

void SnakeLinkedList::Draw(sf::RenderWindow& window)
{
	Node* drawNode = head;
	while (drawNode != nullptr) {
		s.setPosition(drawNode->position.x*16, drawNode->position.y*16);
		window.draw(s);
		drawNode = drawNode->nextUp;
	}
}
