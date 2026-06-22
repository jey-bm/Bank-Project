#ifndef DEF_ENTITE
#define DEF_ENTITE
#include "Compte.hpp"
#include "Portefeuille.hpp"
#include "Titre.hpp"
#include <iostream>
#include <string>
#include <vector>
class Entite {
public:
  // constructeur/ destructeur
  Entite();
  Entite(std::string numTel, std::string nom, std::string prenom,
         std::string dateNaiss);
  virtual ~Entite();
  // Opérations observatrices
  // Opérations modificatrices
  void modifNum(std::string newNum);
  void modifEmail(std::string newEmail);
  void recevoir(double montant); // Une entité peut recevoir de l'argent
  void afficheCompte(
      std::ostream &flux) const; // affiche les comptes et leur compositions

protected:
  int m_nbCompte; // le nombre de compte
  virtual void afficher(
      std::ostream &flux) const = 0; // affiche les informations de l'entité
  int m_id;
  std::string m_email;
  std::string m_numTel;
  std::string m_nom;
  std::string m_prenom;
  std::string m_dateNaiss;
  std::vector<Compte *> m_comptes;
  friend std::ostream &operator<<(std::ostream &flux, Entite const &e1);
};

/////////////////////////////Classe_Client/////////////////////////////////////

class Client : public Entite {
public:
  // constructeur
  Client();
  Client(std::string numTel, std::string nom, std::string prenom,
         std::string dateNaiss);
  ~Client();
  // Opérations observatrices
  virtual void afficher(std::ostream &flux) const;
  // Opérations modificatrices
  void suppCompte();
  void demanderCarte(std::string nomPrenom);
  void creerCompte();
  void envoyer(double montant,
               std::string const &id_compte); // Un client peut envoyer de
                                              // l'argent vers un autre compte
  void ajouterArgent(double montant); // une client peut ajouter de l'argent
  void retirerArgent(double montant); // Une client peut retirer de l'argent
  void acheterTitre(int quanté,
                    Titre const &titre); // un client peut acheter des titres
  void vendreTitre(int quanté,
                   Titre const &titre); // un client peut vendre des titre
  void contracterPret(double montant,
                      double taux); // un client peut contracter un prêt

private:
  static int m_cptClient;
  static std::vector<int> m_listeIdC; // liste d'id qui se sont libéré
  Portefeuille *m_cto; // un client peut possèder un portefeuille de titre
  double m_pret;       // prêt contracté
};

/////////////////////////////Classe_Employer/////////////////////////////////////

class Employe : public Entite {
public:
  // constructeur
  Employe();
  Employe(std::string numTel, std::string nom, std::string prenom,
          std::string dateNaiss, std::string poste, double salaire);
  virtual ~Employe();
  // Opérations observatrices
  virtual void afficher(std::ostream &flux) const;
  // Opérations modificatrices
  void gestionBonus();
  void gestionSalaire();

private:
  static std::vector<int> m_listeIdE; // liste d'id qui se sont libéré
  static int m_cptEmployer;           // compteur d'id
  double m_salaire;                   // Un employer à un salaire
  std::string m_poste;                // Un employer à un poste précis
  bool m_bonus; // un employer peut ou pas recevoir un bonus
};
#endif