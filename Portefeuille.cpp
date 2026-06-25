#include "Portefeuille.hpp"
#include "Titre.hpp"
using namespace std;

// constructeur
Portefeuille::Portefeuille() {}
Portefeuille::Portefeuille(Portefeuille const &copy) {
  for (Titre *t : copy.m_titres) {

    m_titres.push_back(t->clone());
  }
}
Portefeuille::~Portefeuille() {
  for (Titre *t : m_titres) {
    delete t;
  }
  m_titres.clear();
}
// Opérations observatrices
Titre *Portefeuille::rechercher(Titre const &titre) {
  // je parcour mon cto
  for (Titre *t : m_titres) {
    if (t == &titre) {
      return t;
    }
  }
  return nullptr;
} // Recherche un titre et le renvoie
// Opérations modificatrices
void Portefeuille::ajouter(Titre *titre) { m_titres.push_back(titre); }
void Portefeuille::retirer(Titre *titre) {
  for (auto it = m_titres.begin(); it != m_titres.end(); ++it) {
    if (*it == titre) {
      delete *it;
      m_titres.erase(it);
      break;
    }
  }
}
void Portefeuille::afficher(ostream &flux) const {
  for (Titre *t : m_titres) {
    flux << *t << endl;
  }
} // affiche les éléments du portefeuille
ostream &operator<<(ostream &flux, Portefeuille const &p1) {
  p1.afficher(flux);
  return flux;
}