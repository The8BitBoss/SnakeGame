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
	Node* head;
	std::string name;
	sf::Sprite s;
	
	SnakeLinkedList(sf::Vector2f headPos, sf::Texture& t, std::string name);
	SnakeLinkedList() {}
	~SnakeLinkedList() {}
	int Size();
	void PushFront(sf::Vector2f headPos);
	void PushBack(sf::Vector2f pos);
	void PopBack();

	bool DataCheck(int x, int y);

	std::unordered_set<int> CreateHash();

	void Move(int dir);
	int direction{ 0 };
	int lastDirection;
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

