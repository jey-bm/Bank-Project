#ifndef DEF_COMPTE
#define DEF_COMPTE
#include "Carte.hpp"
#include <iostream>
#include <string>
#include <vector>
struct Registre {
  std::string m_date;
  double m_montant;
};
class Compte {
public:
  // constructeur/destructeur
  Compte();
  Compte(double solde);
  virtual ~Compte();
  // copy
  Compte(Compte const &copy);
  // Opérations observatrices
  bool ifexist() const; // Renvoie true si compte existe

  // Opérations modificatrices
  void envoyer(
      double montant,
      std::string const &id_compte); // Envoyer de l'argent vers un autre compte
  void recevoir(double montant,
                std::string const &id_compte); // Rcevoir de l'argent
  void modifierSolde(double new_solde);        // modifier le solde

protected:
  std::vector<Registre> m_registre; // un compte possède un registre de paiement
  std::string m_idCompte;
  double m_taux;                                       // taux d'intérêt
  virtual void afficher(std::ostream &flux) const = 0; // on affiche le solde
  double m_solde;                                      // un compte à un solde
  friend std::ostream &operator<<(std::ostream &flux, Compte const &compte);
};

/////////////////////////////Classe_CompteEpargne/////////////////////////////////////

class CompteEpargne : public Compte {
public:
  // constructeur
  CompteEpargne();
  CompteEpargne(double solde, double limite);
  virtual ~CompteEpargne();
  // copy
  CompteEpargne(CompteEpargne const &copy);
  // Opérations observatrices

  // Opérations modificatrices
private:
  virtual void afficher(std::ostream &flux) const;
  double m_limites; // plafond limite d'épargne
};

/////////////////////////////Classe_CompteCourant/////////////////////////////////////

class CompteCourant : public Compte {
public:
  // constructeur
  CompteCourant();
  CompteCourant(double plafond, double solde, int nbcarte);
  virtual ~CompteCourant();
  // copy
  CompteCourant(CompteCourant const &copy);
  // Opérations observatrices
  void afficherPlafond() const; // On affiche le plafond

  // Opérations modificatrices
  void ajouterCarte(Carte *new_carte);            // ajout de carte
  void retirerCarte(std::string const &id_carte); // supprimer une carte
  void mofierPlafond(double new_plafond);         // modifier modifier plafond
  void modifierNbC(int new_nbC); // modifier nombre de carte limite

private:
  // un compte courant possède une limite de découvert autorisé
  double m_decouvert;
  virtual void afficher(std::ostream &flux) const;
  double m_plafond;              // un compte à un plafond d'envoie
  int m_nbCarte;                 // limite de carte possible
  std::vector<Carte *> m_cartes; // Un comptes peut avoir plusieur cartes
};

#endif