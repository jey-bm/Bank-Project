#ifndef DEF_ENTITE
#define DEF_ENTITE
#include "Carte.hpp"
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
  Entite(Entite const & e);
  Entite(std::string email, std::string numTel, std::string nom,
         std::string prenom, std::string dateNaiss);
  virtual ~Entite();
  // Opérations observatrices
  // Opérations modificatrices
  void modifNum(std::string newNum);
  void modifEmail(std::string newEmail);
  void recevoir(CompteCourant const &c1,
                double montant); // Une entité peut recevoir de l'argent
  void afficheCompte(
      Compte const &c1) const; // affiche le compte et sa composition
  void afficherTousLesComptes() const;
  int getId() const;           // retourne l'id
  std::string getNom() const;
  std::string getPrenom() const;

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
struct Pret {
  double montant, taux;
  int id;
};
class Client : public Entite {
public:
  // constructeur
  Client();
  Client(Client const & c);
  Client(std::string email, std::string numTel, std::string nom,
         std::string prenom, std::string dateNaiss);
  ~Client();
  // Opérations observatrices
  // Opérations modificatrices
  void suppCompte();
  void suppCompte(Compte const &c);

  void demanderCarte(CompteCourant *c);
  void ajouterCompte(Compte *c);
  void envoyer(double montant,
               Compte &c); // Un client peut envoyer de
                           // l'argent vers un autre compte
  void retirerArgent(Carte &c1,
                     double montant); // Une client peut retirer de l'argent
  void acheterTitre(double montant,
                    Titre const &titre); //  un client peut acheter des titres
  void vendreTitre(Titre const &titre,
                   CompteCourant const &c); // un client peut vendre des titre
  void
  contracterPret(double montant, double taux,
                 CompteCourant const &c); // un client peut contracter un prêt
  void rembourserPret(Pret const &p, CompteCourant &c);
  Compte* getCompte(int id);
  void cederAction(const Titre &titre, int qte);// un client peut céder une quantité précise d'une action
private:
  virtual void afficher(std::ostream &flux) const;
  static int cptPret;
  std::vector<Carte *> m_cartes; // un client possèdes une liste de cartes
  static int m_cptClient;
  static std::vector<int> m_listeIdC; // liste d'id qui se sont libéré
  Portefeuille *m_cto; // un client peut possèder un portefeuille de titre
  std::vector<Pret *> m_prets; // prêts contractés
};

/////////////////////////////Classe_Employer/////////////////////////////////////

class Employe : public Entite {
public:
  // constructeur
  Employe(Employe const & copy);
  Employe();
  Employe(std::string email, std::string numTel, std::string nom,
          std::string prenom, std::string dateNaiss, std::string poste,
          double salaire);
  virtual ~Employe();
  // Opérations observatrices
  // Opérations modificatrices
  void gestionSalaire(double montant);

private:
  virtual void afficher(std::ostream &flux) const;
  static std::vector<int> m_listeIdE; // liste d'id qui se sont libéré
  static int m_cptEmployer;           // compteur d'id
  double m_salaire;                   // Un employer à un salaire
  std::string m_poste;                // Un employer à un poste précis
};
#endif