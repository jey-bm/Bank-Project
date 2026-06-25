#ifndef DEF_PORTEFEUILLE
#define DEF_PORTEFEUILLE
#include "Titre.hpp"
#include <ostream>

class Portefeuille {
public:
  // constructeur
  Portefeuille();
  Portefeuille(Portefeuille const &copy);
  ~Portefeuille();
  // Opérations observatrices
  Titre *rechercher(Titre const &titre); // Recherche un titre et le renvoie
  // Opérations modificatrices
  void ajouter(Titre *titre);
  void retirer(Titre *titre);

private:
  void
  afficher(std::ostream &flux) const; // affiche les éléments du portefeuille
  std::vector<Titre *> m_titres;
  friend std::ostream &operator<<(std::ostream &flux, Portefeuille const &p1);
};

#endif