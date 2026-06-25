#include <cstdlib>
#include <ctime>
#include <iostream>

// Inclusions de tes plans
#include "Banque.hpp"
#include "Carte.hpp"
#include "Compte.hpp"
#include "Entite.hpp"
#include "Portefeuille.hpp"
#include "Titre.hpp"

using namespace std;

int main() {
  // 1. Calibrage de l'horloge de l'usine (Pour les codes secrets des cartes)
  srand(time(nullptr));

  cout << "=== OUVERTURE DES PORTES DE LA FORTERESSE BANCAIRE ===" << endl;

  // 2. Fondation de la Banque
  Banque maBanque;

  // 3. Embauche du personnel
  // On utilise 'new' car le destructeur de Banque fera un 'delete'
  Employe *directeur = new Employe("boss@banque.fr", "0102030405", "Wayne",
                                   "Bruce", "19/02/1980", "Directeur", 5000.0);
  maBanque.ajouterEmployer(directeur);

  // 4. Création des contrats boursiers de base (Salle des Marchés)
  Action *actionApple = new Action("Apple", 150.0, 0);
  Obligation *obligEtat = new Obligation("Obligation Etat", 1000.0, 0.05, 10);
  maBanque.ajouterTitre(actionApple);
  maBanque.ajouterTitre(obligEtat);

  // 5. Arrivée d'un nouveau Client
  Client *investisseur = new Client("client@email.com", "0611223344", "Stark",
                                    "Tony", "29/05/1970");
  maBanque.ajouterClient(investisseur);

  // 6. Construction de ses Coffres-Forts (Comptes)
  CompteCourant *cc = new CompteCourant();
  cc->crediter(15000.0); // Le client dépose 15 000 euros
  investisseur->ajouterCompte(cc);

  CompteEpargne *ce = new CompteEpargne();
  ce->crediter(50000.0);
  investisseur->ajouterCompte(ce);

  // 7. Forge de la Clé Magique (Carte Bancaire)
  // Le client demande une carte liée à son Compte Courant
  investisseur->demanderCarte(cc);

  // Pour tester le terminal de paiement indépendant :
  cout << "\n--- TEST TERMINAL DE PAIEMENT ---" << endl;
  Carte carteTest("Stark Tony", cc); // Création d'une carte locale pour le test
  carteTest.payer(500.0);            // Tony achète un costume à 500€
  cout << "Solde du Compte Courant apres achat : " << cc->getSolde()
       << " euros." << endl;

  // 8. Investissement (Salle des Marchés)
  cout << "\n--- TEST SALLE DES MARCHES ---" << endl;
  // Tony achète pour 3000 euros d'actions Apple (Le clone sera fait
  // automatiquement par ta méthode !)
  investisseur->acheterTitre(3000.0, *actionApple);

  // 9. Le Bureau des Prêts
  cout << "\n--- TEST EMPRUNT ---" << endl;
  investisseur->contracterPret(100000.0, 0.02,
                               *cc); // Il emprunte 100 000 euros
  cout << "Solde du Compte Courant apres le pret : " << cc->getSolde()
       << " euros." << endl;

  // 10. Affichage global de l'état
  cout << "\n=== DOSSIER DU CLIENT ===" << endl;
  investisseur->afficher(cout);

  cout << "\nFlux du compte courant : " << endl;
  cc->afficherFlux(); // Affiche tout l'historique des opérations grâce au
                      // Registre

  // 11. Le test ultime : La Machine à Cloner de la Banque
  cout << "\n=== DECLENCHEMENT DU CLONAGE DE LA BANQUE ===" << endl;
  Banque banqueClone=maBanque;
  cout << "La banque a ete clonee avec succes. Si aucun crash n'arrive, "
          "l'usine est parfaite !"
       << endl;

  cout << "\n=== FERMETURE (Destruction de l'usine) ===" << endl;
  // À la fermeture de l'accolade du main, la 'banqueClone' et 'maBanque'
  // vont appeler leur destructeur, envoyer les équipes de démolition (delete)
  // et vider la mémoire de tout ce qu'on a créé avec 'new' !

  return 0;
}