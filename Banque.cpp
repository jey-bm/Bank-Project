#include "Banque.hpp"
#include "Entite.hpp"
using namespace std;
Banque::Banque() : m_nom("BRED") {}
Banque::~Banque() {
  // on parcour chaque element de la liste de clients
  for (int i = 0; i < m_clients.size(); ++i) {
    delete m_clients[i]; // On supprime le poiteur de cette instance
    m_clients[i] = 0;    // On le met à 0 pour éviter des erreurs
  }
  // on parcour chaque element de la liste d'employés
  for (int i = 0; i < m_employers.size(); ++i) {
    delete m_employers[i]; // On supprime le poiteur de cette instance
    m_employers[i] = 0;    // On le met à 0 pour éviter des erreurs
  }
  // on parcour chaque element de la liste de titre
  for (int i = 0; i < m_titres.size(); ++i) {
    delete m_titres[i]; // On supprime le poiteur de cette instance
    m_titres[i] = 0;    // On le met à 0 pour éviter des erreurs
  }
}

bool Banque::existe(int id) const {
  //  Je parcours mon vecteur à la recherche de l'id
  for (int i(0); i < m_clients.size(); ++i) {
    if (m_clients[i]->getId() == id) {
      return true; // retourn true si le client est trouvé
    }
  }
  // si je sort de la boucle le client n'existe pas
  return false;
}
vector<Entite *> Banque::recherche(const std::string &nom,
                                   const std::string &prenom) const {
  vector<Entite *> trouve;
  for (int i(0); i < m_clients.size(); ++i) {
    if (m_clients[i]->getNom() == nom && m_clients[i]->getPrenom() == prenom) {
      trouve.push_back(
          m_clients[i]); // J'ajoute les client ayant le même nom et prénom
    }
  }
  return trouve;
}
void Banque::afficher(Entite *t) const { cout << *t; }
void Banque::ajouterClient(Client *c) { m_clients.push_back(c); }
void Banque::retirerClient(Client *c) {
  for (auto it = m_clients.begin(); it != m_clients.end(); ++it) {
    if (*it == c) {
      delete *it;
      m_clients.erase(it);
      break;
    }
  }
}
void Banque::ajouterEmployer(Employe *e) { m_employers.push_back(e); }
void Banque::retirerEmployer(Employe *e) {
  for (auto it = m_employers.begin(); it != m_employers.end(); ++it) {
    if (*it == e) {
      delete *it;
      m_employers.erase(it);
      break;
    }
  }
}
void Banque::ajouterTitre(Titre *t) { m_titres.push_back(t); }
void Banque::retirerTitre(Titre *t) {
  for (auto it = m_titres.begin(); it != m_titres.end(); ++it) {
    if (*it == t) {
      delete *it;
      m_titres.erase(it);
      break; // Exit the loop since the item is removed
    }
  }
}