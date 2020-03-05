#include <stdio.h>
#include <windows.h>

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
        printf(" 4)  Afficher l'aide du jeu\n\n");
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
                printf("Vous avez choisi d'afficher l'aide du jeu' !");
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