#include <stdio.h>
#include <string.h>

#include "nouvelleSauvegarde.h"
#include "personnage.h"
#include "effacer.h"
#include "fonctionsUtiles.h"
#include "couleur.h"
#include "race.h"
#include "metier.h"
#include "sauvegarde.h"
#include "creerDossier.h"
#include "jeu.h"

void demanderNomNouveauPersonnage(void)
{
	printf("Entrez le nom de votre personnage : ");
	lire(stdin, personnage.nom);
}

void creerNouveauPersonnage(void)
{
	demanderNomNouveauPersonnage();
	demanderRaceNouveauPersonnage();
	demanderMetierNouveauPersonnage();
	
	initialiserNouveauPersonnage();
}

void creerDossierSauvegardeNouveauPersonnage(void)
{
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s", personnage.nom);
    creerNouveauDossier(chemin);
}

void ajouterNomSauvegardeNouvellePartie(const unsigned int indexSauvegarde)
{
	FILE *fichierSauvegarde;
	char buffer[NB_SAUVEGARDE][TAILLE_MAX];
	compteur indexLig;

	fichierSauvegarde = ouvrirFichier("Sauvegarde/nom_sauvegarde.txt", "r", 
	"fichier \"nom_sauvegarde.txt\", fonction \"ajouterNomSauvegardeNouvellePartie\"");

	for(indexLig = 0; indexLig < NB_SAUVEGARDE; ++indexLig)
		lire(fichierSauvegarde, buffer[indexLig]);

	strcpy(buffer[indexSauvegarde], personnage.nom);

	fermerFichier(fichierSauvegarde, 
	"fichier \"nom_sauvegarde.txt\", fonction \"ajouterNomSauvegardeNouvellePartie\"");


	fichierSauvegarde = ouvrirFichier("Sauvegarde/nom_sauvegarde.txt", "w+", 
	"fichier \"nom_sauvegarde.txt\", fonction \"ajouterNomSauvegardeNouvellePartie\"");

	for(indexLig = 0; indexLig < NB_SAUVEGARDE; ++indexLig)
		fprintf(fichierSauvegarde, "%s\n", buffer[indexLig]);

	fermerFichier(fichierSauvegarde, 
	"fichier \"nom_sauvegarde.txt\", fonction \"ajouterNomSauvegardeNouvellePartie\"");
}

void afficherTexteNouvellePartie(void)
{
	effacer();
	titre("Rhyddid", VERT);

	lireEtAfficher("Histoire_Rhyddid/Texte_Debut_Nouvelle_Partie.txt");
	appuyezEntree("Appuyez sur ENTREE pour accepter la mission...");
}

void nouvelleSauvegarde(const unsigned int indexSauvegarde)
{
	effacer();
	titre("Nouvelle Partie", VERT);

	creerNouveauPersonnage();
	creerDossierSauvegardeNouveauPersonnage(); 
	sauvegarderPersonnage();

	ajouterNomSauvegardeNouvellePartie(indexSauvegarde);

	afficherTexteNouvellePartie();

	jeu();
}
