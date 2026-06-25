#include "Compte.hpp"
#include "Carte.hpp"
#include <ctime>
#include <string>
using namespace std;
int Compte::m_cptId = 1;
vector<int> Compte::m_listId;

Compte::Compte() : m_idCompte(0), m_taux(0.01), m_solde(0) {
  if (m_listId.empty()) {
    m_idCompte = m_cptId;
    ++m_cptId;
  } else {
    m_idCompte = m_listId.back();
    m_listId.pop_back();
  }
}
Compte::~Compte() { m_listId.push_back(this->m_idCompte); }
Compte::Compte(Compte const &copy)
    : m_idCompte(0), m_taux(copy.m_taux), m_solde(copy.m_solde),
      m_registre(copy.m_registre) {
  if (m_listId.empty()) {
    m_idCompte = m_cptId;
    ++m_cptId;
  } else {
    m_idCompte = m_listId.back();
    m_listId.pop_back();
  }
}

void Compte::debiter(double montant) {
  Registre r;
  m_solde -= montant;
  // 1. Get the current calendar time (fait par l'IA)
  time_t t = time(nullptr);
  tm *now = localtime(&t);

  // 2. Format the date into a DD/MM/YYYY string (fait par l'IA)
  char dateStr[11];
  strftime(dateStr, sizeof(dateStr), "%d/%m/%Y", now);
  r.m_date = dateStr;
  r.m_montant = -montant;
  m_registre.push_back(r);
}
void Compte::afficherFlux() const {
  // on va parcourir et afficher registre
  for (unsigned int i(0); i < m_registre.size(); ++i) {
    cout << m_registre[i];
  }
}

void Compte::crediter(double montant) {

  Registre r;
  m_solde += montant;

  // fait par L'IA
  time_t t = time(nullptr);
  tm *now = localtime(&t);
  char dateStr[11];
  strftime(dateStr, sizeof(dateStr), "%d/%m/%Y", now);

  r.m_date = dateStr;
  r.m_montant = montant;
  m_registre.push_back(r);
}
void Compte::modifierSolde(double new_solde) { m_solde = new_solde; }
string Compte::getId() const { return to_string(m_idCompte); }
double Compte::getSolde() const { return m_solde; }

ostream &operator<<(ostream &flux, Compte const &compte) {
  compte.afficher(flux);
  return flux;
}

/////////////////////////////Classe_Registre/////////////////////////////////////

void Registre::afficherf(std::ostream &flux) const {
  flux << m_date << " " << m_montant << endl;
}
ostream &operator<<(ostream &flux, Registre const &r) {
  r.afficherf(flux);
  return flux;
}
/////////////////////////////Classe_CompteEpargne/////////////////////////////////////

// constructeur
CompteEpargne::CompteEpargne() : Compte(), m_limites(50000) { m_taux = 0.1; }
CompteEpargne::~CompteEpargne() {}
// copy
CompteEpargne::CompteEpargne(CompteEpargne const &copy)
    : Compte(copy), m_limites(copy.m_limites) {}
// Opérations observatrices

// Opérations modificatrices
void CompteEpargne::afficher(std::ostream &flux) const {
  flux << "Compte d'épargne, Taux : " << m_taux << " , solde : " << m_solde
       << endl;
}

/////////////////////////////Classe_CompteCourant/////////////////////////////////////

// constructeur
CompteCourant::CompteCourant()
    : Compte(), m_decouvert(0), m_plafond(0), m_nbCarte(5) {}
CompteCourant::~CompteCourant() {
  for (Carte *carte : m_cartes) {
    delete carte;
  }
  m_cartes.clear();
}
// copy
CompteCourant::CompteCourant(CompteCourant const &copy)
    : Compte(copy), m_decouvert(copy.m_decouvert), m_plafond(copy.m_plafond),
      m_nbCarte(copy.m_nbCarte) {}
// Opérations observatrices
void CompteCourant::afficherPlafond() const {
  cout << m_plafond << endl;
} // On affiche le plafond

// Opérations modificatrices
void CompteCourant::ajouterCarte(Carte *new_carte) {
  m_cartes.push_back(new_carte);
} // ajout de carte
void CompteCourant::retirerCarte(Carte const &carte) {
  for (auto it = m_cartes.begin(); it != m_cartes.end(); ++it) {
    if (*it == &carte) {
      delete *it;
      m_cartes.erase(it);
      break;
    }
  }
} // supprimer une carte
void CompteCourant::modifierPlafond(double new_plafond) {
  m_plafond = new_plafond;
} // modifier modifier plafond
void CompteCourant::modifierNbC(int new_nbC) {
  m_nbCarte = new_nbC;
} // modifier nombre de carte limite
void CompteCourant::modifierDecouvert(double newD) { m_decouvert = newD; }
void CompteCourant::afficher(ostream &flux) const {
  flux << "Compte Courant, Taux : " << m_taux << " , solde : " << m_solde
       << ", découvert autorisé : " << m_decouvert
       << " , plafond d’envoi : " << m_plafond
       << " , limite de carte : " << m_nbCarte << endl;
}
