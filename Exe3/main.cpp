#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <utility>
#include <stdexcept>

using Element = std::pair<int, std::string>;

class TableHachage {
private:
    std::vector<std::list<Element>> table;
    size_t capacite;
    size_t nbElements;

    const double FACTEUR_CHARGE_MAX = 0.75;

    size_t fonctionHachage(int cle) const {
        return std::abs(cle) % capacite;
    }

    void redimensionner(size_t nouvelleCapacite) {
        std::cout << "\n[Redimensionnement] Passage de la taille " << capacite
                  << " à " << nouvelleCapacite << "..." << std::endl;

        std::vector<std::list<Element>> ancienneTable = table;

        capacite = nouvelleCapacite;
        table.clear();
        table.resize(capacite);
        nbElements = 0;

        for (const auto& alveole : ancienneTable) {
            for (const auto& elem : alveole) {
                insererSansRedimensionner(elem.first, elem.second);
            }
        }
    }

    void insererSansRedimensionner(int cle, const std::string& valeur) {
        size_t index = fonctionHachage(cle);

        for (auto& elem : table[index]) {
            if (elem.first == cle) {
                elem.second = valeur;
                return;
            }
        }

        table[index].push_back({cle, valeur});
        nbElements++;
    }

public:
    explicit TableHachage(size_t capaciteInitiale = 7)
        : capacite(capaciteInitiale), nbElements(0) {
        table.resize(capacite);
    }

    void inserer(int cle, const std::string& valeur) {
        insererSansRedimensionner(cle, valeur);

        if (static_cast<double>(nbElements) / capacite > FACTEUR_CHARGE_MAX) {
            redimensionner(capacite * 2);
        }
    }

    std::string rechercher(int cle) const {
        size_t index = fonctionHachage(cle);

        for (const auto& elem : table[index]) {
            if (elem.first == cle) {
                return elem.second;
            }
        }

        throw std::runtime_error("Erreur : Clé non trouvée (" + std::to_string(cle) + ").");
    }

    bool supprimer(int cle) {
        size_t index = fonctionHachage(cle);
        auto& alveole = table[index];

        for (auto it = alveole.begin(); it != alveole.end(); ++it) {
            if (it->first == cle) {
                alveole.erase(it);
                nbElements--;
                std::cout << "-> Clé " << cle << " supprimée." << std::endl;
                return true;
            }
        }

        std::cout << "-> Échec de suppression : Clé " << cle << " non trouvée." << std::endl;
        return false;
    }

    void afficher() const {
        std::cout << "\n  TABLE DE HACHAGE (Taille : " << capacite
                  << ", Éléments : " << nbElements << ") " << std::endl;
        for (size_t i = 0; i < capacite; ++i) {
            std::cout << "Index [" << i << "] : ";
            if (table[i].empty()) {
                std::cout << "Vide";
            } else {
                for (auto it = table[i].begin(); it != table[i].end(); ++it) {
                    std::cout << "(" << it->first << " => \"" << it->second << "\")";
                    auto suiv = it;
                    if (++suiv != table[i].end()) std::cout << " -> ";
                }
            }
            std::cout << std::endl;
        }
    }

    size_t getTaille() const { return capacite; }
    size_t getNbElements() const { return nbElements; }
};

int main() {
    TableHachage ht(5);

    std::cout << "--- 1. Insertions initiales ---" << std::endl;
    ht.inserer(10, "Aya");
    ht.inserer(15, "Badr");
    ht.inserer(7, "Chaimae");
    ht.inserer(22, "Malak");

    ht.afficher();

    std::cout << "--- 2. Recherche ---" << std::endl;
    try {
        std::cout << "Valeur pour la clé 15 : " << ht.rechercher(15) << std::endl;
        std::cout << "Valeur pour la clé 7  : " << ht.rechercher(7) << std::endl;
        std::cout << "Valeur pour la clé 99 : " << ht.rechercher(99) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "[Exception] " << e.what() << std::endl;
    }

    std::cout << "\n--- 3. Suppression ---" << std::endl;
    ht.supprimer(10);
    ht.afficher();

    std::cout << "--- 4. Test du redimensionnement automatique ---" << std::endl;
    std::cout << "Ajout de nouveaux éléments pour dépasser le facteur de charge (0.75)..." << std::endl;
    ht.inserer(3, "Ève");
    ht.inserer(8, "Frank");
    ht.inserer(19, "Grace");

    ht.afficher();

    return 0;
}
