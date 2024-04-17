#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_set>
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
	SnakeLinkedList(sf::Vector2f headPos);
	~SnakeLinkedList() {}
	int Size();
	void PushFront(sf::Vector2f headPos);
	void PushBack(sf::Vector2f pos);
	void PopBack();

	bool DataCheck(int x, int y);

	std::unordered_set<int> CreateHash();

	void Move(int dir);
	int lastDir;
	enum EDirection
	{
		eRight,
		eDown,
		eLeft,
		eUp
	};
	int segDebt{ 0 };
	int score{ 0 };

	void Draw(sf::RenderWindow& window);

};

