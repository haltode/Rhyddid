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

/* Demande le nom du nouveau personnage */
void demanderNomNouveauPersonnage(void)
{
	/* On demande le nom et on l'enregistre dans personnage */

	printf("Entrez le nom de votre personnage : ");
	lire(stdin, personnage.nom);
}

/* Cree un nouveau personnage */
void creerNouveauPersonnage(void)
{
	/* On demande le nom du nouveau personnage */
	demanderNomNouveauPersonnage();
	/* On demande la race du nouveau personnage */
	demanderRaceNouveauPersonnage();
	/* On demande le metier du nouveau personnage */
	demanderMetierNouveauPersonnage();
	
	/* On initialise les variables du nouveau personnage */
	initialiserNouveauPersonnage();
}

/* Cree le dossier de sauvegarde pour le personnage */
void creerDossierSauvegardeNouveauPersonnage(void)
{
	char chemin[TAILLE_MAX];

	sprintf(chemin, "Sauvegarde/%s", personnage.nom);
	
	creerNouveauDossier(chemin);
}

/* Ajoute le nom de la nouvelle partie dans le fichier nom_sauvegarde.txt */
void ajouterNomSauvegardeNouvellePartie(const unsigned int indexSauvegarde)
{
	FILE *fichierSauvegarde;
	char buffer[NB_SAUVEGARDE][TAILLE_MAX];
	compteur indexLig;

	/* On ouvre le fichier contenant le nom des sauvegardes */
	fichierSauvegarde = ouvrirFichier("Sauvegarde/nom_sauvegarde.txt", "r", 
	"fichier \"nom_sauvegarde.txt\", fonction \"ajouterNomSauvegardeNouvellePartie\"");

	/* On enregistre chaque nom de sauvegarde */
	for(indexLig = 0; indexLig < NB_SAUVEGARDE; ++indexLig)
		lire(fichierSauvegarde, buffer[indexLig]);

	/* On ajoute le nom de la nouvelle partie */
	strcpy(buffer[indexSauvegarde], personnage.nom);

	/* On ferme le fichier contenant le nom des sauvegardes */
	fermerFichier(fichierSauvegarde, 
	"fichier \"nom_sauvegarde.txt\", fonction \"ajouterNomSauvegardeNouvellePartie\"");


	/* On ouvre le fichier contenant le nom des sauvegardes */
	fichierSauvegarde = ouvrirFichier("Sauvegarde/nom_sauvegarde.txt", "w+", 
	"fichier \"nom_sauvegarde.txt\", fonction \"ajouterNomSauvegardeNouvellePartie\"");

	/* On ecrit chaque nom de sauvegarde (incluant celui de la nouvelle partie) */
	for(indexLig = 0; indexLig < NB_SAUVEGARDE; ++indexLig)
		fprintf(fichierSauvegarde, "%s\n", buffer[indexLig]);

	/* On ferme le fichier contenant le nom des sauvegardes */
	fermerFichier(fichierSauvegarde, 
	"fichier \"nom_sauvegarde.txt\", fonction \"ajouterNomSauvegardeNouvellePartie\"");
}

/* Affiche le texte de debut de nouvelle partie */
void afficherTexteNouvellePartie(void)
{
	effacer();
	titre("Rhyddid", VERT);

	/* Affiche le texte Texte_Debut_Nouvelle_Partie.txt */
	lireEtAfficher("Histoire_Rhyddid/Texte_Debut_Nouvelle_Partie.txt");

	appuyezEntree("Appuyez sur ENTREE pour accepter la mission...");
}

/* Cree une nouvelle sauvegarde et lance le jeu */
void nouvelleSauvegarde(const unsigned int indexSauvegarde)
{
	effacer();
	titre("Nouvelle Partie", VERT);

	/* On cree un nouveau personnage */
	creerNouveauPersonnage();
	/* On cree le dossier de sauvegarde correspondant au personnage */
	creerDossierSauvegardeNouveauPersonnage(); 
	/* On sauvegarde le personnage */
	sauvegarderPersonnage();

	/* On ajoute le nom de la sauvegarde de la nouvelle partie au fichier nom_sauvegarde.txt */
	ajouterNomSauvegardeNouvellePartie(indexSauvegarde);

	/* On affiche le texte de debut de nouvelle partie */
	afficherTexteNouvellePartie();

	/* On lance le jeu */
	jeu();
}
