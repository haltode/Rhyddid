#include <stdio.h>
#include <string.h>

#include "race.h"
#include "fonctionsUtiles.h"
#include "effacer.h"
#include "couleur.h"
#include "personnage.h"

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

unsigned int recupererIndexRace(const char *nomRace)
{
	compteur indexRace;

	for(indexRace = 0; indexRace < NB_RACE; ++indexRace)
		if(strcmp(recupererNomRace(indexRace), nomRace) == 0)
			return indexRace;

	return ERREUR_RACE;
}

void creerMenuRace(Menu *menu)
{
	compteur indexRace;

	menuNouveau(menu);

	for(indexRace = 0; indexRace < NB_RACE; ++indexRace)
		menuAjouter(menu, NULL, recupererNomRace(indexRace));
}

void afficherRace(const char *nomRace)
{
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

	for(indexAngleDeVue = 0; indexAngleDeVue < NB_ANGLE_DE_VUE; ++indexAngleDeVue)
	{
		sprintf(chemin, "ASCII_Art/ASCII_Art_Race/%s/%s_%s.txt", nomRace, nomRace, angleDeVue[indexAngleDeVue]);

		effacer();
		titre(titreRace, VERT);

		lireEtAfficher(chemin);

		attendre(1);
	}

	effacer();
	titre(titreRace, VERT);

	sprintf(chemin, "ASCII_Art/ASCII_Art_Race/%s/%s_%s.txt", nomRace, nomRace, angleDeVue[DEVANT]);

	lireEtAfficher(chemin);
}

void visualiserRaceNouveauPersonnage(void)
{
	Menu race;
	unsigned int choixJoueur;

	creerMenuRace(&race);

	printf("\nQuelle race voulez-vous visualiser ?\n\n");

	menuAfficher(&race);
	choixJoueur = choisirMenuSansOperationPossible(NB_RACE);

	afficherRace(recupererNomRace(choixJoueur - 1));

	appuyezEntree("\n\nAppuyez sur ENTREE pour visualiser ou choisir une race : ");
	choisirEtVisualiserRaceNouveauPersonnage();
}

void choisirRaceNouveauPersonnage(void)
{
	Menu race;
	unsigned int choixJoueur;

	creerMenuRace(&race);

	printf("\nQuelle race voulez-vous choisir ?\n\n");

	menuAfficher(&race);
	choixJoueur = choisirMenuSansOperationPossible(NB_RACE);

	strcpy(personnage.race, recupererNomRace(choixJoueur - 1));
}

void choisirEtVisualiserRaceNouveauPersonnage(void)
{
	Menu choixJoueur;

	effacer();
	titre("Nouvelle Partie", VERT);

	menuNouveau(&choixJoueur);

	menuAjouter(&choixJoueur, visualiserRaceNouveauPersonnage, "Visualiser race");
	menuAjouter(&choixJoueur, choisirRaceNouveauPersonnage, "Choisir race");

	menuChoisirSansOperationPossible(&choixJoueur, "Que souhaitez-vous faire ?");		
}

void demanderRaceNouveauPersonnage(void)
{
	choisirEtVisualiserRaceNouveauPersonnage();
	affecterCaracteristiqueRace();
}

void affecterCaracteristiqueRace(void)
{
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

	indexRace = recupererIndexRace(personnage.race);

	personnage.sante = baseCaracteristiqueRace[indexRace][SANTE_RACE];
	personnage.protection = baseCaracteristiqueRace[indexRace][PROTECTION_RACE];
	personnage.degatParTour = baseCaracteristiqueRace[indexRace][DEGAT_RACE];
}
