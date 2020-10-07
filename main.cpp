#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <cmath>
#include <iostream>

using namespace sf;

int tailleX = 1000, tailleY = 600;

struct Element
{
    Texture texture;
    Sprite sprite;
    float vitesse;  // Vitesse calculé par le rapport vitesse de la planete / vitesse de pluton
    int x,y,rayon; // Rayon par rapport au soleil
};

void initialiseElementImage(std::map<std::string, Element>& ElementMAP);

void dessinerFond(std::map<std::string, Element>& ElementMAP, RenderWindow& window);
void dessinerPlanete(std::map<std::string, Element>& ElementMAP, RenderWindow& window, long double t);

void dezoomer(std::map<std::string, Element>& ElementMAP, RenderWindow& window);
void zoomer(std::map<std::string, Element>& ElementMAP, RenderWindow& window);

int main()
{
    RenderWindow window(VideoMode(tailleX, tailleY), "Projet Panete");
    std::map<std::string, Element> ElementMAP;   initialiseElementImage(ElementMAP);


    while (window.isOpen())
    {
        Event event;

        for(long double t = 0 ; t > -1 ; t += 0.0003)
        {
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and tailleX < 11000 and tailleY < 10500)
                dezoomer(ElementMAP,window);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and tailleX > 1000 and tailleY > 600)
                zoomer(ElementMAP,window);

            window.clear();

            dessinerPlanete(ElementMAP, window,t);

            window.display();
        }

    }

    return 0;
}

void initialiseElementImage(std::map<std::string, Element>& ElementMAP)
{
    if (ElementMAP["Espace"].texture.loadFromFile("Images/Fond.gif"))
        ElementMAP["Espace"].sprite.setTexture(ElementMAP["Espace"].texture);

    if (ElementMAP["Soleil"].texture.loadFromFile("Images/Soleil.png"))
    {
        ElementMAP["Soleil"].sprite.setTexture(ElementMAP["Soleil"].texture);
        ElementMAP["Soleil"].x = (tailleX/2)-25;
        ElementMAP["Soleil"].y = (tailleY/2)-75;
        ElementMAP["Soleil"].sprite.setPosition(ElementMAP["Soleil"].x, ElementMAP["Soleil"].y);
    }

    if (ElementMAP["Mercure"].texture.loadFromFile("Images/Mercure.png"))
    {
        ElementMAP["Mercure"].sprite.setTexture(ElementMAP["Mercure"].texture);
        ElementMAP["Mercure"].rayon = 50;
        ElementMAP["Mercure"].vitesse = 9.5;
        ElementMAP["Mercure"].sprite.setPosition(ElementMAP["Soleil"].x + ElementMAP["Mercure"].rayon, ElementMAP["Soleil"].y);
    }

    if (ElementMAP["Venus"].texture.loadFromFile("Images/Venus.png"))
    {
        ElementMAP["Venus"].sprite.setTexture(ElementMAP["Venus"].texture);
        ElementMAP["Venus"].rayon = 92;
        ElementMAP["Venus"].vitesse = 7;
        ElementMAP["Venus"].sprite.setPosition(ElementMAP["Soleil"].x + ElementMAP["Venus"].rayon, ElementMAP["Soleil"].y);
    }

    if (ElementMAP["Terre"].texture.loadFromFile("Images/Terre.png"))
    {
        ElementMAP["Terre"].sprite.setTexture(ElementMAP["Terre"].texture);
        ElementMAP["Terre"].rayon = 128;
        ElementMAP["Terre"].vitesse = 5.8;
        ElementMAP["Terre"].sprite.setPosition(ElementMAP["Soleil"].x + ElementMAP["Terre"].rayon, ElementMAP["Soleil"].y);
    }

    if (ElementMAP["Mars"].texture.loadFromFile("Images/Mars.png"))
    {
        ElementMAP["Mars"].sprite.setTexture(ElementMAP["Mars"].texture);
        ElementMAP["Mars"].rayon = 195;
        ElementMAP["Mars"].vitesse = 4.8;
        ElementMAP["Mars"].sprite.setPosition(ElementMAP["Soleil"].x + ElementMAP["Mars"].rayon, ElementMAP["Soleil"].y);
    }

    if (ElementMAP["Jupiter"].texture.loadFromFile("Images/Jupiter.png"))
    {
        ElementMAP["Jupiter"].sprite.setTexture(ElementMAP["Jupiter"].texture);
        ElementMAP["Jupiter"].rayon = 666;
        ElementMAP["Jupiter"].vitesse = 2.6;
        ElementMAP["Jupiter"].sprite.setPosition(ElementMAP["Soleil"].x + ElementMAP["Jupiter"].rayon, ElementMAP["Soleil"].y);
    }

    if (ElementMAP["Saturne"].texture.loadFromFile("Images/Saturne.png"))
    {
        ElementMAP["Saturne"].sprite.setTexture(ElementMAP["Saturne"].texture);
        ElementMAP["Saturne"].rayon = 1223;
        ElementMAP["Saturne"].vitesse = 2;
        ElementMAP["Saturne"].sprite.setPosition(ElementMAP["Soleil"].x + ElementMAP["Saturne"].rayon, ElementMAP["Saturne"].y);
    }

    if (ElementMAP["Uranus"].texture.loadFromFile("Images/Uranus.png"))
    {
        ElementMAP["Uranus"].sprite.setTexture(ElementMAP["Uranus"].texture);
        ElementMAP["Uranus"].rayon = 2461;
        ElementMAP["Uranus"].vitesse = 1.4;
        ElementMAP["Uranus"].sprite.setPosition(ElementMAP["Soleil"].x + ElementMAP["Uranus"].rayon, ElementMAP["Uranus"].y);
    }

    if (ElementMAP["Neptune"].texture.loadFromFile("Images/Neptune.png"))
    {
        ElementMAP["Neptune"].sprite.setTexture(ElementMAP["Neptune"].texture);
        ElementMAP["Neptune"].rayon = 3846;
        ElementMAP["Neptune"].vitesse = 1.4;
        ElementMAP["Neptune"].sprite.setPosition(ElementMAP["Soleil"].x + ElementMAP["Neptune"].rayon, ElementMAP["Neptune"].y);
    }

    if (ElementMAP["Pluton"].texture.loadFromFile("Images/Pluton.png"))
    {
        ElementMAP["Pluton"].sprite.setTexture(ElementMAP["Pluton"].texture);
        ElementMAP["Pluton"].rayon = 5064;
        ElementMAP["Pluton"].vitesse = 1;
        ElementMAP["Pluton"].sprite.setPosition(ElementMAP["Soleil"].x + ElementMAP["Pluton"].rayon, ElementMAP["Pluton"].y);
    }
}

void dessinerPlanete(std::map<std::string, Element>& ElementMAP, RenderWindow& window, long double t)
{

    int x,y;

    // ---------------------- ESPACE -------------------- \\

    window.draw(ElementMAP["Espace"].sprite);

    // ---------------------- SOLEIL -------------------- \\

    ElementMAP["Soleil"].sprite.setPosition(ElementMAP["Soleil"].x, ElementMAP["Soleil"].y);
    window.draw(ElementMAP["Soleil"].sprite);

    // ---------------------- MERCURE -------------------- \\

    x = ElementMAP["Soleil"].x+ElementMAP["Mercure"].rayon*cos(ElementMAP["Mercure"].vitesse*t + 0.785398163);
    y = ElementMAP["Soleil"].y+ElementMAP["Mercure"].rayon*-sin(ElementMAP["Mercure"].vitesse*t + 0.785398163);

    ElementMAP["Mercure"].sprite.setPosition(x, y);
    window.draw(ElementMAP["Mercure"].sprite);

    // ---------------------- VENUS -------------------- \\

    x = ElementMAP["Soleil"].x+ElementMAP["Venus"].rayon*cos(ElementMAP["Venus"].vitesse*t + 0.523598776);
    y = ElementMAP["Soleil"].y+ElementMAP["Venus"].rayon*-sin(ElementMAP["Venus"].vitesse*t + 0.523598776);

    ElementMAP["Venus"].sprite.setPosition(x, y);
    window.draw(ElementMAP["Venus"].sprite);

    // ---------------------- TERRE -------------------- \\

    x = ElementMAP["Soleil"].x+ElementMAP["Terre"].rayon*cos(ElementMAP["Terre"].vitesse*t);
    y = ElementMAP["Soleil"].y+ElementMAP["Terre"].rayon*-sin(ElementMAP["Terre"].vitesse*t);

    ElementMAP["Terre"].sprite.setPosition(x, y);
    window.draw(ElementMAP["Terre"].sprite);

    // ---------------------- MARS -------------------- \\

    x = ElementMAP["Soleil"].x+ElementMAP["Mars"].rayon*cos(ElementMAP["Mars"].vitesse*t + 3.66519143);
    y = ElementMAP["Soleil"].y+ElementMAP["Mars"].rayon*-sin(ElementMAP["Mars"].vitesse*t + 3.66519143);

    ElementMAP["Mars"].sprite.setPosition(x, y);
    window.draw(ElementMAP["Mars"].sprite);


    // ---------------------- JUPITER -------------------- \\

    x = ElementMAP["Soleil"].x+ElementMAP["Jupiter"].rayon*cos(ElementMAP["Jupiter"].vitesse*t + 0.785398163);
    y = ElementMAP["Soleil"].y+ElementMAP["Jupiter"].rayon*-sin(ElementMAP["Jupiter"].vitesse*t + 0.785398163);

    ElementMAP["Jupiter"].sprite.setPosition(x, y);
    window.draw(ElementMAP["Jupiter"].sprite);

    // ---------------------- SATURNE -------------------- \\

    x = ElementMAP["Soleil"].x+ElementMAP["Saturne"].rayon*cos(ElementMAP["Saturne"].vitesse*t + 5.75958653);
    y = ElementMAP["Soleil"].y+ElementMAP["Saturne"].rayon*-sin(ElementMAP["Saturne"].vitesse*t + 5.75958653);

    ElementMAP["Saturne"].sprite.setPosition(x, y);
    window.draw(ElementMAP["Saturne"].sprite);

    // ---------------------- URANUS -------------------- \\

    x = ElementMAP["Soleil"].x+ElementMAP["Uranus"].rayon*cos(ElementMAP["Uranus"].vitesse*t + 1.04719755);
    y = ElementMAP["Soleil"].y+ElementMAP["Uranus"].rayon*-sin(ElementMAP["Uranus"].vitesse*t + 1.04719755);

    ElementMAP["Uranus"].sprite.setPosition(x, y);
    window.draw(ElementMAP["Uranus"].sprite);

    // ---------------------- NEPTUNE -------------------- \\

    x = ElementMAP["Soleil"].x+ElementMAP["Neptune"].rayon*cos(ElementMAP["Neptune"].vitesse*t);
    y = ElementMAP["Soleil"].y+ElementMAP["Neptune"].rayon*-sin(ElementMAP["Neptune"].vitesse*t);

    ElementMAP["Neptune"].sprite.setPosition(x, y);
    window.draw(ElementMAP["Neptune"].sprite);

    // ---------------------- PLUTON -------------------- \\

    x = ElementMAP["Soleil"].x+ElementMAP["Pluton"].rayon*cos(ElementMAP["Pluton"].vitesse*t + 5.23598776);
    y = ElementMAP["Soleil"].y+ElementMAP["Pluton"].rayon*-sin(ElementMAP["Pluton"].vitesse*t + 5.23598776);

    ElementMAP["Pluton"].sprite.setPosition(x, y);
    window.draw(ElementMAP["Pluton"].sprite);
}

void dezoomer(std::map<std::string, Element>& ElementMAP, RenderWindow& window)
{
    View vue;

    tailleX+=50; tailleY+=50;

    ElementMAP["Soleil"].x = tailleX/2;     ElementMAP["Soleil"].y = tailleY/2;

    ElementMAP["Espace"].sprite.setScale(ElementMAP["Espace"].sprite.getScale().x+0.04,ElementMAP["Espace"].sprite.getScale().y+0.04);

    vue.setSize(tailleX,tailleY);   vue.setCenter( ElementMAP["Soleil"].x , ElementMAP["Soleil"].y);

    window.setView(vue);
}

void zoomer(std::map<std::string, Element>& ElementMAP, RenderWindow& window)
{
    View vue;

    tailleX-=50; tailleY-=50;

    ElementMAP["Soleil"].x = tailleX/2;     ElementMAP["Soleil"].y = tailleY/2;

    ElementMAP["Espace"].sprite.setScale(ElementMAP["Espace"].sprite.getScale().x-0.04,ElementMAP["Espace"].sprite.getScale().y-0.04);

    vue.setSize(tailleX,tailleY);   vue.setCenter( ElementMAP["Soleil"].x , ElementMAP["Soleil"].y);

    window.setView(vue);
}
