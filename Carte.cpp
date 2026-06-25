#include "Carte.hpp"
#include "Compte.hpp"
#include <cstdlib>
#include <ctime>
using namespace std;
int Carte::m_cpt = 1;
vector<int> Carte::m_listeId;
Carte::Carte(string nomPrenom, CompteCourant *c)
    : m_nomPrenom(nomPrenom), m_plafond(1000), m_numCarte(0), m_compte(c),
      m_codeSecret(rand() % 9999), m_cvv(rand() % 999), m_etat(true) {

  time_t t = time(nullptr);
  // A partir d'ici
  tm *now = localtime(&t);
  now->tm_year += 3; // La carte expire dans 3 ans

  char dateStr[11];
  strftime(dateStr, sizeof(dateStr), "%d/%m/%Y", now);
  m_dateExpiration = dateStr;
  // À ici fait Par l'IA

  if (m_listeId.empty()) {
    m_numCarte = m_cpt;
    ++m_cpt;
  } else {
    m_numCarte = m_listeId.back();
    m_listeId.pop_back();
  }
}
Carte::Carte(Carte const &copy)
    : m_numCarte(0), m_codeSecret(copy.m_codeSecret),
      m_nomPrenom(copy.m_nomPrenom), m_compte(copy.m_compte), m_cvv(copy.m_cvv),
      m_etat(copy.m_etat), m_plafond(copy.m_plafond),
      m_dateExpiration(copy.m_dateExpiration) {
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
void Carte::payer(double montant) {
  if (m_etat == true) {
    m_compte->debiter(montant);
  }
}
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