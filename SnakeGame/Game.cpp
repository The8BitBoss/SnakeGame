#include <SFML/Graphics.hpp>
#include "Game.h"
#include "linkedlist.h"
#include <iostream>

Game::Game() {

}
Game::~Game() {

}
void Game::Setup() 
{
    ///////////////   Create Window ///////////////////
    gScreenWidth = spriteSize * n;
    gScreenHeight = spriteSize * m;
    this->window = new sf::RenderWindow(sf::VideoMode(gScreenWidth, gScreenHeight), "Snake");
    //window(sf::VideoMode(gScreenWidth, gScreenHeight), "Snake");


    //////// Load Sprites //////////
 
   if (!tW.loadFromFile("Assets/white.png") || !tR.loadFromFile("Assets/red.png") || !tO.loadFromFile("Assets/orange.png") || !tY.loadFromFile("Assets/yellow.png")|| !tG.loadFromFile("Assets/green.png") || !tLB.loadFromFile("Assets/lBlue.png") || !tB.loadFromFile("Assets/blue.png") || !tP.loadFromFile("Assets/purple.png"))
   {
        return;
   }
        //////////////////////////////Setup()///////////////////////////////////
    player = SnakeLinkedList (sf::Vector2f(3, 1), tG);
    player.PushBack(sf::Vector2f(2.0f, 1.0f));
    player.PushBack(sf::Vector2f(1.0f, 1.0f));
    SnakeLinkedList snake2(sf::Vector2f(3, 5), tG);
    snake2.PushBack(sf::Vector2f(2.0f, 5.0f));
    snake2.PushBack(sf::Vector2f(1.0f, 5.0f));
    
    snakes.push_back(player);
    snakes.push_back(snake2);



}
void Game::Tick() {
    if (dead)
    {
        return;
    }
    snakes.front().Move(playerDir);
    snakes.back().Move(rand() % 4);//Works
    /*player.Move(playerDir);*/// Doesnt Work?
    for (auto& snake : snakes)
    {
        //snake.Move(playerDir);
        for (int i = 0; i < 5; i++)
        {
            if (!fruits[i].dead && snake.head->position == fruits[i].pos)
            {
                snake.segDebt += fruits[i].value;
                snake.score += fruits[i].value;
                fruits[i].respawnTimer = 50 + rand() % 51;
                fruits[i].dead = true;
                break;
            }
            if (fruits[i].dead)
            {
                if (fruits[i].respawnTimer <= 0)
                {
                    fruits[i].respawnTimer = 50 + rand() % 51;
                    fruits[i].dead = false;
                    fruits[i].pos.x = rand() % n;
                    fruits[i].pos.y = rand() % m;
                    fruits[i].value = 1 + rand() % 5;
                }
                else
                {
                    fruits[i].respawnTimer--;
                }
            }
        }
    }
    if (Collisions())
        dead = true;
}
bool Game::Collisions(){
    std::unordered_set<int> allNodes;// create set to store all nodes
    for (SnakeLinkedList& snake : this->snakes)
    {
        std::unordered_set<int> snakeSet = snake.CreateHash();
        // for every node in every snake
        for (int node : snakeSet)
        {
            if (allNodes.find(node) != allNodes.end())
            {// if it is, then there's a collision between snakes
                bool snakefound = false;
                int index = 0;
                for (auto& snake : snakes)
                {
                    index++;
                    if (node == snake.head->position.x * 100 + snake.head->position.y)
                    {
                        //std::cout << "snake " << index << " has died";
                        snakefound = true;
                    }
                }
                if (!snakefound) {
                    //std::cout << "Unknown snake has died";
                }
                return true;
            }
            allNodes.insert(node);
            // if the node is not in the set, add it to the set
        }
    }
    return false;
}
int Game::Run() 
{
    Setup();
    sf::Sprite tileWhite(tW), tileRed(tR), tileOrange(tO), tileYellow(tY), tileLBlue(tLB), tileBlue(tB), tilePurple(tP);
    // window
    while (window->isOpen())
    {
        ///////////////   Timer increment ///////////////
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        ////////////////// Event checker ////////////////
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
        }
        
        ////////////   Direction input checker  ///////////////
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerDir = SnakeLinkedList::EDirection::eLeft;
            std::cout << "Left";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerDir = SnakeLinkedList::EDirection::eRight;
            std::cout << "right";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerDir = SnakeLinkedList::EDirection::eUp;
            std::cout << "up";
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerDir = SnakeLinkedList::EDirection::eDown;
            std::cout << "down";
        }


        //////////////   Tick     /////////////////////
        if (timer > delay) { timer = 0; Tick(); }
        ///////////////////  Drawing  /////////////////////
        window->clear(sf::Color(0, 0, 0, 255));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {//Background//
                tileWhite.setPosition(i * spriteSize, j * spriteSize);  window->draw(tileWhite);
            }
        }
        for (int i = 0; i < 5; i++)
        {//fruit//
            if (!fruits[i].dead) {
                switch (fruits[i].value)
                {
                case 1:
                    tileYellow.setPosition(fruits[i].pos.x * spriteSize, fruits[i].pos.y * spriteSize);
                    window->draw(tileYellow);
                    break;
                case 2:
                    tileLBlue.setPosition(fruits[i].pos.x * spriteSize, fruits[i].pos.y * spriteSize);
                    window->draw(tileLBlue);
                    break;
                case 3:
                    tileOrange.setPosition(fruits[i].pos.x * spriteSize, fruits[i].pos.y * spriteSize);
                    window->draw(tileOrange);
                    break;
                case 4:
                    tileRed.setPosition(fruits[i].pos.x * spriteSize, fruits[i].pos.y * spriteSize);
                    window->draw(tileRed);
                    break;
                case 5:
                    tilePurple.setPosition(fruits[i].pos.x * spriteSize, fruits[i].pos.y * spriteSize);
                    window->draw(tilePurple);
                    break;
                }
            }

        }
        for (auto& snake : snakes)
        {
            snake.Draw(*window);
            //snake
        }

        window->display();
        ////////////////////////////////////
    }
   

    return 0;
}