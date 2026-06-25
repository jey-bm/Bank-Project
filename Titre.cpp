#include "Titre.hpp"
using namespace std;

// constructeur
int Titre::m_cptid = 1;
vector<int> Titre::m_recupId;
Titre::Titre() : m_nom("jondoe"), m_id(0) {
  if (m_recupId.empty()) {
    m_id = m_cptid;
    m_cptid++;
  } else {
    m_id = m_recupId.back();
    m_recupId.pop_back();
  }
}
Titre::Titre(string nom) : m_nom(nom), m_id(0) {
  if (m_recupId.empty()) {
    m_id = m_cptid;
    m_cptid++;
  } else {
    m_id = m_recupId.back();
    m_recupId.pop_back();
  }
}
Titre::Titre(Titre const &copy) : m_nom(copy.m_nom), m_id(0) {
  if (m_recupId.empty()) {
    m_id = m_cptid;
    m_cptid++;
  } else {
    m_id = m_recupId.back();
    m_recupId.pop_back();
  }
}
Titre::~Titre() { m_recupId.push_back(this->m_id); }
ostream &operator<<(ostream &flux, Titre const &e1) {
  e1.afficher(flux);
  return flux;
}
////////////////////////////////Classe_Action////////////////////////////////////
// constructeur
Action::Action() : Titre(), m_prix(0), m_dividende(0), m_qtite(0) {}
Action::Action(string nom, double prix, int qte)
    : Titre(nom), m_dividende(0), m_qtite(qte), m_prix(prix) {}
Action::~Action() {}
// copy
Action::Action(Action const &copy)
    : Titre(copy), m_dividende(copy.m_dividende), m_prix(copy.m_prix),
      m_qtite(copy.m_qtite) {}
// Opérations observatrices
void Action::afficher(ostream &flux) const {
  flux << "Action du groupe : " << m_nom << " , quantité : " << m_qtite
       << " , prix unitaire : " << m_prix << endl;
}
// Opérations modificatrices
void Action::modifPrix(double newPrix) { m_prix = newPrix; }
void Action::modifierQte(short int newQte) { m_qtite = newQte; }
Titre *Action::clone() const { return new Action(*this); }
void Action::investir(double montant) {
  m_qtite += montant / m_prix;
} // Calcul la nouvelle quantité d'action
double Action::getValue() const { return m_prix * m_qtite; }
void Action::modifDividende(double div) { m_dividende = div; }

////////////////////////////////Classe_Obligation////////////////////////////////////

// constructeur
Obligation::Obligation()
    : Titre(), m_montant(0), m_taux(0), m_dureeMaturite(0) {}
Obligation::Obligation(string nom, double montant, double taux, int duree)
    : Titre(nom), m_montant(montant), m_taux(taux), m_dureeMaturite(duree) {}
Obligation::~Obligation() {}
// copy
Obligation::Obligation(Obligation const &copy)
    : Titre(copy), m_montant(copy.m_montant), m_taux(copy.m_taux),
      m_dureeMaturite(copy.m_dureeMaturite) {}
// Opérations observatrices
void Obligation::afficher(ostream &flux) const {
  flux << "Obligation du groupe : " << m_nom
       << " , maturité : " << m_dureeMaturite
       << " , montant investi : " << m_montant
       << " , taux de rendement : " << m_taux << endl;
}
// Opérations modificatrices
Titre *Obligation::clone() const { return new Obligation(*this); }
void Obligation::investir(double montant) { m_montant += montant; }
double Obligation::getValue() const { return m_montant; }
