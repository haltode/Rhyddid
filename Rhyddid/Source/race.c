#include <stdio.h>
#include <string.h>

#include "race.h"
#include "fonctionsUtiles.h"
#include "effacer.h"
#include "couleur.h"
#include "personnage.h"

/* Renvoie le nom de la race correspondant a l'index indexRace */
const char *recupererNomRace(const unsigned int indexRace)
{
	static const char *baseTypeRace[NB_RACE] = 
	{
		"Humain",
		"Alien",
		"Nain",
		"Sorcier",
		"Guerrier",
		"Ogre"
	};

	return baseTypeRace[indexRace];
}

/* Renvoie l'index correspondant au nom de la race donne en parametre */
unsigned int recupererIndexRace(const char *nomRace)
{
	compteur indexRace;

	/* On teste chaque race et on renvoie l'index correspondant */

	for(indexRace = 0; indexRace < NB_RACE; ++indexRace)
	{
		if(strcmp(recupererNomRace(indexRace), nomRace) == 0)
			return indexRace;
	}

	return ERREUR_RACE;
}

/* Cree un menu contenant chaque race */
void creerMenuRace(Menu *menu)
{
	compteur indexRace;

	menuNouveau(menu);

	for(indexRace = 0; indexRace < NB_RACE; ++indexRace)
		menuAjouter(menu, NULL, recupererNomRace(indexRace));
}

/* Affiche la race donnee en parametre */
void afficherRace(const char *nomRace)
{
	/* Contient les differents angles de vue possible d'une race */
	static const char *angleDeVue[NB_ANGLE_DE_VUE] =
	{
		"devant",
		"gauche",
		"derriere",
		"droite"
	};
	compteur indexAngleDeVue;
	char titreRace[TAILLE_MAX];
	char chemin[TAILLE_MAX];

	sprintf(titreRace, "Race : %s", nomRace);

	/* Pour chaque angle de vue possible */
	for(indexAngleDeVue = 0; indexAngleDeVue < NB_ANGLE_DE_VUE; ++indexAngleDeVue)
	{
		sprintf(chemin, "ASCII_Art/ASCII_Art_Race/%s/%s_%s.txt", nomRace, nomRace, angleDeVue[indexAngleDeVue]);

		/* On affiche le nom de la race */

		effacer();
		titre(titreRace, VERT);

		/* On affiche l'ASCII Art correspondant a la race et a l'angle de vue */
		lireEtAfficher(chemin);

		/* On attend une seconde entre chaque angle de vue */
		attendre(1);
	}

	/* On re-affiche l'ASCII Art correspondant a la race mais de l'angle de vue Devant pour 
	permettre au joueur de bien visualiser la race avant de faire son choix */

	effacer();
	titre(titreRace, VERT);

	sprintf(chemin, "ASCII_Art/ASCII_Art_Race/%s/%s_%s.txt", nomRace, nomRace, angleDeVue[DEVANT]);

	lireEtAfficher(chemin);
}

/* Permet de visualiser les differentes races */
void visualiserRaceNouveauPersonnage(void)
{
	Menu race;
	unsigned int choixJoueur;

	/* On cree un menu contenant chaque race */
	creerMenuRace(&race);

	/* On affiche le menu et on demande le choix du joueur */

	printf("\nQuelle race voulez-vous visualiser ?\n\n");

	menuAfficher(&race);
	choixJoueur = choisirMenuSansOperationPossible(NB_RACE);

	/* On affiche la race choisit par le joueur */
	afficherRace(recupererNomRace(choixJoueur - 1));

	appuyezEntree("\n\nAppuyez sur ENTREE pour visualiser ou choisir une race : ");
	choisirEtVisualiserRaceNouveauPersonnage();
}

/* Permet de choisir une race */
void choisirRaceNouveauPersonnage(void)
{
	Menu race;
	unsigned int choixJoueur;

	/* On cree un menu contenant chaque race */
	creerMenuRace(&race);

	printf("\nQuelle race voulez-vous choisir ?\n\n");

	/* On affiche le menu et on demande le choix du joueur */

	menuAfficher(&race);
	choixJoueur = choisirMenuSansOperationPossible(NB_RACE);

	/* On sauvegarde la race choisit par le joueur */
	strcpy(personnage.race, recupererNomRace(choixJoueur - 1));
}

/* Permet de choisir entre soit visualiser soit choisir une race */
void choisirEtVisualiserRaceNouveauPersonnage(void)
{
	Menu choixJoueur;

	effacer();
	titre("Nouvelle Partie", VERT);

	/* On demande au joueur ce qu'il veut faire et on le fait */

	menuNouveau(&choixJoueur);

	menuAjouter(&choixJoueur, visualiserRaceNouveauPersonnage, "Visualiser race");
	menuAjouter(&choixJoueur, choisirRaceNouveauPersonnage, "Choisir race");

	menuChoisirSansOperationPossible(&choixJoueur, "Que souhaitez-vous faire ?");		
}

/* Demande la race du nouveau personnage */
void demanderRaceNouveauPersonnage(void)
{
	/* On demande au joueur s'il veut visualiser ou choisir une race */
	choisirEtVisualiserRaceNouveauPersonnage();

	/* On affecte les caracteristiques de la race choisit */
	affecterCaracteristiqueRace();
}

/* Affecte les caracteristiques d'une race donnee en parametre au joueur */
void affecterCaracteristiqueRace(void)
{
	/* Contient les caracteristiques (sante, protection, degat) de chaque race */
	static const unsigned int baseCaracteristiqueRace[NB_RACE][NB_CARACTERISTIQUE_RACE] =
	{
		{14, 2, 7},
		{13, 3, 7},
		{10, 7, 6},
		{16, 1, 6},
		{7, 4, 12},
		{9, 0, 14}
	};
	unsigned int indexRace;

	/* On recupere l'index correspondant au nom de la race */
	indexRace = recupererIndexRace(personnage.race);

	/* On copie toutes les caracteristiques de la race choisit */

	personnage.sante = baseCaracteristiqueRace[indexRace][SANTE_RACE];
	personnage.protection = baseCaracteristiqueRace[indexRace][PROTECTION_RACE];
	personnage.degatParTour = baseCaracteristiqueRace[indexRace][DEGAT_RACE];
}
