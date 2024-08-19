/*
CSCI 200 - A Period

Written by: Amy Sessions

Snake Game!(to the best of my ability)
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "Snake.h"

using namespace std;
using namespace sf;


int main() {
//set random seed
    srand(time(0));
    rand();

//prep game log file
ofstream fout("GameLog.txt", ios::app);
if (!fout) {
        cerr << "Failed to open file" << endl;
        return -1;
    }
fout << time(0) << " - NEW GAME" << endl;


//set window size
    int const windWidth = 629, windHeight = 629;

//make render window
    RenderWindow window( VideoMode(windWidth, windHeight), "Snake" );

//create initial snake object
    vector<Snake> snake;
    for (float i = 1; i < 6.f; i++) {
        snake.push_back(Snake(Vector2f(i,8), 1));
    }

//generate starting apple
    Vector2f apple(12,8);
    CircleShape appleShape;
    appleShape.setRadius(18.5);
    appleShape.setPosition(apple * 37.f);
    appleShape.setFillColor(Color(164,42,4));

//event and timing for fgame inputs
    Event event;

    Clock programClock;    
    Time lastTime = programClock.getElapsedTime();

    Time currTime = programClock.getElapsedTime();

    bool win = false;
    bool lose = false;

//SFML loop(window display)
    while(window.isOpen()) {

        //generate background
        window.clear(Color(180, 196, 36));
        for (int i = 0; i < 17; i += 2) {
            for (int j = 0; j < 17; j+= 2){
                RectangleShape squares;
                squares.setSize(Vector2f(37,37));
                squares.setPosition(i*37,j*37);
                squares.setFillColor(Color(201, 204, 63));
                window.draw(squares);
                squares.setPosition(i*37+37,j*37+37);
                window.draw(squares);
            }
        }

        //draw current apple
        window.draw(appleShape);

        //draw the snake
        for (int i = 0; i < (int)snake.size(); i++) {
            snake.at(i).draw(window);
        }

        //display message if you lost the game
        if (lose) {
            sf::Font font;
            if (!font.loadFromFile("comic-sans/COMICSANSBOLD.ttf"))
                return EXIT_FAILURE;
            sf::Text text("YOU LOSE :(", font, 74);
            text.setPosition(Vector2f(74,259));
            text.setFillColor(Color::Red);
            window.draw(text);
        }


        //display message if you win the game
        if (win) {
            sf::Font font;
            if (!font.loadFromFile("comic-sans/COMICSANSBOLDITALIC.ttf"))
                return EXIT_FAILURE;
            sf::Text text("YOU WIN!!!!", font, 74);
            text.setPosition(Vector2f(74,259));
            text.setFillColor(Color::Magenta);
            window.draw(text);
        }


        //display
        window.display();

        //Check for events
        while( window.pollEvent(event)) {
            if(event.type == Event::Closed){
                window.close();
            }
            else if(event.type == Event::KeyPressed) {
                //move snake direction variable based on arrow key pressed
                if(event.key.code == Keyboard::Left && snake.back().getDirection() != 1) {
                    snake.back().setDirection(-1);
                }
                if(event.key.code == Keyboard::Right && snake.back().getDirection() != -1) {
                    snake.back().setDirection(1);
                }
                if(event.key.code == Keyboard::Up && snake.back().getDirection() != -2) {
                    snake.back().setDirection(2);
                }
                if(event.key.code == Keyboard::Down && snake.back().getDirection() != 2) {
                    snake.back().setDirection(-2);
                }
                if(event.key.code == Keyboard::Q || event.key.code == Keyboard::Escape) {
                    window.close();
                }
            }
        }



        //move snake forward one square
        currTime = programClock.getElapsedTime();
        
        if ( (currTime - lastTime).asSeconds() > (0.2) && !lose && !win ) {
            bool inSnake = false;


            //check if it runs into itself
            Snake newSnake = Snake(snake.back().getGridPos(), snake.back().getDirection());

            for (int i=0; i < (int)snake.size(); i++){
                if (snake.at(i).getGridPos() == newSnake.getGridPos()) {inSnake=true;}
                    }
            if (inSnake) {lose = true; 
            fout << "Time Elapsed: " << currTime.asSeconds() << endl;
            fout << "Final Size: " << snake.size() << endl;
            fout << "Outcome: ";
            fout << "LOSE" << endl;
            fout << endl << endl;
            continue;}
            
            snake.push_back(newSnake);

            //check if it runs into an apple - generate a new apple in a random position not in the snake if yes
            inSnake = true;
            if (snake.back().getGridPos() == apple) {
                while (inSnake) {
                    inSnake = false;
                    apple = Vector2f(rand()%17, rand()%17);
                    for (int i=0; i < (int)snake.size(); i++){
                        if (snake.at(i).getGridPos() == apple) {inSnake=true;}
                    }
                }
                appleShape.setPosition(apple*37.f);
            }
            else {snake.erase(snake.begin());}
            lastTime = currTime;
            
            }

        //change the 289 to check my win message (I tested with 7 but anything over 5 should work)
        if ((int)snake.size() == 289 && !win) {
            win = true; 
                fout << "Time Elapsed: " << currTime.asSeconds() << endl;
                fout << "Final Size: " << snake.size() << endl;
                fout << "Outcome: ";
                fout << "WIN" << endl;
                fout << endl << endl;
                continue;}

        //close window if out of bounds
        if ((snake.back().getGridPos().x >= 17 || snake.back().getGridPos().x < 0  || snake.back().getGridPos().y >= 17 || snake.back().getGridPos().y < 0) && !lose) {
            lose = true;
            fout << "Time Elapsed: " << currTime.asSeconds() << endl;
            fout << "Final Size: " << snake.size() << endl;
            fout << "Outcome: ";
            fout << "LOSE" << endl;
            fout << endl << endl;
        }
        
    }

    return 0;
}
