/*
 * Projet : Bataille Navale
 * Auteur : Antoine Roulin
 * Date : 14.03.2020
 * Version : V0.1
 * Description : Permet de jouer a la bataille navale et de pouvoir afficher l'aide du jeu
 */

#include <stdio.h>
#include <windows.h>
#include <conio.h>

// fonction qui permet d'afficher l'aide du jeu
void afficherMenu();
void aideJeu();
void jeu();

int main() {
    // ligne qui permet au programme de comprendre l'UTF-8
    SetConsoleOutputCP(65001);

    afficherMenu();

    return 0;
}

void afficherMenu(){

    // déclaration et initialisation des variables
    int choixMenu = 0;

    // boucle qui permet de répéter les actions à l'intérieur tant que la condition de sortie n'est pas respecter
    do{

        // efface le terminal
        system("@cls||clear");  //source: https://stackoverflow.com/a/33450696

        // affichage d'un menu de séléction d'action
        printf("Menu\n\n");
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
                printf("Vous avez choisi de vous login, cette fonction n'est pas encore implémentée\n\nAppuyez sur une touche pour quitter le programme");
                _getch();
                break;

            case 2:
                getchar(); // si on rejoue après avoir gagné erreur passe le premier scanf après le premier passage de la boucle: https://stackoverflow.com/a/9562355
                jeu();
                break;

            case 3:
                printf("Vous avez choisi d'afficher les scores précédants, cette fonction n'est pas encore implémentée\n\nAppuyez sur une touche pour revenir au menu");
                _getch();
                break;

            case 4:
                aideJeu();
                break;

            case 5:
                printf("Fermeture du jeu.\n");
                break;

                // cela donne une suite d'actionà effectuer si la réponse ne correspond pas à une action proposée
            default:
                printf("Cette action n'existe pas !\n\nAppuyez sur une touche pour revenir au menu");
                _getch();
                break;
        }

        // condition pour rester dans la boucle
    }while(choixMenu < 0 || choixMenu >= 4);
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

void jeu(){

    // déclaration des constantes
    const int LARGEUR = 20; // colonnes
    const int HAUTEUR = 20; // lignes
    const int A_ASCII = 65; // code du A en ASCII

    // déclaration des variables
    int grille[LARGEUR][HAUTEUR];
    int entreeLigne = 0;        // ligne entrée par l'utilisateur
    char entreeColonne = 0;     // colonne entrée par l'utilisateur
    int entreeColonneInt = 0;   // colonne entrée par l'utilisateur traduit en numéro
    int jeuEnCours = 1;         // valeur qui défini si le jeu est en cours ou non
    int message = -1;           // définir quelle message afficher

    // initialisation du tableau
    // états:
    //  0 = Rien
    //  1 = Bateau touché
    //  2 = Bateau coulé
    //  3 = Bateau non découvert
    //  4 = Eau
    for(int h = 0; h < HAUTEUR; h++){
        for(int l = 0; l < LARGEUR; l++){
            grille[l][h] = 0;
        }
    }

    // placement des bateaux
    // porte-avion 5 cases
    grille[1][0] = 3;
    grille[2][0] = 3;
    grille[3][0] = 3;
    grille[4][0] = 3;
    grille[5][0] = 3;
    int porteAvionCoule = 0;

    // croiseur 4 cases
    grille[0][9] = 3;
    grille[1][9] = 3;
    grille[2][9] = 3;
    grille[3][9] = 3;
    int croiseurCoule = 0;

    // contre-croiseur 3 cases
    grille[3][4] = 3;
    grille[3][5] = 3;
    grille[3][6] = 3;
    int contreCroiseurCoule = 0;

    // sous-Marin 3 cases
    grille[7][2] = 3;
    grille[7][3] = 3;
    grille[7][4] = 3;
    int sousMarin = 0;

    // torpilleur 2 cases
    grille[7][7] = 3;
    grille[8][7] = 3;
    int torpilleur = 0;

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
                        printf("\033[0;31m"); // couleur rouge
                        break;

                    case 2: // bateau coulé
                        printf("\033[0;32m"); // couleur verte
                        break;

                    case 4: // eau
                        printf("\033[0;36m"); // couleur bleu
                        break;

                    /*case 3:  // cheat
                        printf("\033[0;35m"); // couleur magenta
                        break;*/

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
                    printf("La coordonnée n'est pas sur le tableau ! Veuillez rentrer une donnée valide");
                }
                getchar(); // erreur passe le premier scanf après le premier passage de la boucle: https://stackoverflow.com/a/9562355
            } while(!(entreeColonne >= A_ASCII && entreeColonne <= A_ASCII + LARGEUR));

            // boucle qui empêche les coordonnée en dehors de la grille de jeu
            do{

                printf("Numéro de ligne: ");
                scanf("%d", &entreeLigne);
                if(!(entreeLigne >=1 && entreeLigne <= HAUTEUR)){
                    printf("La coordonnée n'est pas sur le tableau ! Veuillez rentrer une donnée valide");
                }
                getchar();
            } while(!(entreeLigne >= 1 && entreeLigne <= HAUTEUR));

            // transforme le char en int
            entreeColonneInt = entreeColonne - A_ASCII;

            // boucle qui empêche de tirer sur une case déjà touchée
        } while(grille[entreeColonneInt][entreeLigne - 1] == 1 || grille[entreeColonneInt][entreeLigne - 1] == 2 || grille[entreeColonneInt][entreeLigne - 1] == 4);

        // conditions de touché
        if(grille[entreeColonneInt][entreeLigne - 1] == 3){
            grille[entreeColonneInt][entreeLigne - 1] = 1;
            message = 1;
        } else { // loupé
            grille[entreeColonneInt][entreeLigne - 1] = 4;
            message = 0;
        }

        // conditions de coulé
        if(grille[1][0] == 1 && grille[2][0] == 1 && grille[3][0] == 1 && grille[4][0] == 1 && grille[5][0] == 1){
            grille[1][0] = 2;
            grille[2][0] = 2;
            grille[3][0] = 2;
            grille[4][0] = 2;
            grille[5][0] = 2;
            porteAvionCoule = 1;
            message = 2;
        }

        if(grille[0][9] == 1 && grille[1][9] == 1 && grille[2][9] == 1 && grille[3][9] == 1){
            grille[0][9] = 2;
            grille[1][9] = 2;
            grille[2][9] = 2;
            grille[3][9] = 2;
            croiseurCoule = 1;
            message = 3;
        }

        if(grille[3][4] == 1 && grille[3][5] == 1 && grille[3][6] == 1){
            grille[3][4] = 2;
            grille[3][5] = 2;
            grille[3][6] = 2;
            contreCroiseurCoule = 1;
            message = 4;
        }

        if(grille[7][2] == 1 && grille[7][3] == 1 && grille[7][4] == 1){
            grille[7][2] = 2;
            grille[7][3] = 2;
            grille[7][4] = 2;
            sousMarin = 1;
            message = 5;
        }

        if(grille[7][7] == 1 && grille[8][7] == 1){
            grille[7][7] = 2;
            grille[8][7] = 2;
            torpilleur = 1;
            message = 6;
        }

        // vérifier les conditions de victoire
        if(porteAvionCoule == 1 && croiseurCoule == 1 && contreCroiseurCoule == 1 && sousMarin == 1 && torpilleur == 1){
            printf("\nBravo ! vous avez gagné !\n\nAppuyez sur une touche pour revenir au menu");
            _getch();
            jeuEnCours = 0;
        }
    } while(jeuEnCours == 1);
}