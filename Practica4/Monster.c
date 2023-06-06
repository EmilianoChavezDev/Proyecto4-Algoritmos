#include <stdlib.h>
#include "Monster.h"
#include "Dijkstra.h"

/* implement here the Monster game stragegy, i.e. use shortest path to rogue*/
Site moveMonster(Game* game) {
	//system("pause");
	/*REPLACE THIS WITH YOUR CODE TO GET SHORTEST PATH TO ROGUE*/
	Site move;
	move.i = 0;
	move.j = 0;
	if (game) {
		MonsterData* md = game->monsterData;
		Site monster = getMonsterSite(game);
		Site rogue = getRogueSite(game);

		Site sitio = calcularDijkstra(game);
		//if (isLegalMoveDungeon(game->dungeon, monster, sitio)) {
		move.i = sitio.i;
		move.j = sitio.j;
		/*}
		else {

			printf("\n\nERROR DE POSICION\nPosicion[%d][%d]\n", sitio.i, sitio.j);
			system("pause");
		}*/

		/*// take random legal move
		int n = 0;
		for (int i = 0; i < game->N; i++) {
			for (int j = 0; j < game->N; j++) {
				//Site site = new Site(i, j);
				Site site;
				site.i = i;
				site.j = j;

				//printf("Is room [%d, %d]: %d \n", i, j, isWallDungeon(game->dungeon, site));
				if (isLegalMoveDungeon(game->dungeon, monster, site)) {
					n++;
					if (rand() % 1000 <= 1000 / n) {
						move.i = site.i;
						move.j = site.j;
					}
				}
			}
		}
		printf("Nuevo sitio i = %d, j = %d", sitio.i, sitio.j);
		*/
		//system("pause");
	}
	return move;
}