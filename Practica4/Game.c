#define _CTR_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "Game.h"
#include "Rogue.h"
#include "Monster.h"
/*ADD HERE YOUR STRUCTURES DATA
E.G. populateAdjacency matrix from the dungeon model, etc...*/
MonsterData* createMonsterData(Game* g) {
	if (g) {
		MonsterData* m = (MonsterData*)malloc(sizeof(struct _MonsterData));
		if (m) {
			//init your struct/containers
			m->replaceThisWithYourDataContainer = NULL;
			return m;
		}
	}
	return NULL;
}
/*don't forget to free all allocated memory*/
void destroyMonsterData(MonsterData* m) {
	if (m) {
		free(m);
	}
}

RogueData* createRogueData(Game* g) {
	if (g) {
		RogueData* r = (RogueData*)malloc(sizeof(struct _RogueData));
		if (r) {
			//init your struct/containers
			r->replaceThisWithYourDataContainer = NULL;
			return r;
		}
	}
	return NULL;
}

void destroyRogueData(RogueData* r) {
	if (r) {
		free(r);
	}
}

#pragma warning(disable : 4996)
Game* createGame(char* fileName) {
	FILE* in = NULL;
	Game* g = NULL;
	char** board = NULL;
	char line[MAX_LINE_LENGTH];
	int line_count = 0;
	int N = 0;
	in = fopen(fileName, "r");

	if (!in)
	{
		printf("invalid file name %s \n", fileName);
		return NULL;
	}
	g = (Game*)malloc(sizeof(struct _Game));
	g->ROGUE = '@';
	fgets(line, MAX_LINE_LENGTH, in);
	N = atoi(line);
	g->N = N;
	board = (char**)malloc(N * sizeof(char*));
	for (int i = 0; i < N; i++)
		board[i] = (char*)malloc(N * sizeof(char));

	for (int i = 0; i < N; i++) {
		fgets(line, MAX_LINE_LENGTH, in);
		for (int j = 0; j < N; j++) {
			board[i][j] = line[2 * j];
			// check for monster's location
			if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
				g->MONSTER = board[i][j];
				board[i][j] = '.';
				g->monsterSite.i = i;
				g->monsterSite.j = j;
			}

			// check for rogue's location
			if (board[i][j] == g->ROGUE) {
				board[i][j] = '.';
				g->rogueSite.i = i;
				g->rogueSite.j = j;
			}
		}
	}
	g->dungeon = createDungeon(board, N);
	g->monsterData = createMonsterData(g);
	g->rogueData = createRogueData(g);
	//dispose board allocated memory
	if (board) {
		for (int i = 0; i < N; i++)
			free(board[i]);
		free(board);
	}

	if (in)
		fclose(in);
	return g;
}

void destroyGame(Game* g) {
	if (g) {
		if (g->dungeon) {
			free(g->dungeon);
		}
		if (g->monsterData) {
			destroyMonsterData(g->monsterData);
		}
		if (g->rogueData) {
			destroyRogueData(g->rogueData);
		}
		free(g);
	}
}


Site getMonsterSite(Game* g) { return g->monsterSite; }
Site getRogueSite(Game* g) { return g->rogueSite; }
Dungeon* getDungeon(Game* g) { return g->dungeon; }

// print representation of game state 
void printGame(Game* g) {
	for (int i = 0; i < g->N; i++) {
		for (int j = 0; j < g->N; j++) {
			Site site;
			site.i = i;
			site.j = j;
			if (equalsSite(g->rogueSite, g->monsterSite) && (equalsSite(g->rogueSite, site))) printf("* ");
			else if (equalsSite(g->rogueSite, site))                               printf("%c ", g->ROGUE);
			else if (equalsSite(g->monsterSite, site))                             printf("%c ", g->MONSTER);
			else if (isRoomDungeon(g->dungeon, site))                                 printf(". ");
			else if (isCorridorDungeon(g->dungeon, site))                             printf("+ ");
			else if (isRoomDungeon(g->dungeon, site))                                 printf(". ");
			else if (isWallDungeon(g->dungeon, site))                                 printf("  ");
		}
		printf("\n");
	}
	printf("------------------------------------\n");
}

void playGame(Game* g) {
	if (g) {
		for (int t = 1; 1 == 1; t++) {
			printf("Move %d\n", t);
			// monster moves
			if (equalsSite(g->monsterSite, g->rogueSite)) break;
			Site next = moveMonster(g);
			if (isLegalMoveDungeon(g->dungeon, g->monsterSite, next)) g->monsterSite = next;
			else {
				printf("Monster caught cheating\n POS[%d][%d]", next.i, next.j);
				return;
			}
			printGame(g);
			// rogue moves
			if (equalsSite(g->monsterSite, g->rogueSite)) break;
			next = moveRogue(g);
			if (isLegalMoveDungeon(g->dungeon, g->rogueSite, next)) g->rogueSite = next;
			else {
				printf("Rogue caught cheating\n");
				return;
			}
			printGame(g);
		}
		printf("Caught by monster\n");
	}
}
int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Way of use: c:>Proy2.exe dungeonA.txt\n");
		return 1;
	}
	Game* g = createGame(argv[1]);
	//printf("Cantidad de filas: %d", g->N);
	printGame(g);
	playGame(g);
	destroyGame(g);
	return 0;
}