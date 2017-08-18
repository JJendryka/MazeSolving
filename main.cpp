#include <iostream>
#include "MazeRecursiveBacktracker.h"

int main()
{
    std::cout<<"Welcome in maze solving program!\n"
             <<"Choose one of following algorithms:\n"
             <<" 1) Recursive Backtracker\n";
    int algorithm;
    std::cin>>algorithm;
    if (algorithm > 1) {
        std::cout<<"Bad algorithm number! Choose 1 or 2";
        return 0;
    }
    std::cout<<"Relative path to maze\n";
    std::string filePath;
    std::cin>>filePath;
    std::cout<<"Hold any key to progress. Exit on esc\n";
    switch (algorithm) {
        case 1: {
            MazeRecursiveBacktracker maze(filePath);
            maze.solveMaze();
            break;
        }
        default: {
            std::cout << "Bad input! Choose between 1 and 3\n";
            break;
        }
    }
}