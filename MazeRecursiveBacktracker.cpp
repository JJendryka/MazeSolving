#include <algorithm>
#include <array>
#include <stack>
#include <iostream>
#include <SFML/Graphics/Image.hpp>
#include "MazeRecursiveBacktracker.h"

MazeRecursiveBacktracker::MazeRecursiveBacktracker(std::string filePath) : window(sf::VideoMode(800, 800), "Maze maker!!"){
    if(!mazeImage.loadFromFile(filePath)) {
        std::cout<<"Failed to load maze";
    }
    this->size = ((mazeImage.getSize().x - 1) / 2);
    srand(time(nullptr));
    window.clear(sf::Color::Black);

    grid.resize(size * size);
    std::fill(grid.begin(), grid.end(), false);

    texture.loadFromImage(mazeImage);
    rectangle.setPosition(0, 0);
    rectangle.setSize(sf::Vector2f(800, 800));
    rectangle.setTexture(&texture);
    window.draw(rectangle);
    window.display();
}

void MazeRecursiveBacktracker::solveMaze() {
    bool finished = false;
    sf::Vector2i lastPosition(0,0);
    struct Pos {unsigned int x, y, state; std::array<short, 4> order;};
    std::stack<Pos> states;

    Pos pos = {0, 0, 0, randomDirections()};
    states.push(pos);

    while (!states.empty()) {
        auto top = states.top();
        states.pop();

        grid[top.x + top.y * size] = true;

        if (top.x == size - 1 && top.y == size - 1) finished = true;

        if(!finished) {
            mazeImage.setPixel(top.x * 2 + 1, top.y * 2 + 1, sf::Color::Blue);
            if(top.state <= 3) states.push({top.x, top.y, top.state+1, top.order});
            if (top.order[top.state] == 0 && top.x != size - 1) {
                if (!(grid[(top.x + 1) + top.y * size]) &&
                    mazeImage.getPixel((top.x + 1) * 2, top.y * 2 + 1) == sf::Color::White) {
                    states.push({top.x + 1, top.y, 0, randomDirections()});

                    mazeImage.setPixel((top.x + 1) * 2, top.y * 2 + 1, sf::Color::Blue);
                }
            }
            if (top.order[top.state] == 1 && top.y != 0) {
                if (!(grid[top.x + (top.y - 1) * size]) &&
                    mazeImage.getPixel(top.x * 2 + 1, top.y * 2) == sf::Color::White) {
                    states.push({top.x, top.y - 1, 0, randomDirections()});

                    mazeImage.setPixel(top.x * 2 + 1, top.y * 2, sf::Color::Blue);
                }
            }
            if (top.order[top.state] == 2 && top.x != 0) {
                if (!(grid[(top.x - 1) + top.y * size]) &&
                    mazeImage.getPixel(top.x * 2, top.y * 2 + 1) == sf::Color::White) {
                    states.push({top.x - 1, top.y, 0, randomDirections()});

                    mazeImage.setPixel(top.x * 2, top.y * 2 + 1, sf::Color::Blue);
                }
            }
            if (top.order[top.state] == 3 && top.y != size - 1) {
                if (!(grid[top.x + (top.y + 1) * size]) &&
                    mazeImage.getPixel(top.x * 2 + 1, (top.y + 1) * 2) == sf::Color::White) {
                    states.push({top.x, top.y + 1, 0, randomDirections()});

                    mazeImage.setPixel(top.x * 2 + 1, (top.y + 1) * 2, sf::Color::Blue);
                }
            }
        } else {
            mazeImage.setPixel(top.x * 2 + 1, top.y * 2 + 1, sf::Color::Magenta);
            if (lastPosition.x != 0 || lastPosition.y != 0) {
                if (lastPosition.x > top.x) mazeImage.setPixel(top.x * 2 + 2, top.y * 2 + 1, sf::Color::Magenta);
                if (lastPosition.x < top.x) mazeImage.setPixel(top.x * 2, top.y * 2 + 1, sf::Color::Magenta);
                if (lastPosition.y > top.y) mazeImage.setPixel(top.x * 2 + 1, top.y * 2 + 2, sf::Color::Magenta);
                if (lastPosition.y < top.y) mazeImage.setPixel(top.x * 2 + 1, top.y * 2, sf::Color::Magenta);
            }
            lastPosition.x = top.x;
            lastPosition.y = top.y;

        }
        if(size <= 25) {
            texture.loadFromImage(mazeImage);
            window.draw(rectangle);
            window.display();
            bool exit = false;
            while (true) {
                sf::Event event;
                window.pollEvent(event);
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) exit = true;
                    break;
                }
            }
            if (exit) break;
        }
    }

    mazeImage.saveToFile("maze.png");
}

std::array<short, 4> MazeRecursiveBacktracker::randomDirections() {
    std::array<short, 4> directions = {0, 1, 2, 3};
    std::random_shuffle(directions.begin(), directions.end());
    return directions;
};