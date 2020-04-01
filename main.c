/*
 * Projet : Bataille Navale
 * Auteur : Antoine Roulin
 * Date : 01.04.2020
 * Version : V1.0
 * Description : Permet de jouer a la bataille navale et de pouvoir afficher l'aide du jeu
 */

#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// fonction qui permet d'afficher l'aide du jeu
void afficherMenu();
void aideJeu();
void jeu();
void login();
void chercherFicher();
char user();
void writeLog();
void writeScore();
void afficherScores();
void chargementMap();
void changerEtatEnCoule();

int main() {
    // ligne qui permet au programme de comprendre l'UTF-8
    SetConsoleOutputCP(65001);

    writeLog("Application ouverte");

    afficherMenu();

    return 0;
}

void afficherMenu(){

    // déclaration et initialisation des variables
    int choixMenu = 0;
    char nomJoueur[21] = "Invite";   // nom de l'utilisateur (par défaut le nom est Invité sans le "é" car cela fait bugger l'affichage (j'en ai laissé un avec le "é" pour illustrer le bug d'affichage))

    // boucle qui permet de répéter les actions à l'intérieur tant que la condition de sortie n'est pas respecter
    do{
        // efface le terminal
        system("@cls||clear");  //source: https://stackoverflow.com/a/33450696

        // affichage d'un menu de séléction d'action
        printf("Menu\n\n");
        printf("Bienvenue %s\n\n", nomJoueur);
        printf(" 1)  Login\n");
        printf(" 2)  Jouer à la bataille navale\n");
        printf(" 3)  Afficher les scores précédants\n");
        printf(" 4)  Afficher l'aide du jeu\n");
        printf(" 5)  Quitter le jeu\n\n");
        printf("Entrez le numero de l'action que vous souhaitez effectuer: ");

        // scan et stock la réponse dans la variable choixMenu
        scanf("%d", &choixMenu);

        switch (choixMenu) {
            case 1:
                //printf("Vous avez choisi de vous login, cette fonction n'est pas encore implémentée\n\nAppuyez sur une touche pour quitter le programme");
                login(nomJoueur);
                break;

            case 2:
                getchar(); // si on rejoue après avoir gagné erreur passe le premier scanf après le premier passage de la boucle: https://stackoverflow.com/a/9562355
                writeLog("Début du jeu");
                jeu(nomJoueur);
                break;

            case 3:
                afficherScores();
                break;

            case 4:
                aideJeu();
                break;

            case 5:
                printf("Fermeture du jeu.\n");
                writeLog("Application fermer");
                break;

                // cela donne une suite d'actionà effectuer si la réponse ne correspond pas à une action proposée
            default:
                printf("Cette action n'existe pas !\n\nAppuyez sur une touche pour revenir au menu");
                _getch();
                break;
        }

        // condition pour rester dans la boucle
    }while(choixMenu != 5);
}

void aideJeu(){

    system("@cls||clear");

    // texte imprimer comportant les règle de la bataille navale
    printf("Aide du Jeu\n\n");
    printf("Le jeu de la bataille navale est simple.\n\n"
           "Ton but est de couler les 5 bateaux.\n\n"
           "Il y a 1 Porte-avion qui fait 5 cases.\n"
           "Il y a 1 Croiseur qui fait 4 cases.\n"
           "Il y a 1 Contre-croiseur qui fait 3 cases.\n"
           "Il y a 1 Sous-Marin qui fait 3 cases.\n"
           "Il y a 1 Torpilleur qui fait 2 cases.\n\n"
           "Il va y avoir une grille avec des coordonnées.\n"
           "Il va te falloir rentrer les coordonnées de l'endroit de la grille que tu souhaite attaquer.\n\n");

    // les choix possibles après la lecture des règles
    printf("Appuyer sur une touche pour revenir au menu\n");

    // scan et stock le résultat entrer
    _getch();
}

void jeu(char nomUser[21]){

    // déclaration des constantes
    const int LARGEUR = 10; // colonnes (lettre)
    const int HAUTEUR = 10; // lignes (nombre)
    const int A_ASCII = 65; // code du A en ASCII

    // déclaration des variables
    int grille[LARGEUR][HAUTEUR];
    int entreeLigne = 0;        // ligne entrée par l'utilisateur
    char entreeColonne = 0;     // colonne entrée par l'utilisateur
    int entreeColonneInt = 0;   // colonne entrée par l'utilisateur traduit en numéro
    int jeuEnCours = 1;         // valeur qui défini si le jeu est en cours ou non
    int message = -1;           // définir quelle message afficher
    int compteur = 0;           // compteur permetent de compter les scores
    int etat = 0;               // état de la case


    int porteAvionCount = 0;
    int croiseurCount = 0;
    int contreCroiseurCount = 0;
    int sousMarinCount = 0;
    int torpilleurCount = 0;


    int porteAvionCoule = 0;
    int croiseurCoule = 0;
    int contreCroiseurCoule = 0;
    int sousMarinCoule = 0;
    int torpilleurCoule = 0;

    chargementMap(HAUTEUR, LARGEUR, A_ASCII, grille);

    // affichage des case du jeu avec les différentes couleurs
    do{

        system("@cls||clear");  // efface l'affichage pour reafficher

        printf("Bataille navale\n\n");

        // légende
        printf("\n\n\033[0;31mRouge: Touché"
               "   \033[0;32mVert: Coulé"
               "   \033[0;36mBleu: Loupé\n\n\033[0;37m");

        // affichage entete de la grille du jeu (A B C D E ...)
        printf("  ");
        for(int i = 0; i < LARGEUR; i++){
            printf(" %c", A_ASCII + i);
        }
        printf("\n");

        // affichage de la grille
        for(int h = 0; h < HAUTEUR; h++){

            // affichage coordonnées tout a gauche (1 2 3 4 5 ...)
            printf("%2d", h + 1);

            for(int l = 0; l < LARGEUR; l++){

                switch (grille[l][h]) {
                    case 1: // bateau touché
                    case 9:
                    case 10:
                    case 11:
                    case 12:
                    case 13:
                        printf("\033[0;31m"); // couleur rouge
                        break;

                    case 2: // bateau coulé
                        printf("\033[0;32m"); // couleur verte
                        break;

                    case 3: // eau
                        printf("\033[0;36m"); // couleur bleu
                        break;

                    default:
                        printf("\033[0;37m"); // couleur par défaut
                        break;
                }

                printf(" \u2588"); // affiche un rectangle
                printf("\033[0;37m"); // remet la couleur par défaut (bug sans ça reprend la couleur de la derniere case pour le texte qui suit)

                // retour à la ligne après l cases
                if((l + 1) % LARGEUR == 0){
                    printf("\n");
                }
            }
        }

        // affiche un message selon l'action qui a été faite
        switch (message) {
            case 0:
                printf("\nTu as loupé\n");
                break;
            case 1:
                printf("\nBien joué ! Tu as touché un bateau\n");
                break;
            case 2:
                printf("\nBien joué ! Tu as touché et coulé le porte-avion\n");
                break;
            case 3:
                printf("\nBien joué ! Tu as touché et coulé le croiseur\n");
                break;
            case 4:
                printf("\nBien joué ! Tu as touché et coulé le contre-croiseur\n");
                break;
            case 5:
                printf("\nBien joué ! Tu as touché et coulé le sous-marin\n");
                break;
            case 6:
                printf("\nBien joué ! Tu as touché et coulé le torpilleur\n");
                break;
            default:
                printf("\nBonne partie !\n");
                break;
        }

        // boucle d'entrée utilisateur
        do{
            // boucle qui empêche les coordonnée en dehors de la grille de jeu
            do{
                printf("\nQuelle case veux-tu attaquer ?\nLettre de colonne: ");
                scanf("%c", &entreeColonne);
                if(!(entreeColonne >= A_ASCII && entreeColonne <= A_ASCII + LARGEUR)){
                    printf("\nLa coordonnée n'est pas sur le tableau, veuillez rentrer une donnée valide ");
                }
                getchar(); // erreur passe le premier scanf après le premier passage de la boucle: https://stackoverflow.com/a/9562355
            } while(!(entreeColonne >= A_ASCII && entreeColonne <= A_ASCII + LARGEUR));

            // boucle qui empêche les coordonnée en dehors de la grille de jeu
            do{
                printf("Numéro de ligne: ");
                scanf("%d", &entreeLigne);
                if(!(entreeLigne >=1 && entreeLigne <= HAUTEUR)){
                    printf("\nLa coordonnée n'est pas sur le tableau, veuillez rentrer une donnée valide ");
                }
                getchar();
            } while(!(entreeLigne >= 1 && entreeLigne <= HAUTEUR));

            // transforme le char en int
            entreeColonneInt = entreeColonne - A_ASCII;

            // boucle qui empêche de tirer sur une case déjà touchée
        } while(grille[entreeColonneInt][entreeLigne - 1] == 1 || grille[entreeColonneInt][entreeLigne - 1] == 2 || grille[entreeColonneInt][entreeLigne - 1] == 3);

        // ajoute 1 au compteur actuel
        compteur += 1;

        // message log
        char messageLog[100] = "Tir sur la case : ";
        sprintf(messageLog, "%s%c%d", messageLog, entreeColonne, entreeLigne);
        writeLog(messageLog);

        // conditions de touché
        switch (grille[entreeColonneInt][entreeLigne - 1]){

            case 0:
                grille[entreeColonneInt][entreeLigne - 1] = 3;
                message = 0;
                writeLog("Loupé !");
                break;

            case 4:
                porteAvionCount++;
                grille[entreeColonneInt][entreeLigne - 1] = 9;
                message = 1;
                writeLog("Touché !");
                break;

            case 5:
                croiseurCount++;
                grille[entreeColonneInt][entreeLigne - 1] = 10;
                message = 1;
                writeLog("Touché !");
                break;

            case 6:
                contreCroiseurCount++;
                grille[entreeColonneInt][entreeLigne - 1] = 11;
                message = 1;
                writeLog("Touché !");
                break;

            case 7:
                sousMarinCount++;
                grille[entreeColonneInt][entreeLigne - 1] = 12;
                message = 1;
                writeLog("Touché !");
                break;

            case 8:
                torpilleurCount++;
                grille[entreeColonneInt][entreeLigne - 1] = 13;
                message = 1;
                writeLog("Touché !");
                break;

            case 1:
            case 2:
            case 3:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            default:
                printf("\nUn tir a déjà été effectuer sur cette coordonné\n");
                break;
        }

        //printf("%d", porteAvionCount);
        //_getch();

        // conditions de coulé
        if(porteAvionCount == 5){
            etat = 9;
            changerEtatEnCoule(etat, HAUTEUR, LARGEUR, grille);
            message = 2;
            writeLog("Porte avion coulé");
            porteAvionCount = 0;    // évite que le log s'écrive a chaque tour du while et que le message pour l'utilisateur soie supprimer et remplacer par un autre
            porteAvionCoule = 1;    // permet que le compteur soie remis a zero pour éviter les logs et messages pour l'utilisateur excessif ou faux
        }

        if(croiseurCount == 4){
            etat = 10;
            changerEtatEnCoule(etat, HAUTEUR, LARGEUR, grille);
            message = 3;
            writeLog("Croiseur coulé");
            croiseurCount = 0;
            croiseurCoule = 1;
        }

        if(contreCroiseurCount == 3){
            etat = 11;
            changerEtatEnCoule(etat, HAUTEUR, LARGEUR, grille);
            message = 4;
            writeLog("Contre-Croiseur coulé");
            contreCroiseurCount = 0;
            contreCroiseurCoule = 1;
        }

        if(sousMarinCount == 3){
            etat = 12;
            changerEtatEnCoule(etat, HAUTEUR, LARGEUR, grille);
            message = 5;
            writeLog("Sous-Marin coulé");
            sousMarinCount = 0;
            sousMarinCoule = 1;
        }

        if(torpilleurCount == 2){
            etat = 13;
            changerEtatEnCoule(etat, HAUTEUR, LARGEUR, grille);
            message = 6;
            writeLog("Torpilleur coulé");
            torpilleurCount = 0;
            torpilleurCoule = 1;
        }

        // vérifier les conditions de victoire
        if(porteAvionCoule == 1 && croiseurCoule == 1 && contreCroiseurCoule == 1 && sousMarinCoule == 1 && torpilleurCoule == 1){
            printf("\nBravo %s ! Tu as gagné en %d coups !\n\nAppuyez sur une touche pour revenir au menu", nomUser, compteur);

            // message log
            sprintf(messageLog, "%s%s%d%s", nomUser, " a gagné en ", compteur, " coups");
            writeLog(messageLog);

            // message score
            writeScore(nomUser, compteur);

            _getch();
            jeuEnCours = 0;
        }
    } while(jeuEnCours == 1);
}

void login(char nom[]){

    // efface l'affichage
    system("@cls||clear");

    // affichage informatif
    printf("Login\n\n");

    // demande a l'utilisateur de rentrer un nom d'utilisateur
    printf("Entrez un nom d'utilisateur (Le nom doit pas contenir d'espace et faire max 20 caractères) : ");

    // scan la réponse et le mets dans le tableau de caractère
    scanf("%s", nom);

    // printf la chaine de caractère
    printf("Ton nom est : %s \n\n", nom);

    // log
    char message[100] = "L'utilisateur s'est connecté en tant que : ";
    sprintf(message, "%s%s", message, nom);
    writeLog(message);

    // les choix possibles après la lecture des règles
    printf("Appuyer sur une touche pour revenir au menu\n");

    // scan et stock le résultat entrer
    _getch();
}

void writeLog(char logMessage[]){

    // ajouter la date au message https://stackoverflow.com/a/10917605
    char dateText[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(dateText, sizeof(dateText)-1, "%d.%m.%Y %H:%M", t);

    // écrire le message dans le fichier logs.txt
    FILE *fL;
    fL = fopen("../logs/logs.txt", "a+");
    fprintf(fL, "%s - %s\n", dateText, logMessage);
    fclose(fL);
}

void writeScore(char nomUser[21], int saveScore){

    // écrire le message dans le fichier score.txt
    FILE *fS;
    fS = fopen("../logs/score.txt", "a+");
    fprintf(fS, "%-20s || %d\n", nomUser, saveScore);
    fclose(fS);
}

void afficherScores(){

    // déclaration de la variable caractere
    char caractere;

    system("@cls||clear");

    // affichage de l'entête
    printf("Scores\n\n");
    printf("%-20s || Score\n", "Nom");
    printf("=============================\n");

    // affichage des scores
    FILE *fileScore;
    fileScore = fopen("../logs/score.txt", "r");

    // boucle qui tourne tant qu'il y a quelque chose dans le fichier
    while((caractere = fgetc(fileScore)) != EOF){
        printf("%c", caractere);
    }

    fclose(fileScore);

    printf("\n\nAppuyer sur une touche pour revenir au menu\n");

    _getch();
}

void chargementMap(const int HAUTEUR, const int LARGEUR, const int A_ASCII,int grille[][LARGEUR]) {

    // initialisation du tableau
    // états:
    //  0 = Rien
    //  1 = Bateau touché
    //  2 = Bateau coulé
    //  3 = Eau
    //  4 = porteAvion
    //  5 = croiseur
    //  6 = contre-Croiseur
    //  7 = sous-Marin
    //  8 = torpilleur
    for (int h = 0; h < HAUTEUR; h++) {
        for (int l = 0; l < LARGEUR; l++) {
            grille[l][h] = 0;
        }
    }


    // scan le fichier ligne par ligne et mets la ligne dans une variable https://stackoverflow.com/a/39237609
    FILE *fileMaps;

    const int MIN = 1;
    const int MAX = 6;

    int bufferLength = 255;
    char buffer[bufferLength];
    char parametre[16] = "";
    char valeurH[16] = "";
    char valeurLS[16] = "";
    char valeurL;
    int valeurLInt = 0;
    int valeurHInt = 0;
    char map[30] = "";
    int nombreRandom = 0;

    // génére un nombre aléatoire entre 1 et 6
    srand(time(NULL));
    nombreRandom = (rand() % (MAX - MIN + 1)) + MIN;

    sprintf(map, "../maps/map%d.txt", nombreRandom);
    
    fileMaps = fopen(map, "r");

    //../maps/map6.txt

    while (fgets(buffer, bufferLength, fileMaps)) {

        sscanf(buffer, "%15s : %15s %15s", parametre, valeurLS, valeurH);
        valeurL = valeurLS[0];
        valeurLInt = valeurL - A_ASCII;
        valeurHInt = atoi(valeurH) - 1; //atoi(...) permet de transformer un string en int      https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c


        if (strcmp(parametre, "porteAvion") == 0) { // https://www.programiz.com/c-programming/library-function/string.h/strcmp
            grille[valeurLInt][valeurHInt] = 4;
        } else if (strcmp(parametre, "croiseur") == 0) {
            grille[valeurLInt][valeurHInt] = 5;
        } else if (strcmp(parametre, "contre-Croiseur") == 0) {
            grille[valeurLInt][valeurHInt] = 6;
        } else if (strcmp(parametre, "sous-Marin") == 0) {
            grille[valeurLInt][valeurHInt] = 7;
        } else if (strcmp(parametre, "torpilleur") == 0) {
            grille[valeurLInt][valeurHInt] = 8;
        }

    }

    fclose(fileMaps);

}

void changerEtatEnCoule(int etat, const int HAUTEUR, const int LARGEUR, int grille[][LARGEUR]){
    for (int h = 0; h < HAUTEUR; h++) {
        for (int l = 0; l < LARGEUR; l++) {
            if (grille[l][h] == etat){
                grille[l][h] = 2; // change l'état de touché à coulé
            }
        }
    }
}

//todo vérifier le nom de toute les variable si ils sont claires