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

unsigned int estNouvellePartie(void)
{
	FILE *fichierTest;
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s/Niveau/salle_actuelle.txt", personnage.nom);

	fichierTest = fopen(chemin, "r");

	if(fichierTest == NULL)
		return 1;
	else
	{
		fclose(fichierTest);
		return 0;
	}
}

void initialiserCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{
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

void mettreAjourCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{
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

	initialiserCarteNiveau(carteNiveau);

	if(!niveauActuel.estDansCaverne)
	{	
		indexLig = positionJoueurCarte[niveauActuel.salleActuelle][LIG];
		indexCol = positionJoueurCarte[niveauActuel.salleActuelle][COL];
		carteNiveau[indexLig][indexCol] = 'X';
	}
}

void afficherLigneCarteNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE],
	const unsigned int indexLigneCarte)
{
	compteur indexCarte;

	for(indexCarte = 0; carteNiveau[indexLigneCarte][indexCarte] != '\0'; ++indexCarte)
	{
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

void afficherLigneEnnemiNiveau(const unsigned int indexLigneEnnemi)
{
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

void afficherInformationJeu(const char *description, const unsigned int nombre, 
	const unsigned int retourLigne)
{
	printf("%s", description);

	if(strcmp(description, "Sante : ") == 0 && nombre <= 3)
	{
		couleur(ROUGE);
		printf("%d", nombre);
		couleur(BLANC);
	}
	else
	{
		couleur(BLEU);
		printf("%d", nombre);
		couleur(BLANC);
	}
	
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

void afficherLigneInformationNiveau(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE],
	const unsigned int indexLigne)
{
	if(personnage.attaque.aAttaqueEnnemi)
		afficherLigneEnnemiNiveau(indexLigne);
	else
		afficherLigneCarteNiveau(carteNiveau, indexLigne);

	printf("\t\t");
}

void afficherInformationEtCarteJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{	
	compteur indexLigne;

	afficherLigneInformationNiveau(carteNiveau, 0);
	afficherInformationJeu("Niveau actuel : ", personnage.niveauActuel, RETOUR_LIGNE);

	afficherLigneInformationNiveau(carteNiveau, 1);
	afficherInformationJeu("LVL : ", personnage.lvl, RETOUR_LIGNE);
	
	afficherLigneInformationNiveau(carteNiveau, 2);
	afficherInformationJeu("Niveau EXP : ", personnage.niveauEXPActuel, NON_RETOUR_LIGNE);
	afficherInformationJeu("/", NB_EXP_NIVEAU_MAX, RETOUR_LIGNE);
	
	afficherLigneInformationNiveau(carteNiveau, 3);
	afficherInformationJeu("Sante : ", personnage.santeActuelle, NON_RETOUR_LIGNE);
	afficherInformationJeu("/", personnage.sante, RETOUR_LIGNE);
	
	afficherLigneInformationNiveau(carteNiveau, 4);
	afficherInformationJeu("Degat par tour : ", personnage.degatParTour + inventaire.arme.degat, RETOUR_LIGNE);
	
	afficherLigneInformationNiveau(carteNiveau, 5);
	afficherInformationJeu("Protection : ", personnage.protection + inventaire.armure.protection, RETOUR_LIGNE);

	for(indexLigne = 6; indexLigne < 9; ++indexLigne)
	{
		afficherLigneInformationNiveau(carteNiveau, indexLigne);
		putchar('\n');
	}

	if(personnage.attaque.aAttaqueEnnemi)
		afficherCaracteristiqueEnnemi(personnage.attaque.indexEnnemiAttaque);
}

void afficherZoneInformation(void)
{
	compteur indexInfo;

	for(indexInfo = 0; indexInfo < NB_INFO_MAX; ++indexInfo)
	{
		if(zoneInformation.message[indexInfo].texte[0] != '\0')
		{
			coloration(zoneInformation.message[indexInfo].texte, zoneInformation.message[indexInfo].couleur);
			putchar('\n');
		}
	}
}

void initialiserZoneInformation(void)
{
	compteur indexInfo;

	zoneInformation.infoActuelle = 0;

	for(indexInfo = 0; indexInfo < NB_INFO_MAX; ++indexInfo)
		zoneInformation.message[indexInfo].texte[0] = '\0';
}

void ajouterMessageZoneInformation(const char *message, const unsigned int couleurMessage)
{
	sprintf(zoneInformation.message[zoneInformation.infoActuelle].texte, "%s", message);
	zoneInformation.message[zoneInformation.infoActuelle].couleur = couleurMessage;
	++(zoneInformation.infoActuelle);
}

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

	afficherInformationEtCarteJeu(carteNiveau);
	afficherZoneInformation();

	afficherSalleActuelle();
}

void preparatifJeu(char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE])
{
	if(estNouvellePartie())
	{
		genererNiveau();

		if(personnage.niveauActuel == 1)
			initialiserInventaire();
	}
	else
		chargerNiveau();

	chargerInventaire();

	mettreAjourCarteNiveau(carteNiveau);
}

void initialiserVariable(void)
{
	personnage.attaque.aAttaqueEnnemi = 0;
	personnage.attaque.indexEnnemiAttaque = 0;
}

void jeu(void)
{
	char carteNiveau[NB_LIGNE_CARTE][NB_COLONNE_CARTE];

	preparatifJeu(carteNiveau);

	do
	{
		afficherJeu(carteNiveau);

		initialiserZoneInformation();
		initialiserVariable();

		actionJoueur();
		actionCase(carteNiveau);

		IAennemi();

		decrementezNbTourPotionActive();

	} while(personnage.santeActuelle > 0);

	ajouterMessageZoneInformation("Vous etes mort...", ROUGE);

	afficherJeu(carteNiveau);
	initialiserZoneInformation();
	attendre(2);

	mourrir();
}
