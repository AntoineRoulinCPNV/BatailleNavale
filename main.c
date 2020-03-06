#include <stdio.h>
#include <windows.h>
#include<stdio.h>

//Fonction qui permet d'afficher l'aide du jeu
void aideJeu();

int main() {
    //Ligne qui permet au programme de comprendre l'UTF-8
    SetConsoleOutputCP(65001);

    //Déclaration et initialisation des variables
    int choixMenu = 0;

    //Boucle qui permet de répéter les actions à l'intérieur tant que la condition de sortie n'est pas respecter
    do{
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

        //Effectue une suite d'action différente selon la réponse stockée
        switch (choixMenu) {
            case 1:
                printf("Vous avez choisi de vous login !");
                break;

            case 2:
                printf("Vous avez choisi de jouer à la bataille navale !");
                break;

            case 3:
                printf("Vous avez choisi d'afficher les scores précédants !");
                break;

            case 4:
                aideJeu();
                break;

            case 5:
                printf("Fermeture du jeu");
                break;

                //Cela donne une suite d'actionà effectuer si la réponse ne correspond pas à une action proposée
            default:
                printf("Cette action n'existe pas !\n");
                break;
        }
        //Condition pour rester dans la boucle
    }while(choixMenu != 1 && choixMenu != 2 && choixMenu != 3 && choixMenu != 4);

    return 0;
}

void aideJeu(){

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
    printf(" 1)  Retourner au menu du jeu\n");
    printf(" 2)  Quitter le jeu\n\n");
    printf("Que souhaitez-vous faire :");
    //Scan et stock le résultat entrer
    scanf("%d", &choixAide);

    //Fait une suite d'action selon la réponse stocké dans choixAide
    switch (choixAide){
        //Le cas ou la réponse est 1 le programme fait les actions à l'intérieur
        case 1:
            printf("Vous allez retourner au menu principal du jeu.");
            main();

        case 2:
            printf("Le jeu va se fermer");
            break;
    }
}