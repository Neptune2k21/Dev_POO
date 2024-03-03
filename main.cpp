#include<iostream>
#include<ctime>
#include "morpion.h"

// Stratégie pour les 'O' : placer 'O' à côté de la plus grande succession d''O'
void jouerRond(char** tab, int taille, int& x, int& y) {
    // Placer 'O' aléatoirement si aucune succession d''O' n'existe
    bool position_trouver = false;

    while (!position_trouver) {
        x = rand() % taille;
        y = rand() % taille;

        if (estLibre_morpion(tab, taille, x, y)) {
            break;
        }
    }

    int nb_succession = 0;
    int succession_actu = 0;
    int pos_initX = 0;
    int pos_initY = 0;

    // Vérifie les successions horizontales
    for (int i = 0; i < taille; ++i) {
        succession_actu = 0;
        for (int j = 0; j < taille; ++j) {
            if (tab[i][j] == 'O') {
                succession_actu++;
                if (succession_actu > nb_succession) {
                    nb_succession = succession_actu;
                    pos_initX = i - nb_succession + 1;
                    pos_initY = j - nb_succession + 1;
                }
            } else {
                succession_actu = 0;
            }
        }
    }

    // Vérifie les successions verticales
    for (int j = 0; j < taille; ++j) {
        succession_actu = 0;
        for (int i = 0; i < taille; ++i) {
            if (tab[i][j] == 'O') {
                succession_actu++;
                if (succession_actu > nb_succession) {
                    nb_succession = succession_actu;
                    pos_initX = i - nb_succession + 1;
                    pos_initY = j - nb_succession + 1;
                }
            } else {
                succession_actu = 0;
            }
        }
    }

    // Vérifie les successions diagonales
    for (int i = 0; i < taille; ++i) {
        for (int j = 0; j < taille; ++j) {
            succession_actu = 0;

            // Diagonale vers le bas à droite
            for (int k = 0; i + k < taille && j + k < taille; ++k) {
                if (tab[i + k][j + k] == 'O') {
                    succession_actu++;
                    if (succession_actu > nb_succession) {
                        nb_succession = succession_actu;
                        pos_initX = i + k - nb_succession + 1;
                        pos_initY = j + k - nb_succession + 1;
                    }
                } else {
                    succession_actu = 0;
                }
            }

            succession_actu = 0;

            // Diagonale vers le bas à gauche
            for (int k = 0; i + k < taille && j - k >= 0; ++k) {
                if (tab[i + k][j - k] == 'O') {
                    succession_actu++;
                    if (succession_actu > nb_succession) {
                        nb_succession = succession_actu;
                        pos_initX = i + k - nb_succession + 1;
                        pos_initY = j - k + nb_succession - 1;
                    }
                } else {
                    succession_actu = 0;
                }
            }
        }
    }

    // Placer 'O' à côté de la plus grande succession d''O'
    if (nb_succession > 0) {
        // Vérifier les cases adjacentes
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                int NouvX = pos_initX + i;
                int NouvY = pos_initY + j;

                if (NouvX >= 0 && NouvX < taille && NouvY >= 0 && NouvY < taille && tab[NouvX][NouvY] == ' ') {
                    x = NouvX;
                    y = NouvY;
                    position_trouver = true;
                    break;
                }
            }
        }
    }
}

//Stratégie pour les 'X' : cherche à bloquer les suites de plus de 2 'O' et priorise les lignes avec le plus de 'O'
void jouerCroix(char** tab, int taille, int& x, int& y) {
    int groupeMaxX = -1;
    int groupeMaxY = -1;
    int maxAdjacent = 0;

    // Parcourir le tableau pour trouver les positions des 'O'
    for (int i = 0; i < taille; ++i) {
        for (int j = 0; j < taille; ++j) {
            if (tab[i][j] == 'O') {
                int nbAdjacent = 0;

                for (int a = -1; a <= 1; ++a) {
                    for (int b = -1; b <= 1; ++b) {
                        if (a == 0 && b == 0) {
                            // On évite la m^me position
                        } else {
                            int NouvX = i + a;
                            int NouvY = j + b;

                            if (NouvX >= 0 && NouvX < taille && NouvY >= 0 && NouvY < taille && tab[NouvX][NouvY] == 'O') {
                                nbAdjacent++;
                            }
                        }
                    }
                }

                if (nbAdjacent > maxAdjacent) {
                    maxAdjacent = nbAdjacent;
                    groupeMaxX = i;
                    groupeMaxY = j;
                }
            }
        }
    }

    // Choisir une position bloquant les suites de plus de 2 'O' du groupe choisi
    bool position_trouver = false;
    for (int i = -1; i <= 1 && !position_trouver; ++i) {
        for (int j = -1; j <= 1 && !position_trouver; ++j) {
            if (i == 0 && j == 0) {
                // On évite la position actuelle
            } else {
                int NouvX = groupeMaxX + i;
                int NouvY = groupeMaxY + j;

                if (NouvX >= 0 && NouvX < taille && NouvY >= 0 && NouvY < taille && tab[NouvX][NouvY] == 'O') {
                    int blockX = groupeMaxX - i;
                    int blockY = groupeMaxY - j;

                    if (blockX >= 0 && blockX < taille && blockY >= 0 && blockY < taille && tab[blockX][blockY] == ' ') {
                        x = blockX;
                        y = blockY;
                        position_trouver = true;
                        break;
                    }
                }
            }
        }
    }

    // Voir les positions diagonales pour bloquer les suites
    for (int i = -1; i <= 1 && !position_trouver; ++i) {
        for (int j = -1; j <= 1 && !position_trouver; ++j) {
            if (i == 0 || j == 0) {
                // Ignorer la position actuelle
            } else {
                int NouvX = groupeMaxX + i;
                int NouvY = groupeMaxY + j;

                if (NouvX >= 0 && NouvX < taille && NouvY >= 0 && NouvY < taille && tab[NouvX][NouvY] == 'O') {
                    int blockX = groupeMaxX - i;
                    int blockY = groupeMaxY - j;

                    if (blockX >= 0 && blockX < taille && blockY >= 0 && blockY < taille && tab[blockX][blockY] == ' ') {
                        x = blockX;
                        y = blockY;
                        position_trouver = true;
                        break;
                    }
                }
            }
        }
    }

    // Si aucune position de blocage n'est possible, choisir une position aléatoire
    while (!position_trouver) {
        x = rand() % taille;
        y = rand() % taille;

        if (estLibre_morpion(tab, taille, x, y)) {
            break;
        }
    }
}


bool choixDiff() {
    int choix;
    std::cout << "Choisissez la difficulte du joueur 'O':" << std::endl;
    std::cout << "1. Facile" << std::endl;
    std::cout << "2. Moyen" << std::endl;
    std::cout << "Votre choix: ";
    std::cin >> choix;

    return (choix == 2); // Retourne vrai si le choix est Moyen, sinon Facile
}


int main() {
    srand(time(NULL));

    char** tab;
    int taille = 15;
    int nbPion = 5;

    init_morpion(tab, taille);

    bool alignement = false;
    bool joueur = false;

    int nbPl = 0;

    // Choix du mode de jeu
    bool mode = choixDiff();

    while (!alignement && nbPl < taille * taille) {
        affichage_morpion(tab, taille);

        char pion;
        (joueur ? pion = 'X' : pion = 'O');

        int x = -1;
        int y = -1;

        do {
            if (pion == 'O') {
                if (mode) {
                    jouerRond(tab, taille, x, y);
                }
            } else {
                jouerCroix(tab, taille, x, y); 
            }

            std::cout<<std::endl;

        } while (!estLibre_morpion(tab, taille, x, y));

        placer_morpion(tab, taille, x, y, pion);
        affichage_morpion(tab, taille);

        if (pion == 'O') alignement = victoire_morpion(tab, taille, nbPion, 'O');

        joueur = !joueur;
        nbPl++;
    }

    delete_morpion(tab, taille);
    return 0;
}