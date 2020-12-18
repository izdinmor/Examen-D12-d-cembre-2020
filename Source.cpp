#include "Header.h";
void main() {
	srand(time(NULL));
	int nbHunter = 0;
	int x = 0;
	int y = 0;
	char shoot;
	monster MonkC[1];
	hunter* Chasseurs = { NULL };
	mapElement map[widthMax][heightMax] = { NULL };

	do {
		printf("Avec combien de chasseurs voulez vous jouer? (minimum 1 maximum 10 )\n");
		scanf("%d", &nbHunter);
	} while (nbHunter < 1 || nbHunter>10);

	Chasseurs = (hunter*)calloc(nbHunter, sizeof(hunter));
	showMap(map, Chasseurs, MonkC);
	initHunter(nbHunter, Chasseurs, map);

	initMonster(MonkC, map);


	while ((MonkC[0].health != 0) && (aliveHunter)) {
		gameTurn(map, MonkC);
		for (int i = 0; i < nbHunter; i++) {

			if (trackMonster(map, nbHunter, Chasseurs, i, MonkC) == 1) {
				printf("Je vois le monstre !\nAppuyer sur T puis entree pour tirer\n");
				scanf(" %c", &shoot);
				switch (shoot) {
				case 't': shootMonster(MonkC);

				}
			}

			placeHunter(map, i, Chasseurs);
			system("pause");
		}


		for (int i = 0; i < nbHunter; i++) {
			moveHunter(i, Chasseurs, map, MonkC);

		}

	}
	if (MonkC[0].health == 0) {
		printf("Bravo vous avez reussi a tuer le monstre !");
	}
	if (aliveHunter == 0) {
		printf("Le monstre a reussi a tuer tous vos chasseurs, vous avez perdu !")
	}

}
void showMap(mapElement map[][heightMax],hunter*chasseurs,monster MonkC[]) {								//affiche la carte 
	
	system("cls");
	for (int i = 0; i < heightMax; i++) {
		for (int j = 0; j < widthMax; j++) {
			if ((i == 0) || (i == heightMax - 1)) { printf("*"); }
			else if ((j == 0) || (j == widthMax - 1)) { printf("*"); }
			else if (map[j][i].type == 0) { printf(" "); }
			else if (map[j][i].type == 1) { printf("P"); }
			else if (map[j][i].type == 2) { printf("!"); }
			else if (map[j][i].type == 3) { printf("?"); }
			else if ((map[j][i].type == 5) && (MonkC[0].hit == 1)) { printf("M"); }
			else (printf(" "));
		}
		printf("\n");
	}
	
	}

void initHunter(int nbHunter, hunter* chasseurs, mapElement map[][heightMax]) {						//initialisation des places de départ des chasseurs (introduites par le joueur)
	int x = 0;
	int y = 0;
	int ver = 0;
	for (int i = 0; i < nbHunter; i++) {
		chasseurs[i].order = i;
		printf("Indiquez l'emplacement de depart du chasseur %d :\nCoordonnee en X (entre 1 et 29) : ", i + 1);
		scanf("%d", &x);
		while (x < 1 || x>29) {
			printf("Veuillez entrer une valeur comprise entre 1 et 29 (1 et 29 inclus): ");
			scanf("%d", &x);


		}
		printf("Coordonnee en Y (entre 1 et 14) : ", i);
		scanf("%d", &y);
		while (y < 1 || y>14) {
			printf("Veuillez entrer une valeur comprise entre 1 et 14 (1 et 14 inclus): ");
			scanf("%d", &y);

		};
		for (int j = 0; j < nbHunter; j++) {											// vérification si le joueur a déjà mis un chasseur à cet emplacement
				while ((j != i) && (chasseurs[j].x == x) && (chasseurs[j].y == y)) {					
					
					printf("Il y a deja un chasseur a cet emplacement, veuillez entrez des coordonnes valides\nCoordonnee en X (entre 1 et 29) : ");
					scanf("%d", &x);
					printf("Coordonnee en y (entre 1 et 14) : ");
					scanf("%d", &y);
				}	

			}		
		chasseurs[i].x = x;
		chasseurs[i].y = y;
		map[chasseurs[i].x][chasseurs[i].y].hunterTrace = 17;
		placeHunter(map, i, chasseurs);
	}
}

void placeHunter(mapElement map[][heightMax], int i, hunter*chasseurs) {				//place les chasseurs sur la carte
	
		 map[chasseurs[i].x][chasseurs[i].y].type = 1;

}

void eraseHunter(mapElement map[][heightMax], int i, hunter* chasseurs) {				//enlève les chasseurs sur la carte
	
		map[chasseurs[i].x][chasseurs[i].y].type = 0;
}

int trackMonster(mapElement map[][heightMax],int nbHunter, hunter*chasseurs,int i,monster MonkC[]) {
	
	
	map[chasseurs[i].x][chasseurs[i].y].type = 2;
	showMap(map, chasseurs, MonkC);
	printf("Chaseur %d :\n", i+1);
	if (((chasseurs[i].y != 1) && (map[chasseurs[i].x][chasseurs[i].y - 1].type == 5)) //détection monstre en haut
		|| ((chasseurs[i].x != 29) && (map[chasseurs[i].x + 1][chasseurs[i].y].type == 5))  //détection monstre à droite
		|| ((chasseurs[i].y != 14) && (map[chasseurs[i].x][chasseurs[i].y + 1].type == 5))  //détection monstre en bas
		|| (chasseurs[i].x != 1) && (map[chasseurs[i].x - 1][chasseurs[i].y].type == 5))  //détection monstre à gauche
	{
		
		return 1;
		
				
	}
	else {


		if ((chasseurs[i].y != 1) && (chasseurs[i].x != 1)) {

			if (map[chasseurs[i].x - 1][chasseurs[i].y - 1].monsterTrace != 0) { printf("Trace en 1 de valeur %d\n", map[chasseurs[i].x - 1][chasseurs[i].y - 1].monsterTrace); }
			else { printf("Aucune trace en 1\n"); }
		}	//detection haut gauche (1)

		if (chasseurs[i].y != 1) {
			if (map[chasseurs[i].x][chasseurs[i].y - 1].monsterTrace != 0) { printf("Trace en 2 de valeur %d\n", map[chasseurs[i].x][chasseurs[i].y - 1].monsterTrace); }
			else { printf("Aucune trace en 2\n"); }
		}	//détection haut (2)

		if ((chasseurs[i].y != 1) && (chasseurs[i].x != 29)) {
			if (map[chasseurs[i].x + 1][chasseurs[i].y - 1].monsterTrace != 0) { printf("Trace en 3 de valeur %d\n", map[chasseurs[i].x + 1][chasseurs[i].y - 1].monsterTrace); }
			else { printf("Aucune trace en 3\n"); }
		}	//détection haut droite (3)

		if ((chasseurs[i].x != 1)) {
			if (map[chasseurs[i].x - 1][chasseurs[i].y].monsterTrace != 0) { printf("Trace en 4 de valeur %d\n", map[chasseurs[i].x - 1][chasseurs[i].y].monsterTrace); }
			else { printf("Aucune trace en 4\n"); }
		}	//détection milieu gauche (4)

		if ((chasseurs[i].x != 29)) {
			if (map[chasseurs[i].x + 1][chasseurs[i].y].monsterTrace != 0) { printf("Trace en 6 de valeur %d\n", map[chasseurs[i].x + 1][chasseurs[i].y].monsterTrace); }
			else { printf("Aucune trace en 6\n"); }
		}	//détection milieu gauche (6)

		if ((chasseurs[i].y != 14) && (chasseurs[i].x != 1)) {
			if (map[chasseurs[i].x - 1][chasseurs[i].y + 1].monsterTrace != 0) { printf("Trace en 7 de valeur %d\n", map[chasseurs[i].x - 1][chasseurs[i].y + 1].monsterTrace); }
			else { printf("Aucune trace en 7\n"); }
		}	//détection bas gauche (7)

		if (chasseurs[i].y != 14) {
			if (map[chasseurs[i].x][chasseurs[i].y + 1].monsterTrace != 0) { printf("Trace en 8 de valeur %d\n", map[chasseurs[i].x][chasseurs[i].y + 1].monsterTrace); }
			else { printf("Aucune trace en 8\n"); }
		}	//détection bas (8)

		if ((chasseurs[i].y != 14) && (chasseurs[i].x != 29)) {
			if (map[chasseurs[i].x + 1][chasseurs[i].y + 1].monsterTrace != 0) { printf("Trace en 9 de valeur %d\n", map[chasseurs[i].x + 1][chasseurs[i].y + 1].monsterTrace); }
			else { printf("Aucune trace en 9\n"); }
		}	//détection bas droite (9)
		return 0;
	}
	

	
	
	
												
}

void initMonster(monster MonkC[], mapElement map[][heightMax]) {		//initialise la place de départ du monstre sur la carte
	int x = 0;
	int y = 0;
	
	x = rand() % 29 + 1;
	y = rand() % 14 + 1;
	while ((map[x][y].type == 1) && (map[x + 1][y].type == 1) && (map[x - 1][y].type == 1) && (map[x + 1][y + 1].type == 1) && (map[x - 1][y + 1].type == 1) && (map[x - 1][y - 1].type == 1) && (map[x][y - 1].type == 1) && (map[x][y + 1].type == 1) && (map[x + 1][y - 1].type == 1)) { // vérification pour être sur le que le monstre ne commence pas aux alentours d'un chasseur
		x = rand() % 29 + 1;
		y = rand() % 14 + 1;
	};
	
	MonkC[0].x = x;
	MonkC[0].y = y;
	map[x][y].type = 5;
	map[MonkC[0].x][MonkC[0].y].monsterTrace = 17;
	




}

void moveHunter(int i, hunter* chasseurs, mapElement map[][heightMax],monster MonkC[]) {
	int choix = 0;	
	map[chasseurs[i].x][chasseurs[i].y].type = 3; // change le type pour passer à l'indication "?"
	showMap(map, chasseurs, MonkC);
		while (choix == 0) {
			
			
			printf("Choisissez le deplacement du chasseur %d (entrez le chiffre correspondant au deplacement souhaiter):\n1.Gauche 2.Droite 3.Haut 4.Bas\n", i + 1);
			scanf("%d", &choix);
			switch (choix) {
			case 1:if ((chasseurs[i].x != 1) && (map[chasseurs[i].x - 1][chasseurs[i].y].type != 1)) //vérification limite carte
			{
				eraseHunter(map, i, chasseurs);
				chasseurs[i].x = chasseurs[i].x - 1;
				placeHunter(map, i, chasseurs);


			}
				  else {
				printf("Ce deplacement n'est pas disponible choisissez une option valide\n");
				choix = 0;
			}
				  break;
			case 2:if ((chasseurs[i].x != 29) && (map[chasseurs[i].x + 1][chasseurs[i].y].type != 1))//vérification limite carte
			{
				eraseHunter(map, i, chasseurs);
				chasseurs[i].x = chasseurs[i].x + 1;
				placeHunter(map, i, chasseurs);
			}
				  else {
				printf("Ce deplacement n'est pas disponible choisissez une option valide\n");
				choix = 0;
			}
				  break;
			case 3:if ((chasseurs[i].y != 1) && (map[chasseurs[i].x][chasseurs[i].y - 1].type != 1))//vérification limite carte
			{
				eraseHunter(map, i, chasseurs);
				chasseurs[i].y = chasseurs[i].y - 1;
				placeHunter(map, i, chasseurs);
			}
				  else {
				printf("Ce deplacement n'est pas disponible choisissez une option valide\n");
				choix = 0;
			}
				  break;
			case 4:if ((chasseurs[i].y != 14) && (map[chasseurs[i].x][chasseurs[i].y + 1].type != 1))//vérification limite carte
			{
				eraseHunter(map, i, chasseurs);
				chasseurs[i].y = chasseurs[i].y + 1;
				placeHunter(map, i, chasseurs);
			}
				  else {
				printf("Ce deplacement n'est pas disponible choisissez une option valide\n");
				choix = 0;
			}
				  break;
			}

			map[chasseurs[i].x][chasseurs[i].y].hunterTrace = 17;
			
		}
		
}

int aliveHunter(int nbHunter,hunter*chasseurs) { // verification pour qu'au moins un chasseur soit en vie
	int alive = 0;
	for (int i = 0; i < nbHunter; i++) {
		if (chasseurs[i].alive == 1) { alive = alive + 1; }
	};
	if (alive > 1) { alive = 1; };
	return alive;
}

void moveMonster(monster MonkC[], mapElement map[][heightMax]) {
	int move = 0;
	int correct = 0;
	
	map[MonkC[0].x][MonkC[0].y].type = 0;
	if (trackHunter(map, MonkC) == 0) { //vérification si le déplacement du monstre doit être aléatoire ou pas, en focntion de la présence de trace ou de chasseurs 
		while (correct == 0) {
			correct = 1;
			move = rand() % 4 + 1;
			if ((move == 1) && (MonkC[0].y == 1)) { correct == 0; }	//verification du déplacement
			if ((move == 2) && (MonkC[0].x == widthMax)) { correct == 0; } //verification du déplacement
			if ((move == 3) && (MonkC[0].y == heightMax)) { correct == 0; } //verification du déplacement
			if ((move == 4) && (MonkC[0].x == 1)) { correct == 0; } //verification du déplacement
		}
	}
	else { move = trackHunter(map, MonkC); }
	switch (move) {								// déplacements différents du monstre
	case 1: MonkC[0].y = MonkC[0].y - 1;
		break;
	case 2: MonkC[0].x = MonkC[0].x + 1;
		break;
	case 3: MonkC[0].y = MonkC[0].y + 1;
		break;
	case 4: MonkC[0].x = MonkC[0].x - 1;
		break;

	}
	map[MonkC[0].x][MonkC[0].y].monsterTrace = 17;
	map[MonkC[0].x][MonkC[0].y].type = 5;
	
	
	
}

int trackHunter(mapElement map[][heightMax],monster MonkC[]) { //détection des traces/emplacement des chasseurs par le monstre pour déterminer son déplacement
	int trace[4] = { NULL };
	int deplacement = 0;
	int traceSup = 0;
	if ((MonkC[0].y != 1) && (map[MonkC[0].x][MonkC[0].y - 1].type == 1)) { deplacement == 1; } //détection chasseur en haut
	else if ((MonkC[0].x != 29) && (map[MonkC[0].x+1][MonkC[0].y].type == 1)) { deplacement == 2; } //détection chasseur à droite
	else if ((MonkC[0].y != 14) && (map[MonkC[0].x][MonkC[0].y + 1].type == 1)) { deplacement == 3; } //détection chasseur en bas
	else if ((MonkC[0].x != 1) && (map[MonkC[0].x-1][MonkC[0].y].type == 1)) { deplacement == 4; } //détection chasseur à gauche
	else {


		if ((MonkC[0].y != 1) && (map[MonkC[0].x][MonkC[0].y - 1].hunterTrace != 0)) { //trace de chasseur en haut
			trace[0] = map[MonkC[0].x][MonkC[0].y - 1].hunterTrace;
		}
		if ((MonkC[0].x != 29) && (map[MonkC[0].x + 1][MonkC[0].y].hunterTrace != 0)) {	//trace de chasseur à droite
			trace[1] = map[MonkC[0].x + 1][MonkC[0].y].hunterTrace;
		}
		if ((MonkC[0].y != 14) && (map[MonkC[0].x][MonkC[0].y + 1].hunterTrace != 0)) {	//trace de chasseur en bas
			trace[2] = map[MonkC[0].x][MonkC[0].y + 1].hunterTrace;
		}
		if ((MonkC[0].x != 1) && (map[MonkC[0].x - 1][MonkC[0].y].hunterTrace != 0)) { //trace de chasseur à gauche
			trace[3] = map[MonkC[0].x - 1][MonkC[0].y].hunterTrace;
		}
		for (int i = 0; i < 4; i++) { //comparaison pour pister la trace la plus "fraiche" (ayant la valeur la plus élévée)
			if (trace[i] != 0) {
				if (trace[i] > traceSup) {
					traceSup = trace[i];
					deplacement = i + 1;
				}

			}

		}
	}
	return deplacement;
}

void gameTurn(mapElement map[][heightMax],monster MonkC[]) {
	for (int i = 0; i < heightMax; i++) {				// effacement des traces des chasseurs et du monstres
		for (int j = 0; j < widthMax; j++) {
			if (map[j][i].monsterTrace != 0) { map[j][i].monsterTrace = map[j][i].monsterTrace - 1; }
			if (map[j][i].hunterTrace != 0) { map[j][i].hunterTrace = map[j][i].hunterTrace - 1; }
		}

	}
	MonkC[0].turnVisible = MonkC[0].turnVisible - 1; // durée de la visibilité du monstre si touché
	if (MonkC[0].turnVisible == 0) { MonkC[0].hit = 0; } //fin de la visibilité du monstre
}

void killHunter(int nbHunter,monster MonkC[],hunter*chasseurs) { //mort d'un chasseur si le monstre va sur sa case

	for (int i = 0; i < nbHunter; i++) {
		if ((MonkC[0].x == chasseurs[i].x) && (MonkC[0].y == chasseurs[i].y)) {
			if (chasseurs[i].alive == 1) {

				chasseurs[i].alive = 0;
				printf("Le chasseur %d a ete tue par le monstre", i + 1);
			}
		}
	}
}

void shootMonster(monster MonkC[]) { //tir sur le monstre quand un chasseur en a l'occasion
	int chanceHit = 0;
	chanceHit = rand() % 100 + 1;
	if (chanceHit < 41) {
		MonkC[0].health = MonkC[0].health - 1;
		MonkC[0].hit = 1;
		MonkC[0].turnVisible = 4;
	}
	
	
}
