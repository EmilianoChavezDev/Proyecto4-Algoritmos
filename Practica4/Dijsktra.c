#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<conio.h>
#include <math.h>
#include "Game.h"


#define INFINITY 99999
#define MAX 100

typedef struct _Nodo {
	int i;
	int j;
	int nombre;
	struct _Nodo* Suroeste;
	struct _Nodo* Noroeste;
	struct _Nodo* Noreste;
	struct _Nodo* Oeste;
	struct _Nodo* Este;
	struct _Nodo* Sureste;
	struct _Nodo* Norte;
	struct _Nodo* Sur;
}Nodo;

Site dijkstra(int G[MAX][MAX], int n, int startnode, int endnode);

Site calcularDijkstra(Game* g) {
	Nodo listaNodo[MAX];

	int n = sqrt(MAX);
	int G[MAX][MAX];


	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			listaNodo[i * n + j].i = i;
			listaNodo[i * n + j].j = j;
			listaNodo[i * n + j].nombre = i * n + j;

			Site site;
			site.i = i;
			site.j = j;

			//si es pasillo permitir que solo carge norte, sur, este y oeste
			//conexion al Este
			if (j + 1 < n && (isCorridorDungeon(g->dungeon, site) || isRoomDungeon(g->dungeon, site))) {
				Site auxSite;
				auxSite.i = i;
				auxSite.j = j + 1;
				if (!isWallDungeon(g->dungeon, auxSite)) {
					listaNodo[i * n + j].Este = &(listaNodo[i * n + j + 1]);
				}
				else {
					listaNodo[i * n + j].Este = NULL;
				}
			}
			else {
				listaNodo[i * n + j].Este = NULL;
			}


			//conexion al Oeste
			if (j - 1 >= 0 && (isCorridorDungeon(g->dungeon, site) || isRoomDungeon(g->dungeon, site))) {
				Site auxSite;
				auxSite.i = i;
				auxSite.j = j - 1;


				if (!isWallDungeon(g->dungeon, auxSite)) {
					listaNodo[i * n + j].Oeste = &(listaNodo[i * n + j - 1]);
				}
				else {
					listaNodo[i * n + j].Oeste = NULL;
				}
			}
			else {
				listaNodo[i * n + j].Oeste = NULL;
			}
			//conexion al Norte
			if (i - 1 >= 0 && (isCorridorDungeon(g->dungeon, site) || isRoomDungeon(g->dungeon, site))) {
				Site auxSite;
				auxSite.i = i - 1;
				auxSite.j = j;


				if (!isWallDungeon(g->dungeon, auxSite)) {
					listaNodo[i * n + j].Norte = &(listaNodo[(i - 1) * n + j]);
				}
				else {
					listaNodo[i * n + j].Norte = NULL;
				}
			}
			else {
				listaNodo[i * n + j].Norte = NULL;
			}

			//conexion al Sur
			if (i + 1 < n && (isCorridorDungeon(g->dungeon, site) || isRoomDungeon(g->dungeon, site))) {
				Site auxSite;
				auxSite.i = i + 1;
				auxSite.j = j;

				if (!isWallDungeon(g->dungeon, auxSite)) {
					listaNodo[i * n + j].Sur = &(listaNodo[(i + 1) * n + j]);
				}
				else {
					listaNodo[i * n + j].Sur = NULL;
				}
			}
			else {
				listaNodo[i * n + j].Sur = NULL;
			}

			//conexion al Noreste
			if (j + 1 < n && i - 1 >= 0 && isRoomDungeon(g->dungeon, site)) {
				Site auxSite;
				auxSite.i = i - 1;
				auxSite.j = j + 1;


				if (!isWallDungeon(g->dungeon, auxSite)) {
					listaNodo[i * n + j].Noreste = &(listaNodo[(i - 1) * n + j + 1]);
				}
				else {
					listaNodo[i * n + j].Noreste = NULL;
				}
			}
			else {
				listaNodo[i * n + j].Noreste = NULL;
			}

			//conexion al Noroeste
			if (j - 1 >= 0 && i - 1 >= 0 && isRoomDungeon(g->dungeon, site)) {
				Site auxSite;
				auxSite.i = i - 1;
				auxSite.j = j - 1;


				if (!isWallDungeon(g->dungeon, auxSite)) {
					listaNodo[i * n + j].Noroeste = &(listaNodo[(i - 1) * n + j - 1]);
				}
				else {
					listaNodo[i * n + j].Noroeste = NULL;
				}
			}
			else {
				listaNodo[i * n + j].Noroeste = NULL;
			}

			//conexion al Suroeste
			if (j - 1 >= 0 && i + 1 < n && isRoomDungeon(g->dungeon, site)) {
				Site auxSite;
				auxSite.i = i + 1;
				auxSite.j = j - 1;


				if (!isWallDungeon(g->dungeon, auxSite)) {
					listaNodo[i * n + j].Suroeste = &(listaNodo[(i + 1) * n + j - 1]);
				}
				else {
					listaNodo[i * n + j].Suroeste = NULL;
				}
			}
			else {
				listaNodo[i * n + j].Suroeste = NULL;
			}
			//conexion al Sureste
			if (j + 1 < n && i + 1 < n && isRoomDungeon(g->dungeon, site)) {
				Site auxSite;
				auxSite.i = i + 1;
				auxSite.j = j + 1;


				if (!isWallDungeon(g->dungeon, auxSite)) {
					listaNodo[i * n + j].Sureste = &(listaNodo[(i + 1) * n + j + 1]);
				}
				else {
					listaNodo[i * n + j].Sureste = NULL;
				}
			}
			else {
				listaNodo[i * n + j].Sureste = NULL;
			}

		}
	}

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			if (listaNodo[i].Noreste && listaNodo[i].Noreste->nombre == j) {

				G[i][j] = 1;
			}
			else if (listaNodo[i].Noroeste && listaNodo[i].Noroeste->nombre == j) {
			
				G[i][j] = 1;
			}
			else if (listaNodo[i].Oeste && listaNodo[i].Oeste->nombre == j) {
			
				G[i][j] = 1;
			}
			else if (listaNodo[i].Suroeste && listaNodo[i].Suroeste->nombre == j) {
		
				G[i][j] = 1;
			}
			else if (listaNodo[i].Norte && listaNodo[i].Norte->nombre == j) {
				
				G[i][j] = 1;
			}
			else if (listaNodo[i].Sur && listaNodo[i].Sur->nombre == j) {
			
				G[i][j] = 1;
			}
			else if (listaNodo[i].Sureste && listaNodo[i].Sureste->nombre == j) {
			
				G[i][j] = 1;
			}
			else if (listaNodo[i].Este && listaNodo[i].Este->nombre == j) {
				
				G[i][j] = 1;
			}
			else {
			
				G[i][j] = 0;
			}
		}
		
	}

	
	int nodo = g->monsterSite.i * 10 + g->monsterSite.j;
	int nodoFinal = g->rogueSite.i * 10 + g->rogueSite.j;

	printf("\nPosicion del monstruo: %d\n", nodo);
	Site ret = dijkstra(G, MAX, nodo, nodoFinal);
	return ret;
}



Site dijkstra(int G[MAX][MAX], int n, int startnode, int endnode)
{

	int cost[MAX][MAX], distance[MAX], pred[MAX];
	int visited[MAX], count, mindistance, nextnode, i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (G[i][j] == 0)
				cost[i][j] = INFINITY;
			else
				cost[i][j] = G[i][j];

	for (i = 0; i < n; i++)
	{
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}

	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;

	while (count < n - 1)
	{
		mindistance = INFINITY;

		//nextnode gives the node at minimum distance
		for (i = 0; i < n; i++)
			if (distance[i] < mindistance && !visited[i])
			{
				mindistance = distance[i];
				nextnode = i;
			}

		//check if a better path exists through nextnode            
		visited[nextnode] = 1;
		for (i = 0; i < n; i++)
			if (!visited[i])
				if (mindistance + cost[nextnode][i] < distance[i])
				{
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
		count++;
	}

	//print the path and distance of each node
	int nodos[10];
	int cantNodos = 0;
	for (i = 0; i < n; i++)
		if (i != startnode)
		{
			if (distance[i] < 50 && endnode == i) {

				
				j = i;
				do
				{
					j = pred[j];
					nodos[cantNodos++] = j;
				
				} while (j != startnode);
			}
		}

	if (cantNodos - 2 < 0) {
		printf("\nJuego Finalizado\n%d %d\n\n\n", nodos[0] / 10, (nodos[0] - (nodos[0] / 10) * 10));
		Site retorno;
		retorno.i = endnode / 10;
		retorno.j = endnode - (endnode / 10) * 10;
		return retorno;
	}
	Site retorno;
	int pos = cantNodos - 2 < 0 ? 0 : cantNodos - 2;
	retorno.i = nodos[pos] / 10;
	retorno.j = (nodos[pos] - (nodos[pos] / 10) * 10);

	return retorno;
}











