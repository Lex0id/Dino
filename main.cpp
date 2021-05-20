#include <iostream>

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define WIDTH 1080
#define HEIGHT 720

bool key_control = false;
bool dino_fly = false;
bool dino_up = false;
int dino_height = 0;
int jump_height = -150;
bool block = false;
int rockPosition[3];
int distance = 100;

using namespace sf;
int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "ZOMBIE TIME");
    window.setFramerateLimit(30);
    Texture textureBackground, dinoImg, rockImg;
    Sprite sprite, dino, rock[3];

    float dinoSpeed = 1;

    if(!textureBackground.loadFromFile("../background.png")){
        std::cout << "error backround image" << std::endl;
    }

    else{
        Vector2u TextureSize = textureBackground.getSize();
        Vector2u WindowSize = window.getSize();
        float ScaleX = (float) WindowSize.x / TextureSize.x;
        float ScaleY = (float ) WindowSize.y /TextureSize.y;
        sprite.setTexture(textureBackground);
        sprite.setScale(ScaleX, ScaleY);
    }
    if(!rockImg.loadFromFile("../rock.png")){
        std::cout << "error rock image" << std:: endl;
    }else
    {

        rock[0].setTexture(rockImg);
        rock[1].setTexture(rockImg);
        rock[2].setTexture(rockImg);

        rock[0].setPosition(-300,0);
        rock[1].setPosition(-300,0);
        rock[2].setPosition(-300,0);

    }
    if(!dinoImg.loadFromFile("../dino.png")){
        std::cout << "error dino image" << std:: endl;
    }
    else
    {
        dino.setTexture(dinoImg);
        dino.setPosition(0,0);
    }
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if(Keyboard::isKeyPressed((Keyboard::Delete)))
                window.close();
        }
        //dino movement

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            dino_fly = true;
            key_control = true;
        }
        if (dino_fly == true)
        {
            if (dino_up == false && dino_height >= jump_height)
            {
                dino_height -= 20;
            }
            else if (dino_up == true)
            {
                dino_height += 20;
            }
            dino.setPosition(20, dino_height+100);

            window.draw(dino);

            if (dino_height <= jump_height)
            {
                dino_up=true;
            }
            if(dino_height==0)
            {
                dino_up = false;
                dino_fly = false;
                key_control = false;
            }

        }
        else if (dino_fly == false)
        {
            dino_height = 0;
            dino.setPosition(20, 100);
        }


        if (rand() % 9 == 0 && block == false && distance > 300)
        {
            for(int i = 0; i < 3; i ++)
            {

                if(rockPosition[i] <= -300)
                {
                    rock[i].setPosition(WIDTH, 370);
                    rockPosition[i] = WIDTH;
                    break;
                }

            }

            distance = 0;



            block = true;


        }else

            for(int i = 0; i < 3; i ++)
                rockPosition[i] -= 20;

            for(int i = 0; i < 3; i ++)
                rock[i].setPosition(rockPosition[i], 370);



            distance += 20;

            if(distance > 300)
                block = false;



        window.clear(Color::White);
        // draw everything here...
        window.draw(sprite);
        window.draw(dino);
        for(int i = 0; i < 3; i++)
        window.draw(rock[i]);
        // end the current frame
        window.display();

    }

    return 0;
}
