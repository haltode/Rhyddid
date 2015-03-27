#ifndef ATTAQUE_H
#define ATTAQUE_H

/* attaque.c/attaque.h : permet au joueur d'attaquer un ennemi */

/* ----- A inclure ----- */


/* ----- Define ----- */


/* ----- Structure + Enumeration ----- */

typedef struct Attaque Attaque;
struct Attaque
{
	unsigned int aAttaqueEnnemi;
	unsigned int indexEnnemiAttaque;
};

/* ----- Prototype ----- */

void infligerDegatEnnemi(const unsigned int indexEnnemi, const unsigned int degat);


unsigned int joueurPeutAttaquerEnnemi(const unsigned int indexEnnemi);
void attaquerEnnemi(void);

/* ----- Declaration ----- */

#endif
