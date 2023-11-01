#include <iostream>

#include "Player.h"
#include "Computer.h"
#include "Battleship.h"

int main()
{
    Player player;

    player.placeShipsFleet();
    system("cls");
    
    Computer comp;
    
    comp.placeShipsFleet();
    
    do {
        system("cls");
        std::cout << "Your lives: " << player.getLivesCount() << " - Opponent lives: " << comp.getLivesCount() << '\n';
        std::cout << "Your hit board:\n";
        player.showPlayersHitBoard();
        std::cout << "\nYour fleet:\n";
        player.showPlayersBoard();
        player.hit(&comp);
        comp.hit(&player);
        

    } while (player.getLivesCount() > 0 && comp.getLivesCount() > 0);

    system("cls");

    if (player.getLivesCount() == 0) {
        player.showPlayersBoard();
        std::cout << "Computer won.\n";
    }
    else {
        player.showPlayersHitBoard();
        std::cout << "You won.\n";
    }
    std::cout << "Your lives: " << player.getLivesCount() << " - Opponent lives: " << comp.getLivesCount() << '\n';

    //ok

    return 0;
}