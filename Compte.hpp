#ifndef DEF_COMPTE
#define DEF_COMPTE
#include "Carte.hpp"
#include <iostream>
#include <string>
#include <vector>
struct Registre {
  std::string m_date;
  double m_montant;
  void afficherf(std::ostream &flux) const;
};
std::ostream &operator<<(std::ostream &flux, Registre const &r);
class Compte {
public:
  // constructeur/destructeur
  Compte();
  virtual ~Compte();
  // copy
  Compte(Compte const &copy);
  // Opérations observatrices

  // Opérations modificatrices
  void debiter(double montant);  // un compte peut etre débité
  void crediter(double montant); // un compte créditer
  /* void envoyer(
      double montant,
      std::string const &id_compte); // Envoyer de l'argent vers un autre compte
  void recevoir(double montant,
                std::string const &id_compte); // Rcevoir de l'argent */
  void modifierSolde(double new_solde); // modifier le solde
  std::string getId() const;
  double getSolde() const;
  void afficherFlux() const;
  virtual Compte* clone() const =0;

protected:
  static int m_cptId;
  static std::vector<int> m_listId;
  std::vector<Registre> m_registre; // un compte possède un registre de paiement
  int m_idCompte;
  double m_taux;                                       // taux d'intérêt
  virtual void afficher(std::ostream &flux) const = 0; // on affiche le solde
  long double m_solde;                                      // un compte à un solde
  friend std::ostream &operator<<(std::ostream &flux, Compte const &compte);
};

/////////////////////////////Classe_CompteEpargne/////////////////////////////////////

class CompteEpargne : public Compte {
public:
  // constructeur
  CompteEpargne();
  virtual ~CompteEpargne();
  // copy
  CompteEpargne(CompteEpargne const &copy);
  // Opérations observatrices
  // Opérations modificatrices
  virtual Compte* clone() const;
private:
  virtual void afficher(std::ostream &flux) const;
  double m_limites; // plafond limite d'épargne
};

/////////////////////////////Classe_CompteCourant/////////////////////////////////////

class CompteCourant : public Compte {
public:
  // constructeur
  CompteCourant();
  virtual ~CompteCourant();
  // copy
  CompteCourant(CompteCourant const &copy);
  // Opérations observatrices
  void afficherPlafond() const; // On affiche le plafond
  // Opérations modificatrices
  void ajouterCarte(Carte *new_carte);      // ajout de carte
  void retirerCarte(Carte const &carte);    // supprimer une carte
  void modifierPlafond(double new_plafond); // modifier modifier plafond
  void modifierNbC(int new_nbC);            // modifier nombre de carte limite
  void modifierDecouvert(double newD);      // modifie le découvert
  virtual Compte* clone() const;
private:
  virtual void afficher(std::ostream &flux) const;
  // un compte courant possède une limite de découvert autorisé
  double m_decouvert;
  double m_plafond;              // un compte à un plafond d'envoie
  int m_nbCarte;                 // limite de carte possible
  std::vector<Carte *> m_cartes; // Un comptes peut avoir plusieur cartes
};

#endif