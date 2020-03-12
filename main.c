#include <stdio.h>
#include <windows.h>
#include <stdio.h>
#include <unistd.h>

#include <conio.h>
#include <ctype.h>

//Fonction qui permet d'afficher l'aide du jeu
void afficherMenu();
void aideJeu();
void jeu();

int main() {
    //Ligne qui permet au programme de comprendre l'UTF-8
    SetConsoleOutputCP(65001);

    afficherMenu();

    return 0;
}

void afficherMenu(){

    //Déclaration et initialisation des variables
    int choixMenu = 0;

    //Boucle qui permet de répéter les actions à l'intérieur tant que la condition de sortie n'est pas respecter
    do{

        //efface le terminal
        system("@cls||clear");  //source: https://stackoverflow.com/a/33450696

        //Affichage d'un menu de séléction d'action
        printf("Menu\n\n");
        printf(" 1)  Login\n");
        printf(" 2)  Jouer à la bataille navale\n");
        printf(" 3)  Afficher les scores précédants\n");
        printf(" 4)  Afficher l'aide du jeu\n");
        printf(" 5)  Quitter le jeu\n\n");
        //Affiche la demande du nombre d'un des programme proposer
        printf("Entrez le numero de l'action que vous souhaitez effectuer :");

        //scan et stock la réponse dans la variable choixMenu
        scanf("%d", &choixMenu);
        //choixMenu = 2;

        switch (choixMenu) {
            case 1:
                printf("Vous avez choisi de vous login !\n");
                _getch();
                break;

            case 2:
                getchar(); // erreur passe le premier scanf après le premier passage de la boucle: https://stackoverflow.com/a/9562355
                jeu();
                break;

            case 3:
                printf("Vous avez choisi d'afficher les scores précédants !\n");
                _getch();
                break;

            case 4:
                aideJeu();
                break;

            case 5:
                printf("Fermeture du jeu.\n");
                break;

                //Cela donne une suite d'actionà effectuer si la réponse ne correspond pas à une action proposée
            default:
                printf("Cette action n'existe pas !\n");
                break;
        }

        //Condition pour rester dans la boucle
    }while(choixMenu > 0 && choixMenu <= 4);
}

void aideJeu(){
    system("@cls||clear");
    //Déclaration et initialisation des variable
    int choixAide = 0;
    //Texte imprimer comportant les règle de la bataille navale
    printf("Aide du Jeu\n\n");
    printf("Le jeu de la bataille navale est simple.\n\n"
           "Ton but est de couler les 5 bateaux.\n\n"
           "Il y a 1 Porte-avion qui fait 5 cases.\n"
           "Il y a 1 Croisseur qui fait 4 cases.\n"
           "Il y a 1 Contre-croisseur qui fait 3 cases.\n"
           "Il y a 1 Sous-Marin qui fait 3 cases.\n"
           "Il y a 1 Torpilleur qui fait 2 cases.\n\n"
           "Il va y avoir une grille avec des coordonnées.\n"
           "Il va te falloir rentrer les coordonnées de l'endroit de la grille que tu souhaite attaquer.\n\n");
    //Les choix possibles après la lecture des règles
    printf("Appuyer sur une touche pour revenir au menu\n");
    //Scan et stock le résultat entrer
    _getch();
    system("@cls||clear");
}

void jeu(){

    const int LARGEUR = 10; //Colonnes
    const int HAUTEUR = 10; //Lignes

    int grille[LARGEUR][HAUTEUR];
    int entreeLigne = 0;
    char entreeColonne = 0;
    int entreeColonneInt = 0;
    int jeuEnCours = 1;

    //initialisation du tableau
    //états:
    // 0 = Rien
    // 1 = Bateau touché
    // 2 = Bateau coulé
    // 3 = Bateau non découvert
    // 4 = Eau
    for(int h = 0; h < HAUTEUR; h++){
        for(int l = 0; l < LARGEUR; l++){
            grille[l][h] = 0;
        }
    }

    //placement des bateaux
    //Porte-avion 5 cases
    grille[1][0] = 3;
    grille[2][0] = 3;
    grille[3][0] = 3;
    grille[4][0] = 3;
    grille[5][0] = 3;
    int porteAvionCoule = 0;

    //Croisseur 4 cases
    grille[0][9] = 3;
    grille[1][9] = 3;
    grille[2][9] = 3;
    grille[3][9] = 3;
    int croisseurCoule = 0;

    //Contre-croisseur 3 cases
    grille[3][4] = 3;
    grille[3][5] = 3;
    grille[3][6] = 3;
    int contreCroisseurCoule = 0;

    //Sous-Marin 3 cases
    grille[7][2] = 3;
    grille[7][3] = 3;
    grille[7][4] = 3;
    int sousMarin = 0;

    //Torpilleur 2 cases
    grille[7][7] = 3;
    grille[8][7] = 3;
    int torpilleur = 0;

    //Affichage des case avec les différentes couleurs
    do{

        system("@cls||clear");
        printf("Bataille navale\n\n");

        // légende
        printf("\n\n\033[0;31mRouge: Touché"
               "   \033[0;32mVert: Coulé"
               "   \033[0;36mBleu: Loupé\n\n\033[0;37m");

        //Affichage de la grille

        //coordonnées X
        printf("  ");
        for(int i = 0; i < LARGEUR; i++){
            printf(" %c", 65 + i);
        }

        printf("\n");

        for(int h = 0; h < HAUTEUR; h++){

            //coordonnées Y
            printf("%2d", h + 1);

            for(int l = 0; l < LARGEUR; l++){

                switch (grille[l][h]) {
                    case 1: // bateau touché
                        printf("\033[0;31m"); //couleur rouge
                        break;

                    case 2: // bateau coulé
                        printf("\033[0;32m"); //couleur verte
                        break;

                    case 4: // eau
                        printf("\033[0;36m"); //couleur bleu
                        break;

                        //cheat
                        /*case 3:
                            printf("\033[0;35m"); //couleur verte
                            break;*/

                    default:
                        printf("\033[0;37m"); //couleur par défaut
                        break;
                }

                printf(" \u2588");

                // retour à la ligne après l cases
                if((l + 1) % LARGEUR == 0){
                    printf("\n");
                }
            }
        }


        do{

            //Boucle qui empêche les coordonnée en dehors de la grille de jeu
            do{
                printf("\nQuelle case veux-tu attaquer ?\nLettre de colonne: ");
                scanf("%c", &entreeColonne);
                if(!(entreeColonne >= 65 && entreeColonne <= 65 + LARGEUR)){
                    printf("La coordonnée n'est pas sur le tableau ! Veuillez rentrer une donnée valide");
                    printf("test");
                };
                getchar(); // erreur passe le premier scanf après le premier passage de la boucle: https://stackoverflow.com/a/9562355
            }while(!(entreeColonne >= 65 && entreeColonne <= 65 + LARGEUR));


            //Boucle qui empêche les coordonnée en dehors de la grille de jeu
            do{
                printf("Numéro de ligne: ");
                scanf("%d", &entreeLigne);
                if(!(entreeLigne >=1 && entreeLigne <= 10)){
                    printf("La coordonnée n'est pas sur le tableau ! Veuillez rentrer une donnée valide");
                };
            }while(!(entreeLigne >= 1 && entreeLigne <= 10));

            //Transforme le char en int
            entreeColonneInt = entreeColonne - 65;

            //Boucle qui empêche de tirer sur une case déjà touchée
        }while(grille[entreeColonneInt][entreeLigne] == 1 || grille[entreeColonneInt][entreeLigne] == 2 || grille[entreeColonneInt][entreeLigne] == 4);


        /*do{

        printf("Numéro de ligne: ");
        scanf("%d", &entreeLigne);
        getchar(); // erreur passe le premier scanf après le premier passage de la boucle: https://stackoverflow.com/a/9562355
        }while(!(entreeColonne >= 65 && entreeColonne <= 65 + LARGEUR && entreeLigne >=1 && entreeLigne <= 10));
         */




        // conditions de touché
        if(grille[entreeColonneInt][entreeLigne - 1] == 3){
            grille[entreeColonneInt][entreeLigne - 1] = 1;
        } else {
            grille[entreeColonneInt][entreeLigne - 1] = 4;
        }

        // conditions de coulé
        if(grille[1][0] == 1 && grille[2][0] == 1 && grille[3][0] == 1 && grille[4][0] == 1 && grille[5][0] == 1){
            grille[1][0] = 2;
            grille[2][0] = 2;
            grille[3][0] = 2;
            grille[4][0] = 2;
            grille[5][0] = 2;
            porteAvionCoule = 1;
        }

        if(grille[0][9] == 1 && grille[1][9] == 1 && grille[2][9] == 1 && grille[3][9] == 1){
            grille[0][9] = 2;
            grille[1][9] = 2;
            grille[2][9] = 2;
            grille[3][9] = 2;
            croisseurCoule = 1;
        }

        if(grille[3][4] == 1 && grille[3][5] == 1 && grille[3][6] == 1){
            grille[3][4] = 2;
            grille[3][5] = 2;
            grille[3][6] = 2;
            contreCroisseurCoule = 1;
        }

        if(grille[7][2] == 1 && grille[7][3] == 1 && grille[7][4] == 1){
            grille[7][2] = 2;
            grille[7][3] = 2;
            grille[7][4] = 2;
            sousMarin = 1;
        }

        if(grille[7][7] == 1 && grille[8][7] == 1){
            grille[7][7] = 2;
            grille[8][7] = 2;
            torpilleur = 1;
        }

        // vérifier les conditions de victoire
        if(porteAvionCoule == 1 && croisseurCoule == 1 && contreCroisseurCoule == 1 && sousMarin == 1 && torpilleur == 1){
            printf("\nBravo ! vous avez gagné !\n\nAppuyez sur une touche pour revenir au menu");
            _getch();
            jeuEnCours = 0;
        }
    }while(jeuEnCours == 1);
}