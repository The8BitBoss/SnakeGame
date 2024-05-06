#include <SFML/Graphics.hpp>
#include "Game.h"
#include <iostream>

Game::Game() {

}
Game::~Game() {

}
void Game::Setup() 
{
    //////// Load Sprites //////////
 
   if (!tW.loadFromFile("Assets/white.png") ||!tGry.loadFromFile("Assets/gray.png") ||!tKey.loadFromFile("Assets/key.png") || !tR.loadFromFile("Assets/red.png") || !tO.loadFromFile("Assets/orange.png") || !tY.loadFromFile("Assets/yellow.png") || !tG.loadFromFile("Assets/green.png") || !tLB.loadFromFile("Assets/lBlue.png") || !tB.loadFromFile("Assets/blue.png") || !tP.loadFromFile("Assets/purple.png"))
   {
        return;
   }
   spriteSize = tW.getSize().y;
    ///////////////   Create Window ///////////////////
    gScreenWidth = spriteSize * n;
    gScreenHeight = spriteSize * m;
    scoreUI = GUI(15, m, n, tGry);
    scoreUI.AddWidgit(2, 30, tKey);
    this->window = new sf::RenderWindow(sf::VideoMode(gScreenWidth + scoreUI.width, gScreenHeight), "Snake");


        //////////////////////////////Setup()///////////////////////////////////
    player = SnakeLinkedList (sf::Vector2f(3, 1), tG, "player");
    player.PushBack(sf::Vector2f(2.0f, 1.0f));
    player.PushBack(sf::Vector2f(1.0f, 1.0f));
    SnakeLinkedList snake2(sf::Vector2f(3, 5), tG, "Jormun");
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

    //Mini collison function to check against only the head
    for (auto& snake : snakes)
    {
        //snake.Move(playerDir);
        for (int i = 0; i < 5; i++)
        {
            if (!fruits[i].dead && snake.head->position == fruits[i].pos)
            {
                snake.segDebt += fruits[i].value;
                snake.score += fruits[i].value;
                std::cout << snake.name << " " << snake.score*100<< std::endl;
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
bool Game::Collisions(){// Main collision function to check against all nodes on a snake
    /////////////////////////
    // Note: while researching how to optimise collisions i was encouraged to use hashes to manage the collisions,
    // while i know how they work and can impliment them as below i struggle to see how it's easier for the machine
    // to create a hash and compare rather than just compare a vector2f, although maybe i don't truly grasp it yet   ¯\_('-')_/¯
    //////////////////////

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
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerDir = SnakeLinkedList::EDirection::eRight;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerDir = SnakeLinkedList::EDirection::eUp;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerDir = SnakeLinkedList::EDirection::eDown;
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
        scoreUI.Draw(*window);
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