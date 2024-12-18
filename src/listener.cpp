/*
Author: Adarsh TS
Class: ECE6122 A
Last Date Modified: Nov 16, 2025 
Description:
This files acts as the server code that sends controls the the robot
*/

#include <iostream>

#include <SFML/Network/UdpSocket.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    std::cout << "Enter a port number: ";
    sf::UdpSocket socket;
    socket.setBlocking(false);
    unsigned short port;
    std::cin >> port;

    // bind the socket to a port
    if (socket.bind(port) != sf::Socket::Done)
    {
        std::cout << "Error binding!" << std::endl;
        return 1;
    }

    char cmd;
    std::size_t received;
    sf::IpAddress sender;

    bool sim_start = false;
    sf::Texture texture;
    if (!texture.loadFromFile("robot.png"))
    {
        std::cout << "Unable to load robot texture" << std::endl;
    }
    sf::Sprite robot;
    robot.setTexture(texture);
    robot.setPosition(200, 200);
    robot.setScale(0.5, 0.5);

    sf::Vector2f direction = sf::Vector2f(0, -1);
    int speed = 3;
    sf::Vector2f motion = sf::Vector2f(direction.x * speed, direction.y * speed);
    sf::Clock clock;
    clock.restart();

    // run the program as long as the window is open
    while (window.isOpen())
    {
        window.clear(sf::Color::White);
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        if (socket.receive(&cmd, 1, received, sender, port) == sf::Socket::Done)
        {
            std::cout << "Received: " << cmd << std::endl;
            sim_start = true;

            switch (cmd)
            {
            case 'w':
                direction = sf::Vector2f(0, -1);
                break;
            case 's':
                direction = sf::Vector2f(0, 1);
                break;
            case 'a':
                direction = sf::Vector2f(-1, 0);
                break;
            case 'd':
                direction = sf::Vector2f(1, 0);
                break;
            case 'g':
                speed = std::min(speed + 1, 100);
                break;
            case 'h':
                speed = std::max(1, speed - 1);
                break;
			case 'q':
				std::cout << "Client is disconnecting!" << std::endl;	
				sim_start = false;
				break;
            default:
                break;
            }
        }

        if (sim_start && clock.getElapsedTime().asSeconds() >= 1)
        {
            motion = sf::Vector2f(direction.x * speed, direction.y * speed);
            robot.move(motion);
            clock.restart();
        }

        if(sim_start)
        {
            window.draw(robot);
        }
        window.display();
    }

    return 0;
}
