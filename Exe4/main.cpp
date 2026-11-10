#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

template <typename T>
class Pile {
private:
    std::vector<T> elements;

public:
    Pile() = default;

    void empiler(const T& element) {
        elements.push_back(element);
    }

    T depiler() {
        if (estVide()) {
            throw std::underflow_error("Erreur : Impossible de dépiler, la pile est vide !");
        }
        T valeurSommet = elements.back();
        elements.pop_back();
        return valeurSommet;
    }

    T sommet() const {
        if (estVide()) {
            throw std::underflow_error("Erreur : La pile est vide, aucun sommet à consulter !");
        }
        return elements.back();
    }

    bool estVide() const {
        return elements.empty();
    }

    size_t taille() const {
        return elements.size();
    }

    void inverser() {
        std::reverse(elements.begin(), elements.end());
    }

    void afficher() const {
        if (estVide()) {
            std::cout << "[ Pile vide ]" << std::endl;
            return;
        }

        std::cout << "Sommet -> [ ";
        for (auto it = elements.rbegin(); it != elements.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "]" << std::endl;
    }
};

int main() {

    std::cout << "=== 1. Test avec une Pile d'entiers (int) ===" << std::endl;
    Pile<int> pileInt;

    pileInt.empiler(10);
    pileInt.empiler(20);
    pileInt.empiler(30);

    std::cout << "État de la pile : ";
    pileInt.afficher();

    std::cout << "Élément au sommet : " << pileInt.sommet() << std::endl;
    std::cout << "Élément dépilé : " << pileInt.depiler() << std::endl;

    std::cout << "Après dépilement : ";
    pileInt.afficher();

    std::cout << "\nInversion de la pile d'entiers..." << std::endl;
    pileInt.inverser();
    std::cout << "Après inversion : ";
    pileInt.afficher();


    std::cout << "\n=== 2. Test avec une Pile de std::string ===" << std::endl;
    Pile<std::string> pileString;

    pileString.empiler("Premier");
    pileString.empiler("Second");
    pileString.empiler("Troisième");

    std::cout << "État de la pile : ";
    pileString.afficher();

    std::cout << "Dépilement : " << pileString.depiler() << std::endl;
    std::cout << "Nouveau sommet : " << pileString.sommet() << std::endl;


    std::cout << "\n=== 3. Test avec une Pile de double ===" << std::endl;
    Pile<double> pileDouble;

    pileDouble.empiler(1.5);
    pileDouble.empiler(3.14);
    pileDouble.empiler(9.81);

    std::cout << "État de la pile : ";
    pileDouble.afficher();


    std::cout << "\n=== 4. Test de la gestion des exceptions ===" << std::endl;
    Pile<int> pileVide;

    try {
        std::cout << "Tentative de lecture du sommet sur une pile vide..." << std::endl;
        pileVide.sommet();
    } catch (const std::underflow_error& e) {
        std::cout << "[Attrapé] " << e.what() << std::endl;
    }

    try {
        std::cout << "Tentative de dépilement sur une pile vide..." << std::endl;
        pileVide.depiler();
    } catch (const std::underflow_error& e) {
        std::cout << "[Attrapé] " << e.what() << std::endl;
    }

    return 0;
}
