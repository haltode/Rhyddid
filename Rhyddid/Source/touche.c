#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "touche.h"
#include "deplacement.h"
#include "sauvegarderNiveau.h"
#include "pause.h"
#include "inventaire.h"
#include "attaque.h"
#include "fonctionsUtiles.h"
#include "personnage.h"

/* Touche de Rhyddid :

z = haut
s = bas
q = gauche
d = droite

n = sauvegarder et quitter
m = sauvegarder

ECHAP = pause

e = inventaire

t = attaquer ennemi

h = potion de sante niveau I
j = potion de force niveau I
k = potion de resistance niveau I

H = potion de sante niveau II
J = potion de force niveau II
K = potion de resistance niveau II

*/

unsigned int estDirection(const char touche)
{
	static const char basedirectionPossible[] = "zZsSqQdD";

	return strchr(basedirectionPossible, touche) != NULL;
}

unsigned int estMenuPause(const unsigned int touche)
{
	return touche == ECHAP;
}

unsigned int testerTouche(const char touche, const char actionTouche)
{
	char minuscule, majuscule;
	
	minuscule = tolower(actionTouche);
	majuscule = toupper(actionTouche);

	return touche == minuscule || touche == majuscule;
}

void effectuerActionToucheEntree(const char toucheEntree)
{
	static const Touche baseTouche[NB_TOUCHE] =
	{
		{'n', 	&sauvegarderEtQuitterNiveau},
		{'m', 	&sauvegarderNiveau},
		{'e', 	&ouvrirInventaire},
		{'t', 	&attaquerEnnemi}
	};
	compteur indexTouche;

	for(indexTouche = 0; indexTouche < NB_TOUCHE; ++indexTouche)
		if(testerTouche(toucheEntree, baseTouche[indexTouche].touche))
			baseTouche[indexTouche].pointeurFonction();

	if(estDirection(toucheEntree))
	{
		unsigned int directionTouche;
	
		directionTouche = recupererDirectionTouche(toucheEntree);
		deplacerJoueurDirection(directionTouche, personnage.positionJoueur);
	}
	else if(estMenuPause(toucheEntree))
		menuPause();
	else if(testerTouche(toucheEntree, 'h'))
		utiliserPotionSante(toucheEntree);
	else if(testerTouche(toucheEntree, 'j'))
		utiliserPotionForce(toucheEntree);
	else if(testerTouche(toucheEntree, 'k'))
		utiliserPotionResistance(toucheEntree);
}
