#include <iostream>
#include <string>
#include <exception>

class FileVideException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Erreur : Impossible de défiler, la file est vide !";
    }
};

struct Maillon {
    int valeur;
    Maillon* suivant;

    Maillon(int val) : valeur(val), suivant(nullptr) {}
};

class File {
private:
    Maillon* tete;
    Maillon* queue;
    int nbElements;

public:
    File() : tete(nullptr), queue(nullptr), nbElements(0) {}

    ~File() {
        while (!estVide()) {
            try {
                defiler();
            } catch (...) {
            }
        }
    }

    bool estVide() const {
        return tete == nullptr;
    }

    bool estPleine() const {
        return false;
    }

    void enfiler(int valeur) {
        Maillon* nouveau = new Maillon(valeur);
        if (estVide()) {
            tete = queue = nouveau;
        } else {
            queue->suivant = nouveau;
            queue = nouveau;
        }
        nbElements++;
        std::cout << "-> Éléments enfilé : " << valeur << std::endl;
    }

    int defiler() {
        if (estVide()) {
            throw FileVideException();
        }

        Maillon* temp = tete;
        int valeurRetiree = temp->valeur;
        tete = tete->suivant;

        if (tete == nullptr) {
            queue = nullptr;
        }

        delete temp;
        nbElements--;
        return valeurRetiree;
    }

    void afficher() const {
        if (estVide()) {
            std::cout << "File actuelle : [ Vide ]" << std::endl;
            return;
        }

        std::cout << "File (Tête -> Queue) : [ ";
        Maillon* courant = tete;
        while (courant != nullptr) {
            std::cout << courant->valeur << " ";
            courant = courant->suivant;
        }
        std::cout << "]" << std::endl;
    }

    int taille() const {
        return nbElements;
    }
};

void afficherMenu() {
    std::cout << "     GESTION DE LA FILE (FIFO)  " << std::endl;
    std::cout << "1. Enfiler un élément" << std::endl;
    std::cout << "2. Défiler un élément" << std::endl;
    std::cout << "3. Afficher la file" << std::endl;
    std::cout << "4. Vérifier si la file est vide" << std::endl;
    std::cout << "5. Quitter" << std::endl;
    std::cout << "Choix : ";
}

int main() {
    File file;
    int choix = 0;

    do {
        afficherMenu();
        std::cin >> choix;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Saisie invalide. Veuillez entrer un nombre entre 1 et 5." << std::endl;
            continue;
        }

        switch (choix) {
            case 1: {
                int val;
                std::cout << "Entrer une valeur entière à enfiler : ";
                std::cin >> val;
                file.enfiler(val);
                break;
            }
            case 2: {
                try {
                    int val = file.defiler();
                    std::cout << "<- Élément défilé : " << val << std::endl;
                } catch (const FileVideException& e) {
                    std::cout << "[ATTENTION] " << e.what() << std::endl;
                }
                break;
            }
            case 3:
                file.afficher();
                break;

            case 4:
                if (file.estVide()) {
                    std::cout << "La file est actuellement VIDE." << std::endl;
                } else {
                    std::cout << "La file contient " << file.taille() << " élément(s)." << std::endl;
                }
                break;

            case 5:
                std::cout << "Fermeture du programme." << std::endl;
                break;

            default:
                std::cout << "Choix invalide !" << std::endl;
                break;
        }

    } while (choix != 5);

    return 0;
}
