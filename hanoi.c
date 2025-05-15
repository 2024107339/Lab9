#include "hanoi.h"
#include "disk.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#define NUMBER_DISKS 3 // You can adjust the number of disks here

HanoiGame hanoiInit() {
    HanoiGame game;

    // Create a new stack to represent each tower.
    // There are always three towers.
    for(int i=0; i<3; i++) {
        game.towers[i] = stackCreate(); //TODO: create a new stack
    }

    //Place all disks in first tower, i.e., in game.towers[0]
    //the larger disk must sit at the bottom of the tower
    for(int i=NUMBER_DISKS; i>0; i--) {
        Disk disk = diskCreate(i); //TODO: create a new disk
        stackPush(game.towers[0], disk); //TODO: push the disk to the tower
    }

    //TODO: constant NUMBER_DISKS defines the disk count 

    return game;
}

void hanoiPrint(PtHanoiGame game) {
    printf("### GAME STATE ###\n");

    // Print all tower's contents
    for(int i=0; i<3; i++) {
        printf("\n🗼 Tower %d: \n", (i+1));
        stackPrint(game->towers[i]);
    }

    printf("\n##################\n");
}

bool hanoiMakeMove(PtHanoiGame game, int towerFrom, int towerTo) {
    Disk diskToMove;
    Disk diskOnTop;

    // Check if the tower numbers are valid
    if (towerFrom < 1 || towerFrom > 3 || towerTo < 1 || towerTo > 3) {
        return false;
    }
    // Adjust for 0-based indexing
    towerFrom--;
    towerTo--;

    // Check if the source tower is empty
    if (stackIsEmpty(game->towers[towerFrom])) {
        return false;
    }
    // Check if the destination tower is empty or if the top disk on the destination tower is larger
    // than the disk being moved
    stackPeek(game->towers[towerFrom], &diskToMove);
    if (!stackIsEmpty(game->towers[towerTo])) {
        stackPeek(game->towers[towerTo], &diskOnTop);
        if (diskToMove.size > diskOnTop.size) {
            return false;
        }
    }

    // Move the disk from the source tower to the destination tower
    stackPop(game->towers[towerFrom], &diskToMove);
    stackPush(game->towers[towerTo], diskToMove);
    
    // Check if the move was successful
    stackPeek(game->towers[towerTo], &diskOnTop);
    if (diskOnTop.size == diskToMove.size) {
        return true;
    }

    // If the move was not successful, free the disk and return false
    return false;
}

bool hanoiSolved(PtHanoiGame game) {
    if (stackIsEmpty(game->towers[0]) && stackIsEmpty(game->towers[1])) {
        return true;
    }
    //TODO...
    return false;
}

void hanoiCleanup(PtHanoiGame game) {
    // Free each tower
    for (int i = 0; i < 3; i++) {
        stackClear(game->towers[i]);
    }
}