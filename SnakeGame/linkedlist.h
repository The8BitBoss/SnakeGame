#pragma once
#include <SFML/Graphics.hpp>
class SnakeLinkedList
{
public:
	struct Node
	{
		sf::Vector2f position;
		Node* nextUp;

		Node(sf::Vector2f defaultPosition) :position(defaultPosition), nextUp(nullptr) {}
		// Everytime you add a node you want the pointer nextUp to be the last linked node
		Node(sf::Vector2f defaultPosition, Node* tempnextUp) :position(defaultPosition), nextUp(tempnextUp) {}
	};
	sf::Texture t;
	sf::Sprite s;
	Node* head;
	SnakeLinkedList(sf::Vector2f headpos);
	~SnakeLinkedList() {}
	void Move(int dir);
	int lastDir;
	enum EDirection
	{
		eRight,
		eDown,
		eLeft,
		eUp
	};
	void insert(sf::Vector2f pos);
	void Draw(sf::RenderWindow& window);

};

