#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>

class Snake {

    public:
        /**
         * @brief Construct a new Snake object
         * 
         */
        Snake();
        
        /**
         * @brief Construct a new Snake object in a specified position
         * 
         * @param gridPos Vector2f with coordinate of this part of the snake
         * @param Direction Which direction the snake is moving in
         */
        Snake( sf::Vector2f gridPos, int direction );

        /**
         * @brief Get the Grid Position of the piece
         * 
         * @return sf::Vector2f 
         */
        sf::Vector2f getGridPos() const;

        /**
         * @brief Get the Direction object
         * 
         * @return int 
         */
        int getDirection() const;

        /**
         * @brief Set the Direction the snake piece is moving in
         * 
         * @param newDir 
         */
        void setDirection(int const NEW_DIR);

        /**
         * @brief draws the piece of the snake
         * 
         * @param window 
         */
        void draw(sf::RenderWindow& window);


    private:
        sf::RectangleShape _body;
        sf::Vector2f _gridPos;
        int _direction;
};

#endif //SNAKE_H
