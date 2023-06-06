#pragma once
#ifndef DEFINE_GAME_H
#define DEFINE_GAME_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "Dungeon.h"
#define MAX_LINE_LENGTH 80
/*ADD HERE YOUR DATA STRUCTURES NEEDED FOR MONSTER STRATEGY.
E.G. add a Adjacency Matrix for graph implementation*/
typedef struct _MonsterData {
	//add your needed structs/data containers for the Graph here.
	void* replaceThisWithYourDataContainer;
}MonsterData;

typedef struct _RogueData {
	//add your needed structs/data containers here.
	void* replaceThisWithYourDataContainer;
}RogueData;



typedef struct _Game {
	Dungeon* dungeon;
	char MONSTER;
	char ROGUE;
	int N;
	Site monsterSite;
	Site rogueSite;
	MonsterData* monsterData;
	RogueData* rogueData;
}Game;

Game* createGame(char* fileName);
void destroyGame(Game* g);
Site getMonsterSite(Game* g);
Site getRogueSite(Game* g);
Dungeon* getDungeon(Game* g);
void printGame(Game* g);
void playGame(Game* g);

MonsterData* createMonsterData(Game* g);
void destroyMonsterData(MonsterData* r);

RogueData* createRogueData(Game* g);
void destroyRogueData(RogueData* r);

#endif