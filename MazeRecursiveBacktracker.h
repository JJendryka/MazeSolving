#pragma once

#include <vector>
#include <bitset>
#include <array>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class MazeRecursiveBacktracker {
public:
    MazeRecursiveBacktracker(std::string filePath);
    void solveMaze();

private:
    std::array<short, 4> randomDirections();

    unsigned int size;
    unsigned short difficulty;

    std::vector<bool> grid;

    sf::RenderWindow window;
    sf::Image mazeImage;
    sf::Texture texture;
    sf::RectangleShape rectangle;
};