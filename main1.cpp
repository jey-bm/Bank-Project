    #include <cstdlib>
    #include <ctime>
    #include <iostream>
    #include<array>

    // Inclusions de tes plans
    #include "Banque.hpp"
    #include "Carte.hpp"
    #include "Compte.hpp"
    #include "Entite.hpp"
    #include "Portefeuille.hpp"
    #include "Titre.hpp"

    using namespace std;

    struct tabE
        {
            string email; 
            string numTel; 
            string nom;
            string prenom;
            string dateNaiss;
            string poste; 
            double salaire;
        };
    struct tabC
    {
        string email; 
        string numTel; 
        string nom; 
        string prenom; 
        string dateNaiss;
    };

    void afficher(Banque* b,Entite*e)
    {
        b->afficher(e);
    }
    int main()
    {
        // On commence par calibrere l'horloge
        srand(time(nullptr));

        // On construit notre banque
        Banque *lcl = new Banque("LCL");

        // J'embauche mes premiers salariers
    
        array<tabE,9> salariers = {{// FRONT OFFICE
            {"jean.dupont@banque.com", "0601020304", "Dupont", "Jean", "12/05/1992", "Conseiller Particuliers", 34000.0},
            {"alice.martin@banque.com", "0611223344", "Martin", "Alice", "28/11/1985", "Chargé d'Affaires Entreprises", 58000.0},
            {"marc.lefevre@banque.com", "0622334455", "Lefevre", "Marc", "03/02/1978", "Directeur d'Agence", 52000.0},
            
            // MIDDLE OFFICE
            {"sophie.durand@banque.com", "0633445566", "Durand", "Sophie", "19/07/1990", "Analyste Crédit", 42000.0},
            {"thomas.bernard@banque.com", "0644556677", "Bernard", "Thomas", "25/08/1988", "Compliance Officer", 48000.0},
            {"lucie.petit@banque.com", "0655667788", "Petit", "Lucie", "14/01/1983", "Risk Manager", 63000.0},
            
            // BACK OFFICE & TECH
            {"pierre.dubois@banque.com", "0666778899", "Dubois", "Pierre", "30/09/1995", "Gestionnaire Back-Office", 31000.0},
            {"lucas.baker@banque.com", "0677889900", "Baker", "Lucas", "05/04/1994", "Expert Cybersécurité", 55000.0}}};

        
        for(unsigned i(0); i<salariers.size();++i)
        {
            lcl->ajouterEmployer(new Employe(salariers[i].email,salariers[i].numTel,salariers[i].nom,salariers[i].prenom,salariers[i].dateNaiss,salariers[i].poste,salariers[i].salaire));
            
        }
        // Je test si l'opération a fonctionné 
        for(Entite *e:lcl->recherche("Baker", "Lucas"))
        {
            lcl->afficher(e);
        }

        
        array<tabC,5> client =
            {{{"thomas.schutz@email.com", "0612345678", "Schutz", "Thomas", "15/03/1988"},
            {"emilie.bernard@email.com", "0687654321", "Bernard", "Emilie", "22/07/1991"},
            {"lucas.petit@email.com", "0745238910", "Petit", "Lucas", "05/11/2000"},
            {"chloe.durand@email.com", "0611998877", "Durand", "Chloé", "30/01/1975"},
            {"bruce.de_witt@email.com", "0655443322", "De witt", "Bruce", "14/09/1983"}}};
        // je vais y stocker les client
        vector<Entite*> salonVip;
        for(tabC c :client )
        {
            // j'enregistre mes premiers clients 
            Client *c1 =new Client(c.email,c.numTel,c.nom,c.prenom,c.dateNaiss);
            lcl->ajouterClient(c1);
            //on cherche puis on stock
            vector<Entite*> recherche1 = lcl->recherche(c.nom,c.prenom);
            salonVip.insert(salonVip.end(), recherche1.begin(), recherche1.end());

            // je leur créer un compte avec 10k chacun
            CompteCourant *compte =new CompteCourant;
            c1->ajouterCompte(compte);
            c1->recevoir(*compte, 10000);
        }

        // Je test si l'opération a fonctionné 
        for(Entite *e: salonVip)
        {
            lcl->afficher(e);
            // Je m'assure que c'est un client
            Client* vraiClient = dynamic_cast<Client*>(e);

            if(vraiClient != nullptr)
            {
                cout << "Le client " << vraiClient->getPrenom() << " est dans le salon." << endl;
                vraiClient->afficherTousLesComptes();
            }
        }

        // La partie fun je vais faire les clients intéragir entre eux :
        Client* thomas = nullptr;
        Client* bruce = nullptr;
        
        // Je parcours mon salon VIP à la recherche de ceux ci
        for(Entite *e: salonVip) {
            // Je tchek si se sont bien des clients
            Client* vraiClient = dynamic_cast<Client*>(e);
            
            if(vraiClient != nullptr) {
                if(vraiClient->getPrenom() == "Thomas") {
                    thomas = vraiClient;
                    cout << "[Accueil VIP] Le client Thomas Schutz s'installe confortablement." << endl;
                }
                else if(vraiClient->getPrenom() == "Bruce") {
                    bruce = vraiClient;
                    cout << "[Accueil VIP] Le client Bruce De witt allume son cigare." << endl;
                }
            }
        }

        // Si nos deux VIP sont bien présents dans la pièce, l'économie peut tourner !
        if(thomas != nullptr && bruce != nullptr) {
            
            CompteCourant* ccThomas = dynamic_cast<CompteCourant*>(thomas->getCompte(0));
            CompteCourant* ccBruce = dynamic_cast<CompteCourant*>(bruce->getCompte(0));

            if(ccThomas != nullptr && ccBruce != nullptr) {
                
                // ---------------------------------------------------------
                // LE BUREAU DES PRÊTS
                // ---------------------------------------------------------
                cout << "\n[Bureau des Prets] Bruce signe les papiers pour l'achat de Wayne Enterprises." << endl;
                bruce->contracterPret(1000000.0, 0.05, *ccBruce); // Bruce emprunte 1 Million

                cout << "[Bureau des Prets] Thomas contracte un emprunt de 500 000 euros." << endl;
                thomas->contracterPret(500000.0, 0.04, *ccThomas); // Thomas emprunte 500 000

                // ---------------------------------------------------------
                // LE VIRTEMENT BANCAIRE PRIVÉ
                // ---------------------------------------------------------
                cout << "\n[Virement] Thomas envoie secraitement 250 000 euros dans le coffre de Bruce." << endl;
                ccThomas->debiter(250000.0);
                bruce->envoyer(250000.0, *ccBruce); 

                // ---------------------------------------------------------
                // LA SALLE DES MARCHÉS : L'Usine à Titres
                // ---------------------------------------------------------
                cout << "\n=== LA BOURSE S'AFFOLE ===" << endl;
                // L'usine fabrique les contrats boursiers
                Action *actionApple = new Action("Apple", 150.0, 0);
                Action *actionAmazon = new Action("Amazon", 3000.0, 0);
                Action *actionPortailliance = new Action("Portailliance", 50.0, 0); 
                
                lcl->ajouterTitre(actionApple);
                lcl->ajouterTitre(actionAmazon);
                lcl->ajouterTitre(actionPortailliance);

                // Bruce de Witt dévalise le marché
                cout << "[Achat] Bruce investit massivement en bourse." << endl;
                bruce->acheterTitre(150000.0, *actionApple);
                bruce->acheterTitre(300000.0, *actionAmazon);
                bruce->acheterTitre(500000.0, *actionPortailliance); 

                // Thomas suit la tendance
                cout << "[Achat] Thomas place son argent strategiquement." << endl;
                thomas->acheterTitre(50000.0, *actionApple);
                thomas->acheterTitre(100000.0, *actionAmazon);
                thomas->acheterTitre(10000.0, *actionPortailliance);

                // ---------------------------------------------------------
                // LA TRANSACTION DE GRÉ À GRÉ DANS LE SALON
                // ---------------------------------------------------------
                cout << "\n[Transaction VIP] Bruce revend 100 actions Portailliance a Thomas." << endl;
                // La transaction manuelle chirurgicale
                double prixUnitaire = 500.0;
                double montantTransaction = 100 * prixUnitaire; 
                
                // Transfert des fonds
                ccThomas->debiter(montantTransaction);
                ccBruce->crediter(montantTransaction);
                
                // Thomas reçoit les titres dans sa mallette 
                thomas->acheterTitre(montantTransaction, *actionPortailliance);
                
                // Bruce cède physiquement ses 10 actions ! 
                bruce->cederAction(*actionPortailliance, 10);
        
                cout << "La poignee de main est donnee. Transaction validee." << endl;
            }
        }

        // ---------------------------------------------------------
        // L'INSPECTION FINALE DES COFFRES
        // ---------------------------------------------------------
        cout << "\n=== BILAN FIN DE JOURNEE DANS LE SALON ===" << endl;
        if(thomas != nullptr) thomas->afficherTousLesComptes();
        if(bruce != nullptr) bruce->afficherTousLesComptes();
        
        // On envoie l'équipe de démolition pour raser l'usine entière !
        delete lcl; 
    
        return 0;

        
    }