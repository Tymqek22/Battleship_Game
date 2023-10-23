#include <iostream>

#include "Player.h"
#include "Computer.h"

int main()
{
    Player player;

    player.placeShipsFleet();
    system("cls");
    
    Computer comp;
    
    comp.placeShipsFleet();

    do {
        system("cls");
        player.showPlayersHitBoard();
        player.hit(&comp);
        comp.hit(&player);
        

    } while (player.getLivesCount() > 0 && comp.getLivesCount() > 0);
    

    if (player.getLivesCount() == 0) {
        std::cout << "Computer won.\n";
    }
    else {
        std::cout << "Player won.\n";
    }

    //ok

    return 0;
}