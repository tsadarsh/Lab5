#include <iostream>

#include <SFML/Network/UdpSocket.hpp>

int main()
{
    sf::UdpSocket socket;

    // bind the socket to a port
    if (socket.bind(54000) != sf::Socket::Done)
    {
        std::cout << "Error binding!" << std::endl;
        return 1;
    }

    // UDP socket:
    char cmd;
    sf::IpAddress recipient = sf::IpAddress::getLocalAddress();
    std::cout << "Local IP: " << recipient << std::endl;
    unsigned short port;
    std::cout << "Enter port number to send command: ";
    std::cin >> port;
    while (true)
    {
        std::cout << "Enter command to send: ";
        std::cin >> cmd;
        if (socket.send(&cmd, 1, recipient, port) != sf::Socket::Done)
        {
            std::cout << "Error sending command!" << std::endl;
        }
    }


    return 0;
}