#include <iostream>
#include <cstddef>

struct Noeud {
    int valeur;
    Noeud* suivant;

    Noeud(int val) : valeur(val), suivant(nullptr) {}
};

class ListeChainee {
private:
    Noeud* tete;
    int nbElements;

public:
    ListeChainee() : tete(nullptr), nbElements(0) {}

    ~ListeChainee() {
        Noeud* courant = tete;
        while (courant != nullptr) {
            Noeud* suivant = courant->suivant;
            delete courant;
            courant = suivant;
        }
        tete = nullptr;
        nbElements = 0;
    }

    void ajouterDebut(int valeur) {
        Noeud* nouveau = new Noeud(valeur);
        nouveau->suivant = tete;
        tete = nouveau;
        nbElements++;
    }

    void ajouterFin(int valeur) {
        Noeud* nouveau = new Noeud(valeur);
        if (tete == nullptr) {
            tete = nouveau;
        } else {
            Noeud* courant = tete;
            while (courant->suivant != nullptr) {
                courant = courant->suivant;
            }
            courant->suivant = nouveau;
        }
        nbElements++;
    }

    bool supprimer(int valeur) {
        if (tete == nullptr) return false;

        if (tete->valeur == valeur) {
            Noeud* aSupprimer = tete;
            tete = tete->suivant;
            delete aSupprimer;
            nbElements--;
            return true;
        }

        Noeud* courant = tete;
        while (courant->suivant != nullptr && courant->suivant->valeur != valeur) {
            courant = courant->suivant;
        }

        if (courant->suivant != nullptr) {
            Noeud* aSupprimer = courant->suivant;
            courant->suivant = courant->suivant->suivant;
            delete aSupprimer;
            nbElements--;
            return true;
        }

        return false;
    }

    void afficher() const {
        Noeud* courant = tete;
        std::cout << "[ ";
        while (courant != nullptr) {
            std::cout << courant->valeur << " ";
            courant = courant->suivant;
        }
        std::cout << "]" << std::endl;
    }

    int taille() const {
        return nbElements;
    }

    class Iterator {
    private:
        Noeud* courant;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type        = int;
        using difference_type   = std::ptrdiff_t;
        using pointer           = int*;
        using reference         = int&;

        explicit Iterator(Noeud* ptr) : courant(ptr) {}

        reference operator*() const {
            return courant->valeur;
        }

        Iterator& operator++() {
            if (courant != nullptr) {
                courant = courant->suivant;
            }
            return *this;
        }

        bool operator==(const Iterator& autre) const {
            return courant == autre.courant;
        }

        bool operator!=(const Iterator& autre) const {
            return courant != autre.courant;
        }
    };

    Iterator begin() const { return Iterator(tete); }
    Iterator end() const { return Iterator(nullptr); }
};

int main() {
    ListeChainee liste;

    liste.ajouterDebut(10);
    liste.ajouterDebut(5);
    liste.ajouterFin(20);
    liste.ajouterFin(30);

    std::cout << "Liste après insertions : ";
    liste.afficher();
    std::cout << "Taille de la liste : " << liste.taille() << std::endl;

    std::cout << "\nSuppression de la valeur 10..." << std::endl;
    liste.supprimer(10);
    liste.afficher();
    std::cout << "Taille actuelle : " << liste.taille() << std::endl;

    std::cout << "\nParcours avec l'itérateur personnalisé (for-range loop) : ";
    for (int val : liste) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}
