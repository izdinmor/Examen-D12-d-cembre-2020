#pragma once
#pragma warning (disable:4996);
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

const int widthMax = 31;
const int heightMax = 16;
typedef struct element {
	int type = 0;		// valeur qui permettra de déterminer ce qu'il faudra afficher 0=rien, 1= chasseur,2 = chasseur faisant son rapport, 3=chasseur en attente,4 = monstre
	int monsterTrace = 0; // enregistrera la valeur des traces laisséespar le monstre 
	int hunterTrace = 0; //enregistrera la valeur des traces laissées par les chasseurs

}mapElement;

typedef struct joueur {
	int x = 0;
	int y = 0;
	int alive = 1;
	int order = 0;
}hunter;

typedef struct personnage {
	int x = 0;
	int y = 0;
	int health = 4;
	int hit = 0; //détermine si le monstre a ete touché
	int turnVisible = -1; 
}monster;
void showMap(mapElement map[][heightMax],hunter* chasseurs, monster MonkC[]);
void initHunter(int nbHunter, hunter* chasseurs, mapElement map[][heightMax]);
void placeHunter(mapElement map[][heightMax], int nbHunter, hunter* chasseurs);
void eraseHunter(mapElement map[][heightMax], int nbHunter, hunter* chasseurs);
int trackMonster(mapElement map[][heightMax], int nbHunter, hunter* chasseurs, int i,monster MonkC[]);
void initMonster(monster MonkC[], mapElement map[][heightMax]);
void moveHunter(int i, hunter* chasseurs, mapElement map[][heightMax],monster MonkC[]);
int aliveHunter(int nbHunter, hunter* chasseurs);
void moveMonster(monster MonkC[], mapElement map[][heightMax]);
int trackHunter(mapElement map[][heightMax], monster MonkC[]);
void gameTurn(mapElement map[][heightMax],monster MonkC[]);
void killHunter(int nbHunter, monster MonkC[], hunter* chasseurs);
void shootMonster(monster MonkC[]);