#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    //Create the window with a set resolution:
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Project");
    
    //Creating a convex shape:
    sf::ConvexShape Triangle;
    Triangle.setPointCount(3);
    Triangle.setPoint(0, sf::Vector2f(640.0f, 200.0f));
    Triangle.setPoint(1, sf::Vector2f(840.0f, 500.0f));
    Triangle.setPoint(2, sf::Vector2f(440.0f, 500.0f));
    Triangle.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        //Receive and deal with events here (mouse clicks, key events, window buttons etc).
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        window.clear();
        //Do all your drawing in here/////


        window.draw(Triangle);
        

        //////////////////////////////////
        window.display();
    }

    return 0;
}