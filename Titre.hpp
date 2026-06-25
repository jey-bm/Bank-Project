#ifndef DEF_TITRE
#define DEF_TITRE
#include <iostream>
#include <string>
#include <vector>
class Titre {
public:
  // constructeur
  Titre();
  Titre(std::string nom);
  virtual ~Titre();
  Titre(Titre const &copy);
  // Opérations observatrices
  // Opérations modificatrices
  virtual Titre *clone() const = 0; // clone le titre lors de l'achat
  virtual void investir(double montant) = 0;
  virtual double getValue() const = 0; // retourne la valeur du titre

protected:
  static int m_cptid; // s'incrémente à chaque création de titre
  virtual void afficher(std::ostream &flux) const = 0;
  friend std::ostream &operator<<(std::ostream &flux, Titre const &e1);
  std::string m_nom;
  static std::vector<int> m_recupId; // récupère les id des titre vendu
  int m_id;                          // chaque titre à un id
};

class Action : public Titre {
public:
  // constructeur
  Action();
  Action(std::string nom, double prix, int qte);
  virtual ~Action();
  // copy
  Action(Action const &copy);
  // Opérations observatrices
  virtual void afficher(std::ostream &flux) const;
  // Opérations modificatrices
  void modifPrix(double newPrix);
  void modifierQte(short int newQte);
  virtual Titre *clone() const;
  virtual void investir(double montant); // Calcul la nouvelle quantité d'action
  virtual double getValue() const;
  void modifDividende(double div);

private:
  double m_prix; // prix unité en bourse
  int m_qtite;   // quantité de titre possédé
  double m_dividende;
};

class Obligation : public Titre {
public:
  // constructeur
  Obligation();
  Obligation(std::string nom, double montant, double taux, int duree);
  virtual ~Obligation();
  // copy
  Obligation(Obligation const &copy);
  // Opérations observatrices
  virtual void afficher(std::ostream &flux) const;
  // Opérations modificatrices
  virtual Titre *clone() const;
  virtual void investir(double montant);
  virtual double getValue() const;

private:
  double m_montant;    // Montant investi initiallement 0
  double m_taux;       // taux d'intérêt
  int m_dureeMaturite; // Durée de vie du contrat à la de celle ci, l'obligation
                       // est automatiquement détruite
};
#endif