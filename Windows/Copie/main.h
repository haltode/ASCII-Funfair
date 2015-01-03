#ifndef MAIN_H
#define MAIN_H

/* ----- Lib a inclure ----- */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dir.h>
#include <conio.h>

/* ----- Define ----- */

#define effacer() system("cls")
	
#define SOLO 0
#define MULTI 1

#define DROIT_FICHIER 757

#define RE_INIT
#define ROUGE 1
#define JAUNE 2
#define VERT 3
#define BLEU 4
#define BLANC 5
#define CYAN 6
#define FUCHIA 7

#define COULEUR_ROUGE 1
#define COULEUR_JAUNE 2
#define COULEUR_VERT 3
#define COULEUR_BLEU 4
#define COULEUR_BLANC 5
#define COULEUR_CYAN 6
#define COULEUR_FUCHIA 7

#define TAILLE_MAX 500
#define NB_JEUX 8
#define NB_TYPES_JEUX 4
#define NB_BATEAU 5
#define NB_MOTS_PENDU 100
#define DIMENSION_MORPION 3

#define DEJA_VU 1

#define INDEX_DEBUT_REFLEXION 0
#define INDEX_FIN_REFLEXION 1
#define INDEX_DEBUT_STRATEGIE 2
#define INDEX_FIN_STRATEGIE 5
#define INDEX_DEBUT_CLASSIQUE 6
#define INDEX_DEBUT_HASARD 7

#define REFLEXION 0
#define STRATEGIE 2
#define CLASSIQUE 6
#define HASARD 7

#define NIVEAU_FACILE 1
#define NIVEAU_NORMAL 2
#define NIVEAU_DIFFICILE 3

#define NB_MAX_FACILE_PLUS_OU_MOINS 100
#define NB_MAX_NORMAL_PLUS_OU_MOINS 500
#define NB_MAX_DIFFICILE_PLUS_OU_MOINS 1000

#define NB_VIE_PLUS_OU_MOINS 10

#define NB_LIGNE_TAILLE_PENDU 10

#define NB_VIE_PENDU 10

#define PAS_TEST 0
#define TEST 1

#define GAGNER 1

#define VIDE 0
#define IA 1
#define HUMAIN 2
#define ADVERSAIRE 1

#define LIGNE_GAGNANTE 3

#define MILIEU_PLATEAU 3
#define HAUTEUR_PUISSANCE_4 6
#define LONGUEUR_PUISSANCE_4 7
#define NOMBRE_GAGNANT 4

#define RATE 4
#define TOUCHE 5
#define DECOUVERT 6

#define NB_CASES_TOTAL 17

#define HAUT 0
#define BAS 1
#define GAUCHE 2
#define DROITE 3
#define AUCUNE 4

#define NB_LIGNE_MASTERMIND 10
#define NB_COLONNE_MASTERMIND 4
#define LONGUEUR_CODE 4
#define NB_COULEUR_MASTERMIND 7
#define COTE_DROIT_MASTERMIND 1
#define COTE_GAUCHE_MASTERMIND 0
#define NB_TENTATIVE_MASTERMIND 10

#define RIEN 0
#define A_VISITER 1
#define ALENTOUR 2
#define CONTINUER 3
#define A_TOUCHE 4

#define NB_POINTS_PACMAN 224

#define NB_BALLES_REVOLVER_ROULETTE_RUSSE 6
#define CONTIENT_BALLE_ROULETTE_RUSSE 1

#define NB_LIGNE_NIVEAU_PACMAN 32
#define NB_COLONNE_NIVEAU_PACMAN 50
#define POSITION_DEPART_PACMAN 24
#define NB_VIE_PACMAN 3
#define NB_FANTOME_PACMAN 6
#define ACTIVE 1
#define DESACTIVE 0
#define NB_TOUR_BONUS_ACTIVE_PACMAN 25

#define NB_LIGNE_BATAILLE_NAVALE 10
#define NB_COLONNE_BATAILLE_NAVALE 10
#define NB_SECONDE_DEBLOQUER_POINT_VIP_BATAILLE_NAVALE 60.0

#define NB_SECONDE_DEBLOQUER_POINT_VIP_PACMAN 80.0

#define PAS_BLOQUE 0
#define BLOQUE 1

#define NB_POINTS_GAGNES_ROULETTE_RUSSE 500

/* ----- Structures + Enum ----- */

typedef struct
{
	char nom[TAILLE_MAX];
	void (*fonction)(int);
	int points;
}jeu;

typedef struct
{
	char nom[TAILLE_MAX];
	int nbCases;
}bateauBatailleNavale;

/* ----- Prototypes ----- */

void asciiArtDebut(void);
void afficherAsciiArt(void);
void choixModeDeJeuxMenu(void);

void solo(void);

void systemeSauvegardeSolo(void);
int afficherDernierePartieJoueeSolo(void);
int afficherPartieSolo(void);
void chargerPartieSolo(void);
void selectionnerPartieChargeeSolo(int partieChargee);
void nouvellePartieSolo(void);
void creerNouvellePartieSolo(const char *nomPartie);
void supprimerPartieSolo(void);

void multi(void);

void afficherMenuSolo(void);
void actionMenuSolo(int choix);
void menuSolo(void);

void initTypeDeJeux(int typeJeux[NB_JEUX]);
int differentsTypesDeJeux(int indexJeux, int *indexTypesJeux);
int afficherJeux(int modeDeJeux);
void aucunJeux(void);
void actionJeux(int choix, int modeDeJeux);
void appelerFonctionJeux(int choix, int modeDeJeux);
void jeux(int modeDeJeux);

int menuMagasinChoix(void);
int afficherMagasin(void);
void afficherTypeJeux(int indice);
int estDansListeDeJeux(int indice);
void actionMagasin(int choix);
void debloquerJeux(int idJeux);
void magasinPointsVIP(void);
int tousJeuxDebloques(void);
int debloquerProchainJeux(void);
void debloquerJeuxVIP(int idJeux);
void magasin(void);

void menuPlusOuMoins(int modeDeJeux);
int difficultePlusOuMoins(void);
void systemeDePointsPlusOuMoinsEtPendu(int coups, int modeDeJeux, int choixNiveauDifficulte);
int faireChoisirNombreMysterePlusOuMoins(void);
int choixNombreMysterePlusOuMoins(int modeDeJeux, int *choixNiveauDifficulte);
void plusOuMoins(int modeDeJeu);

void menuPendu(int modeDeJeux);
void choisirMotDictionnairePendu(char mot[]);
int gagnerPendu(int compteurPendu[], size_t longueur);
void afficherPendu(int coups);
void afficherLettreMauvaisePendu(char lettre[], int taille);
void faireChoisirMotPendu(char mot[]);
void motMysterePendu(char mot[], int modeDeJeux);
void initMotCompteurPendu(int motCompteur[], char motHasard[]);
void afficherMotCachePendu(int motCompteur[], char motMystere[]);
void verifierLettrePendu(char lettre, int *nbLettreMauvaise, char lettreMauvaise[], int motCompteur[], char motMystere[], int *vie);
void afficherReponsePendu(int vie, char motMystere[]);
void pendu(int modeDeJeu);

void menuMorpion(int modeDeJeux, int *niveauDifficulte);
void initMorpion(void);
int testerCaseIAMorpion(int type, int *ligne, int *colonne);
void IAMorpionFacile(void);
void IAMorpionNormal(void);
void IAMorpionDifficile(void);
void IAMorpion(int niveauDifficulte);
void afficherMorpion(void);
void ligneEnVertGagnanteMorpionHorizontale(int ligne, int joueur);
void ligneEnVertGagnanteMorpionVerticale(int ligne, int joueur);
int testerLigneGagnanteMorpion(int numeroJoueur, int estUnTest);
int testerColonneGagnanteMorpion(int numeroJoueur, int estUnTest);
int testerDiagonaleDebutEnHautaGaucheMorpion(int numeroJoueur, int estUnTest);
int testerDiagonaleDebutEnHautaDroiteMorpion(int numeroJoueur, int estUnTest);
int gagnerMorpion(int estUnTest);
void afficherGagnantMorpionSolo(int gagnant, int nbCoups, int modeDeJeux, int niveauDifficulte);
int estMorpionPlein(void);
int demanderPositionJoueurMorpion(void);
void recupererPositionCoupJoueurMorpion(int *ligne, int *colonne, int position);
void jouerCoupHumainMorpion(int typeJoueur, int modeDeJeux);
void afficherGagnantMorpionMulti(int gagnant);
void morpion(int modeDeJeu);

void menuPuissance4(int modeDeJeux, int *niveauDifficulte);
void initPuissance4(void);
void afficherPuissance4(void);
int placerPuissance4(int colonne, int typeJoueur);
int puissance4pasRempli(void);
int testerLigneGagnantePuissance4(int lig, int col, int numeroJoueur, int estUnTest);
int testerColonneGagnantePuissance4(int lig, int col, int numeroJoueur, int estUnTest);
int testerDiagonaleDebutEnHautaGauchePuissance4(int lig, int col, int numeroJoueur, int estUnTest);
int testerDiagonaleDebutEnHautaDroitePuissance4(int lig, int col, int numeroJoueur, int estUnTest);
int gagnerPuissance4(int estUnTest);
int testerCaseIAPuissance4(int type, int *colonne);
void IAPuissance4Facile(void);
void IAPuissance4Normal(void);
void IAPuissance4Difficile(void);
void IAPuissance4(int niveauDifficulte);
void afficherGagnantPuissance4Solo(int nbCoups, int modeDeJeux, int niveauDifficulte);
int demanderPositionCroixJoueurPuissance4(void);
void jouerCoupHumainPuissance4(int typeJoueur, int modeDeJeux);
void afficherGagnantPuissance4Multi(void);
int estColonneRempliePuissance4(int colonne);
int estPuissance4Vide(void);
void puissance4(int modeDeJeu);

void menuMastermind(int modeDeJeux);
void initMastermind(void);
void initCodeSecretMastermind(char code[LONGUEUR_CODE + 1]);
void afficherCoteMastermind(int lig, int estCoteDroit);
void afficherPionMastermind(int pion);
void afficherCaractereCouleurMastermind(void);
void afficherMastermind(void);
void placerPionMastermind(const char *combinaison, int lig);
void verifierCodeMastermind(const char *code, const char *tentative, int *nbBienPlace, int *nbMalPlace);
void placerPionCouleurCoteMastermind(int nbBienPlace, int nbMalPlace, int lig);
int gagnerMastermind(const char *code, const char *tentative);
void victoireMastermindSolo(int coups, int modeDeJeux);
void afficherReponseMastermind(const char *code);
void defaiteMastermindSolo(int modeDeJeux);
int estCodeBon(const char code[LONGUEUR_CODE + 1]);
void demanderCodeSecretMastermind(char code[LONGUEUR_CODE + 1]);
void victoireMastermindMulti(void);
void defaiteMastermindMulti(void);
void mastermind(int modeDeJeu);

void afficherLegendeMenuBatailleNavale(void);
void menuBatailleNavale(int modeDeJeux, int *niveauDifficulte);
void initBatailleNavale(void);
void afficherBatailleNavale(void);
void formaterChaineBatailleNavale(const char *chaine, int *ligne, int *colonne, int *direction);
int placerDirectionBatailleNavale(int ligne, int colonne, int dir, int nbCases, int contenu, int estUnTest);
int estValidePositionBateauHumainBatailleNavale(char positionBateau[TAILLE_MAX]);
void placerNavireHumainBatailleNavale(void);
void formaterCadrillageIABatailleNavale(void);
void placerNavireIABatailleNavale(void);
int jouerCoupHumainBatailleNavale(const char *emplacement);
int lancerTorpilleIABatailleNavale(int lig, int col);
void verifierAlentourIABatailleNavale(int lig, int col);
void enleverDejaToucheIABatailleNavale(void);
int rechercheIABatailleNavale(int recherche);
void enleverAlentourIABatailleNavale(void);
int directionIABatailleNavale(int ligne, int colonne);
void verifierBateauIABatailleNavale(int lig, int col, int direction);
int IABatailleNavaleFacile(char position[10]);
int IABatailleNavaleNormal(char position[10]);
int IABatailleNavaleDifficile(char position[10]);
int jouerCoupIABatailleNavale(char position[10], int niveauDifficulte);
void victoireBatailleNavale(int modeDeJeux, double secondes, int niveauDifficulte);
void defaiteBatailleNavale(int modeDeJeux);
int estValideCoupHumainBatailleNavale(char emplacement[TAILLE_MAX]);
void demanderCoupHumainBatailleNavale(char emplacement[TAILLE_MAX]);
void batailleNavale(int modeDeJeu);

void afficherLegendePacman(void);
void menuPacman(int modeDeJeux);
void initNiveauPacman(char emplacementFantome[NB_FANTOME_PACMAN], int *lig, int *col, int *dir);
void afficherDirectionPacman(int direction);
void afficherNiveauPacman(int ligne, int colonne, int direction);
void deplacerPacman(int entree, int *lig, int *col, int *direction, int *score, int *bonus);
void rechercherFantomePacman(int id, int *ligne, int *colonne);
int deplacerDirectionFantomePacman(int *ligne, int *colonne, int direction, int lig, int col);
void testerTousLesCotesFantomeBloquePacman(int ligActuel, int colActuel, int ligne, int colonne, int *nbCoteDisponibleLibre);
int estBloquerFantomePacman(int lig, int col);
int deplacerFantomePacman(int ligne, int colonne, char emplacementFantome[NB_FANTOME_PACMAN], int bonus);
void perdreViePacman(int nbVie, int score, int modeDeJeux, int joueurActuel);
void defaitePacmanSolo(int modeDeJeux, int score);
void victoirePacmanSolo(int modeDeJeux, int vie, double temps);
void afficherGagnantPacmanMulti(int joueurActuel, int score, int vie[2]);
void pacman(int modeDeJeu);

void menuRouletteRusse(int modeDeJeux);
void perduRouletteRusse(int nbPoints, int modeDeJeux);
void gagneRouletteRusse(int nbPoints, int modeDeJeux);
void rouletteRusse(int modeDeJeu);


void aide(void);

void quitter(void);

void attendre(float temps);
int nbPointsTotal(void);
void systemePoints(int nbPointsGagnes, int nbPointsVIP, int modeDeJeux);
void appuyezEntree(const char *texte);
void coloration(const char *texte, const char *typeCouleur);
FILE *ouvrirFichier(const char *chemin, const char *mode, const char *messageErreur);
void viderBuffer(void);
void lireLigneSansEspace(FILE *fichier, char ligne[]);
int lireFichier(FILE *fichier, char ligne[]);
void erreur(const char *message);
void titre(const char *s);
int choixMenu(int min, int max);
int hasard(int min, int max);
void enregistrerDernierePartieJoueeSolo(void);
char lireSansEntree(void);
void revenirMenuMulti(void);
void lireEtAfficherFichier(const char *chemin);
int choisirDifficulte(void);
void couleur(int defineCouleur);

/* ----- Declarations ----- */

char nomPartie[TAILLE_MAX];
char nomDossierSauvegarde[TAILLE_MAX];

jeu base[NB_JEUX] =
{
	{"Plus ou Moins", plusOuMoins, 0},
	{"Pendu", pendu, 300},
	{"Morpion", morpion, 600},
	{"Puissance 4", puissance4, 900},
	{"Mastermind", mastermind, 1200},
	{"Bataille Navale", batailleNavale, 1500},
	{"Pacman", pacman, 2500},
	{"Roulette Russe", rouletteRusse, 3200},
};

bateauBatailleNavale baseBateau[NB_BATEAU] =
{
	{"porte-avions", 5},
	{"croiseur", 4},
	{"contre-torpilleurs", 3},
	{"sous-marin", 3},
	{"torpilleur", 2}
};

int jeuMorpion[DIMENSION_MORPION][DIMENSION_MORPION];

int jeuPuissance4[HAUTEUR_PUISSANCE_4][LONGUEUR_PUISSANCE_4];

int jeuMastermind[NB_LIGNE_MASTERMIND][NB_COLONNE_MASTERMIND];
int coteMastermind[NB_LIGNE_MASTERMIND][NB_COLONNE_MASTERMIND];

int jeuBatailleNavale[NB_LIGNE_BATAILLE_NAVALE][NB_COLONNE_BATAILLE_NAVALE];
int cadrillage[NB_LIGNE_BATAILLE_NAVALE][NB_COLONNE_BATAILLE_NAVALE];

char niveau[NB_LIGNE_NIVEAU_PACMAN][TAILLE_MAX];

#endif

