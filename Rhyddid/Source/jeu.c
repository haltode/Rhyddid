#include <stdio.h>
#include <string.h>

#include "jeu.h"
#include "effacer.h"
#include "couleur.h"
#include "personnage.h"
#include "niveau.h"
#include "action.h"
#include "inventaire.h"
#include "ennemi.h"
#include "mourrir.h"
#include "deplacement.h"
#include "genererNiveau.h"
#include "chargerNiveau.h"

/* Retourne 1 si c'est une nouvelle partie et 0 sinon */
unsigned int estNouvellePartie(void)
{
	FILE *fichierTest;
	char chemin[TAILLE_MAX];

	/* On ouvre le fichier salle_actuelle.txt */
	sprintf(chemin, "Sauvegarde/%s/Niveau/salle_actuelle.txt", personnage.nom);

	fichierTest = fopen(chemin, "r");

	/* Si on arrive pas a l'ouvrir, le fichier n'existe pas, donc c'est une nouvelle partie */
	if(fichierTest == NULL)
		return 1;
	/* Sinon si on arrive a l'ouvrir, le fichier existe, donc ce n'est pas une nouvelle partie */
	else
	{
		/* On ferme le fichier avant de retourner 0 */
		fclose(fichierTest);

		return 0;
	}
}

/* Initialise la carte du niveau */
void initialiserCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{
	/* Tableau contenant la map */
	static const char baseCarteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE] =
	{
		"|-E-|---|---|",
		"|   |   |   |",
		"|___|___|___|",
		"|   |   |   |",
		"|   |   |   |",
		"|___|___|___|",
		"|   |   |   |",
		"|   |   |   |",
		"|---|---|-S-|"
	};
	compteur indexLig, indexCol;

	for(indexLig = 0; indexLig < NB_LIGNE_CARTE; ++indexLig)
		for(indexCol = 0; indexCol < NB_COLONNE_CARTE; ++indexCol)
			carteNiveau[indexLig][indexCol] = baseCarteNiveau[indexLig][indexCol];
}

/* Met a jour la carte du niveau (place un X dans la salle ou se trouve le joueur) */
void mettreAjourCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{
	/* Tableau contenant les coordonnes du le tableau baseCarteNiveau pour marquer l'emplacement du
	joueur sur la carte */
	static const unsigned int positionJoueurCarte[NB_SALLE_NIVEAU][2] = 
	{
		{1, 2},
		{1, 6},
		{1, 10},
		{4, 2},
		{4, 6},
		{4, 10},
		{7, 2},
		{7, 6},
		{7, 10}
	};
	unsigned int indexLig, indexCol;

	/* On initialise la map */
	initialiserCarteNiveau(carteNiveau);

	/* Si le joueur n'est pas dans une caverne */
	if(!niveauActuel.estDansCaverne)
	{	
		/* On recupere les coordonnes (ligne et colonne) du X sur la map */

		indexLig = positionJoueurCarte[niveauActuel.salleActuelle][LIG];
		indexCol = positionJoueurCarte[niveauActuel.salleActuelle][COL];

		/* On place un X sur la map */
		carteNiveau[indexLig][indexCol] = 'X';
	}
}

/* Affiche une ligne de la carte */
void afficherLigneCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE],
	const unsigned int indexLigneCarte)
{
	compteur indexCarte;

	/* Pour chaque caractere de la ligne de la map */
	for(indexCarte = 0; carteNiveau[indexLigneCarte][indexCarte] != '\0'; ++indexCarte)
	{
		/* On affiche la carte en couleur */

		switch(carteNiveau[indexLigneCarte][indexCarte])
		{
			/* Entree */
			case 'E':
				colorationCaractere('E', CYAN);
			break;
			/* Sortie */
			case 'S':
				colorationCaractere('S', CYAN);
			break;
			/* Emplacement joueur */
			case 'X':
				colorationCaractere('X', VERT);
			break;	
			/* Mur */
			case '|':
				colorationCaractere('|', BLEU);
			break;
			/* Mur */
			case '-':
				colorationCaractere('-', BLEU);
			break;
			/* Mur */
			case '_':
				colorationCaractere('_', BLEU);
			break;
			/* Autre */
			default :
				putchar(carteNiveau[indexLigneCarte][indexCarte]);
			break;
		}
	}
}

/* Affiche une ligne de l'ennemi */
void afficherLigneEnnemiNiveau(const unsigned int indexLigneEnnemi)
{
	/* Tableau contenant l'ennemi */
	static const char baseEnnemi[NB_LIGNE_ENNEMI][NB_COLONNE_ENNEMI] =
	{
	    "    //\\/\\/\\",
	    "    | 0  0 |",
	    "    \\_---__/",
	    "    __|  |__",
	   "   /__    __\\",
	 " {-/ /    \\ \\-}",
	     "     |----|",
	    "    _||  ||_",
	   "   /__\\  /__\\"
	};

	coloration(baseEnnemi[indexLigneEnnemi], ROUGE);
}

/* Affiche les informations du joueur dans le jeu */
void afficherInformationJeu(const char *description, const unsigned int nombre, 
	const unsigned int retourLigne)
{
	/* On affiche la description */
	printf("%s", description);

	/* Si le nombre donne en parametre est le nombre indiquant la sante du joueur et qu'elle est
	inferieure ou egale a 3 on l'affiche en rouge */
	if(strcmp(description, "Sante : ") == 0 && nombre <= 3)
	{
		couleur(ROUGE);
		printf("%d", nombre);
		couleur(BLANC);
	}
	/* Sinon on l'affiche en bleu */
	else
	{
		couleur(BLEU);
		printf("%d", nombre);
		couleur(BLANC);
	}
	
	/* Teste pour savoir si le joueur utilise une potion et affiche le bonus a cote de la barre
	en vert */

	if(nombre == personnage.sante && description[0] == '/' && 
		inventaire.sante.nbTourPotionActive > 0)
	{
		couleur(VERT);
		printf(" (+%d)", inventaire.sante.nbBonus);
		couleur(BLANC);
	}
	else if(strcmp(description, "Degat par tour : ") == 0 && 
		inventaire.force.nbTourPotionActive > 0)
	{
		couleur(VERT);
		printf(" (+%d)", inventaire.force.nbBonus);
		couleur(BLANC);
	}
	else if(strcmp(description, "Protection : ") == 0 && 
		inventaire.resistance.nbTourPotionActive > 0)
	{
		couleur(VERT);
		printf(" (+%d)", inventaire.resistance.nbBonus);
		couleur(BLANC);
	}

	if(retourLigne)
		putchar('\n');
}

/* Affiche une ligne soit de la carte soit de l'ennemi */
void afficherLigneInformationNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE],
	const unsigned int indexLigne)
{
	/* Si le joueur a attaque un ennemi */
	if(personnage.attaque.aAttaqueEnnemi)
		/* On affiche une ligne de l'ennemi */
		afficherLigneEnnemiNiveau(indexLigne);
	/* Sinon */
	else
		/* On affiche une ligne de la map */
		afficherLigneCarteNiveau(carteNiveau, indexLigne);

	printf("\t\t");
}

/* Affiche les informations du joueur et la carte dans le jeu */
void afficherInformationEtCarteJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{	
	compteur indexLigne;

	/* Affiche la ligne 0 soit de la carte soit de l'ennemi */
	afficherLigneInformationNiveau(carteNiveau, 0);
	/* Affiche le niveau actuel du joueur */
	afficherInformationJeu("Niveau actuel : ", personnage.niveauActuel, RETOUR_LIGNE);

	/* Affiche la ligne 1 soit de la carte soit de l'ennemi */
	afficherLigneInformationNiveau(carteNiveau, 1);
	/* Affiche le lvl du joueur */
	afficherInformationJeu("LVL : ", personnage.lvl, RETOUR_LIGNE);
	
	/* Affiche la ligne 2 soit de la carte soit de l'ennemi */
	afficherLigneInformationNiveau(carteNiveau, 2);
	/* Affiche le EXP du joueur */
	afficherInformationJeu("Niveau EXP : ", personnage.niveauEXPActuel, NON_RETOUR_LIGNE);
	afficherInformationJeu("/", NB_EXP_NIVEAU_MAX, RETOUR_LIGNE);
	
	/* Affiche la ligne 3 soit de la carte soit de l'ennemi */
	afficherLigneInformationNiveau(carteNiveau, 3);
	/* Affiche la sante du joueur */
	afficherInformationJeu("Sante : ", personnage.santeActuelle, NON_RETOUR_LIGNE);
	afficherInformationJeu("/", personnage.sante, RETOUR_LIGNE);
	
	/* Affiche la ligne 4 soit de la carte soit de l'ennemi */
	afficherLigneInformationNiveau(carteNiveau, 4);
	/* Affiche les degats du joueur */
	afficherInformationJeu("Degat par tour : ", personnage.degatParTour + inventaire.arme.degat, RETOUR_LIGNE);
	
	/* Affiche la ligne 5 soit de la carte soit de l'ennemi */
	afficherLigneInformationNiveau(carteNiveau, 5);
	/* Affiche la protection du joueur */
	afficherInformationJeu("Protection : ", personnage.protection + inventaire.armure.protection, RETOUR_LIGNE);

	/* Pour chaque ligne restante de soit la carte soit de l'ennemi */
	for(indexLigne = 6; indexLigne < 9; ++indexLigne)
	{
		/* On affiche la ligne */
		afficherLigneInformationNiveau(carteNiveau, indexLigne);
		putchar('\n');
	}

	if(personnage.attaque.aAttaqueEnnemi)
		afficherCaracteristiqueEnnemi(personnage.attaque.indexEnnemiAttaque);
}

/* Affiche la zone d'information sur le jeu */
void afficherZoneInformation(void)
{
	compteur indexInfo;

	/* Pour chaque info */
	for(indexInfo = 0; indexInfo < NB_INFO_MAX; ++indexInfo)
	{
		/* Si il y a une info */
		if(zoneInformation.message[indexInfo].texte[0] != '\0')
		{
			/* On l'affiche */
			coloration(zoneInformation.message[indexInfo].texte, zoneInformation.message[indexInfo].couleur);
			putchar('\n');
		}
	}
}

/* Initialise la zone d'information sur le jeu */
void initialiserZoneInformation(void)
{
	compteur indexInfo;

	/* On met a 0 la variable infoActuelle */
	zoneInformation.infoActuelle = 0;

	/* Pour chaque info */
	for(indexInfo = 0; indexInfo < NB_INFO_MAX; ++indexInfo)
		/* On initialise le texte a 0 */
		zoneInformation.message[indexInfo].texte[0] = '\0';
}

/* Ajoute un message sur la zone d'information du jeu */
void ajouterMessageZoneInformation(const char *message, const unsigned int couleurMessage)
{
	/* On ajoute le message */
	sprintf(zoneInformation.message[zoneInformation.infoActuelle].texte, "%s", message);
	/* On ajoute la couleur */
	zoneInformation.message[zoneInformation.infoActuelle].couleur = couleurMessage;

	/* On incremente de 1 la variable infoActuelle */
	++(zoneInformation.infoActuelle);
}

/* Affiche le jeu */
void afficherJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{
	char message[TAILLE_MAX];

	effacer();
		
	if(niveauActuel.estDansCaverne)
	{
		sprintf(message, "Caverne - %s", personnage.nom);
		titre(message, VERT);
	}
	else
	{
		sprintf(message, "Rhyddid - %s", personnage.nom);
		titre(message, VERT);
	}

	/* On affiche les informations du joueur ainsi que la carte du niveau */
	afficherInformationEtCarteJeu(carteNiveau);
	/* On affiche la zone d'information du jeu */
	afficherZoneInformation();

	/* On affiche la salle */
	afficherSalleActuelle();
}

/* Fait tous les preparatifs avant le jeu */
void preparatifJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{
	/* Si c'est une nouvelle partie ou un nouveau niveau */
	if(estNouvellePartie())
	{
		/* On genere un nouveau niveau */
		genererNiveau();

		/* Si le joueur n'a  pas passe de niveau (nouvelle partie) */
		if(personnage.niveauActuel == 1)
			/* On initialise l'inventaire */
			initialiserInventaire();
	}
	/* Sinon */
	else
		/* On charge le niveau */
		chargerNiveau();

	/* On charge l'inventaire */
	chargerInventaire();

	/* On met a jour la carte du niveau */
	mettreAjourCarteNiveau(carteNiveau);
}

/* Initialise les variables importantes */
void initialiserVariable(void)
{
	personnage.attaque.aAttaqueEnnemi = 0;
	personnage.attaque.indexEnnemiAttaque = 0;
}

/* Lance le jeu */
void jeu(void)
{
	/* Contient la carte situee en haut a gauche */
	char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE];


	/* On fait les preparatifs avant de lancer le jeu */
	preparatifJeu(carteNiveau);

	/* Faire */
	do
	{
		/* On affiche le jeu */
		afficherJeu(carteNiveau);

		/* On efface la zone de texte */
		initialiserZoneInformation();
		/* On initialise les variables importantes */
		initialiserVariable();

		/* On recupere la touche entree du joueur et on execute cette touche */
		actionJoueur();
		/* On execute l'interaction avec la case sur lequel le joueur est */
		actionCase(carteNiveau);

		/* On fait bouger les ennemis grace a leur IA */
		IAennemi();

		/* On decremente les potions si le joueur en a utilisees */
		decrementezNbTourPotionActive();

	/* Tant que le joueur n'est pas mort */
	} while(personnage.santeActuelle > 0);

	/* Le joueur est mort, on affiche le jeu pendant 2 secondes et on appelle la fonction 
	mourrir */

	ajouterMessageZoneInformation("Vous etes mort...", ROUGE);

	afficherJeu(carteNiveau);
	initialiserZoneInformation();
	attendre(2);

	mourrir();
}
