#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using std::string;

void JeuContreOrdinateur() {
    std::string joueur, ordinateur;
    int scoreJoueur = 0;
    int scoreOrdinateur = 0;
    int Essai, limite = 0;
    
    std::cout << "Combien de parties voulez-vous jouer ? : ";
    std::cin >> Essai;

    while (limite < Essai) {
        std::cout << "Choisissez Pierre, Papier ou Ciseaux (ou 'quitter' pour sortir) : ";
        std::cin >> joueur;

        if (joueur == "quitter") {
            break;
        }

        int randomNum = rand() % 3;

        if (randomNum == 0) {
            ordinateur = "pierre";
            limite++;
        } else if (randomNum == 1) {
            ordinateur = "papier";
            limite++;
        } else {
            ordinateur = "ciseaux";
            limite++;
        }

        std::cout << "L'ordinateur choisit : " << ordinateur << std::endl;

        if (joueur == ordinateur) {
            std::cout << "Match nul.\n";
        } 
        else if ((joueur == "pierre" && ordinateur == "ciseaux") ||
                   (joueur == "papier" && ordinateur == "pierre") ||
                   (joueur == "ciseaux" && ordinateur == "papier")) {
            std::cout << "Vous avez gagné !\n";
            scoreJoueur++;
        } else {
            std::cout << "Vous avez perdu.\n";
            scoreOrdinateur++;
        }

        std::cout << "Score - Vous : " << scoreJoueur << ", Ordinateur : " << scoreOrdinateur << "\n";
    }

    std::cout << "Merci d'avoir joué ! Votre score final : Vous " << scoreJoueur << " - " << scoreOrdinateur << " Ordinateur\n";
}
void JeuJoueurVsJoueur() {
    std::string joueur1, joueur2;
    int scoreJoueur1 = 0;
    int scoreJoueur2 = 0;
    int Essai, limite = 0;
    
    std::cout << "Combien de parties voulez-vous jouer ? : ";
    std::cin >> Essai;

    while (limite < Essai) {
        std::cout << "Joueur 1, choisissez Pierre, Papier ou Ciseaux (ou 'quitter' pour sortir) : ";
        std::cin >> joueur1;

        if (joueur1 == "quitter") {
            break;
        }

        std::cout << "Joueur 2, choisissez Pierre, Papier ou Ciseaux (ou 'quitter' pour sortir) : ";
        std::cin >> joueur2;

        if (joueur2 == "quitter") {
            break;
        }

        std::cout << "Joueur 1 a choisi : " << joueur1 << std::endl;
        std::cout << "Joueur 2 a choisi : " << joueur2 << std::endl;

        if (joueur1 == joueur2) {
            std::cout << "Match nul.\n";
        } 
        else if((joueur1 == "pierre" && joueur2 == "ciseaux") ||
                   (joueur1 == "papier" && joueur2 == "pierre") ||
                   (joueur1 == "ciseaux" && joueur2== "papier")) {
            std::cout << "Joueur 1 a gagné !\n";
            scoreJoueur1++;
        } else {
            std::cout << "Joueur 2 a gagné !\n";
            scoreJoueur2++;
        }

        std::cout << "Score - Joueur 1 : " << scoreJoueur1 << ", Joueur 2 : " << scoreJoueur2 << "\n";
        limite++; 
    }

    std::cout << "Merci d'avoir joué ! Score final : Joueur 1 " << scoreJoueur1 << " - " << scoreJoueur2 << " Joueur 2\n";
}


int main() {
    std::cout << "Bienvenue dans ce jeu\n";

    // Demander au joueur s'il veut jouer contre l'ordinateur ou contre un autre joueur
    std::cout << "Choisissez un mode de jeu : " << std::endl;
    std::cout << "1- Joueur contre Ordinateur" << std::endl;
    std::cout << "2- Joueur contre Joueur" << std::endl;

    int mode;
    std::cin >> mode;

    if (mode == 1) {
        JeuContreOrdinateur();
    } else if (mode == 2) {
        JeuJoueurVsJoueur();
    } else {
        std::cout << "Sortie du jeu." << std::endl;
    }

    return 0;
}
