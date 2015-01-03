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

/* Retourne 1 si le caractere donne en parametre est l'entree du niveau et 0 sinon */
unsigned int estCaractereEntreeNiveau(const char caractere)
{	
	/* On retourne le booleen de la condition : on teste si le caractere est '0' (caractere 
	de l'entree) ET que la salle actuelle est la premiere (car la sortie est aussi indique par
	'0' mais se trouve dans la derniere salle) ET que le joueur n'est pas dans une caverne
	(car la sortie de la caverne est aussi indique par '0') */
	return 	caractere == '0' && 
		niveauActuel.salleActuelle == 0 && 
		!niveauActuel.estDansCaverne;
}

/* Retourne 1 si le caractere donne en parametre est la sortie du niveau et 0 sinon */
unsigned int estCaractereSortieNiveau(const char caractere)
{	
	/* On retourne le booleen de la condition : on teste si le caractere est '0' (caractere 
	de sortie) ET que soit la salle actuelle est la derniere (sortie du niveau normal) soit
	que le joueur est dans une caverne (sortie de la caverne) */
	return 	caractere == '0' && 
		(niveauActuel.salleActuelle == 8 || 
		niveauActuel.estDansCaverne);
}

/* Retourne 1 si le caractere donne en parametre est une porte du niveau et 0 sinon */
unsigned int estCaracterePorteNiveau(const char caractere)
{
	/* Retourne le resusltat de isdigit (definit dans ctype.h) qui retourne 1 si le caractere
	est un chiffre et 0 sinon */
	return isdigit(caractere);
}

/* Affecte un element dans la table de donnee des caracteres du niveau */
void affecterElementTableCaractereNiveau(const char caractereSauvegardeTable, 
	const char caractereAfficheTable, const unsigned int couleurCaractereTable)
{
	/* On utilise une table de hachage pour gerer l'affichage*/

	/* On cree un nouvel element */
	ElementNiveau* element;
	/* On le fait pointer vers la case correspondante a la table de donnee */
	element = baseCaracterereNiveau + caractereSauvegardeTable;

	/* On assigne les valeurs de l'element */

	element->caractereSauvegarde = caractereSauvegardeTable;
	element->caractereAffiche = caractereAfficheTable;
	element->couleurCaractere = couleurCaractereTable;
}

/* Cree la table de donnee des caracteres du niveau */
void creerTableCaractereNiveau(void)
{
	/* On cree chaque element de la table de donnee */

	affecterElementTableCaractereNiveau('#', '#', BLEU); 	/* Mur */
	affecterElementTableCaractereNiveau('.', '.', BLANC); 	/* Espace inacessible */
	affecterElementTableCaractereNiveau(' ', ' ', BLANC); 	/* Sol */
	affecterElementTableCaractereNiveau('?', 'C', JAUNE); 	/* Coffre */
	affecterElementTableCaractereNiveau('_', '_', VIOLET); 	/* Mur */
	affecterElementTableCaractereNiveau('-', '-', VIOLET); 	/* Mur */
	affecterElementTableCaractereNiveau('|', '|', VIOLET);	/* Mur */
	affecterElementTableCaractereNiveau('\\', '\\', VIOLET);	/* Mur */
	affecterElementTableCaractereNiveau('/', '/', VIOLET); 	/* Mur */
	affecterElementTableCaractereNiveau('\'', '\'', BLANC); 	/* Mur */
	affecterElementTableCaractereNiveau('`', '`', BLANC); 	/* Mur */
	affecterElementTableCaractereNiveau(',', ',', BLANC); 	/* Mur */
	affecterElementTableCaractereNiveau('E', ' ', BLANC);	/* Entree de la caverne */
	affecterElementTableCaractereNiveau('C', ' ', BLANC); 	/* Interieur de la caverne */
	affecterElementTableCaractereNiveau('N', ' ', BLANC); 	/* Endroit ou rien ne peut etre
	place (entree des cavernes/niveaux etc.) */
}

/* Affiche un caractere de la salle donne en parametre */
void afficherCaractereNiveau(const char caractere)
{
	/* On teste d'abord les cas speciaux (entree, sortie, porte) */

	/* Entree */
	if(estCaractereEntreeNiveau(caractere))
		colorationCaractere('E', CYAN);
	/* Sortie */
	else if(estCaractereSortieNiveau(caractere))
		colorationCaractere('S', CYAN);
	/* Porte */
	else if(estCaracterePorteNiveau(caractere))	
		colorationCaractere('P', CYAN);
	/* Sinon c'est un cas normal et on affiche le caractere correspondant */
	else
	{
		/* On cree un nouvel element */
		ElementNiveau* elementNiveau;
		/* On le fait pointer vers la case correspondante a la table de donnee */
		elementNiveau = baseCaracterereNiveau + caractere; 
		
		/* On affiche l'element (caractere dans la couleur) */
		colorationCaractere(elementNiveau->caractereAffiche, elementNiveau->couleurCaractere);
	}
}

/* Affiche un ennemi aux coordonees ligne colonne */
void afficherEnnemi(const unsigned int ligne, const unsigned int colonne)
{
	unsigned int indexEnnemiAafficher;
	unsigned int vieEnnemi;

	/* On recupere l'index de l'ennemi a afficher */
	indexEnnemiAafficher = trouverIndexEnnemi(ligne, colonne);

	/* On recupere la vie de l'ennemi */

	if(niveauActuel.estDansCaverne)
		vieEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].caverne.ennemi[indexEnnemiAafficher].nbVie;
	else
		vieEnnemi = niveauActuel.salle[niveauActuel.salleActuelle].ennemi[indexEnnemiAafficher].nbVie;

	/* On regarde si l'ennemi est en vie ou pas */

	/* Si l'ennemi est en vie */
	if(vieEnnemi > 0)
		/* On affiche l'ennemi */
		colorationCaractere('X', ROUGE);
	/* Sinon */
	else
		/* On affiche le sol */
		putchar(' ');
}

/* Affiche la salle actuelle du niveau ou se trouve le joueur */
void afficherSalleActuelle(void)
{
	compteur indexLig, indexCol;

	/* Pour chaque ligne de la salle */
	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
	{
		/* Pour chaque colonne de la salle */
		for(indexCol = 0; indexCol < LONGUEUR_SALLE; ++indexCol)
		{
			/* On teste le caractere sur lequel on se trouve */

			/* Si c'est le joueur */
			if(indexLig == personnage.positionJoueur[LIG] && indexCol == personnage.positionJoueur[COL])
				colorationCaractere('@', VERT);
			/* Sinon si c'est un ennemi */
			else if(estEnnemi(indexLig, indexCol))
				afficherEnnemi(indexLig, indexCol);
			/* Sinon si c'est autre chose */

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

/* Recherche les coordonnes de l'entree d'une nouvelle salle et les place dans indexLigEntree 
et indexColEntree */
void rechercherCoordoneeEntreeNouvelleSalleNiveau(const char indexSalle, 
	unsigned int *indexLigEntree, unsigned int *indexColEntree)
{
	compteur indexLig, indexCol;

	/* Pour chaque ligne de la salle  */
	for(indexLig = 0; indexLig < LARGUEUR_SALLE; ++indexLig)
	{
		/* Pour chaque colonne de la salle */
		for(indexCol = 0; indexCol < LONGUEUR_SALLE; ++indexCol)
		{
			/* Si on a trouve l'emplacement de la porte par laquelle le joueur est passe */
			if(niveauActuel.salle[niveauActuel.salleActuelle].mapSalle[indexLig][indexCol] == indexSalle)
			{
				/* On sauvegarde les coordonnes */

				*indexLigEntree = indexLig;
				*indexColEntree = indexCol;

				/* On quitte la fonction */
				return ;
			}
		}
	}
}

/* Change le joueur de salle */
void changerSalleNiveau(const unsigned int indexAncienneSalle, 
	const unsigned int indexNouvelleSalle)
{
	char message[TAILLE_MAX];
	unsigned int indexLig, indexCol;

	/* On affiche un message indiquant le changement de salle */

	sprintf(message, "Vous entrez dans la salle %d !", indexNouvelleSalle + 1);
	ajouterMessageZoneInformation(message, VERT);

	/* On change la variable salleActuelle */
	niveauActuel.salleActuelle = indexNouvelleSalle;

	/* On cherche les coordonnes de l'entree de la nouvelle salle */
	rechercherCoordoneeEntreeNouvelleSalleNiveau(indexAncienneSalle + '1', &indexLig, &indexCol);

	/* On positionne le joueur sur ces coordonnes */

	personnage.positionJoueur[LIG] = indexLig;
	personnage.positionJoueur[COL] = indexCol;
}
