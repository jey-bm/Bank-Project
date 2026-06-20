#ifndef DEF_CARTE
#define DEF_CARTE
class Compte; // Déclaration anticipé car assosiation bidirectionnelle
#include <iostream>
#include <string>

class Carte {
public:
  // opération modificatrice
  void payer(double montant); // On peut payer avec une carte
  void bloquer();             // on peut bloquer la carte
  void activer();             // On peut activer la carte
private:
  double m_plafond; // une carte possède un plafond de paiement
  Compte *m_compte; // une carte possède un solde du compte qui pointe sur le
                    // solde ddu compte
  std::string m_numCarte; // une carte possède un numéros de carte
  std::string
      m_nomPrenom; // une carte possède le nom et prénom de celui qui la possède
  std::string m_dateExpiration; // une carte possède une date d'expiration
  short int m_cvv;              // une carte possède un numéro crypté
  short int m_codeSecret;       // une carte possède un code secret
  bool m_etat;                  // Une carte peut être active ou inactive
};

#endif