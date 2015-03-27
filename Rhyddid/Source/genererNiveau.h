#ifndef GENERER_NIVEAU_H
#define GENERER_NIVEAU_H

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */


/* ----- Prototype ----- */

void bloquerAccesIndispensableLigneNouveauNiveau(const unsigned int indexSalle, 
	unsigned int indexLig, const unsigned int indexCol, const unsigned int longueurMax);
void bloquerAccesIndispensableColonneNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexLig, unsigned int indexCol, const unsigned int longueurMax);
void bloquerAccesIndispensableNouveauNiveau(const unsigned int indexSalle);


void remplirSalleNouveauNiveau(void);


void tirerCoordonneeAleatoireNiveau(const unsigned int indexSalle, unsigned int *ligne,
	unsigned int *colonne, const unsigned int estCaverne);


void tirerNombreCoffreEtEnnemiNouveauNiveau(void);


void placerCoffreEtEnnemiNouveauNiveau(void);


unsigned int testerPlacementObstacleNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int longueurObstacle, unsigned int indexLig, unsigned int indexCol,
	const unsigned int directionObstacle);
void placerObstacleEmplacementNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int indexLig, const unsigned int indexCol,
	const unsigned int directionObstacle);
void placerObstacleIndividuelNouveauNiveau(const unsigned int indexSalle, 
	const unsigned int longueurObstacle);
void placerObstacleNouveauNiveau(void);


void genererNiveau(void);

/* ----- Declaration ----- */

#endif
