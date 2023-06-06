#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Game.h"
#include "Dungeon.h"
#include "AlgoRogue.h"



Site getMovimientoRogue(Game* g) {
	//Para ver donde se encentra el monstruo y el rogue
	Site posicionMonstruo = g->monsterSite;
	Site posicionRogue = g->rogueSite;
	Site posicionNueva;
	posicionNueva.i = posicionRogue.i;
	posicionNueva.j = posicionRogue.j;

	
	// Ver que las posisiones a la que se intenta posicionar sean validas
	if ((posicionRogue.j - posicionMonstruo.j) > 0 && (posicionRogue.j + 1) < g->N) {
		posicionNueva.j += 1;

		if (!isLegalMoveDungeon(g->dungeon, posicionRogue, posicionNueva)) {
			posicionNueva.j -= 1;
		}

	}
	else if ((posicionRogue.j - posicionMonstruo.j) <= 0 && (posicionRogue.j - 1 >= 0)) {
		posicionNueva.j -= 1;

		if (!isLegalMoveDungeon(g->dungeon, posicionRogue, posicionNueva)) {
			posicionNueva.j += 1;
		}
	}
	//El rogue está en una posicion por encima del mostruo 
	if ((posicionRogue.i - posicionMonstruo.i) > 0 && (posicionRogue.i + 1) < g->N) {
		posicionNueva.i += 1;

		if (!isLegalMoveDungeon(g->dungeon, posicionRogue, posicionNueva)) {
			posicionNueva.i -= 1;
		}
	}
	else if ((posicionRogue.i - posicionMonstruo.i) <= 0 && (posicionRogue.i - 1 >= 0)) {
		posicionNueva.i -= 1;

		if (!isLegalMoveDungeon(g->dungeon, posicionRogue, posicionNueva)) {
			posicionNueva.i += 1;
		}
	}
	return posicionNueva;
}
