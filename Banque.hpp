#ifndef DEF_BANQUE
#define DEF_BANQUE
#include "Compte.hpp"
#include "Entite.hpp"
#include "Titre.hpp"
#include <string>
#include <vector>
class Banque {
public:
  // constructeur
  Banque();
  Banque(std::string nom );
  Banque(Banque const &copy);
  ~Banque();
  // Opération observatrice
  bool existe(int id) const; // vérifie l'existance d'un client
  std::vector<Entite *>
  recherche(std::string const &nom,
            std::string const &prenom) const; // recherche client ou employe
  void afficher(Entite *t) const;             // afficher   employe et client

  // opération modificatrice
  void ajouterClient(Client *c);    // Ajouter un client
  void retirerClient(Client *c);    // retirer un client
  void ajouterEmployer(Employe *e); // Ajouter un employe
  void retirerEmployer(Employe *e); // retirer un employe
  void ajouterTitre(Titre *t);      // ajouter un titre
  void retirerTitre(Titre *t);      // retirer un titre

private:
  std::string m_nom;                  // nom de la banque
  std::vector<Client *> m_clients;    // La banque possède plusieur clients
  std::vector<Employe *> m_employers; // La banque possède plusieur employés
  std::vector<Titre *> m_titres; // La banque possède plusieurs portefeuilles
};

#endif