#ifndef GENERER_NIVEAU_H
#define GENERER_NIVEAU_H

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

/* Permet de bloquer les acces indispensables commencant de indexLig indexCol et s'etendant de
longueurMax blocs (ligne) */
void bloquerAccesIndispensableLigneNouveauNiveau(const unsigned int indexSalle, 
	unsigned int indexLig, const unsigned int indexCol, const unsigned int longueurMax);
	/* Permet de bloquer les acces indispensables commencant de indexLig indexCol et s'etendant de
longueurMax blocs (colonne) */
void bloquerAccesIndispensableColonneNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexLig, unsigned int indexCol, const unsigned int longueurMax);
/* Permet de bloquer les acces indispensables au passage du joueur */
void bloquerAccesIndispensableNouveauNiveau(const unsigned int indexSalle);


/* Remplit la salle aleatoirement (forme et bloque les acces indispensables) */
void remplirSalleNouveauNiveau(void);


/* Tire des coordonnes aleatoirement dans la salle indexSalle du niveau et place le resultat
dans ligne et colonne */
void tirerCoordonneeAleatoireNiveau(const unsigned int indexSalle, unsigned int *ligne,
	unsigned int *colonne, const unsigned int estCaverne);


/* Tire au hasard un nombre de coffre et d'ennemi pour les salles du nouveau niveau */
void tirerNombreCoffreEtEnnemiNouveauNiveau(void);


/* Place les coffres et les ennemis des salles du niveau */
void placerCoffreEtEnnemiNouveauNiveau(void);


/* Renvoie 1 si l'obstacle a indexLig indexCol de direction directionObstacle et de longueur 
longueurObstacle est bien place et 0 sinon */
unsigned int testerPlacementObstacleNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int longueurObstacle, unsigned int indexLig, unsigned int indexCol,
	const unsigned int directionObstacle);
	/* Place un obstacle a indexLig indexCol de direction directionObstacle */
void placerObstacleEmplacementNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexLig, const unsigned int indexCol,
	const unsigned int directionObstacle);
/* Place un obstacle de longueur longueurObstacle sur le nouveau niveau */
void placerObstacleIndividuelNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int longueurObstacle);
/* Place les obstacles sur un nouveau niveau */
void placerObstacleNouveauNiveau(void);


/* Genere un nouveau niveau */
void genererNiveau(void);

/* ----- Declaration ----- */

#endif
