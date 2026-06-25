#include "Entite.hpp"
#include "Carte.hpp"
#include "Compte.hpp"
#include "Portefeuille.hpp"
#include "Titre.hpp"
#include <cstddef>
using namespace std;

Entite::Entite() {}
Entite::Entite(string email, string numTel, string nom, string prenom,
               string dateNaiss)
    : m_id(0), m_email(email), m_numTel(numTel), m_nom(nom), m_prenom(prenom),
      m_dateNaiss(dateNaiss), m_nbCompte(0) {}

Entite::Entite(Entite const & e): m_id(0), m_email(e.m_email), m_numTel(e.m_numTel), m_nom(e.m_nom), m_prenom(e.m_prenom),
      m_dateNaiss(e.m_dateNaiss), m_nbCompte(e.m_nbCompte){
//On copy les comptes
for (Compte *cp : e.m_comptes){
m_comptes.push_back(cp->clone());
}
}
Entite::~Entite() {
  // on suprime le vecteur de compte
  for (Compte *compte : m_comptes) {
    delete compte;
  }
  m_comptes.clear();
}

void Entite::modifNum(string newNum) { m_numTel = newNum; }
void Entite::modifEmail(string newEmail) { m_email = newEmail; }
void Entite::recevoir(CompteCourant const &c1, double montant) {
  // on cherche dans ses comptes le compte à créditer
  for (unsigned int i(0); i < m_comptes.size(); ++i) {
    if (m_comptes[i] == &c1) {
      m_comptes[i]->crediter(montant);
      break;
    }
  }
}
void Entite::afficheCompte(Compte const &c1) const {
  // On cherche le compte à afficher

  for (int i(0); i < m_comptes.size(); ++i) {
    if (m_comptes[i] == &c1) {
      cout << *m_comptes[i];
      break;
    }
  }
}
int Entite::getId() const { return m_id; }
string Entite::getNom() const { return m_nom; }
string Entite::getPrenom() const { return m_prenom; }

ostream &operator<<(ostream &flux, Entite const &e1){
  e1.afficher(flux);
  return flux;
}

/////////////////////////////Classe_Client/////////////////////////////////////
int Client::m_cptClient = 1;
vector<int> Client::m_listeIdC;
Client::Client() {}
Client::Client(string email, string numTel, string nom, string prenom,
               string dateNaiss)
    : Entite(email, numTel, nom, prenom, dateNaiss), m_cto(new Portefeuille()) {
  // cas si la liste d'id réutilisable est vide
  if (m_listeIdC.empty()) {
    m_id = m_cptClient;
    ++m_cptClient;
  } else {
    // si elle ne l'est pas
    m_id = m_listeIdC.back(); // Je prend le dernier élement
    m_listeIdC.pop_back();    // puis je le retir de la liste
  }
}
Client::Client(Client const & c):Entite(c),m_cto(new Portefeuille(*c.m_cto)){
// On copy les cartes
for(Carte *ct: c.m_cartes){

  m_cartes.push_back(new Carte(*ct));
}
// On copy les prêts
for(Pret *pt: c.m_prets){
  m_prets.push_back(new Pret(*pt));
}
}
Client::~Client() {
  m_listeIdC.push_back(this->m_id);
  delete m_cto;
  m_cto = nullptr;
  // on suprime le vecteur de cartes
  for (int i(0); i < m_cartes.size(); ++i) {
    delete m_cartes[i];
    m_cartes[i] = 0;
  }
  // on suprime le vecteur de prêt
  for (int i(0); i < m_prets.size(); ++i) {
    delete m_prets[i];
    m_prets[i] = 0;
  }
}
void Client::afficher(ostream &flux) const {
  flux << "le compte : " << m_id << ", nom : " << m_nom
       << ", prenom : " << m_prenom << ", téléphone : " << m_numTel
       << ", date de naissance : " << m_dateNaiss
       << ", nombre de compte : " << m_nbCompte << endl;
}
void Client::suppCompte() {
  for (Compte *compte : m_comptes) {
    delete compte;
  }
  m_comptes.clear();
}

void Client::suppCompte(Compte const &c) {
  // On parcours le vecteur de compte et on supprime celui qui nous intéresse
  for (auto it = m_comptes.begin(); it != m_comptes.end(); ++it) {
    if (*it == &c) {
      delete *it;
      m_comptes.erase(it);
      break;
    }
  }
}
void Client::demanderCarte(CompteCourant *c) {
  // Je crée une instance de carte
  Carte *c1 = new Carte(m_nom + " " + m_prenom, c);
  // je l’insère dans ma liste de carte
  m_cartes.push_back(c1);
}
void Client::ajouterCompte(Compte *c) {
  if (c != nullptr) {
    m_comptes.push_back(c);
  }
  m_nbCompte++;
}

void Client::envoyer(double montant, Compte &c) { c.crediter(montant); }
void Client::retirerArgent(Carte &c1, double montant) { c1.payer(montant); }
void Client::acheterTitre(double montant, const Titre &titre) {
  // je créer le titre adapté
  Titre *t = titre.clone();
  // j'ajuste le montant investi
  t->investir(montant);
  // je l'ajoute dans mon portefeuille
  m_cto->ajouter(t);
}
void Client::vendreTitre(const Titre &titre, CompteCourant const &c) {
  // Je vais chercher le titre que je veux vendre
  Titre *t = m_cto->rechercher(titre);
  // On récupère la valeur de ce titre à l'instant T
  double value = t->getValue();
  // je crédite mon compte
  this->recevoir(c, value);
}
int Client::cptPret = 1;
void Client::contracterPret(double montant, double taux,
                            CompteCourant const &c) {
  // je créer le pret
  Pret *p = new Pret();
  p->montant = montant;
  p->taux = taux;
  p->id = cptPret;
  ++cptPret;
  // je crédite mon compte du montant du prêt
  this->recevoir(c, montant);
  // je l'ajoute dans la liste de pret
  m_prets.push_back(p);
}
void Client::rembourserPret(const Pret &p, CompteCourant &c) {
  // On cherche le prêt à rembourser
  for (int i(0); i < m_prets.size(); ++i) {
    if (m_prets[i] == &p) {
      // Je débite le montant à pyer
      c.debiter(m_prets[i]->montant * m_prets[i]->taux);
      break;
    }
  }
}

/////////////////////////////Classe_Employer/////////////////////////////////////
int Employe::m_cptEmployer = 1;
vector<int> Employe::m_listeIdE;
Employe::Employe() {}
Employe::Employe(Employe const & copy):Entite(copy),m_salaire(copy.m_salaire),m_poste(copy.m_poste){

}
Employe::Employe(string email, string numTel, string nom, string prenom,
                 string dateNaiss, string poste, double salaire)
    : Entite(email, numTel, nom, prenom, dateNaiss), m_salaire(salaire),
      m_poste(poste) {
  if (m_listeIdE.empty()) {
    m_id = m_cptEmployer;
    ++m_cptEmployer;
  } else {
    m_id = m_listeIdE.back();
    m_listeIdE.pop_back();
  }
}
Employe::~Employe() { m_listeIdE.push_back(this->m_id); }
void Employe::afficher(ostream &flux) const {
  flux << "Nom : " << m_nom << " ,prenom : " << m_prenom << " Id : " << m_id
       << " ,poste : " << m_poste << " , salaire : " << m_salaire << endl;
}
void Employe::gestionSalaire(double montant) { m_salaire = montant; }