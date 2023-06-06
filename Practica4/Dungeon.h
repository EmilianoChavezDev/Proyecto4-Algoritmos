#pragma once
//#include <stdlib.h>
#ifndef DEFINE_DUNGEON_H
#define DEFINE_DUNGEON_H
typedef struct _Dungeon {
	int** isRoom;// is v-w a room site?
	int** isCorridor;// is v-w a corridor site?
	int N;// dimension of dungeon

}Dungeon;

typedef struct _Site {
	int i;
	int j;
}Site;


// return dimension of dungeon
int dungeonSize(Dungeon* d);

// does v correspond to a corridor site? 
int isCorridorDungeon(Dungeon* d, Site v);

// does v correspond to a room site?
int isRoomDungeon(Dungeon* d, Site v);


// does v correspond to a wall site?
int isWallDungeon(Dungeon* d, Site v);
// does v-w correspond to a legal move?
int isLegalMoveDungeon(Dungeon* d, Site v, Site w);



int manhattanToSite(Site v, Site w);

// does invoking site equal site w?
int equalsSite(Site v, Site w);

// initialize a new dungeon based on the given board
Dungeon* createDungeon(char** board, int size);

#endif