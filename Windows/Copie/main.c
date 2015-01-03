#include "main.h"

int main(void)
{	
	srand((unsigned int) time(NULL));
	asciiArtDebut();
	
	return EXIT_SUCCESS;
}

void asciiArtDebut(void)
{
	effacer();
	afficherAsciiArt();
	
	appuyezEntree("\nAPPUYEZ SUR ENTREE POUR COMMENCER\n");
	choixModeDeJeuxMenu();
}

void afficherAsciiArt(void)
{
	FILE *fichier;
	
	fichier = ouvrirFichier("ASCII.txt", "r",
	"fichier \"ASCII.txt\", fonction \"asciiArtDebut\" !");
	
	while(!feof(fichier))
	{
		char buffer[TAILLE_MAX];
		
		fgets(buffer, TAILLE_MAX, fichier);
		
		if(!feof(fichier))
			coloration(buffer, BLEU);
	}
	
	fclose(fichier);
}

void choixModeDeJeuxMenu(void)
{
	int choix;
	
	titre("Mode de jeux");
	
	printf("Dans quel mode de jeux voulez-vous jouer ?\n\n");
	printf("\t1 - Solo\n");
	printf("\t2 - Multijoueur\n\n");
	
	do
	{
		choix = choixMenu(1, 2);
		
		if(choix == -1)
			printf("Veuillez d'abord selectionnez un menu !\n");
			
	} while(choix == -1);
	
	switch(choix)
	{
		case 0:
			quitter();
		break;
		
		case 1:
			solo();
		break;
		
		case 2:
			multi();
		break;
	}
}

void solo(void)
{
	systemeSauvegardeSolo();
	menuSolo();
}

void systemeSauvegardeSolo(void)
{
	int choix;
	int retour, nbLigneMax;
	
	titre("Sauvegarde");
	
	printf("Que souhaitez-vous faire ?\n\n");
	
	retour = afficherDernierePartieJoueeSolo();
	
	if(!retour)
		nbLigneMax = 3;
	else
		nbLigneMax = 4;
	
	printf("\t%d - Charger partie\n", nbLigneMax - 2);
	printf("\t%d - Nouvelle partie\n", nbLigneMax - 1);
	printf("\t%d - Supprimer partie\n\n", nbLigneMax);

	choix = choixMenu(1, nbLigneMax);
	
	if(choix == 0)
		quitter();
	else if(choix == -1)
		asciiArtDebut();
	else if(choix == nbLigneMax - 2)
		chargerPartieSolo();
	else if(choix == nbLigneMax - 1)
		nouvellePartieSolo();
	else if(choix == nbLigneMax)
		supprimerPartieSolo();
}

int afficherDernierePartieJoueeSolo(void)
{
	FILE *fichier;
	int retour;
	
	fichier = ouvrirFichier("dernierePartie.txt", "r",
	"fichier \"dernierePartie.txt\", fonction \"afficherDernierePartieJouee\" !");
	
	if(!lireFichier(fichier, nomPartie))
		retour = 0;
	else
	{
		retour = 1;
		
		printf("\t1 - Continuer : ");
		
		lireFichier(fichier, nomDossierSauvegarde);
	
		coloration(nomPartie, VERT);
		printf("\n");
	}
	
	fclose(fichier);
	
	return retour;
}

int afficherPartieSolo(void)
{
	FILE *fichier;
	int nbLigne;
	
	fichier = ouvrirFichier("nomSauvegarde.txt", "r",
	"fichier \"nomSauvegarde.txt\", fonction \"afficherPartieSolo\" !");
	nbLigne = 0;
	
	while(!feof(fichier))
	{
		char buffer[TAILLE_MAX];
		
		if(!lireFichier(fichier, buffer) && nbLigne == 0)
			printf("Aucune sauvegarde pour le moment");
		
		if(!feof(fichier))
		{
			printf("\t%d - %s\n", nbLigne + 1, buffer);
			nbLigne++;
		}
	}
	
	printf("\n\n");
	
	fclose(fichier);
	
	return nbLigne;
}

void chargerPartieSolo(void)
{
	int nbParties, choix;
	
	titre("Charger Partie");
	
	printf("Quelle partie voulez-vous charger ?\n\n");
	nbParties = afficherPartieSolo();
	choix = choixMenu(1, nbParties);
	
	switch(choix)
	{
		case 0:
			quitter();
		break;
		
		case -1:
			systemeSauvegardeSolo();
		break;
		
		default:
			selectionnerPartieChargeeSolo(choix);
		break;
	}
}

void selectionnerPartieChargeeSolo(int partieChargee)
{	
	FILE *fichier;
	int nbLigne;
	char buffer[TAILLE_MAX];
	char debutNomDossier[TAILLE_MAX];
	
	fichier = ouvrirFichier("nomSauvegarde.txt", "r",
	"fichier \"nomSauvegarde.txt\", fonction \"selectionnerPartieChargeeSolo\" !");
	nbLigne = 0;
	
	while(!feof(fichier) && nbLigne < partieChargee)
	{	
		lireFichier(fichier, buffer);
		
		if(!feof(fichier))
			nbLigne++;
	}
	
	fclose(fichier);
	
	strcpy(nomPartie, buffer);
	sprintf(debutNomDossier, "Sauvegarde/%s", nomPartie);
	strcpy(nomDossierSauvegarde, debutNomDossier);
}

void nouvellePartieSolo(void)
{
	char nomNouvellePartie[TAILLE_MAX];
	
	titre("Nouvelle Partie");
	
	printf("Entrez le nom de votre nouvelle partie : ");
	lireFichier(stdin, nomNouvellePartie);

	creerNouvellePartieSolo(nomNouvellePartie);
	systemeSauvegardeSolo();
}

void creerNouvellePartieSolo(const char *nomPartie)
{
	FILE *fichier;
	int nbLigne;
	char chemin[TAILLE_MAX];
	
	fichier = ouvrirFichier("nomSauvegarde.txt", "r+",
	"fichier \"nomSauvegarde.txt\", fonction \"creerNouvellePartieSolo\" !");
	nbLigne = 0;
	
	while(!feof(fichier))
	{
		char buffer[TAILLE_MAX];
		
		lireFichier(fichier, buffer);
		
		if(!feof(fichier))
			nbLigne++;
	}
	
	fprintf(fichier, "%s\n", nomPartie);
	
	fclose(fichier);
	
	sprintf(nomDossierSauvegarde, "Sauvegarde/%s", nomPartie);
	mkdir(nomDossierSauvegarde, DROIT_FICHIER);
	
	sprintf(chemin, "%s/nb_points.txt", nomDossierSauvegarde);
	fichier = ouvrirFichier(chemin, "w+",
	"fichier \"nb_points.txt\", fonction \"creerNouvellePartieSolo\" !");
	
	fprintf(fichier, "0 0");
	
	fclose(fichier);
	
	sprintf(chemin, "%s/liste_jeux.txt", nomDossierSauvegarde);
	fichier = ouvrirFichier(chemin, "w+",
	"fichier \"liste_jeux.txt\", fonction \"creerNouvellePartieSolo\" !");
	
	fclose(fichier);
}

void supprimerPartieSolo(void)
{
	FILE *fichier;
	int nbLigneSolo, nbLigne, choix;
	char chemin[TAILLE_MAX];
	char buffer[TAILLE_MAX];
	
	fichier = ouvrirFichier("nomSauvegarde.txt", "r",
	"fichier \"nomSauvegarde.txt\", fonction \"supprimerPartieSolo\" !");
	
	titre("Supprimer partie");
	
	printf("Quelle partie souhaitez-vous supprimer ?\n\n");
	nbLigneSolo = afficherPartieSolo();
	choix = choixMenu(1, nbLigneSolo);
	char nomSauvegarde[nbLigneSolo][TAILLE_MAX];
	
	nbLigne = 0;

	while(!feof(fichier))
	{	
		char buffer[TAILLE_MAX];
		
		lireFichier(fichier, buffer);
		
		if(!feof(fichier))
		{
			strcpy(nomSauvegarde[nbLigne], buffer);
			nbLigne++;
		}
	}
	
	fclose(fichier);
	
	nbLigne--;
	
	sprintf(chemin, "Sauvegarde/%s/nb_points.txt", nomSauvegarde[choix - 1]);
	remove(chemin);
	sprintf(chemin, "Sauvegarde/%s/liste_jeux.txt", nomSauvegarde[choix - 1]);
	remove(chemin);
	
	sprintf(chemin, "Sauvegarde/%s", nomSauvegarde[choix - 1]);
	rmdir(chemin);
	
	fichier = ouvrirFichier("nomSauvegarde.txt", "w+",
	"fichier \"nomSauvegarde.txt\", fonction \"supprimerPartieSolo\" !");
	
	for(nbLigne = 0; nbLigne < nbLigneSolo; nbLigne++)
	{
		if(nbLigne != choix - 1)
			fprintf(fichier, "%s\n", nomSauvegarde[nbLigne]);
	}

	fclose(fichier);
	
	fichier = ouvrirFichier("dernierePartie.txt", "r",
	"fichier \"dernierePartie.txt\", fonction \"supprimerPartieSolo\" !");
	
	lireFichier(fichier, buffer);
	
	if(strcmp(nomSauvegarde[choix - 1], buffer) == 0)
	{
		fclose(fichier);
		fichier = ouvrirFichier("dernierePartie.txt", "w+",
	"fichier \"dernierePartie.txt\", fonction \"supprimerPartieSolo\" !");
		fclose(fichier);
	}
	else
		fclose(fichier);
	
	systemeSauvegardeSolo();
}

void multi(void)
{
	jeux(MULTI);
}

/* ----- Menu ----- */

void afficherMenuSolo(void)
{	
	couleur(VERT);
	printf("%s\t\t\tASCII Funfair\n\n", nomPartie);
	couleur(RE_INIT);
	
	couleur(BLEU);
	printf("\t1 - Jeux\n");
	printf("\t2 - Magasin de jeux\n");
	couleur(RE_INIT);
	
	coloration("\t3 - Aide\n", VERT);
	coloration("\t4 - Revenir a l'ecran d'accueil\n", ROUGE);
	
	printf("\n");
}

void actionMenuSolo(int choix)
{
	switch(choix)
	{
		case -1:
			menuSolo();
		break;
		
		case 0:
			quitter();
		break;
		
		case 1:
			jeux(SOLO);
		break;
		
		case 2:
			magasin();
		break;
		
		case 3:
			aide();
		break;
		
		case 4:
			enregistrerDernierePartieJoueeSolo();
			asciiArtDebut();
		break;
	}
}

void menuSolo(void)
{
	int choix;
	
	effacer();
	
	afficherMenuSolo();
	choix = choixMenu(1, 4);
	actionMenuSolo(choix);
}

/* ----- Jeux ----- */

void initTypeDeJeux(int typeJeux[NB_TYPES_JEUX])
{
	int indexJeux;
	
	for(indexJeux = 0; indexJeux < NB_TYPES_JEUX; indexJeux++)
		typeJeux[indexJeux] = VIDE;
}

int differentsTypesDeJeux(int indexJeux, int *indexTypesJeux)
{
	if(indexJeux == INDEX_DEBUT_REFLEXION || indexJeux == INDEX_FIN_REFLEXION)
	{
		*indexTypesJeux = 0;
		return REFLEXION;
	}
	else if(indexJeux >= INDEX_DEBUT_STRATEGIE && indexJeux <= INDEX_FIN_STRATEGIE)
	{
		*indexTypesJeux = 1;
		return STRATEGIE;
	}
	else if(indexJeux == INDEX_DEBUT_CLASSIQUE)
	{
		*indexTypesJeux = 2;
		return CLASSIQUE;
	}
	else if(indexJeux == INDEX_DEBUT_HASARD)
	{
		*indexTypesJeux = 3;
		return HASARD;
	}
}

int afficherJeux(int modeDeJeux)
{
	int compteur;
	int indexJeux, indexTypesJeux;
	int typeJeux[NB_TYPES_JEUX];
	int nbTypesJeux;

	compteur = 0;

	initTypeDeJeux(typeJeux);

	titre("Jeux");
	
	for(indexJeux = 0; indexJeux < NB_JEUX; indexJeux++)
	{
		if((modeDeJeux == SOLO && estDansListeDeJeux(indexJeux)) || modeDeJeux == MULTI)
		{
			nbTypesJeux = differentsTypesDeJeux(indexJeux, &indexTypesJeux);
			
			if(typeJeux[indexTypesJeux] == VIDE)
			{
				afficherTypeJeux(nbTypesJeux);
				typeJeux[indexTypesJeux] = DEJA_VU;
				indexTypesJeux++;
			}
			
			printf("\t%d - %s\n", compteur + 1, base[indexJeux].nom);
			compteur++;
		}
	}

	if(compteur == 0)
		aucunJeux();
	
	return compteur;
}

void aucunJeux(void)
{
	int choix;
		
	printf("Vous n'avez aucun jeux pour le moment, je vous conseille de lire le menu \"Aide\"\npuis de debloquer les jeux depuis le magasin de jeux.\n");
	printf("Entrez -1 pour revenir au menu principal, ou 0 pour quitter la plateforme de\njeux :\n");
		
	do
	{
		printf("> ");
		scanf("%d", &choix);
		viderBuffer();
	
		if(choix == 0)
			quitter();
		else if(choix != -1)
			printf("Entrez -1 pour revenir au menu principal, ou 0 pour quitter la plateforme de \njeux !\n");
				
	} while(choix != -1 && choix != 0);
		
	menuSolo();
}

void actionJeux(int choix, int modeDeJeux)
{
	switch(choix)
	{
		case 0:
			quitter();
		break;
		
		case -1:
			if(modeDeJeux == SOLO)
				menuSolo();
			else if(modeDeJeux == MULTI)
				asciiArtDebut();
		break;
		
		default:
			appelerFonctionJeux(choix, modeDeJeux);
		break;
	}
}

void appelerFonctionJeux(int choix, int modeDeJeux)
{
	FILE *fichier;
	int lig;
	char chemin[TAILLE_MAX];
	char buffer[TAILLE_MAX];
	
	if(modeDeJeux == SOLO)
	{
		sprintf(chemin, "%s/liste_jeux.txt", nomDossierSauvegarde);
	
		fichier = ouvrirFichier(chemin, "r",
		"fichier \"liste_jeux.txt\", fonction \"appelerFonctionJeux\" !");
	
		for(lig = 0; lig < choix; lig++)
			lireFichier(fichier, buffer);
		
		for(lig = 0; lig < NB_JEUX; lig++)
		{
			if(strcmp(buffer, base[lig].nom) == 0)
				break;
		}
		
		if(lig < NB_JEUX)
			base[lig].fonction(modeDeJeux);
	}
	else if(modeDeJeux == MULTI)
		base[choix - 1].fonction(modeDeJeux);
}

void jeux(int modeDeJeux)
{
	int nbJeux, choix;
	
	nbJeux = afficherJeux(modeDeJeux);
	choix = choixMenu(1, nbJeux);
	actionJeux(choix, modeDeJeux);
}

/* ----- Magasin ----- */

int menuMagasinChoix(void)
{
	int choix;
	
	printf("Bienvenue dans le magasin, que souhaitez-vous faire ?\n\n");
	printf("\t1 - Debloquer de nouveaux jeux graces a vos points\n");
	printf("\t2 - Debloquer le prochain jeux avec vos points VIP\n\n");
	
	choix = choixMenu(1, 2);
	
	if(choix == -1)
		menuSolo();
	else if(choix == 0)
		quitter();
	else 
		return choix;
		
	return -1;
}

int afficherMagasin(void)
{
	FILE *fichier;
	int nbPoints, nbJeuxAccessible;
	int indexJeux;
	char chemin[TAILLE_MAX];
	
	sprintf(chemin, "%s/nb_points.txt", nomDossierSauvegarde);
	
	fichier = ouvrirFichier(chemin, "r",
	"fichier \"nb_points.txt\", fonction \"afficherMagasin\" !");
	
	nbJeuxAccessible = 0;
	
	titre("Magasin de Jeux");
	
	fscanf(fichier, "%d", &nbPoints);
	
	fclose(fichier);
	
	printf("Vous avez actuellement %d point(s), quel jeux souhaitez-vous debloquer ?\n\n", nbPoints);
	
	for(indexJeux = 0; indexJeux < NB_JEUX; indexJeux++)
	{
		afficherTypeJeux(indexJeux);
		
		if(estDansListeDeJeux(nbJeuxAccessible))
		{
			couleur(VERT);
			nbJeuxAccessible++;
		}
		else if(nbPoints >= base[indexJeux].points)
		{
			couleur(BLEU);		
			nbJeuxAccessible++;
		}
		else
			couleur(ROUGE);
			
		printf("\t%d - %s (%d points)\n", indexJeux + 1, base[indexJeux].nom, base[indexJeux].points);	
			
		couleur(RE_INIT);
	}
	
	return nbJeuxAccessible;
}

void afficherTypeJeux(int indice)
{
	switch(indice)
	{
		case REFLEXION:
			coloration("Reflexion : \n\n", BLEU);
		break;
		
		case STRATEGIE:
			coloration("Strategie : \n\n", BLEU);
		break;
		
		case CLASSIQUE:
			coloration("Classique : \n\n", BLEU);
		break;
		
		case HASARD:
			coloration("Hasard : \n\n", BLEU);
		break;
	}	
}

int estDansListeDeJeux(int indice)
{
	FILE *fichier;
	char buffer[TAILLE_MAX];
	char chemin[TAILLE_MAX];
	
	sprintf(chemin, "%s/liste_jeux.txt", nomDossierSauvegarde);
	
	fichier = ouvrirFichier(chemin, "r",
	"fichier \"liste_jeux.txt\", fonction \"estDansListe\"");
		
	while(!feof(fichier))
	{
		lireFichier(fichier, buffer);
		
		if(!feof(fichier))
		{
			if(strcmp(buffer, base[indice].nom) == 0)
			{
				fclose(fichier);
				return 1;
			}
		}	
	}
	
	fclose(fichier);
	
	return 0;
}

void actionMagasin(int choix)
{
	switch(choix)
	{
		case -1:
			menuSolo();
		break;
		
		case 0:
			quitter();
		break;
		
		default:
			debloquerJeux(choix);
		break;
	}
}

void debloquerJeux(int idJeux)
{
	FILE *listeJeux, *nbPoints;
	int nbPointsFichier, nbPointsVIP;
	
	if(estDansListeDeJeux(idJeux - 1))
	{
		printf("\nVous avez deja achete ce jeux !\n");
		appuyezEntree("");
	}
	else
	{
		char chemin[TAILLE_MAX];
		char chemin2[TAILLE_MAX];
	
		sprintf(chemin, "%s/liste_jeux.txt", nomDossierSauvegarde);
		sprintf(chemin2, "%s/nb_points.txt", nomDossierSauvegarde);
	
		effacer();		
		
		listeJeux = ouvrirFichier(chemin, "a",
		"fichier \"liste_jeux.txt\", fonction \"debloquerJeux\"");

		nbPoints = ouvrirFichier(chemin2, "r",
		"fichier \"nb_points.txt\", fonction \"debloquerJeux\"");
		
		printf("\nBravo ! Vous avez debloque(e) le jeux \"%s\".\n", base[idJeux - 1].nom);
	
		fprintf(listeJeux, "%s\n", base[idJeux - 1].nom);
		
		fscanf(nbPoints, "%d %d", &nbPointsFichier, &nbPointsVIP);
		nbPointsFichier -= base[idJeux - 1].points;
	
		fclose(listeJeux);
		fclose(nbPoints);
	
		sprintf(chemin, "%s/nb_points.txt", nomDossierSauvegarde);
		
		nbPoints = ouvrirFichier(chemin, "w+",
		"fichier \"nb_points.txt\", fonction \"debloquerJeux\"");
		
		fprintf(nbPoints, "%d %d", nbPointsFichier, nbPointsVIP);
	
		fclose(nbPoints);
	}
}

void magasinPointsVIP(void)
{
	FILE *fichier;
	int nbPoints, nbPointsVIP;
	int indexProchainJeux;
	char chemin[TAILLE_MAX];
	
	indexProchainJeux = debloquerProchainJeux();
	sprintf(chemin, "%s/nb_points.txt", nomDossierSauvegarde);
	
	fichier = ouvrirFichier(chemin, "r",
	"fichier \"nb_points.txt\", fonction \"magasinPointsVIP\" !");
	
	titre("VIP");
	
	fscanf(fichier, "%d %d", &nbPoints, &nbPointsVIP);
	
	fclose(fichier);
	
	if(tousJeuxDebloques())
	{
		printf("Vous avez actuellement %d points VIP.\n", nbPointsVIP);
		printf("Vous avez deja debloquer tous les jeux !\n");
		appuyezEntree("Appuyez sur entree pour revenir dans le menu principal : ");
		menuSolo();
	}
	else
	{
		if((nbPointsVIP - 5) < 0)
		{
			printf("Vous n'avez que %d point(s) VIP et il vous en faut 5 pour debloquer \"%s\" !\n", nbPointsVIP, base[indexProchainJeux].nom);
			appuyezEntree("Appuyez sur ENTREE pour revenir dans le menu principal : ");
			menuSolo();
		}
		
		printf("Vous avez actuellement %d points VIP.\n", nbPointsVIP);
		printf("Souhaitez-vous utiliser 5 points VIP pour debloquer \"%s\" ? (Appuyez sur ENTREE pour valider)\n\n", base[indexProchainJeux].nom);
		getchar();
		
		if(tousJeuxDebloques() == 0)
		{
			sprintf(chemin, "%s/nb_points.txt", nomDossierSauvegarde);
	
			fichier = ouvrirFichier(chemin, "w+",
			"fichier \"nb_points.txt\", fonction \"magasinPointsVIP\" !");

			nbPointsVIP -= 5;
			fprintf(fichier, "%d %d", nbPoints, nbPointsVIP);
			fclose(fichier);
			indexProchainJeux = debloquerProchainJeux();
			debloquerJeuxVIP(indexProchainJeux);
			printf("Il vous reste %d point(s) VIP !\n", nbPointsVIP);
			appuyezEntree("Appuyez sur ENTREE pour revenir au menu principal : ");
			menuSolo();
		}
		else
		{
			appuyezEntree("Appuyez sur ENTREE pour revenir au menu principal : ");
			menuSolo();
		}
	}
}

int tousJeuxDebloques(void)
{
	FILE *fichier;
	int index, compteur, compteurJeux;
	char buffer[TAILLE_MAX];
	char chemin[TAILLE_MAX];
	
	sprintf(chemin, "%s/liste_jeux.txt", nomDossierSauvegarde);
	
	fichier = ouvrirFichier(chemin, "r",
	"fichier \"liste_jeux.txt\", fonction \"tousJeuxDebloques\" !");
	
	compteurJeux = 0;
	
	while(!feof(fichier))
	{
		lireFichier(fichier, buffer);
		
		if(!feof(fichier))
		{
			for(index = 0, compteur = 0; index < NB_JEUX; index++)
			{
				if(strcmp(buffer, base[index].nom) == 0)
					compteur++;
			}
			
			if(compteur == 1)
				compteurJeux++;
		}
	}

	fclose(fichier);
	
	if(compteurJeux == NB_JEUX)
		return 1;
	else
		return 0;
}

int debloquerProchainJeux(void)
{
	int index, nbJeuxDebloqueVIP;
	
	nbJeuxDebloqueVIP = 0;
	
	for(index = 0; index < NB_JEUX; index++)
	{
		if(estDansListeDeJeux(index) == 0)
		{
			if(nbJeuxDebloqueVIP == 0)
				return index;
			else 
				break;
				
			nbJeuxDebloqueVIP++;
		}
	}
}

void debloquerJeuxVIP(int idJeux)
{
	FILE *fichier;
	char chemin[TAILLE_MAX];
	
	sprintf(chemin, "%s/liste_jeux.txt", nomDossierSauvegarde);
	
	fichier = ouvrirFichier(chemin, "a",
	"fichier \"liste_jeux.txt\", fonction \"debloquerJeuxVIP\" !");
	
	fprintf(fichier, "%s\n", base[idJeux].nom);
	
	printf("Bravo vous venez de debloquer le jeu \"%s\" grace a vos points VIP !\n", base[idJeux].nom);
	
	fclose(fichier);
}

void magasin(void)
{
	int maxJeux;
	int menuChoisis, choix;
	
	titre("Magasin");
	
	menuChoisis = menuMagasinChoix();
	
	if(menuChoisis == 1)
	{
		do
		{
			maxJeux = afficherMagasin();
			choix = choixMenu(1, maxJeux);
			actionMagasin(choix);
		
		} while(choix != -1 || choix != 0);
	}
	else
		magasinPointsVIP();
}

/* ----- Jeux dans le magasin ----- */

/* ----- Plus ou moins ----- */

void menuPlusOuMoins(int modeDeJeux)
{	
	titre("Plus ou Moins");
	
	if(modeDeJeux == SOLO)
		lireEtAfficherFichier("Texte de presentation/Plus ou moins/plusOuMoinsSolo.txt");
	else if(modeDeJeux == MULTI)
		lireEtAfficherFichier("Texte de presentation/Plus ou moins/plusOuMoinsMulti.txt");
		
	printf("\n\n");
	
	appuyezEntree("Appuyez sur ENTREE pour commencer : ");
}

int difficultePlusOuMoins(void)
{
	int choix;
	int compteur;
	
	compteur = 0;
	
	printf("\n\nChoisissez votre niveau de difficulte : \n\n");
	
	coloration("\t1 - Facile (nombre tire entre 1 et 100)\n\n", VERT);
	coloration("\t2 - Normal (nombre tire entre 1 et 500)\n\n", JAUNE);
	coloration("\t3 - Difficile (nombre tire entre 1 et 1000)\n\n", ROUGE);
	
	do
	{	
		if(compteur > 0)
			printf("Veuillez entrer un nombre compris entre 1 et 3 !\n");
			
		printf("> ");
		scanf("%d", &choix);
		viderBuffer();
		compteur++;
		
	} while(choix < NIVEAU_FACILE || choix > NIVEAU_DIFFICILE);
	
	return choix;
}

void systemeDePointsPlusOuMoinsEtPendu(int coups, int modeDeJeux, int choixNiveauDifficulte)
{
	int nbPointsGagnes, nbPointsVIP;
	
	nbPointsGagnes = nbPointsVIP = 0;
	
	switch(coups)
	{
		case 0:
			nbPointsGagnes = 250;
			nbPointsVIP = 2;
		break;
		
		case 1:
			nbPointsGagnes = 200;
			nbPointsVIP = 1;
		break;
		
		case 10:
		
		break;
		
		default:
			coups = 20 / coups;
			nbPointsGagnes = coups * 10;	
		break;		
	}
	
	nbPointsGagnes *= choixNiveauDifficulte;
	
	systemePoints(nbPointsGagnes, nbPointsVIP, modeDeJeux);
}

int faireChoisirNombreMysterePlusOuMoins(void)
{
	int nbMystere;
	
	effacer();
	
	printf("Joueur 1 :\n");
	printf("Choisissez un nombre mystere a faire deviner au Joueur 2 : ");
	scanf("%d", &nbMystere);
	viderBuffer();
	
	effacer();
	
	return nbMystere;
}

int choixNombreMysterePlusOuMoins(int modeDeJeux, int *choixNiveauDifficulte)
{
	int choixEntree, max;
	int nbMystere;
	
	if(modeDeJeux == SOLO)
	{
		choixEntree = difficultePlusOuMoins();
		*choixNiveauDifficulte = choixEntree;
		
		switch(choixEntree)
		{
			case NIVEAU_FACILE:
				max = NB_MAX_FACILE_PLUS_OU_MOINS;
			break;
		
			case NIVEAU_NORMAL:
				max = NB_MAX_NORMAL_PLUS_OU_MOINS;
			break;
			
			case NIVEAU_DIFFICILE:
				max = NB_MAX_DIFFICILE_PLUS_OU_MOINS;
			break;
		}
		
		nbMystere = hasard(1, max);
	}
	else if(modeDeJeux == MULTI)
		nbMystere = faireChoisirNombreMysterePlusOuMoins();
		
	return nbMystere;
}

void plusOuMoins(int modeDeJeux)
{
	int nombreMystere, nombreEntree;
	int choixNiveauDifficulte;
	int vie, coups;
	
	vie = NB_VIE_PLUS_OU_MOINS;
	
	menuPlusOuMoins(modeDeJeux);
	nombreMystere = choixNombreMysterePlusOuMoins(modeDeJeux, &choixNiveauDifficulte);
		
	do
	{	
		if(modeDeJeux == MULTI)
			printf("Joueur 2 :\n");
			
		printf("Vous avez %d vie(s) !\n", vie);
		printf("Entrez un nombre : ");
		scanf("%d", &nombreEntree);
		viderBuffer();
		
		if(nombreEntree > nombreMystere)
		{
			coloration("C'est moins !\n", ROUGE);
			vie--;
		}
		else if(nombreEntree < nombreMystere)
		{
			coloration("C'est plus !\n", VERT);
			vie--;
		}
		else
		{
			coups = NB_VIE_PLUS_OU_MOINS - vie;
			printf("\nBravo ! Vous avez trouve le nombre mystere en %d coup(s).\n", coups);
		}
			
		printf("\n");
			
	} while(nombreEntree != nombreMystere && vie > 0);
	
	if(vie == 0)
	{
		coups = NB_VIE_PLUS_OU_MOINS;
		printf("Dommage vous avez perdu, le nombre mystere etait : %d\n", nombreMystere);
	}	
	
	if(modeDeJeux == SOLO)
		systemeDePointsPlusOuMoinsEtPendu(coups, modeDeJeux, choixNiveauDifficulte);
	else if(modeDeJeux == MULTI)
		revenirMenuMulti();
}

/* ----- Pendu ----- */

void menuPendu(int modeDeJeux)
{
	titre("Pendu");

	if(modeDeJeux == SOLO)
		lireEtAfficherFichier("Texte de presentation/Pendu/penduSolo.txt");
	else if(modeDeJeux == MULTI)
		lireEtAfficherFichier("Texte de presentation/Pendu/penduMulti.txt");
		
	printf("\n\n");
	
	appuyezEntree("Appuyez sur ENTREE pour commencer : ");
}

void choisirMotDictionnairePendu(char mot[])
{	
	FILE *fichier;
	int nbHasard, nbLignes;
	char buffer[TAILLE_MAX];

	fichier = ouvrirFichier("dico.txt", "r",
	"fichier \"dico.txt\", fonction \"choisirMot\"");
	
	nbHasard = hasard(1, NB_MOTS_PENDU);
	nbLignes = 0;

	while(!feof(fichier) && (nbLignes < nbHasard))
	{
		if(!feof(fichier))
		{
			lireFichier(fichier, buffer);
			nbLignes++;
		}
	}
	
	fclose(fichier);

	strcpy(mot, buffer);
}

int gagnerPendu(int compteurPendu[], size_t longueur)
{
	int indexMot;
	
	for(indexMot = 0; indexMot < longueur; indexMot++)
	{
		if(compteurPendu[indexMot] == 0)
			return 0;
	}
	
	return 1;
}

void afficherPendu(int coups)
{
	FILE *fichier;
	int nbLigne, nbLignesAeviter;		
	char buffer[TAILLE_MAX];
	
	fichier = ouvrirFichier("motifPendu.txt", "r",
	"fichier \"motifPendu.txt\", fonction \"afficherPendu\"");
	nbLigne = 0;
	nbLignesAeviter = coups * NB_LIGNE_TAILLE_PENDU;
	
	while(nbLigne < nbLignesAeviter)
	{
		if(!feof(fichier))
		{
			fgets(buffer, TAILLE_MAX, fichier);
			nbLigne++;
		}
	}
	
	nbLigne = 0;
	
	while(nbLigne < NB_LIGNE_TAILLE_PENDU)
	{
		if(!feof(fichier))
		{
			fgets(buffer, TAILLE_MAX, fichier);
			nbLigne++;
			printf("%s", buffer);
		}
	}
	
	fclose(fichier);
	
	printf("\n\n");
}

void afficherLettreMauvaisePendu(char lettre[], int taille)
{
	int indexLettre;
	
	couleur(ROUGE);
	
	for(indexLettre = 0; indexLettre < taille; indexLettre++)
		printf(" %c ", lettre[indexLettre]);
	
	printf("\n\n");
	couleur(RE_INIT);
}

void faireChoisirMotPendu(char mot[])
{
	int indexMot;

	effacer();
	
	printf("Joueur 1 :\n");
	printf("Entrez un mot a faire deviner a l'autre joueur : ");
	lireLigneSansEspace(stdin, mot);
	
	for(indexMot = 0; mot[indexMot] != '\0'; indexMot++)
		mot[indexMot] = toupper(mot[indexMot]);
	
	effacer();
}

void motMysterePendu(char mot[], int modeDeJeux)
{
	if(modeDeJeux == SOLO)
		choisirMotDictionnairePendu(mot);
	else if(modeDeJeux == MULTI)
		faireChoisirMotPendu(mot);
}

void initMotCompteurPendu(int motCompteur[], char motHasard[])
{
	int indexTab;
	size_t longueur;
	
	longueur = strlen(motHasard);
	
	for(indexTab = 0; indexTab < longueur; indexTab++)
		motCompteur[indexTab] = 0;
	
	motCompteur[0] = 1;
	
	for(indexTab = 1; indexTab < longueur; indexTab++)
	{
		if(motHasard[indexTab] == motHasard[0])
			motCompteur[indexTab] = 1;
	}
}

void afficherMotCachePendu(int motCompteur[], char motMystere[])
{
	int indexTab;
	
	for(indexTab = 0; indexTab < strlen(motMystere); indexTab++)
	{
		if(motCompteur[indexTab] == 0)
			printf(" _ ");
		else
			printf(" %c ", motMystere[indexTab]);
	}
			
	printf("\n\n");
}

void verifierLettrePendu(char lettre, int *nbLettreMauvaise, char lettreMauvaise[], int motCompteur[], char motMystere[], int *vie)
{
	int indexLettreMauvaise, indexTab;
	int lettreDejaProposee, estDansMot;
	
	lettreDejaProposee = estDansMot = 0;
	
	if(!isalpha(lettre))
	{
		effacer();
		printf("Veuillez entrer un caractere valide !\n");
	}
	else
	{
		lettre = toupper(lettre);
		
		for(indexLettreMauvaise = 0; indexLettreMauvaise < *nbLettreMauvaise; indexLettreMauvaise++)
		{
			if(lettreMauvaise[indexLettreMauvaise] == lettre)
				lettreDejaProposee = 1;
		}
		
		if(lettreDejaProposee)
		{
			effacer();
			printf("Vous avez deja propose cette lettre !\n");
			lettreDejaProposee = 0;
		}
		else
		{
			for(indexTab = 0; indexTab < strlen(motMystere); indexTab++)
			{	
				if(motMystere[indexTab] == lettre)
				{
					motCompteur[indexTab] = 1;
					estDansMot = 1;
				}
			}
		
			if(!estDansMot)
			{
				(*vie)--;
				lettreMauvaise[*nbLettreMauvaise] = lettre;
				(*nbLettreMauvaise)++;
			}
				
			effacer();
		}			
	}
}

void afficherReponsePendu(int vie, char motMystere[])
{
	if(vie == 0)
		printf("\nDommage vous avez perdu, le mot etait : %s\n", motMystere);
	else
		printf("\nBravo vous avez trouve le mot mystere ! Le mot etait bien : %s\n", motMystere);
}

void pendu(int modeDeJeux)
{	
	int *motActuelle;
	int vie;
	int nbLettreMauvaise;
	char motHasard[TAILLE_MAX];
	char lettreMauvaise[TAILLE_MAX];
	size_t longueur;

	motActuelle = NULL;
	vie = NB_VIE_PENDU;
	nbLettreMauvaise = 0;
	
	menuPendu(modeDeJeux);
	
	motMysterePendu(motHasard, modeDeJeux);
	
	longueur = strlen(motHasard);	
	motActuelle = malloc(longueur * sizeof(int));

	initMotCompteurPendu(motActuelle, motHasard);
	
	do
	{
		char lettre;
		
		effacer();
		
		afficherPendu(NB_VIE_PENDU - vie);
		afficherLettreMauvaisePendu(lettreMauvaise, nbLettreMauvaise);
			
		afficherMotCachePendu(motActuelle, motHasard);
			
		if(modeDeJeux == MULTI)
			printf("Joueur 2 :\n");	
		
		printf("Vous avez %d vie(s).\n", vie);
		printf("Lettre : ");
		scanf("%c", &lettre);
		viderBuffer();
		
		verifierLettrePendu(lettre, &nbLettreMauvaise, lettreMauvaise, motActuelle, motHasard, &vie);
		
	} while(!gagnerPendu(motActuelle, longueur) && vie > 0);
	
	afficherReponsePendu(vie, motHasard);
	
	if(modeDeJeux == SOLO)
		systemeDePointsPlusOuMoinsEtPendu(NB_VIE_PENDU - vie, modeDeJeux, 1); /* Ici le 1 signifie difficulte de niveau 1 (a cause du plus ou moins) */
	else if(modeDeJeux == MULTI)
	{
		appuyezEntree("Appuyez sur ENTREE pour revenir au menu : ");
		multi();
	}
	
	free(motActuelle);
}

/* ----- Morpion ----- */

void menuMorpion(int modeDeJeux, int *niveauDifficulte)
{
	int choixDifficulte;
	
	titre("Morpion");
	
	if(modeDeJeux == SOLO)
		lireEtAfficherFichier("Texte de presentation/Morpion/morpionSolo.txt");
	else if(modeDeJeux == MULTI)
		lireEtAfficherFichier("Texte de presentation/Morpion/morpionMulti.txt");
		
	printf("\n\n");
	printf("1 2 3\n");
	printf("4 5 6\n");
	printf("7 8 9\n\n");
	
	if(modeDeJeux == SOLO)
		printf("Vous = '");
	else if(modeDeJeux == MULTI)
		printf("Joueur 1 = '");
		
	coloration("O", ROUGE);
	
	if(modeDeJeux == SOLO)
		printf("'\nOrdinateur = '");
	else if(modeDeJeux == MULTI)
		printf("'\nJoueur 2 = '");
		
	coloration("X", BLEU);
	
	printf("'\n\n");
	
	appuyezEntree("Appuyez sur ENTREE pour commencer : ");
	
	if(modeDeJeux == SOLO)
	{
		choixDifficulte = choisirDifficulte();
		*niveauDifficulte = choixDifficulte;
	}
}

void initMorpion(void)
{
	int lig, col;
	
	for(lig = 0; lig < DIMENSION_MORPION; lig++)
	{
		for(col = 0; col < DIMENSION_MORPION; col++)
		{
			jeuMorpion[lig][col] = VIDE;
		}
	}
}

int testerCaseIAMorpion(int type, int *ligne, int *colonne)
{
	int lig, col;
	
	for(lig = 0; lig < DIMENSION_MORPION; lig++)
	{
		for(col = 0; col < DIMENSION_MORPION; col++)
		{
			if(jeuMorpion[lig][col] == VIDE)
			{
				jeuMorpion[lig][col] = type;
			
				if(gagnerMorpion(TEST) == type)
				{
					*ligne = lig;
					*colonne = col;
					
					jeuMorpion[lig][col] = VIDE;
					
					return 1;
				}
				
				jeuMorpion[lig][col] = VIDE;
			}
		}
	}
	
	return 0;
}

void IAMorpionFacile(void)
{
	int ligAjouer, colAjouer;

	do
	{
		ligAjouer = hasard(0, 2);
		colAjouer = hasard(0, 2);
		
	} while(jeuMorpion[ligAjouer][colAjouer] != VIDE);
	
	jeuMorpion[ligAjouer][colAjouer] = IA;
}

void IAMorpionNormal(void)
{
	int aleatoire;
	
	aleatoire = hasard(1, 2);
	
	if(aleatoire == 1)
		IAMorpionFacile();
	else if(aleatoire == 2)
		IAMorpionDifficile();
}

void IAMorpionDifficile(void)
{
	int ligAjouer, colAjouer;
	
	if(testerCaseIAMorpion(IA, &ligAjouer, &colAjouer) == 1)
		jeuMorpion[ligAjouer][colAjouer] = IA;
	else if(testerCaseIAMorpion(HUMAIN, &ligAjouer, &colAjouer) == 1)
		jeuMorpion[ligAjouer][colAjouer] = IA;
	else
	{
		do
		{
			ligAjouer = hasard(0, 2);
			colAjouer = hasard(0, 2);
			
		} while(jeuMorpion[ligAjouer][colAjouer] != VIDE);
		
		jeuMorpion[ligAjouer][colAjouer] = IA;
	}
}

void IAMorpion(int niveauDifficulte)
{
	switch(niveauDifficulte)
	{
		case NIVEAU_FACILE:
			IAMorpionFacile();
		break;
		
		case NIVEAU_NORMAL:
			IAMorpionNormal();
		break;
		
		case NIVEAU_DIFFICILE:
			IAMorpionDifficile();
		break;
	}
}

void afficherMorpion(void)
{
	int lig, col;
	int numero;
	
	numero = 1;
	
	for(lig = 0; lig < DIMENSION_MORPION; lig++)
	{
		for(col = 0; col < DIMENSION_MORPION; col++)
		{
			if(jeuMorpion[lig][col] == IA)
				coloration(" X ", BLEU);
			else if(jeuMorpion[lig][col] == HUMAIN)
				coloration(" O ", ROUGE);
			else if(jeuMorpion[lig][col] == LIGNE_GAGNANTE)
				coloration(" X ", VERT);
			else if(jeuMorpion[lig][col] == LIGNE_GAGNANTE + 1)
				coloration(" O ", VERT);
			else
				printf(" . ");
		}
		
		printf("\t%d %d %d", numero, numero + 1, numero + 2);
		numero += 3;
		printf("\n");
	}
	
	/* Affiche le tableau du morpion + une aide pour connaitre le numero des cases :
	
	.  .  . 	1 2 3
	.  .  . 	4 5 6
	.  .  . 	7 8 9
	
	*/

}

void ligneEnVertGagnanteMorpionHorizontale(int ligne, int joueur)
{
	int col;
	
	for(col = 0; col < DIMENSION_MORPION; col++)
		jeuMorpion[ligne][col] = joueur + 2;
}

void ligneEnVertGagnanteMorpionVerticale(int ligne, int joueur)
{
	int col;
	
	for(col = 0; col < DIMENSION_MORPION; col++)
		jeuMorpion[col][ligne] = joueur + 2;
}

int testerLigneGagnanteMorpion(int numeroJoueur, int estUnTest)
{
	int lig, col;
	int compteur, ligGagnantePotentiellement;
	
	for(lig = 0; lig < DIMENSION_MORPION; lig++)
	{	
		compteur = ligGagnantePotentiellement = 0;
				
		for(col = 0; col < DIMENSION_MORPION; col++)
		{
			if(jeuMorpion[lig][col] == numeroJoueur)
			{
				compteur++;
				ligGagnantePotentiellement = lig;
			}
		}
		
		if(compteur == DIMENSION_MORPION)
		{
			if(!estUnTest)
			{
				ligneEnVertGagnanteMorpionHorizontale(ligGagnantePotentiellement, numeroJoueur);
				afficherMorpion();
			}
			
			return 1;
		}
	}	
		
	return 0;
}

int testerColonneGagnanteMorpion(int numeroJoueur, int estUnTest)
{
	int lig, col;
	int compteur, colGagnantePotentiellement;
	
	for(lig = 0; lig < DIMENSION_MORPION; lig++)
	{	
		compteur = colGagnantePotentiellement = 0;
				
		for(col = 0; col < DIMENSION_MORPION; col++)
		{
			if(jeuMorpion[col][lig] == numeroJoueur)
			{
				compteur++;
				colGagnantePotentiellement = lig;
			}
		}
		
		if(compteur == DIMENSION_MORPION)
		{
			if(!estUnTest)
			{
				ligneEnVertGagnanteMorpionVerticale(colGagnantePotentiellement, numeroJoueur);
				afficherMorpion();
			}
			
			return 1;
		}
	}	
		
	return 0;
}

int testerDiagonaleDebutEnHautaGaucheMorpion(int numeroJoueur, int estUnTest)
{
	if(jeuMorpion[0][0] == numeroJoueur && jeuMorpion[1][1] == numeroJoueur &&
	   jeuMorpion[2][2] == numeroJoueur)
	{  	
		if(!estUnTest)
		{
			jeuMorpion[0][0] = jeuMorpion[1][1] = jeuMorpion[2][2] = numeroJoueur + 2;
			afficherMorpion();
		}	
		
		return 1;
	}
	
	return 0;
}

int testerDiagonaleDebutEnHautaDroiteMorpion(int numeroJoueur, int estUnTest)
{
	if(jeuMorpion[0][2] == numeroJoueur && jeuMorpion[1][1] == numeroJoueur &&
	   jeuMorpion[2][0] == numeroJoueur)
	{  		
		if(!estUnTest)
		{
			jeuMorpion[0][2] = jeuMorpion[1][1] = jeuMorpion[2][0] = numeroJoueur + 2;
			afficherMorpion();
		}
				
		return 1;
	}
	
	return 0;
}

int gagnerMorpion(int estUnTest)
{
	int indexJoueur;
	
	for(indexJoueur = 1; indexJoueur <= 2; indexJoueur++)
	{
		if(testerLigneGagnanteMorpion(indexJoueur, estUnTest) == GAGNER)
			return indexJoueur;
		else if(testerColonneGagnanteMorpion(indexJoueur, estUnTest) == GAGNER)
			return indexJoueur;
		else if(testerDiagonaleDebutEnHautaGaucheMorpion(indexJoueur, estUnTest) == GAGNER)
			return indexJoueur;
		else if(testerDiagonaleDebutEnHautaDroiteMorpion(indexJoueur, estUnTest) == GAGNER)
			return indexJoueur;
	}
	
	return 0;
}

void afficherGagnantMorpionSolo(int gagnant, int nbCoups, int modeDeJeux, int niveauDifficulte)
{
	int nbPointsGagnes, nbPointsVIP;
	
	nbPointsGagnes = nbPointsVIP = 0;
	
	printf("\n");
	
	switch(gagnant)
	{
		case 0:
			effacer();
			afficherMorpion();
			
			printf("\nMatch nul !\n");
			nbPointsGagnes = 5;
		break;
		
		case IA:
			coloration("Dommage ! Vous avez perdu.\n", ROUGE);
		break;
		
		case HUMAIN:
			coloration("Bravo ! Vous avez gagne.\n", VERT);
			nbPointsGagnes = 20;
			
			if(nbCoups <= 4 && niveauDifficulte == NIVEAU_DIFFICILE)
				nbPointsVIP = 1;
		break;
	}
	
	nbPointsGagnes *= niveauDifficulte;
	
	systemePoints(nbPointsGagnes, nbPointsVIP, modeDeJeux);
}

int estMorpionPlein(void)
{
	int lig, col;
	
	for(lig = 0; lig < DIMENSION_MORPION; lig++)
	{
		for(col = 0; col < DIMENSION_MORPION; col++)
		{
			if(jeuMorpion[lig][col] == VIDE)
				return 0;
		}
	}
	
	return 1;
}

int demanderPositionJoueurMorpion(void)
{
	int position;
	int compteur;
	int lig, col;
	
	compteur = 0;
			
	do
	{
		afficherMorpion();
		
		if(compteur > 0)
			printf("\nVeuillez entrer une position valide !\n");

		printf("\nA vous de jouer !\n");
		printf("Position : ");
		scanf("%d", &position);
		viderBuffer();
		compteur++;
		
		if(position >= 1 && position <= 9)
		{
			recupererPositionCoupJoueurMorpion(&lig, &col, position);
		
			if(jeuMorpion[lig][col] != VIDE)
				printf("Cette case est deja occupe !\n");
		}
		
		printf("\n");
		
	} while(position < 1 || position > 9 || jeuMorpion[lig][col] != VIDE);
	
	return position;
}

void recupererPositionCoupJoueurMorpion(int *ligne, int *colonne, int position)
{
	int placement[9][2] = {{0, 0}, {0, 1}, {0, 2}, {1, 0}, {1, 1}, {1, 2}, {2, 0}, {2, 1}, {2, 2}}; 
	/* Position relative a un numero allant de 1 a 9 sur le tableau du morpion */
	
	*ligne = placement[position - 1][0];
	*colonne = placement[position - 1][1];
}

void jouerCoupHumainMorpion(int typeJoueur, int modeDeJeux)
{
	int position;
	int lig, col;
	
	if(modeDeJeux == MULTI)
	{
		if(typeJoueur == HUMAIN)
			printf("Joueur 1 :\n");
		else if(typeJoueur == ADVERSAIRE)
			printf("Joueur 2 :\n");
	}
	
	position = demanderPositionJoueurMorpion();
	recupererPositionCoupJoueurMorpion(&lig, &col, position);
		
	jeuMorpion[lig][col] = typeJoueur;
}

void afficherGagnantMorpionMulti(int gagnant)
{
	switch(gagnant)
	{
		case 0:
			effacer();
			afficherMorpion();
			
			printf("\nMatch nul !\n");
		break;
		
		case HUMAIN:
			coloration("Le joueur 1 a gagne !\n", VERT);
		break;
		
		case ADVERSAIRE:
			coloration("Le joueur 2 a gagne !\n", VERT);
		break;
	}
	
	appuyezEntree("Appuyez sur ENTREE pour revenir au menu : ");
	multi();
}

void morpion(int modeDeJeux)
{
	int nbCoups;
	int niveauDifficulte;
	int gagnant;
	
	nbCoups = 0;
	
	menuMorpion(modeDeJeux, &niveauDifficulte);
	initMorpion();
	
	effacer();
	
	do
	{
		effacer();
		
		jouerCoupHumainMorpion(HUMAIN, modeDeJeux);
		nbCoups++;
		
		if(!gagnerMorpion(TEST) && !estMorpionPlein())
		{
			effacer();
			
			if(modeDeJeux == SOLO)	
				IAMorpion(niveauDifficulte);
			else if(modeDeJeux == MULTI)
				jouerCoupHumainMorpion(ADVERSAIRE, modeDeJeux);
		}
				
		gagnant = gagnerMorpion(PAS_TEST);

	} while(!gagnant && !estMorpionPlein());

	if(modeDeJeux == SOLO)
		afficherGagnantMorpionSolo(gagnant, nbCoups, modeDeJeux, niveauDifficulte);
	else if(modeDeJeux == MULTI)
		afficherGagnantMorpionMulti(gagnant);
}

/* ----- Puissance 4 ----- */

void menuPuissance4(int modeDeJeux, int *niveauDifficulte)
{
	int choixDifficulte;
	
	titre("Puissance 4");
	
	if(modeDeJeux == SOLO)
		lireEtAfficherFichier("Texte de presentation/Puissance 4/puissance4Solo.txt");
	else if(modeDeJeux == MULTI)
		lireEtAfficherFichier("Texte de presentation/Puissance 4/puissance4Multi.txt");
		
	printf("\n\n");
	printf("  1 2 3 4 5 6 7\n");
	printf("1 - - - - - - -\n");
	printf("2 - - - - - - -\n");
	printf("3 - - - - - - -\n");
	printf("4 - - - - - - -\n");
	printf("5 - - - - - - -\n");
	printf("6 - - - - - - -\n\n");
	
	if(modeDeJeux == SOLO)
		printf("Vous = '");
	else if(modeDeJeux == MULTI)
		printf("Joueur 1 = '");
		
	coloration("O", ROUGE);
	
	if(modeDeJeux == SOLO)
		printf("'\nOrdinateur = '");
	else if(modeDeJeux == MULTI)
		printf("'\nJoueur 2 = '");
		
	coloration("O", JAUNE);
	
	printf("'\n\n");
	
	appuyezEntree("Appuyez sur ENTREE pour commencer : ");
	
	if(modeDeJeux == SOLO)
	{
		choixDifficulte = choisirDifficulte();
		*niveauDifficulte = choixDifficulte;
	}
}

void initPuissance4(void)
{
	int lig, col;
	
	for(lig = 0; lig < HAUTEUR_PUISSANCE_4; lig++)
		for(col = 0; col < LONGUEUR_PUISSANCE_4; col++)
			jeuPuissance4[lig][col] = VIDE;
}

void afficherPuissance4(void)
{
	int lig, col;
	
	printf("  1 2 3 4 5 6 7\n");
	
	for(lig = 0; lig < HAUTEUR_PUISSANCE_4; lig++)
	{
		printf("%d", lig + 1);
		
		for(col = 0; col < LONGUEUR_PUISSANCE_4; col++)
		{
			if(jeuPuissance4[lig][col] == VIDE)
				printf(" -");
			else if(jeuPuissance4[lig][col] == IA)
				coloration(" O", ROUGE);
			else if(jeuPuissance4[lig][col] == HUMAIN)
				coloration(" O", JAUNE);
			else if(jeuPuissance4[lig][col] >= LIGNE_GAGNANTE)
				coloration(" O", VERT);
		}
		
		printf("\n");
	}
}

int placerPuissance4(int colonne, int typeJoueur)
{
	int lig;
	
	for(lig = 0; lig < HAUTEUR_PUISSANCE_4 && jeuPuissance4[lig][colonne] == VIDE; lig++)
		;
	
	lig--;
	jeuPuissance4[lig][colonne] = typeJoueur;
	
	return lig;
}

int puissance4pasRempli(void)
{
	int lig, col;
	
	for(lig = 0; lig < HAUTEUR_PUISSANCE_4; lig++)
	{
		for(col = 0; col < LONGUEUR_PUISSANCE_4; col++)
		{
			if(jeuPuissance4[lig][col] == VIDE)
				return 1;
		}		
	}
				
	return 0;
}

int testerLigneGagnantePuissance4(int lig, int col, int numeroJoueur, int estUnTest)
{
	if((col + 3) < LONGUEUR_PUISSANCE_4)
	{
		if(jeuPuissance4[lig][col + 1] == numeroJoueur &&
		   jeuPuissance4[lig][col + 2] == numeroJoueur &&
		   jeuPuissance4[lig][col + 3] == numeroJoueur)
		{
			if(!estUnTest)
			{
				jeuPuissance4[lig][col] = 
				jeuPuissance4[lig][col + 1] = 
				jeuPuissance4[lig][col + 2] = 
				jeuPuissance4[lig][col + 3] = 
				numeroJoueur + 2;
				
				afficherPuissance4();
			}
										
			return 1;
		}
	}
	
	return 0;
}

int testerColonneGagnantePuissance4(int lig, int col, int numeroJoueur, int estUnTest)
{
	if((lig + 3) < HAUTEUR_PUISSANCE_4)
	{
		if(jeuPuissance4[lig + 1][col] == numeroJoueur &&
		   jeuPuissance4[lig + 2][col] == numeroJoueur &&
		   jeuPuissance4[lig + 3][col] == numeroJoueur)
		{
			if(!estUnTest)
			{
				jeuPuissance4[lig][col] = 
				jeuPuissance4[lig + 1][col] = 
				jeuPuissance4[lig + 2][col] = 
				jeuPuissance4[lig + 3][col] = 
				numeroJoueur + 2;
				
				afficherPuissance4();
			}
						
			return 1;
		}
	}
	
	return 0;
}

int testerDiagonaleDebutEnHautaGauchePuissance4(int lig, int col, int numeroJoueur, int estUnTest)
{
	if((col + 3) < LONGUEUR_PUISSANCE_4 && (lig + 3) < HAUTEUR_PUISSANCE_4)
	{
		if(jeuPuissance4[lig + 1][col + 1] == numeroJoueur &&
		   jeuPuissance4[lig + 2][col + 2] == numeroJoueur &&
		   jeuPuissance4[lig + 3][col + 3] == numeroJoueur)
		{
			if(!estUnTest)
			{
				jeuPuissance4[lig][col] = 
				jeuPuissance4[lig + 1][col + 1] = 
				jeuPuissance4[lig + 2][col + 2] = 
				jeuPuissance4[lig + 3][col + 3] = 
				numeroJoueur + 2;
				
				afficherPuissance4();
			}
				
			return 1;
		}
	}
	
	return 0;
}

int testerDiagonaleDebutEnHautaDroitePuissance4(int lig, int col, int numeroJoueur, int estUnTest)
{
	if((col - 3) >= 0 && (lig + 3) < HAUTEUR_PUISSANCE_4)
	{
		if(jeuPuissance4[lig + 1][col - 1] == numeroJoueur &&
		   jeuPuissance4[lig + 2][col - 2] == numeroJoueur &&
		   jeuPuissance4[lig + 3][col - 3] == numeroJoueur)
		{
			if(!estUnTest)
			{
				jeuPuissance4[lig][col] = 
				jeuPuissance4[lig + 1][col - 1] = 
				jeuPuissance4[lig + 2][col - 2] = 
				jeuPuissance4[lig + 3][col - 3] = 
				numeroJoueur + 2;
				
				afficherPuissance4();
			}
						
			return 1;
		}
	}
	
	return 0;
}

int gagnerPuissance4(int estUnTest)
{
	int lig, col;
	int indexJoueur;
	
	for(lig = 0; lig < HAUTEUR_PUISSANCE_4; lig++)
	{
		for(col = 0; col < LONGUEUR_PUISSANCE_4; col++)
		{
			indexJoueur = jeuPuissance4[lig][col];
			
			if(indexJoueur != VIDE)
			{
				if(testerLigneGagnantePuissance4(lig, col, indexJoueur, estUnTest) == GAGNER)
					return indexJoueur;
				else if(testerColonneGagnantePuissance4(lig, col, indexJoueur, estUnTest) == GAGNER)
					return indexJoueur;
				else if(testerDiagonaleDebutEnHautaGauchePuissance4(lig, col, indexJoueur, estUnTest) == GAGNER)
					return indexJoueur;
				else if(testerDiagonaleDebutEnHautaDroitePuissance4(lig, col, indexJoueur, estUnTest) == GAGNER)
					return indexJoueur;
			}
		}	
	}

    return 0;
}

int testerCaseIAPuissance4(int type, int *colonne)
{
	int col;
	int hauteur;
	
	for(col = 0; col < LONGUEUR_PUISSANCE_4; col++)
	{
		hauteur = placerPuissance4(col, type);
		
		if(gagnerPuissance4(TEST) == type)
		{
			*colonne = col;
			jeuPuissance4[hauteur][col] = VIDE;
			
			return 1;
		}
				
		jeuPuissance4[hauteur][col] = VIDE;
	}
	
	return 0;
}

void IAPuissance4Facile(void)
{
	int colonneAjouer;
	
	do
	{
		colonneAjouer = hasard(0, HAUTEUR_PUISSANCE_4);
		
	} while(estColonneRempliePuissance4(colonneAjouer + 1));
	
	placerPuissance4(colonneAjouer, IA);
}

void IAPuissance4Normal(void)
{
	int aleatoire;
	
	aleatoire = hasard(1, 2);
	
	if(aleatoire == 1)
		IAPuissance4Facile();
	else if(aleatoire == 2)
		IAPuissance4Difficile();
}

void IAPuissance4Difficile(void)
{
	int colonneAjouer, col;
	int hauteur;
	
	if(estPuissance4Vide())
		hauteur = placerPuissance4(MILIEU_PLATEAU, IA);
	else
	{
		if(testerCaseIAPuissance4(IA, &colonneAjouer) == GAGNER)
			placerPuissance4(colonneAjouer, IA);
		else if(testerCaseIAPuissance4(HUMAIN, &colonneAjouer) == GAGNER)
			placerPuissance4(colonneAjouer, IA);
		else
		{
			do
			{
				colonneAjouer = hasard(0, HAUTEUR_PUISSANCE_4);
				
			} while(estColonneRempliePuissance4(colonneAjouer + 1));
			
			placerPuissance4(colonneAjouer, IA);
		}
	}
}

void IAPuissance4(int niveauDifficulte)
{
	switch(niveauDifficulte)
	{
		case NIVEAU_FACILE:
			IAPuissance4Facile();
		break;
		
		case NIVEAU_NORMAL:
			IAPuissance4Normal();
		break;
		
		case NIVEAU_DIFFICILE:
			IAPuissance4Difficile();
		break;
	}
}

void afficherGagnantPuissance4Solo(int nbCoups, int modeDeJeux, int niveauDifficulte)
{
	int nbPointsGagnes, nbPointsVIP;
	
	nbPointsGagnes = nbPointsVIP = 0;
	
	printf("\n");
	
	switch(gagnerPuissance4(TEST))
	{
		case LIGNE_GAGNANTE: case LIGNE_GAGNANTE + 2:
			coloration("Dommage ! Vous avez perdu.\n", ROUGE);
		break;
		
		case LIGNE_GAGNANTE + 1:
			coloration("Bravo ! Vous avez gagne.\n", VERT);
			nbPointsGagnes = 25;
			if(nbCoups <= 8 && niveauDifficulte == NIVEAU_DIFFICILE)
				nbPointsVIP = 1;
		break;
		
		case 0:
			effacer();
			afficherPuissance4();
			
			printf("\nMatch nul !\n");
			
			nbPointsGagnes = 5;
		break;
	}
	
	nbPointsGagnes *= niveauDifficulte;
	
	systemePoints(nbPointsGagnes, nbPointsVIP, modeDeJeux);
}

int demanderPositionCroixJoueurPuissance4(void)
{
	int colonne;
	int compteur;
	
	compteur = 0;
			
	do
	{
		afficherPuissance4();
		
		if(compteur > 0)
			printf("Veuillez entrer une position valide !\n");

		printf("\nA vous de jouer !\n");
		printf("Colonne : ");
		scanf("%d", &colonne);
		viderBuffer();
		compteur++;
		
		printf("\n");
		
	} while(colonne < 1 || colonne > LONGUEUR_PUISSANCE_4 || estColonneRempliePuissance4(colonne));
	
	return colonne;
}

void jouerCoupHumainPuissance4(int typeJoueur, int modeDeJeux)
{
	int colonne;
	int placement;
	
	if(modeDeJeux == MULTI)
	{
		if(typeJoueur == HUMAIN)
			printf("Joueur 1 :\n\n");
		else if(typeJoueur == ADVERSAIRE)
			printf("Joueur 2 :\n\n");
	}
	
	colonne = demanderPositionCroixJoueurPuissance4();
	placement = placerPuissance4(colonne - 1, typeJoueur);
}

void afficherGagnantPuissance4Multi(void)
{
	printf("\n");
	
	switch(gagnerPuissance4(TEST))
	{
		case LIGNE_GAGNANTE: case LIGNE_GAGNANTE + 2:
			coloration("Le joueur 2 a gagne !\n", VERT);
		break;
		
		case LIGNE_GAGNANTE + 1:
			coloration("Le joueur 1 a gagne\n", VERT);
		break;
		
		case 0:
			effacer();
			afficherPuissance4();
			
			printf("\nMatch nul !\n");
		break;
	}
	
	appuyezEntree("Appuyez sur ENTREE pour revenir au menu : ");
	multi();
}

int estColonneRempliePuissance4(int colonne)
{
	if(jeuPuissance4[0][colonne - 1] != VIDE)
		return 1;
	else
		return 0;
}

int estPuissance4Vide(void)
{
	int lig, col;
	
	for(lig = 0; lig < HAUTEUR_PUISSANCE_4; lig++)
	{
		for(col = 0; col < LONGUEUR_PUISSANCE_4; col++)
		{
			if(jeuPuissance4[lig][col] != VIDE)
				return 0;
		}		
	}
				
	return 1;
}

void puissance4(int modeDeJeux)
{
	int nbCoups;
	int niveauDifficulte;
	
	nbCoups = 0;

	menuPuissance4(modeDeJeux, &niveauDifficulte);
	initPuissance4();
	
	effacer();
	
	do
	{
		effacer();
		
		if(modeDeJeux == SOLO)
			IAPuissance4(niveauDifficulte);
		else if(modeDeJeux == MULTI)
			jouerCoupHumainPuissance4(HUMAIN, modeDeJeux);
	
		if(!gagnerPuissance4(TEST) && puissance4pasRempli())
		{	
			effacer();
			
			if(modeDeJeux == SOLO)
				jouerCoupHumainPuissance4(HUMAIN, modeDeJeux);
			else if(modeDeJeux == MULTI)
				jouerCoupHumainPuissance4(ADVERSAIRE, modeDeJeux);
				
			nbCoups++;
		}
		
	} while(!gagnerPuissance4(PAS_TEST) && puissance4pasRempli());
	
	if(modeDeJeux == SOLO)
		afficherGagnantPuissance4Solo(nbCoups, modeDeJeux, niveauDifficulte);
	else if(modeDeJeux == MULTI)
		afficherGagnantPuissance4Multi();
}

/* ----- Mastermind ----- */

void menuMastermind(int modeDeJeux)
{
	titre("Mastermind");
	
	if(modeDeJeux == SOLO)
		lireEtAfficherFichier("Texte de presentation/Mastermind/mastermindSolo.txt");
	else if(modeDeJeux == MULTI)
		lireEtAfficherFichier("Texte de presentation/Mastermind/mastermindMulti.txt");
		
	printf("\n\n");

	appuyezEntree("Appuyez sur ENTREE pour commencer : ");
}

void initMastermind(void)
{
	int lig, col;
	
	for(lig = 0; lig < NB_LIGNE_MASTERMIND; lig++)
	{
		for(col = 0; col < NB_COLONNE_MASTERMIND; col++)
		{
			jeuMastermind[lig][col] = VIDE;
			coteMastermind[lig][col] = VIDE;
		}
	}
}

void initCodeSecretMastermind(char code[LONGUEUR_CODE + 1])
{
	const char baseCode[] = "rjvbBcf";
	int combinaison[LONGUEUR_CODE] = {-1, -1, -1, -1};
	int indexHasard;
	
	for(indexHasard = 0; indexHasard < LONGUEUR_CODE; indexHasard++)
	{
		int nbHasard;
		
		do
		{
			nbHasard = hasard(0, NB_COULEUR_MASTERMIND - 1);
			
		} while(nbHasard == combinaison[0] || nbHasard == combinaison[1] || 
				nbHasard == combinaison[2] || nbHasard == combinaison[3]);
		
		combinaison[indexHasard] = nbHasard;
		code[indexHasard] = baseCode[nbHasard];
	}
	
	code[4] = '\0';
}

void afficherCoteMastermind(int lig, int estCoteDroit)
{
	int col, indexCol;
	
	if(estCoteDroit)
		col = 2;
	else
		col = 0;
		
	for(indexCol = 0; indexCol < NB_COLONNE_MASTERMIND / 2; indexCol++, col++)
	{
		switch(coteMastermind[lig][col])
		{
			case VIDE:
				coloration("x ", NOIR);
			break;
			
			case COULEUR_ROUGE:
				coloration("x ", ROUGE);
			break;
			
			case COULEUR_BLANC:
				printf("x ");
			break;
		}
	}
}

void afficherPionMastermind(int pion)
{
	switch(pion)
	{
		case VIDE:
			printf("- ");
		break;
		
		case COULEUR_ROUGE: case 'r':
			coloration("o ", ROUGE);
		break;
		
		case COULEUR_JAUNE: case 'j':
			coloration("o ", JAUNE);
		break;
		
		case COULEUR_VERT: case 'v':
			coloration("o ", VERT);
		break;
		
		case COULEUR_BLEU: case 'b':
			coloration("o ", BLEU);
		break;
		
		case COULEUR_BLANC: case 'B':
			printf("o ");
		break;
		
		case COULEUR_CYAN: case 'c':
			coloration("o ", CYAN);
		break;
		
		case COULEUR_FUCHIA: case 'f':
			coloration("o ", VIOLET);
		break;
	}
}

void afficherCaractereCouleurMastermind(void)
{
	coloration("o", ROUGE);
	printf(" = r (rouge)\t");
	
	coloration("o", JAUNE);
	printf(" = j (jaune)\t");
	
	coloration("o", VERT);
	printf(" = v (vert)\n");
	
	coloration("o", BLEU);
	printf(" = b (bleu)\t");
	
	printf("o = B (blanc)\t");
	
	coloration("o", CYAN);
	printf(" = c (cyan)\n");
	
	coloration("o", VIOLET);
	printf(" = f (fuchia)\n\n");
}

void afficherMastermind(void)
{
	int lig, col;
	
	printf("      ? ? ? ? \n");
	printf("     _________\n");
	
	for(lig = 0; lig < NB_LIGNE_MASTERMIND; lig++)
	{
		afficherCoteMastermind(lig, COTE_GAUCHE_MASTERMIND);
		printf("| ");
		
		for(col = 0; col < NB_COLONNE_MASTERMIND; col++)
			afficherPionMastermind(jeuMastermind[lig][col]);
	
		printf("| ");
		afficherCoteMastermind(lig, COTE_DROIT_MASTERMIND);
		printf("\n");
	}
	
	printf("     _________\n\n");
	
	afficherCaractereCouleurMastermind();
}	

void placerPionMastermind(const char *combinaison, int lig)
{
	int indexLig, col;
	
	for(indexLig = 0, col = 0; indexLig < NB_COLONNE_MASTERMIND; indexLig++, col++)
	{
		switch(combinaison[indexLig])
		{
			case 'r':
				jeuMastermind[lig][col] = COULEUR_ROUGE;
			break;
			
			case 'j':
				jeuMastermind[lig][col] = COULEUR_JAUNE;
			break;
			
			case 'v':
				jeuMastermind[lig][col] = COULEUR_VERT;
			break;
			
			case 'b':
				jeuMastermind[lig][col] = COULEUR_BLEU;
			break;
			
			case 'B':
				jeuMastermind[lig][col] = COULEUR_BLANC;
			break;
			
			case 'c':
				jeuMastermind[lig][col] = COULEUR_CYAN;
			break;
			
			case 'f':
				jeuMastermind[lig][col] = COULEUR_FUCHIA;
			break;
		}
	}
}

void verifierCodeMastermind(const char *code, const char *tentative, int *nbBienPlace, int *nbMalPlace)
{
	int indexLig, indexTab;
	
	for(indexLig = 0; indexLig < NB_COLONNE_MASTERMIND; indexLig++)
	{
		int dejaVu;
		char *emplacement;
		
		emplacement = strchr(code, tentative[indexLig]);
		dejaVu = 0;
		
		for(indexTab = 0; indexTab < NB_COLONNE_MASTERMIND; indexTab++)
		{
			if(indexTab != indexLig && tentative[indexTab] == tentative[indexLig])
				dejaVu = 1;
		}
		
		if(emplacement != NULL)
		{
			if(tentative[indexLig] == code[indexLig])
				(*nbBienPlace)++;
			else if(!dejaVu && tentative[indexLig] != code[indexLig])
				(*nbMalPlace)++;
		}
	}
}

void placerPionCouleurCoteMastermind(int nbBienPlace, int nbMalPlace, int lig)
{
	int indexTab, nbHasard;
	
	for(indexTab = 0; indexTab < nbBienPlace; indexTab++)
	{
		do
		{
			nbHasard = hasard(0, NB_COLONNE_MASTERMIND - 1);
			
		} while(coteMastermind[lig][nbHasard] != VIDE);
		
		coteMastermind[lig][nbHasard] = COULEUR_ROUGE;
	}
		
	for(indexTab = 0; indexTab < nbMalPlace; indexTab++)
	{
		do
		{
			nbHasard = hasard(0, NB_COLONNE_MASTERMIND - 1);
			
		} while(coteMastermind[lig][nbHasard] != VIDE);
		
		coteMastermind[lig][nbHasard] = COULEUR_BLANC;
	}
}

int gagnerMastermind(const char *code, const char *tentative)
{
	if(strcmp(code, tentative) == 0)
		return 1;
	else
		return 0;
}

void victoireMastermindSolo(int coups, int modeDeJeux)
{
	int nbPoints, nbPointsVIP;
	
	nbPoints = nbPointsVIP = 0;
	
	if(coups <= 4)
	{
		nbPoints = 300;
		nbPointsVIP = 3;
	}
	else
		nbPoints = 40 / coups * 10;

	coloration("Bravo ! Vous avez gagne.\n", VERT);
	systemePoints(nbPoints, nbPointsVIP, modeDeJeux);
}

void afficherReponseMastermind(const char *code)
{
	int indexLig;
	
	effacer();
	
	printf("Le code secret etait : \n");
	
	for(indexLig = 0; indexLig < NB_COLONNE_MASTERMIND; indexLig++)
		afficherPionMastermind(code[indexLig]);
		
	printf("\n\n");
}

void defaiteMastermindSolo(int modeDeJeux)
{
	coloration("Dommage ! Vous avez perdu.\n", ROUGE);
	systemePoints(0, 0, modeDeJeux);
}

int estCodeBon(const char code[LONGUEUR_CODE + 1])
{
	const char baseCode[] = "rjvbBcf";
	int indexLettre;
	
	if(strlen(code) != LONGUEUR_CODE)
		return 0;
		
	for(indexLettre = 0; indexLettre < LONGUEUR_CODE; indexLettre++)
	{
		char *estDansBase;
		
		estDansBase = strchr(baseCode, code[indexLettre]);
		
		if(estDansBase == NULL)
			return 0;
	}
	
	return 1;
}

void demanderCodeSecretMastermind(char code[LONGUEUR_CODE + 1])
{
	char codeEntree[LONGUEUR_CODE + 1];
	int compteur;
	
	compteur = 0;

	effacer();
	
	do
	{
		if(compteur > 0)
			printf("Veuillez entrer un code de %d lettres, composes des lettres correspondantes aux couleurs !\n", LONGUEUR_CODE);
	
		printf("Joueur 1, entrez un code secret de %d lettres a faire deviner a votre adversaire !\n\n", LONGUEUR_CODE);
		afficherCaractereCouleurMastermind();
		printf("> ");
	
		lireLigneSansEspace(stdin, codeEntree);
		
		compteur++;
	
	} while(!estCodeBon(codeEntree));
	
	strcpy(code, codeEntree);
}

void victoireMastermindMulti(void)
{
	coloration("Le joueur 1 a gagne !\n", VERT);
}

void defaiteMastermindMulti(void)
{
	coloration("Le joueur 2 a gagne !\n", VERT);
}

void mastermind(int modeDeJeux)
{
	int tentative;
	int ligActuelle;
	int nbBienPlace, nbMalPlace;
	char codeCouleur[LONGUEUR_CODE + 1];
	char combinaisonEntree[TAILLE_MAX];
	
	tentative = NB_TENTATIVE_MASTERMIND;
	ligActuelle = NB_LIGNE_MASTERMIND - 1;
	
	menuMastermind(modeDeJeux);
	initMastermind();
	
	if(modeDeJeux == SOLO)
		initCodeSecretMastermind(codeCouleur);
	else if(modeDeJeux == MULTI)
		demanderCodeSecretMastermind(codeCouleur);
	
	do
	{
		effacer();	
	
		if(modeDeJeux == MULTI)
			printf("Joueur 2 :\n\n");
	
		afficherMastermind();

		nbBienPlace = nbMalPlace = 0;	
		
		printf("Il vous reste %d tentative(s) !\n", tentative);
		printf("> ");
		lireLigneSansEspace(stdin, combinaisonEntree);
		
		verifierCodeMastermind(codeCouleur, combinaisonEntree, &nbBienPlace, &nbMalPlace);
			
		placerPionCouleurCoteMastermind(nbBienPlace, nbMalPlace, ligActuelle);
	
		placerPionMastermind(combinaisonEntree, ligActuelle);
		
		tentative--;
		ligActuelle--;
		
	} while(!gagnerMastermind(codeCouleur, combinaisonEntree) && tentative != 0);
	
	afficherReponseMastermind(codeCouleur);
	afficherMastermind();
	
	if(modeDeJeux == SOLO)
	{
		if(gagnerMastermind(codeCouleur, combinaisonEntree))
			victoireMastermindSolo(NB_TENTATIVE_MASTERMIND - tentative, modeDeJeux);
		else
			defaiteMastermindSolo(modeDeJeux);
	}
	else if(modeDeJeux == MULTI)
	{
		if(gagnerMastermind(codeCouleur, combinaisonEntree))
			victoireMastermindMulti();
		else
			defaiteMastermindMulti();
			
		appuyezEntree("Appuyez sur ENTREE pour revenir au menu : ");
		multi();
	}
}

/* ----- Bataille Navale ----- */

void afficherLegendeMenuBatailleNavale(void)
{
	printf("Legende :\n\n");
	
	printf("\t- ");
	coloration("~", BLEU);
	printf(" : ocean, case vide\n");
	
	printf("\t- ");
	coloration("o", VERT);
	printf(" : partie de votre navire\n");
	
	printf("\t- ");
	coloration("o", ROUGE);
	printf(" : partie du navire touchee\n");
	
	printf("\t- X : case deja visitee et ne contenant rien\n");
	
	printf("\t- ");
	coloration("X", ROUGE);
	printf(" : navire ennemi\n\n");
}

void menuBatailleNavale(int modeDeJeux, int *niveauDifficulte)
{
	int choixDifficulte;
	
	titre("Bataille Navale");
	
	if(modeDeJeux == SOLO)
		lireEtAfficherFichier("Texte de presentation/Bataille navale/batailleNavaleSolo.txt");
	else if(modeDeJeux == MULTI)
	{
		printf("Ce jeu n'est pas disponible en multijoueur.\n");
		revenirMenuMulti();
	}
		
	printf("\n\n");
	
	afficherLegendeMenuBatailleNavale();
	
	printf("Pour placer votre bateau veuillez indiquez les coordonnes puis la direction (H, B, G, D).\nExemple : A3 D (cela placera un bateau en A3 dirige vers la droite)\n\n");
	
	appuyezEntree("Appuyez sur ENTREE pour commencer : ");
	
	choixDifficulte = choisirDifficulte();
	*niveauDifficulte = choixDifficulte;
}

void initBatailleNavale(void)
{
	int lig, col;
	
	for(lig = 0; lig < NB_LIGNE_BATAILLE_NAVALE; lig++)
	{
		for(col = 0; col < NB_COLONNE_BATAILLE_NAVALE; col++)
		{
			jeuBatailleNavale[lig][col] = VIDE;
			
			cadrillage[lig][col] = A_VISITER;
		}
	}
}

void afficherBatailleNavale(void)
{
	int lig, col, ligBas;
	
	printf("     A   B   C   D   E   F   G   H   I   J\n");
	
	printf("    ");
	
	for(ligBas = 0; ligBas < 40; ligBas++)
		printf("_");
	
	printf("\n");
	
	for(lig = 0; lig < NB_LIGNE_BATAILLE_NAVALE; lig++)
	{
		printf("%2d ", lig + 1);
		
		for(col = 0; col < NB_COLONNE_BATAILLE_NAVALE; col++)
		{
			if(col == 0)
				printf("| ");
				
			switch(jeuBatailleNavale[lig][col])
			{
				case VIDE: case IA:
					coloration("~ ", BLEU);
				break;
				
				case HUMAIN:
					coloration("o ", VERT);
				break;
				
				case RATE:
					printf("X ");
				break;
				
				case TOUCHE:
					coloration("o ", ROUGE);
				break;
				
				case DECOUVERT:
					coloration("X ", ROUGE);
				break;
			}	
			
			printf("| ");
		}
		
		printf("\n");
		
		printf("    ");
		for(ligBas = 0; ligBas < 40; ligBas++)
			printf("_");
			
		printf("\n");
	}
	
	printf("\n");
}

void formaterChaineBatailleNavale(const char *chaine, int *ligne, int *colonne, int *direction)
{
	int lig;
	char col, dir;
	
	sscanf(chaine, "%c%d %c", &col, &lig, &dir);
	
	*colonne = col - 'A';
	*ligne = lig - 1;
	
	switch(dir)
	{
		case 'H':
			*direction = HAUT;
		break;
		
		case 'B':
			*direction = BAS;
		break;
		
		case 'G':
			*direction = GAUCHE;
		break;
		
		case 'D':
			*direction = DROITE;
		break;
	}
}

int placerDirectionBatailleNavale(int ligne, int colonne, int dir, int nbCases, int contenu, int estUnTest)
{
	int lig, col;
	
	switch(dir)
	{
		case HAUT:
			if(!estUnTest)
			{
				for(lig = 0; lig < nbCases ; lig++)
					jeuBatailleNavale[ligne - lig][colonne] = contenu;
			}
			else
			{
				for(lig = 0; lig < nbCases ; lig++)
				{
					if(ligne - lig > NB_LIGNE_BATAILLE_NAVALE - 1 || ligne - lig < 0)
						return -1;
					else if(jeuBatailleNavale[ligne - lig][colonne] != VIDE)
						return -1;	
				}	
			}	
		break;
		
		case BAS:
			if(!estUnTest)
			{
				for(lig = 0; lig < nbCases ; lig++)
					jeuBatailleNavale[ligne + lig][colonne] = contenu;
			}
			else
			{
				for(lig = 0; lig < nbCases ; lig++)
				{
					if(ligne + lig > NB_LIGNE_BATAILLE_NAVALE - 1 || ligne + lig < 0)
						return -1;
					else if(jeuBatailleNavale[ligne + lig][colonne] != VIDE)
						return -1;	
				}		
			}	
		break;
		
		case GAUCHE:
			if(!estUnTest)
			{
				for(col = 0; col < nbCases ; col++)
					jeuBatailleNavale[ligne][colonne - col] = contenu;
			}
			else
			{
				for(col = 0; col < nbCases ; col++)
				{
					if(colonne - col > NB_COLONNE_BATAILLE_NAVALE - 1 || colonne - col < 0)
						return -1;
					else if(jeuBatailleNavale[ligne][colonne - col] != VIDE)
						return -1;	
				}		
			}	
		break;
		
		case DROITE:
			if(!estUnTest)
			{
				for(col = 0; col < nbCases ; col++)
					jeuBatailleNavale[ligne][colonne + col] = contenu;
			}
			else
			{
				for(col = 0; col < nbCases ; col++)
				{
					if(colonne + col > NB_COLONNE_BATAILLE_NAVALE - 1 || colonne + col < 0)
						return -1;
					else if(jeuBatailleNavale[ligne][colonne + col] != VIDE)
						return -1;	
				}	
			}		
		break;
	}
}

int estValidePositionBateauHumainBatailleNavale(char positionBateau[TAILLE_MAX])
{
	int ligne;
	char colonne, direction;
	
	sscanf(positionBateau, "%c%d %c", &colonne, &ligne, &direction);
	
	if(colonne < 'A' || colonne > 'J')
		return 0;
	if(ligne < 1 || ligne > 10)
		return 0;
	if(direction != 'H' &&
	   direction != 'B' &&
	   direction != 'G' &&
	   direction != 'D')
	    return 0;
		
	return 1;
}

void placerNavireHumainBatailleNavale(void)
{
	int indexBateau;
	
	for(indexBateau = 0; indexBateau < NB_BATEAU; indexBateau++)
	{
		char positionBateau[TAILLE_MAX];
		int lig, col, dir;
		int compteur;
		
		compteur = 0;
		
		effacer();
		afficherBatailleNavale();
		
		do
		{
			if(compteur > 0)
				printf("Veuillez entrer une position valide !\n");
				
			printf("Ou voulez-vous placer votre \"%s\" de %d cases de long ?\n", baseBateau[indexBateau].nom, baseBateau[indexBateau].nbCases);
			printf("> ");
		
			lireFichier(stdin, positionBateau);	
			
			compteur++;
				
		} while(!estValidePositionBateauHumainBatailleNavale(positionBateau));
		
		formaterChaineBatailleNavale(positionBateau, &lig, &col, &dir);
		
		placerDirectionBatailleNavale(lig, col, dir, baseBateau[indexBateau].nbCases,  HUMAIN, 0);
	}	
}

void formaterCadrillageIABatailleNavale(void)
{
	int lig, col;
	
	for(lig = 0; lig < NB_LIGNE_BATAILLE_NAVALE; lig++)
	{
		for(col = 0; col < NB_COLONNE_BATAILLE_NAVALE; col++)
		{
			if(jeuBatailleNavale[lig][col] == IA)
				cadrillage[lig][col] = RIEN;
		}
	}
}

void placerNavireIABatailleNavale(void)
{
	int indexBateau;
	
	printf("L'ordinateur dispose ses navires...\n");
	attendre(2);
		
	for(indexBateau = 0; indexBateau < NB_BATEAU; indexBateau++)
	{
		int lig,col, dir;
		int retour;
		
		do
		{
			lig = hasard(0, NB_LIGNE_BATAILLE_NAVALE - 1);
			col = hasard(0, NB_COLONNE_BATAILLE_NAVALE - 1);
			dir = hasard(HAUT, DROITE);
			
			retour = placerDirectionBatailleNavale(lig, col, dir, baseBateau[indexBateau].nbCases, IA, 1);
		} while(retour == -1);
		
		placerDirectionBatailleNavale(lig, col, dir, baseBateau[indexBateau].nbCases, IA, 0);
		formaterCadrillageIABatailleNavale();
	}
}

int jouerCoupHumainBatailleNavale(const char *emplacement)
{
	int lig, col;
	char colonne;
	
	sscanf(emplacement, "%c%d", &colonne, &lig);
	
	col = colonne - 'A';
	lig--;
	
	if(jeuBatailleNavale[lig][col] != HUMAIN)
		cadrillage[lig][col] = RIEN;
	
	if(jeuBatailleNavale[lig][col] == VIDE)
	{
		coloration("Rate !\n", ROUGE);
		jeuBatailleNavale[lig][col] = RATE;
		
		return 0;
	}
	else if(jeuBatailleNavale[lig][col] == IA)
	{
		coloration("Touche !\n", VERT);
		jeuBatailleNavale[lig][col] = DECOUVERT;
		
		return 1;
	}
}

int lancerTorpilleIABatailleNavale(int lig, int col)
{
	if(jeuBatailleNavale[lig][col] == HUMAIN)
		return 1;
	else
		return 0;
}

void verifierAlentourIABatailleNavale(int lig, int col)
{	
	if((lig - 1) >= 0)
	{
		if(cadrillage[lig - 1][col] == A_VISITER)
			cadrillage[lig - 1][col] = ALENTOUR;
	}
	if((lig + 1) < NB_LIGNE_BATAILLE_NAVALE)
	{
		if(cadrillage[lig + 1][col] == A_VISITER)
			cadrillage[lig + 1][col] = ALENTOUR;
	}
	if((col - 1) >= 0)
	{
		if(cadrillage[lig][col - 1] == A_VISITER)	
			cadrillage[lig][col - 1] = ALENTOUR;
	}
	if((col + 1) < NB_COLONNE_BATAILLE_NAVALE)
	{
		if(cadrillage[lig][col + 1] == A_VISITER)
			cadrillage[lig][col + 1] = ALENTOUR;
	}
}

void enleverDejaToucheIABatailleNavale(void)
{
	int lig, col;
		
	for(lig = 0; lig < NB_LIGNE_BATAILLE_NAVALE; lig++)
	{
		for(col = 0; col < NB_COLONNE_BATAILLE_NAVALE; col++)
		{
			if(cadrillage[lig][col] == A_TOUCHE)
				cadrillage[lig][col] = RIEN;
		}
	}
}

int rechercheIABatailleNavale(int recherche)
{
	int lig, col;
		
	for(lig = 0; lig < NB_LIGNE_BATAILLE_NAVALE; lig++)
	{
		for(col = 0; col < NB_COLONNE_BATAILLE_NAVALE; col++)
		{
			if(cadrillage[lig][col] == recherche)
				return 1;
		}
	}
	
	return 0;
}

void enleverAlentourIABatailleNavale(void)
{
	int lig, col;
		
	for(lig = 0; lig < NB_LIGNE_BATAILLE_NAVALE; lig++)
	{
		for(col = 0; col < NB_COLONNE_BATAILLE_NAVALE; col++)
		{
			if(cadrillage[lig][col] == ALENTOUR)
				cadrillage[lig][col] = A_VISITER;
		}
	}
}

int directionIABatailleNavale(int ligne, int colonne)
{	
	if((ligne - 1) >= 0)
	{
		if(cadrillage[ligne - 1][colonne] == A_TOUCHE)
			return HAUT;
	}
	if((ligne + 1) < NB_LIGNE_BATAILLE_NAVALE)
	{
		if(cadrillage[ligne + 1][colonne] == A_TOUCHE)
			return BAS;
	}
	if((colonne - 1) >= 0)
	{
		if(cadrillage[ligne][colonne - 1] == A_TOUCHE)
			return DROITE;
	}
	if((colonne + 1) < NB_COLONNE_BATAILLE_NAVALE)
	{
		if(cadrillage[ligne][colonne + 1] == A_TOUCHE)
			return GAUCHE;
	}
}

void verifierBateauIABatailleNavale(int lig, int col, int direction)
{
	int index;
	
	if(direction == HAUT || direction == BAS)
	{
		for(index = 1; (lig - index) >= 0 && index < 4; index++)
		{
			if(cadrillage[lig - index][col] == A_VISITER ||
				cadrillage[lig - index][col] == ALENTOUR)
				cadrillage[lig - index][col] = CONTINUER;
		}
		
		for(index = 1; (lig + index) < NB_LIGNE_BATAILLE_NAVALE && index < 4; index++)
		{
			if(cadrillage[lig + index][col] == A_VISITER ||
				cadrillage[lig + index][col] == ALENTOUR)
				cadrillage[lig + index][col] = CONTINUER;
		}	
	}
	else if(direction == GAUCHE || direction == DROITE)
	{	
		for(index = 1; (col - index) >= 0 && index < 4; index++)
		{
			if(cadrillage[lig][col - index] == A_VISITER ||
				cadrillage[lig][col - index] == ALENTOUR)
				cadrillage[lig][col - index] = CONTINUER;
		}
		
		for(index = 1; (col + index) < NB_COLONNE_BATAILLE_NAVALE && index < 4; index++)
		{
			if(cadrillage[lig][col + index] == A_VISITER ||
				cadrillage[lig][col + index] == ALENTOUR)
				cadrillage[lig][col + index] = CONTINUER;
		}
	}
}

int IABatailleNavaleFacile(char position[10])
{
	int ligHasard, colHasard;
	
	do
	{
		ligHasard = hasard(0, NB_LIGNE_BATAILLE_NAVALE - 1);
		colHasard = hasard(0, NB_COLONNE_BATAILLE_NAVALE - 1);
		
	} while(cadrillage[ligHasard][colHasard] != A_VISITER);
	
	if(lancerTorpilleIABatailleNavale(ligHasard, colHasard))
	{
		cadrillage[ligHasard][colHasard] = A_VISITER;
		sprintf(position, "%c%d", 'A' + colHasard, ligHasard + 1);
		jeuBatailleNavale[ligHasard][colHasard] = TOUCHE;
		
		return 1;
	}
	else
	{
		cadrillage[ligHasard][colHasard] = RIEN;
		
		return 0;
	}
}

int IABatailleNavaleNormal(char position[10])
{
	int aleatoire;
	
	aleatoire = hasard(1, 2);
	
	if(aleatoire == 1)
		IABatailleNavaleFacile(position);
	else if(aleatoire == 2)
		IABatailleNavaleDifficile(position);
}

int IABatailleNavaleDifficile(char position[10])
{
	int ligHasard, colHasard;
	int dir;
	
	
	if(rechercheIABatailleNavale(CONTINUER))
	{
		do
		{
			ligHasard = hasard(0, NB_LIGNE_BATAILLE_NAVALE - 1);
			colHasard = hasard(0, NB_COLONNE_BATAILLE_NAVALE - 1);
			
		} while(cadrillage[ligHasard][colHasard] != CONTINUER);
		
		if(lancerTorpilleIABatailleNavale(ligHasard, colHasard))
		{
			cadrillage[ligHasard][colHasard] = RIEN;
			sprintf(position, "%c%d", 'A' + colHasard, ligHasard + 1);
			jeuBatailleNavale[ligHasard][colHasard] = TOUCHE;
			
			return 1;
		}
		else
		{
			cadrillage[ligHasard][colHasard] = RIEN;
			
			return 0;
		}
	}
	else if(rechercheIABatailleNavale(ALENTOUR))
	{
		do
		{
			ligHasard = hasard(0, NB_LIGNE_BATAILLE_NAVALE - 1);
			colHasard = hasard(0, NB_COLONNE_BATAILLE_NAVALE - 1);
			
		} while(cadrillage[ligHasard][colHasard] != ALENTOUR);
		
		if(lancerTorpilleIABatailleNavale(ligHasard, colHasard))
		{
			cadrillage[ligHasard][colHasard] = A_TOUCHE;
			dir = directionIABatailleNavale(ligHasard, colHasard);
			verifierBateauIABatailleNavale(ligHasard, colHasard, dir);
			enleverAlentourIABatailleNavale();
			sprintf(position, "%c%d", 'A' + colHasard, ligHasard + 1);
			jeuBatailleNavale[ligHasard][colHasard] = TOUCHE;

			return 1;
		}
		else
		{
			cadrillage[ligHasard][colHasard] = RIEN;

			return 0;
		}
	}
	else
	{
		do
		{
			ligHasard = hasard(0, NB_LIGNE_BATAILLE_NAVALE - 1);
			colHasard = hasard(0, NB_COLONNE_BATAILLE_NAVALE - 1);
			
		} while(cadrillage[ligHasard][colHasard] != A_VISITER);
			
		if(lancerTorpilleIABatailleNavale(ligHasard, colHasard))
		{
			enleverDejaToucheIABatailleNavale();
			cadrillage[ligHasard][colHasard] = A_TOUCHE;
			sprintf(position, "%c%d", 'A' + colHasard, ligHasard + 1);
			jeuBatailleNavale[ligHasard][colHasard] = TOUCHE;
			verifierAlentourIABatailleNavale(ligHasard, colHasard);
			
			return 1;
		}
		else
		{
			cadrillage[ligHasard][colHasard] = RIEN;
			
			return 0;
		}
	}
}

int jouerCoupIABatailleNavale(char position[10], int niveauDifficulte)
{
	int retour;

	switch(niveauDifficulte)
	{
		case NIVEAU_FACILE:
			retour = IABatailleNavaleFacile(position);
		break;
		
		case NIVEAU_NORMAL:
			retour = IABatailleNavaleNormal(position);
		break;
		
		case NIVEAU_DIFFICILE:
			retour = IABatailleNavaleDifficile(position);
		break;
	}
	
	return retour;
}

void victoireBatailleNavale(int modeDeJeux, double secondes, int niveauDifficulte)
{
	int nbPoints, nbPointsVIP;
	
	nbPoints = 50;
	nbPointsVIP = 0;
	
	coloration("Bravo ! Vous avez gagne.\n", VERT);
	
	if(secondes <= NB_SECONDE_DEBLOQUER_POINT_VIP_BATAILLE_NAVALE)
		nbPointsVIP = 2;
		
	nbPoints *= niveauDifficulte;	
		
	systemePoints(nbPoints, nbPointsVIP, modeDeJeux);
}

void defaiteBatailleNavale(int modeDeJeux)
{
	coloration("Dommage ! Vous avez perdu.\n", ROUGE);
	systemePoints(0, 0, modeDeJeux);
}

int estValideCoupHumainBatailleNavale(char emplacement[TAILLE_MAX])
{
	int ligne;
	char colonne;
	
	sscanf(emplacement, "%c%d", &colonne, &ligne);
	
	if(colonne < 'A' || colonne > 'J')
		return 0;
	if(ligne < 1 || ligne > 10)
		return 0;
		
	return 1;
}

void demanderCoupHumainBatailleNavale(char emplacement[TAILLE_MAX])
{
	int compteur;
	
	compteur = 0;
	
	do
	{
		if(compteur > 0)
			printf("Veuillez entrer une position valide !\n");
			
		printf("A vous de jouer !\n");
		printf("> ");
		lireFichier(stdin, emplacement);
	
		compteur++;
		
	} while(!estValideCoupHumainBatailleNavale(emplacement));
}

void batailleNavale(int modeDeJeux)
{
	int nbBateauHumain, nbBateauIA;
	int nbTour, aTouche;
	int niveauDifficulte;
	char position[10];
	time_t debut, fin;
	double temps;
	
	nbBateauHumain = nbBateauIA = NB_CASES_TOTAL;
	nbTour = aTouche = 0;
	
	menuBatailleNavale(modeDeJeux, &niveauDifficulte);
	initBatailleNavale();

	placerNavireHumainBatailleNavale();
	afficherBatailleNavale();
	
	placerNavireIABatailleNavale();
	
	effacer();
	appuyezEntree("Appuyez sur ENTREE pour commencer la partie : ");
	
	time(&debut);
	
	do
	{
		char emplacement[TAILLE_MAX];
		
		effacer();
		
		afficherBatailleNavale();
		
		if(aTouche)
		{
			couleur(ROUGE);
			printf("L'ordinateur vous a touche en %s !\n", position);
			couleur(RE_INIT);
		}
		else if(nbTour != 0)
			coloration("L'ordinateur a rate !\n", BLEU);
			
		demanderCoupHumainBatailleNavale(emplacement);
		
		if(jouerCoupHumainBatailleNavale(emplacement) == 1)
			nbBateauIA--;
		
		if(nbBateauHumain != 0 && nbBateauIA != 0)
		{
			attendre(1);
				
			effacer();
			afficherBatailleNavale();
			
			aTouche = jouerCoupIABatailleNavale(position, niveauDifficulte);
			if(aTouche)
				nbBateauHumain--;
		}
		
		nbTour++;
		
	} while(nbBateauHumain != 0 && nbBateauIA != 0);
	
	time(&fin);
	
	temps = difftime(fin, debut);

	effacer();
	
	afficherBatailleNavale();
	
	if(nbBateauIA == 0)
		victoireBatailleNavale(modeDeJeux, temps, niveauDifficulte);
	else
		defaiteBatailleNavale(modeDeJeux);
}

/* ----- Pacman ---- */

void afficherLegendePacman(void)
{
	printf("Legende : \n\n");
	
	printf("\t- ");
	coloration(">", VERT);
	printf(", ");
	coloration("<", VERT);
	printf(", ");
	coloration("^", VERT);
	printf(", ");
	coloration("v", VERT);
	printf(" : vous\n");
	
	printf("\t- ");
	coloration("$", ROUGE);
	printf(", ");
	coloration("$", CYAN);
	printf(", ");
	printf("$");
	printf(", ");
	coloration("$", JAUNE);
	printf(", ");
	coloration("$", VIOLET);
	printf(", ");
	coloration("$", VERT);
	printf(" : fantome\n");
	
	printf("\t- ");
	coloration(".", JAUNE);
	printf(" : pac-gomme\n");
	
	printf("\t- ");
	coloration("@", JAUNE);
	printf(" : bonus\n");
	
	printf("\t- ");
	coloration("#", BLEU);
	printf(" : mur\n\n");
}

void menuPacman(int modeDeJeux)
{
	titre("Pacman");
	
	if(modeDeJeux == SOLO)
		lireEtAfficherFichier("Texte de presentation/Pacman/pacmanSolo.txt");
	else if(modeDeJeux == MULTI)
		lireEtAfficherFichier("Texte de presentation/Pacman/pacmanMulti.txt");
		
	printf("\n\n");

	afficherLegendePacman();		
		
	appuyezEntree("Appuyez sur ENTREE pour commencer : ");
}

void initNiveauPacman(char emplacementFantome[NB_FANTOME_PACMAN], int *lig, int *col, int *dir)
{
	FILE *fichier;
	int indexLigne, indexEmplacement;
	
	fichier = ouvrirFichier("pacman.txt", "r",
	"fichier \"pacman.txt\", fonction \"initNiveauPacman\"");
	indexLigne = 0;
	
	while(!feof(fichier))
	{
		char buffer[TAILLE_MAX];
		
		lireFichier(fichier, buffer);
		
		if(!feof(fichier))
		{
			strcpy(niveau[indexLigne], buffer);
			indexLigne++;
		}
	}
	
	fclose(fichier);
	
	for(indexEmplacement = 0; indexEmplacement < NB_FANTOME_PACMAN; indexEmplacement++)
		emplacementFantome[indexEmplacement] = '.';
		
	*lig = POSITION_DEPART_PACMAN;
	*col = POSITION_DEPART_PACMAN;
	*dir = GAUCHE;
}

void afficherDirectionPacman(int direction)
{
	switch(direction)
	{
		case HAUT:
			coloration("v", VERT);
		break;
		
		case BAS:
			coloration("^", VERT);
		break;
		
		case GAUCHE:
			coloration(">", VERT);
		break;
		
		case DROITE:
			coloration("<", VERT);
		break;
	}
}

void afficherNiveauPacman(int ligne, int colonne, int direction)
{
	int lig, col;
	
	for(lig = 0; lig < NB_LIGNE_NIVEAU_PACMAN; lig++)
	{
		for(col = 0; niveau[lig][col] != '\0'; col++)
		{
			if(ligne == lig && colonne == col)
				afficherDirectionPacman(direction);
			else
			{
				switch(niveau[lig][col])
				{
					case '#':
						coloration("#", BLEU);
					break;
				
					case '.':
						coloration(".", JAUNE);
					break;
					
					case '@':
						coloration("@", JAUNE);
					break;
						
					case '1':
						coloration("$", ROUGE);
					break;
					
					case '2':
						coloration("$", CYAN);
					break;
					
					case '3':
						coloration("$", VIOLET);
					break;
					
					case '4':
						coloration("$", VERT);
					break;
					
					case '5':
						printf("$");
					break;
					
					case '6':
						coloration("$", JAUNE);
					break;
					
					case '-':
						printf("-");
					break;
					
					case ' ': case 'X':
						printf(" ");
					break;	
				}
			}
		}
		
		printf("\n");
	}
		
	printf("\n\n");
}

void deplacerPacman(int entree, int *lig, int *col, int *direction, int *score, int *bonus)
{
	switch(entree)
	{
		case 'z': case 'Z' : case 'w' : case 'W': /* En haut */
			if(((*lig) - 1) >= 0) /* S'il y a une ligne en dessus de pacman ... */
			{
				if(niveau[(*lig) - 1][*col] == '.' || niveau[(*lig) - 1][*col] == ' '
				|| niveau[(*lig) - 1][*col] == '@') /* Si la ligne en dessus de pacman est soit une boule, soit rien, soit un bonus ... */
				{
					if(niveau[(*lig) - 1][*col] == '.') /* Si c'est une boule ... */
					{
						(*score)++; /* ... On augmente le score est en remplace la boule par un espace vide */
						niveau[(*lig) - 1][*col] = ' ';
					}
					else if(niveau[(*lig) - 1][*col] == '@') /* Si c'est un bonus ... */
					{
						(*bonus)++; /* ... On active le bonus et on remplace le bonus par un espace vide */
						niveau[(*lig) - 1][*col] = ' ';
					}
					
					(*lig)--; /* ... On deplace pacman d'une ligne vers le haut et on change la valeur de la direction */
					*direction = HAUT;
				}
			}
		break;
		
		case 's' : case 'S': /* En bas (meme procedure que pour le 1er cas) */
			if(((*lig) + 1) < NB_LIGNE_NIVEAU_PACMAN) 
			{
				if(niveau[(*lig) + 1][*col] == '.' || niveau[(*lig) + 1][*col] == ' ' 
				|| niveau[(*lig) + 1][*col] == '@')
				{
					if(niveau[(*lig) + 1][*col] == '.')
					{
						(*score)++;
						niveau[(*lig) + 1][*col] = ' ';
					}
					else if(niveau[(*lig) + 1][*col] == '@')
					{
						(*bonus)++;
						niveau[(*lig) + 1][*col] = ' ';
					}
					
					(*lig)++;
					*direction = BAS;
				}
			}
		break;
		
		case 'q': case 'Q' : case 'a' : case 'A': /* A gauche (meme procedure que pour le 1er cas) */
			if(((*col) - 2) >= 0)
			{
				if(niveau[*lig][(*col) - 2] == '.' || niveau[*lig][(*col) - 2] == ' ' 
				|| niveau[*lig][(*col) - 2] == '@')
				{
					if(niveau[*lig][(*col) - 2] == '.')
					{
						(*score)++;
						niveau[*lig][(*col) - 2] = ' ';
					}
					else if(niveau[*lig][(*col) - 2] == '@')
					{
						(*bonus)++;
						niveau[*lig][(*col) - 2] = ' ';
					}
					
					(*col) -= 2;
					*direction = GAUCHE;
				}
			}
		break;
		
		case 'd': case 'D' : /* A droite (meme procedure que pour le 1er cas) */
			if(((*col) + 2) < NB_COLONNE_NIVEAU_PACMAN)
			{
				if(niveau[*lig][(*col) + 2] == '.' || niveau[*lig][(*col) + 2] == ' ' 
				|| niveau[*lig][(*col) + 2] == '@')
				{
					if(niveau[*lig][(*col) + 2] == '.')
					{
						(*score)++;
						niveau[*lig][(*col) + 2] = ' ';
					}
					else if(niveau[*lig][(*col) + 2] == '@')
					{
						(*bonus)++;
						niveau[*lig][(*col) + 2] = ' ';
					}
					
					(*col) += 2;
					*direction = DROITE;
				}
			}
		break;
	}
}

void rechercherFantomePacman(int id, int *ligne, int *colonne)
{
	int lig, col;
	
	for(lig = 0; lig < NB_LIGNE_NIVEAU_PACMAN; lig++)
	{
		for(col = 0; niveau[lig][col] != '\0'; col++)
		{
			if(niveau[lig][col] == ('0' + id))
			{
				*ligne = lig;	
				*colonne = col;
			}
		}
	}
}

int deplacerDirectionFantomePacman(int *ligne, int *colonne, int direction, int lig, int col)
{
	int estDedans;
	
	estDedans = 1;
	
	switch(direction)
	{
		case HAUT:
			if((lig - 1) >= 0)
			{
				if(niveau[lig - 1][col] == '.' ||
					niveau[lig - 1][col] == '@' || 
					niveau[lig - 1][col] == ' ')
					*ligne = -1;
				else
					estDedans = 0;
			} 
			else
				estDedans = 0;
		break;
					
		case BAS:
			if((lig + 1) < NB_LIGNE_NIVEAU_PACMAN)
			{ 
				if(niveau[lig + 1][col] == '.' ||
					niveau[lig + 1][col] == '@' || 
					niveau[lig + 1][col] == ' ')
					*ligne = 1;
				else
					estDedans = 0;
			}
			else
				estDedans = 0;
		break;
					
		case GAUCHE:
			if((col - 2) >= 0)
			{  
				if(niveau[lig][col - 2] == '.' ||
					niveau[lig][col - 2] == '@' || 
					niveau[lig][col - 2] == ' ')
					*colonne = -2;
				else
					estDedans = 0;
			}
			else
				estDedans = 0;
		break;	
					
		case DROITE:
			if((col + 2) < NB_COLONNE_NIVEAU_PACMAN) 
			{
				if(niveau[lig][col + 2] == '.' ||
					niveau[lig][col + 2] == '@' || 
					niveau[lig][col + 2] == ' ')
					*colonne = 2;
				else
					estDedans = 0;
			}
			else
				estDedans = 0;
		break;
	}
	
	return estDedans;
}

void testerTousLesCotesFantomeBloquePacman(int ligActuel, int colActuel, int ligne, int colonne, int *nbCoteDisponibleLibre)
{
	if(niveau[ligActuel + ligne][colActuel + colonne] == '.' ||
	   niveau[ligActuel + ligne][colActuel + colonne] == '@' || 
	   niveau[ligActuel + ligne][colActuel + colonne] == ' ')
		(*nbCoteDisponibleLibre)++;
}

int estBloquerFantomePacman(int lig, int col)
{
	int nbCoteDisponibleLibre;
	
	nbCoteDisponibleLibre = 0;
	
	/* On verifie toutes les directions pour savoir si un fantome est bloque, si oui il ne bouge pas */
	
	if((lig - 1) >= 0) /* En Haut */
	{
		testerTousLesCotesFantomeBloquePacman(lig, col, -1, 0, &nbCoteDisponibleLibre);
	} 
	if((lig + 1) < NB_LIGNE_NIVEAU_PACMAN) /* En Bas */
	{ 
		testerTousLesCotesFantomeBloquePacman(lig, col, 1, 0, &nbCoteDisponibleLibre);
	}
	if((col - 2) >= 0) /* A Gauche */
	{  
		testerTousLesCotesFantomeBloquePacman(lig, col, 0, -2, &nbCoteDisponibleLibre);
	}
	if((col + 2) < NB_COLONNE_NIVEAU_PACMAN) /* A Droite */
	{
		testerTousLesCotesFantomeBloquePacman(lig, col, 0, -2, &nbCoteDisponibleLibre);
	}
	
	if(nbCoteDisponibleLibre > 0)
		return PAS_BLOQUE;
	else
		return BLOQUE;
}

int deplacerFantomePacman(int ligne, int colonne, char emplacementFantome[NB_FANTOME_PACMAN], int bonus)
{
	static int direction[NB_FANTOME_PACMAN] = {AUCUNE, AUCUNE, AUCUNE, AUCUNE, AUCUNE, AUCUNE};
	int indexFantome;
	
	for(indexFantome = 0; indexFantome < NB_FANTOME_PACMAN; indexFantome++)
	{
		int lig, col;
		int ligHasard, colHasard, directionHasard;
		
		rechercherFantomePacman(indexFantome + 1, &lig, &col);
		
		if(!estBloquerFantomePacman(lig, col))
		{
			if(direction[indexFantome] == AUCUNE)
			{	
				do
				{
					ligHasard = colHasard = 0;
					
					directionHasard = hasard(0, 3);
						
				} while(deplacerDirectionFantomePacman(&ligHasard, &colHasard, directionHasard, lig, col) == 0);	
			}
			else
			{
				ligHasard = colHasard = 0;
			
				if(deplacerDirectionFantomePacman(&ligHasard, &colHasard, 
					direction[indexFantome], lig, col) == 0)
				{
					do
					{
						ligHasard = colHasard = 0;
					
						directionHasard = hasard(0, 3);
						
					} while(deplacerDirectionFantomePacman(&ligHasard, &colHasard, directionHasard, lig, col) == 0);		
				}
				else
					directionHasard = direction[indexFantome];
			}			
				
			direction[indexFantome] = directionHasard;	
				
			niveau[lig][col] = emplacementFantome[indexFantome];
			emplacementFantome[indexFantome] = niveau[lig + ligHasard][col + colHasard];
			
			if(ligne == (lig + ligHasard) && colonne == (col + colHasard) && !bonus)
				return indexFantome;
			else	
				niveau[lig + ligHasard][col + colHasard] = '0' + (indexFantome + 1);	
		}
	}
	
	return -1;
}

void perdreViePacman(int nbVie, int score, int modeDeJeux, int joueurActuel)
{
	if(nbVie != 0)
	{
		effacer();
	
		if(modeDeJeux == MULTI)
			printf("Joueur %d : ", joueurActuel + 1);
	
		couleur(ROUGE);
		printf("Vous avez perdu une vie et fait un score de %d point(s) ! Il vous reste %d vie(s).\n\n", score, nbVie);
		couleur(RE_INIT);
		
		attendre(1);
		
		if(modeDeJeux == SOLO)
			printf("Le jeu va reprendre depuis le debut !\n");
		else if(modeDeJeux == MULTI)
		{
			if(joueurActuel == 0)
				joueurActuel = 1;
			else if(joueurActuel == 1)
				joueurActuel = 0;
			
			printf("A vous Joueur %d !\n", joueurActuel + 1);
		}
		
		appuyezEntree("Appuyez sur ENTREE pour recommencer : ");
		
	}
}

void defaitePacmanSolo(int modeDeJeux, int score)
{
	effacer();
	
	couleur(ROUGE);
	printf("Dommage ! Vous avez perdu avec %d point(s).\n\n", score);
	couleur(RE_INIT);
	
	attendre(1);
	
	systemePoints(0, 0, modeDeJeux);
}

void victoirePacmanSolo(int modeDeJeux, int vie, double temps)
{
	int nbPoints, nbPointsVIP;
	
	nbPoints = nbPointsVIP = 0;
	
	effacer();
	
	coloration("Bravo ! Vous avez gagne.\n\n", VERT);
	
	attendre(1);
	
	switch(vie)
	{
		case 3:
			nbPoints = 75;
			
			if(temps < NB_SECONDE_DEBLOQUER_POINT_VIP_PACMAN)
				nbPointsVIP = 2;
		break;
		
		case 2:
			nbPoints = 50;
		break;
		
		case 1:
			nbPoints = 25;
		break;
	}
	
	systemePoints(nbPoints, nbPointsVIP, modeDeJeux);
}

void afficherGagnantPacmanMulti(int joueurActuel, int score, int vie[2])
{
	int gagnant;

	gagnant = -1;

	effacer();
	
	if(vie[0] != 0 && vie[1] == 0)
		gagnant = 0;
	else if(vie[0] == 0 && vie[1] != 0)
		gagnant = 1;
	else if(score == NB_POINTS_PACMAN)
		gagnant = joueurActuel;
	
	switch(gagnant)
	{
		case -1:
			printf("Match nul !\n");
		break;
		
		case 0:
			coloration("Le joueur 1 a gagne !\n", VERT);
		break;
		
		case 1:
			coloration("Le joueur 2 a gagne !\n", VERT);
		break;
	}
	
	appuyezEntree("Appuyez sur ENTREE pour revenir au menu : ");
	multi();
}

void pacman(int modeDeJeux)
{
	char emplacementFantome[NB_FANTOME_PACMAN];
	int lig, col, dir;
	int score, bonus, peutMangerFantome, nbTourBonus;
	int index;
	int retourDeplacerFantome;
	int joueurActuel;
	int vie[2];
	int indexVie;
	time_t debut, fin;
	double temps;

	score = 0;
	peutMangerFantome = DESACTIVE;
	nbTourBonus = -1;
	joueurActuel = 0;
	
	menuPacman(modeDeJeux);
	initNiveauPacman(emplacementFantome, &lig, &col, &dir);
	
	for(indexVie = 0; indexVie < 2; indexVie++)
		vie[indexVie] = NB_VIE_PACMAN;
	
	time(&debut);
	
	do
	{
		char touche;	
		
		attendre(0.04);
		effacer();
		
		bonus = DESACTIVE;
		
		couleur(VERT);
		printf("Score : %d points\t\t\tVie : %d\n", score, vie[joueurActuel]);
		printf("Bonus (");
		coloration("@", JAUNE);
		coloration(") : ", VERT);
		
		if(peutMangerFantome)
		{
			couleur(ROUGE);
			printf("Active, %d tour(s) restant(s) !", nbTourBonus);
			couleur(RE_INIT);
		}
		else
			coloration("Desactive", VERT);
		
		if(modeDeJeux == MULTI)	
			printf("\n\nJoueur %d :", joueurActuel + 1);
			
		printf("\n\n");

		afficherNiveauPacman(lig, col, dir); // Les parametres sont la position et la direction du pacman
		touche = lireSansEntree();
		deplacerPacman(touche, &lig, &col, &dir, &score, &bonus);
		
		if(bonus == ACTIVE)
		{
			peutMangerFantome = ACTIVE;
			nbTourBonus = NB_TOUR_BONUS_ACTIVE_PACMAN;
		}
		
		if(vie != 0 && score != NB_POINTS_PACMAN)
		{
			retourDeplacerFantome = deplacerFantomePacman(lig, col, emplacementFantome, peutMangerFantome);
			
			if(retourDeplacerFantome != -1)
			{
				if(!peutMangerFantome)
				{		
					vie[joueurActuel]--;
					
					niveau[lig][col] = retourDeplacerFantome + 1 + '0';
					
					effacer();
					afficherNiveauPacman(-1, -1, -1);
					
					attendre(2);
					initNiveauPacman(emplacementFantome, &lig, &col, &dir);
					perdreViePacman(vie[joueurActuel], score, modeDeJeux, joueurActuel);
					
					if(vie[joueurActuel] > 0) /* Pour conserver le score si le joueur perd */
						score = 0;
						
					if(vie[joueurActuel] > 0)
					{	
						if(modeDeJeux == MULTI)
						{
							if(joueurActuel == 0)
								joueurActuel = 1;
							else if(joueurActuel == 1)
								joueurActuel = 0;
						}
					}
				}
			}
		}
		
		if(nbTourBonus == 0)
		{
			peutMangerFantome = DESACTIVE;
			nbTourBonus = -1;
		}
		else if(nbTourBonus > 0)
			nbTourBonus--;
		
	} while(vie[joueurActuel] != 0 && score != NB_POINTS_PACMAN);
	
	time(&fin);
	
	temps = difftime(fin, debut);
	
	if(modeDeJeux == SOLO)
	{
		if(vie[joueurActuel] == 0)
			defaitePacmanSolo(modeDeJeux, score);
		else
			victoirePacmanSolo(modeDeJeux, vie[joueurActuel], temps);
	}
	else if(modeDeJeux == MULTI)
	{
		if(vie[joueurActuel] == 0 || score == NB_POINTS_PACMAN)
			afficherGagnantPacmanMulti(joueurActuel, score, vie);
	}
}

/* ----- Roulette Russe ----- */

void menuRouletteRusse(int modeDeJeux)
{
	titre("Roulette Russe");
	
	if(modeDeJeux == SOLO)
		lireEtAfficherFichier("Texte de presentation/Roulette russe/rouletteRusseSolo.txt");
	else if(modeDeJeux == MULTI)
	{
		printf("Ce jeu n'est pas disponible en multijoueur.\n");
		revenirMenuMulti();
	}
		
	printf("\n\n");
	
	appuyezEntree("Appuyez sur ENTREE pour commencer : ");
}

void perduRouletteRusse(int nbPoints, int modeDeJeux)
{
	couleur(ROUGE);
	printf("\nVous etes mort et vous avez perdu %d point(s) !\n", nbPoints);
	couleur(RE_INIT);
	
	systemePoints(-nbPoints, 0, modeDeJeux);
}

void gagneRouletteRusse(int nbPoints, int modeDeJeux)
{
	coloration("\nVous etes en vie !\n", VERT);
	
	systemePoints(nbPoints, 0, modeDeJeux);
}

void rouletteRusse(int modeDeJeux)
{
	int revolver[NB_BALLES_REVOLVER_ROULETTE_RUSSE];
	int index, endroitBalle;
	
	menuRouletteRusse(modeDeJeux); /* La fonction est place avant les initialisations pour gerer le cas du multijoueur */
	effacer();
	
	for(index = 0; index < NB_BALLES_REVOLVER_ROULETTE_RUSSE; index++)
		revolver[index] = VIDE;
		
	endroitBalle = hasard(0, NB_BALLES_REVOLVER_ROULETTE_RUSSE - 1);
	revolver[endroitBalle] = CONTIENT_BALLE_ROULETTE_RUSSE;
	
	do
	{
	
		endroitBalle = hasard(0, NB_BALLES_REVOLVER_ROULETTE_RUSSE - 1);
	
	} while(revolver[endroitBalle] == CONTIENT_BALLE_ROULETTE_RUSSE);
	
	revolver[endroitBalle] = CONTIENT_BALLE_ROULETTE_RUSSE;
	
	printf("Que le jeu commence !\n\n");
	attendre(3);

	printf("Rechargement du canon...\n");
	attendre(2);
	printf("Le barrilet tourne...\n");
	attendre(3);
	
	printf("\nTout est en place !\n\n");
	
	endroitBalle = hasard(1, 100);	
	endroitBalle %= NB_BALLES_REVOLVER_ROULETTE_RUSSE;
	
	appuyezEntree("Appuyez sur ENTREE pour presser la detente : ");
	
	if(revolver[endroitBalle] == CONTIENT_BALLE_ROULETTE_RUSSE)
		perduRouletteRusse(nbPointsTotal(), modeDeJeux);
	else
		gagneRouletteRusse(NB_POINTS_GAGNES_ROULETTE_RUSSE, modeDeJeux);
}	

/* ----- Aide ----- */

void aide(void)
{
	titre("Aide");
	
	lireEtAfficherFichier("aide.txt");
	
	appuyezEntree("Appuyez sur ENTREE pour revenir au menu principal : ");

	menuSolo();
}

/* ----- Quitter ----- */

void quitter(void)
{
	
	enregistrerDernierePartieJoueeSolo();
	printf("Au revoir ! :)\n");
		
	exit(EXIT_SUCCESS);
}

/* ----- Autres ----- */

void attendre(float temps)
{
	clock_t arrivee;
	
	arrivee = clock() + (clock_t)(temps * CLOCKS_PER_SEC);
	
	while(clock() < arrivee)
		;
}

int nbPointsTotal(void)
{
	FILE *fichier;
	int nbPointsFichier;	
	char chemin[TAILLE_MAX];
	
	sprintf(chemin, "%s/nb_points.txt", nomDossierSauvegarde);
	
	fichier = ouvrirFichier(chemin, "r",
	"fichier \"nb_points.txt\", fonction \"nbPointsTotal\"");
	
	fscanf(fichier, "%d", &nbPointsFichier);
	
	fclose(fichier);
	
	return nbPointsFichier;
}

void systemePoints(int nbPointsGagnes, int nbPointsVIP, int modeDeJeux)
{
	FILE *fichier;
	int nbPoints, nbPointsVIPFichier;
	char chemin[TAILLE_MAX];
	
	sprintf(chemin, "%s/nb_points.txt", nomDossierSauvegarde);
	
	fichier = ouvrirFichier(chemin, "r",
	"fichier \"nb _points.txt\", fonction \"nbPointsGagnes\"");
		
	fscanf(fichier, "%d %d", &nbPoints, &nbPointsVIPFichier);
	
	fclose(fichier);
	
	nbPoints += nbPointsGagnes;
	nbPointsVIPFichier = nbPointsVIPFichier + nbPointsVIP;

	sprintf(chemin, "%s/nb_points.txt", nomDossierSauvegarde);
	
	fichier = ouvrirFichier(chemin, "w+",
	"fichier \"nb_points.txt\", fonction \"nbPointsGagnes\"");
		
	fprintf(fichier, "%d %d", nbPoints, nbPointsVIPFichier);
	
	fclose(fichier);
	
	if(nbPointsGagnes > 0)
		printf("Vous avez gagne %d point(s) !\n", nbPointsGagnes);
	if(nbPointsVIP > 0)
		printf("Vous avez gagne %d point(s) VIP !\n", nbPointsVIP);
		
	printf("Vous avez actuellement %d point(s) et %d point(s) VIP !\n", nbPoints, nbPointsVIPFichier);
	
	appuyezEntree("\nAppuyez sur ENTREE pour revenir dans le menu \"Jeu\" : ");

	jeux(modeDeJeux);
}

void appuyezEntree(const char *texte)
{
	printf("%s", texte);
	getchar();
}

void coloration(const char *texte, const char *typeCouleur)
{
	couleur(typeCouleur);
	printf("%s", texte);
	couleur(RE_INIT);
}

FILE *ouvrirFichier(const char *chemin, const char *mode, const char *messageErreur)
{
	FILE *test;
	
	test = NULL;
	test = fopen(chemin, mode);
	
	if(test == NULL)
		erreur(messageErreur);
	
	return test;
}

void viderBuffer(void)
{
    int c;
    
    c = 0;
    
    while (c != '\n' && c != EOF)
        c = getchar();
}

void lireLigneSansEspace(FILE *fichier, char ligne[])
{
	int indexLig, caractereActuelle;
	char buffer[TAILLE_MAX];
	
	lireFichier(fichier, buffer);
	
	for(indexLig = 0, caractereActuelle = 0; buffer[indexLig] != '\0'; indexLig++)
	{
		if(buffer[indexLig] != ' ')
		{
			ligne[caractereActuelle] = buffer[indexLig];
			caractereActuelle++;
		}
	}
	
	ligne[caractereActuelle] = '\0';
}

int lireFichier(FILE *fichier, char ligne[])
{
	int longueur;
	
	if(fgets(ligne, TAILLE_MAX, fichier) == NULL)
		return 0;
			
	for(longueur = 0; ligne[longueur] != '\n' && ligne[longueur] != '\0'; longueur++)
		;
		
	ligne[longueur] = '\0';	
}

void erreur(const char *message)
{
	printf("ERREUR : %s\n", message);
	exit(EXIT_FAILURE);
}

void titre(const char *s)
{
	effacer();
	
	couleur(BLEU);
	printf("\t\t\t%s\n\n", s);
	couleur(RE_INIT);
}

int choixMenu(int min, int max)
{
	int choix;
	int compteur;
	
	compteur = 0;
	
	do
	{
		if(compteur > 0)
		{
			if(min == max)
				printf("Veuillez saisir le nombre 1 pour choisir, -1 pour revenir au menu \nprinciale ou 0 pour quitter la plateforme de jeux !\n");
			else
				printf("Veuillez saisir un nombre compris entre %d et %d, -1 pour revenir au menu \nprincipale ou 0 pour quitter la plateforme de jeux ! \n", min, max);
		}
			
		printf("> ");
		scanf("%d", &choix);
		viderBuffer();
		compteur++;
		
	} while(choix < -1 || choix > max);
	
	return choix;
}

int hasard(int min, int max)
{
	return (rand() % (max - min + 1)) + min;
}

void enregistrerDernierePartieJoueeSolo(void)
{
	FILE *fichier;
	
	fichier = ouvrirFichier("dernierePartie.txt", "w+",
	"fichier \"dernierePartie.txt\", fonction \"quitter\"");
	
	fprintf(fichier, "%s\n", nomPartie);
	fprintf(fichier, "%s", nomDossierSauvegarde);
	
	fclose(fichier);
}

char lireSansEntree(void)
{
	char c;
	
	c = getch();

	return c;
}

void revenirMenuMulti(void)
{
	appuyezEntree("Appuyez sur ENTREE pour revenir au menu : ");
	multi();		
}

void lireEtAfficherFichier(const char *chemin)
{
	FILE *fichier;
	char buffer[TAILLE_MAX];
	
	fichier = ouvrirFichier(chemin, "r",
	"fichier \"texte de presentation\", fonction \"lireEtAfficherFichier\"");
		
	while(!feof(fichier))
	{
		fgets(buffer, TAILLE_MAX, fichier);
		
		if(!feof(fichier))
			printf("%s", buffer);
	}
	
	fclose(fichier);
}

int choisirDifficulte(void)
{
	int choix;
	int compteur;
	
	compteur = 0;
	
	printf("\n\nChoisissez votre niveau de difficulte : \n\n");
	
	coloration("\t1 - Facile\n\n", VERT);
	coloration("\t2 - Normal\n\n", JAUNE);
	coloration("\t3 - Difficile\n\n", ROUGE);
	
	do
	{	
		if(compteur > 0)
			printf("Veuillez entrer un nombre compris entre 1 et 3 !\n");
			
		printf("> ");
		scanf("%d", &choix);
		viderBuffer();
		compteur++;
		
	} while(choix < NIVEAU_FACILE || choix > NIVEAU_DIFFICILE);
	
	return choix;
}

void couleur(int defineCouleur) 
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, defineCouleur);
}

