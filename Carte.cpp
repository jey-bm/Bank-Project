#include "Carte.hpp"
#include "Compte.hpp"
#include <cstdlib>
using namespace std;
int Carte::m_cpt = 1;
vector<int> Carte::m_listeId;
Carte::Carte(string nomPrenom, CompteCourant *c)
    : m_nomPrenom(nomPrenom), m_plafond(1000), m_numCarte(0), m_compte(c),
      m_dateExpiration("02/06/2026"), m_codeSecret(rand() % 9999),
      m_cvv(rand() % 999), m_etat(true) {
  if (m_listeId.empty()) {
    m_numCarte = m_cpt;
    ++m_cpt;
  } else {
    m_numCarte = m_listeId.back();
    m_listeId.pop_back();
  }
}
Carte::~Carte() {
  m_listeId.push_back(this->m_numCarte);
  m_compte = nullptr;
}
void Carte::payer(double montant) { m_compte->debiter(montant); }
void Carte::bloquer() {
  if (m_etat != false) {
    m_etat = false;
  }
}
void Carte::activer() {
  if (m_etat != true) {
    m_etat = true;
  }
}
void Carte::gererPlafond(double newP) {
  if (newP < 10000) {
    m_plafond = newP;
  } else {
    m_plafond = 10000;
  }
}