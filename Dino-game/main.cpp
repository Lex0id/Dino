#include <iostream>

#include <iostream>
#include <stdlib.h>
#include <time.h>

#include <SFML/Audio.hpp>
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
int score = 0;
bool spawn = false;
int rockWidth = 60;
int rockHeight = 70;
bool stop = false;
int speed = 20;
using namespace sf;
int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "ZOMBIE TIME");
    window.setFramerateLimit(30);
    Texture textureBackground, dinoImg, rockImg;
    Sprite sprite, dino, rock[3];

    float dinoSpeed = 1;

    Texture t_game_over;
    if (!t_game_over.loadFromFile("../game_over.png")) {
        std::cout << "can't load game_over.png file" << std::endl;
    }

    Sprite game_over;
    game_over.setTexture(t_game_over);

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

        rock[0].setPosition(-300,-500);
        rock[1].setPosition(-300,-500);
        rock[2].setPosition(-300,-500);

    }
    if(!dinoImg.loadFromFile("../dino.png")){
        std::cout << "error dino image" << std:: endl;
    }
    else
    {
        dino.setTexture(dinoImg);
        dino.setPosition(0,0);
    }
    Font neodgm;
    if (!neodgm.loadFromFile("../neodgm.ttf")) {
        std::cout << "can't neodgm.ttf file" << std::endl;
    }
    Text text_score, text_best_score;
    text_score.setFont(neodgm);
    text_score.setCharacterSize(50);
    text_score.setFillColor(Color::White);
    text_score.setPosition(950, 20);
    Clock score_time;
    for(int i = 0; i < 3; i ++)
        rockPosition[i] = -300;
    // run the program as long as the window is open
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed((Keyboard::Delete)))
                window.close();
        }
        if(!stop) {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                dino_fly = true;
                key_control = true;
            }
            // score---------------------------------
            if (score_time.getElapsedTime().asSeconds() >= 0.1f) {
                score += 1;
            }
            text_score.setString(std::to_string(score));
            // score---------------------------------

            if (dino_fly) {
                if (!dino_up && dino_height >= jump_height) {
                    dino_height -= 20;
                } else if (dino_up) {
                    dino_height += 20;
                }
                dino.setPosition(20, dino_height + 100);


                if (dino_height <= jump_height) {
                    dino_up = true;
                }
                if (dino_height == 0) {
                    dino_up = false;
                    dino_fly = false;
                    key_control = false;
                }

            } else if (!dino_fly) {
                dino_height = 0;
                dino.setPosition(20, 100);
            }


            if (rand() % 9 == 0 && distance > 300) {
                for (int i = 0; i < 3; i++) {

                    if (rockPosition[i] <= -300) {
                        rock[i].setPosition(WIDTH, 370);
                        rockPosition[i] = WIDTH;
                        break;
                    }

                }
                distance = 0;
            }
            if(score % 100 == 0 && score < 500){
                speed += 5;
            }

            for (int i = 0; i < 3; i++)
                rockPosition[i] -= speed;

            for (int i = 0; i < 3; i++)
                rock[i].setPosition(rockPosition[i], 370);

            distance += speed - 15;//odleglosc miedzy kamieniami
            window.clear(Color::White);
            window.draw(sprite);
            window.draw(dino);
            window.draw(text_score);

            for(int i = 0; i < 3; i++)
                window.draw(rock[i]);

            for (int i = 0; i < 3; i++)
                if ((dino.getPosition().x - rock[i].getPosition().x > -rockWidth) &&
                    (dino.getPosition().x - rock[i].getPosition().x < rockWidth + 20)) {
                    if ((dino.getPosition().y - rock[i].getPosition().y + 270 > -rockHeight) &&
                        (dino.getPosition().y - rock[i].getPosition().y + 270 < rockHeight))
                    {
                        stop = true;

                    }
                }
        }else
        {
           // window.clear(Color:: White);
            window.draw(game_over);
            if (Keyboard::isKeyPressed(Keyboard::Space)) {
                stop = false;
                score_time.restart();
                dino_fly = false;
                dino_up = false;
                dino_height = 0;
                jump_height = -150;
                block = false;
                for(int i = 0; i < 3; i ++)
                    rockPosition[i] = -300;
                distance = 100;
                score = 0;
                speed =20;
            }
        }

        window.display();

    }

    return 0;
}