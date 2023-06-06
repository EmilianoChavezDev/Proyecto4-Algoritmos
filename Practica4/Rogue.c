#include <stdlib.h>
#include "Rogue.h"
#include "Game.h"
#include "Monster.h"
#include "Dungeon.h"
#include "AlgoRogue.h"


/* implement here the Rogue game stragegy to escape from Monster*/
Site moveRogue(Game* game) {
	/*REPLACE THIS WITH YOUR CODE TO AVOID MONSTER*/
	Site move;
	move.i = 0;
	move.j = 0;

	Site nuevo = getMovimientoRogue(game);
	move.i = nuevo.i;
	move.j = nuevo.j;
	/*if (game) {
		RogueData* rg = game->rogueData;
		Site monster = getMonsterSite(game);
		Site rogue = getRogueSite(game);
		// take random legal move
		int n = 0;
		for (int i = 0; i < game->N; i++) {
			for (int j = 0; j < game->N; j++) {
				Site site;
				site.i = i;
				site.j = j;
				if (isLegalMoveDungeon(game->dungeon, rogue, site)) {
					n++;
					if (rand() % 1000 <= 1000 / n) {
						move.i = site.i;
						move.j = site.j;
					}
				}
			}
		}
	}*/
	return move;
}
