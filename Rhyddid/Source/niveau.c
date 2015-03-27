#include <stdio.h>
#include <ctype.h>

#include "niveau.h"
#include "fonctionsUtiles.h"
#include "couleur.h"
#include "deplacement.h"
#include "effacer.h"
#include "personnage.h"
#include "jeu.h"

static ElementNiveau baseCaracterereNiveau[256];

unsigned int estCaractereEntreeNiveau(const char caractere)
{	
    return  caractere == '0' && 
            niveauActuel.salleActuelle == 0 && 
            !niveauActuel.estDansCaverne;
}

unsigned int estCaractereSortieNiveau(const char caractere)
{	
    return  caractere == '0' && 
            (niveauActuel.salleActuelle == 8 || 
            niveauActuel.estDansCaverne);
}

unsigned int estCaracterePorteNiveau(const char caractere)
{
	return isdigit(caractere);
}

void affecterElementTableCaractereNiveau(const char caractereSauvegardeTable, 
	const char caractereAfficheTable, const unsigned int couleurCaractereTable)
{
	ElementNiveau* element;
	element = baseCaracterereNiveau + caractereSauvegardeTable;

	element->caractereSauvegarde = caractereSauvegardeTable;
	element->caractereAffiche = caractereAfficheTable;
	element->couleurCaractere = couleurCaractereTable;
}

void creerTableCaractereNiveau(void)
{
	affecterElementTableCaractereNiveau('#', '#', BLEU);       /* Mur */
	affecterElementTableCaractereNiveau('.', '.', BLANC);      /* Espace inacessible */
	affecterElementTableCaractereNiveau(' ', ' ', BLANC);      /* Sol */
	affecterElementTableCaractereNiveau('?', 'C', JAUNE);      /* Coffre */
	affecterElementTableCaractereNiveau('_', '_', VIOLET);     /* Mur */
	affecterElementTableCaractereNiveau('-', '-', VIOLET);     /* Mur */
	affecterElementTableCaractereNiveau('|', '|', VIOLET);     /* Mur */
	affecterElementTableCaractereNiveau('\\', '\\', VIOLET);   /* Mur */
	affecterElementTableCaractereNiveau('/', '/', VIOLET);     /* Mur */
	affecterElementTableCaractereNiveau('\'', '\'', BLANC);    /* Mur */
	affecterElementTableCaractereNiveau('`', '`', BLANC);      /* Mur */
	affecterElementTableCaractereNiveau(',', ',', BLANC);      /* Mur */
	affecterElementTableCaractereNiveau('E', ' ', BLANC);      /* Entree de la caverne */
	affecterElementTableCaractereNiveau('C', ' ', BLANC);      /* Interieur de la caverne */
	affecterElementTableCaractereNiveau('N', ' ', BLANC);      /* Endroit ou rien ne peut etre
	                                                           place (entree des cavernes/niveaux etc.) */
}

void afficherCaractereNiveau(const char caractere)
{
	/* Entree */
	if(estCaractereEntreeNiveau(caractere))
		colorationCaractere('E', CYAN);
	/* Sortie */
	else if(estCaractereSortieNiveau(caractere))
		colorationCaractere('S', CYAN);
	/* Porte */
	else if(estCaracterePorteNiveau(caractere))	
		colorationCaractere('P', CYAN);
	else
	{
		ElementNiveau* elementNiveau;
		elementNiveau = baseCaracterereNiveau + caractere; 
		
		colorationCaractere(elementNiveau->caractereAffiche, elementNiveau->couleurCaractere);
	}
}

void afficherEnnemi(const unsigned int ligne, const unsigned int colonne)
{
	unsigned int indexEnnemiAafficher;
	unsigned int vieEnnemi;

	indexEnnemiAafficher = trouverIndexEnnemi(ligne, colonne);

	if(niveauActuel.estDansCaverne)
		vieEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemiAafficher].nbVie;
	else
		vieEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemiAafficher].nbVie;

	if(vieEnnemi > 0)
		colorationCaractere('X', ROUGE);
	else
		putchar(' ');
}

void afficherSalleActuelle(void)
{
	compteur indexLig, indexCol;

	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
	{
		for(indexCol = 0; indexCol < LONGUEUR_SALLE; ++indexCol)
		{
			/* Joueur */
			if(indexLig == personnage.positionJoueur[LIG] && indexCol == personnage.positionJoueur[COL])
				colorationCaractere('@', VERT);
            /* Ennemi */
			else if(estEnnemi(indexLig, indexCol))
				afficherEnnemi(indexLig, indexCol);
            /* Autre */
			else if(niveauActuel.estDansCaverne)
				afficherCaractereNiveau(niveauActuel.salle[niveauActuel.salleActuelle].caverne.mapSalle[indexLig][indexCol]);
			else
				afficherCaractereNiveau(niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[indexLig][indexCol]);
		}

		#ifndef __WIN32__
			putchar('\n');
		#endif
	}
}

void rechercherCoordoneeEntreeNouvelleSalleNiveau(const char indexSalle, 
	unsigned int *indexLigEntree, unsigned int *indexColEntree)
{
	compteur indexLig, indexCol;

	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
	{
		for(indexCol = 0; indexCol < LONGUEUR_SALLE; ++indexCol)
		{
			if(niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[indexLig][indexCol] == indexSalle)
			{
				*indexLigEntree = indexLig;
				*indexColEntree = indexCol;

				return ;
			}
		}
	}
}

void changerSalleNiveau(const unsigned int indexAncienneSalle, 
	const unsigned int indexNouvelleSalle)
{
	char message[TAILLE_MAX];
	unsigned int indexLig, indexCol;

	sprintf(message, "Vous entrez dans la salle %d !", indexNouvelleSalle + 1);
	ajouterMessageZoneInformation(message, VERT);

	niveauActuel.salleActuelle = indexNouvelleSalle;

	rechercherCoordoneeEntreeNouvelleSalleNiveau(indexAncienneSalle + '1', &indexLig, &indexCol);

	personnage.positionJoueur[LIG] = indexLig;
	personnage.positionJoueur[COL] = indexCol;
}
