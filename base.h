#ifndef BASE_H
#define BASE_H

#include "pieces.h"
#include "machine.h"
#include "bt.h"
#include "traceur.h"
#include "trace.h"
#include <QStringList>
#include "commandes.h"
#include "fournisseurs.h"
#include <QtWidgets>

class base
{
public:
    base();
    void addpieces(std::string tprix, std::string tfabricant, std::string tfournisseur,std::string tname,std::string treference,std::string tcommentaire);
    void addmachine(std::string tatelier,std::string tzone,std::string tgroupe, std::string tfabricant,std::string tname,std::string treference,std::string tcommentaire,std::string tdate);
    void addbt(std::string tatelier,std::string tmachine,std::string type, std::string ttech,std::string tdate,std::string ttime,std::string tcommentaire,std::string lien_photo1,std::string lien_photo2,std::string lien_photo3,std::string lien_photo4);
    void addcommande(std::string tfournisseur,std::string treference,std::string tprix, std::string tdestinataire,std::string tdate,std::string tcommentaire);
    int iscorrompue();
    void majbase();
    void savebase();
    void saveressources();
    void ajouterdocument(std::string format, std::string &adresse);
    int nbpieces();
    int nbmachines();
    int nbbts();
    int nbcommandes();
    int nbtech();
    int nbfournisseurs();
    int nbfabricants();
    int nbcategories();
    int nbtypetaf();
    int nbateliers();
    int nbdestinataires();
    bool ismodified();
    bool ischargee();
    std::string path() const;
    void setpath(std::string dossier);
    std::string name() const;
    void setname(std::string dossier);
    std::string pieces_fabricant(int num) const;
    std::string pieces_key(int num) const;
    std::string pieces_prix(int num) const;
    std::string pieces_reference(int num) const;
    std::string pieces_nom(int num) const;
    std::string pieces_commentaire(int num) const;
    std::string pieces_date(int num) const;
    std::string pieces_qty(int num) const;
    std::string pieces_cout(int num) const;
    std::string pieces_four1(int num) const;
    std::string pieces_four2(int num) const;
    std::string pieces_four3(int num) const;
    std::string pieces_emplacement(int num) const;
    std::string pieces_adresse(int num) const;
    std::string pieces_categorie(int num) const;
    std::string pieces_liendoc(int num) const;
    std::string pieces_lienplan(int num) const;
    std::string pieces_lienphoto(int num) const;
    std::string bt_atelier(int num) const;
    std::string bt_machine(int num) const;
    std::string bt_temps(int num) const;
    std::string bt_type(int num) const;
    std::string bt_tech(int num) const;
    std::string bt_commentaire(int num) const;
    std::string bt_date(int num) const;
    std::string bt_slu(int num) const;
    std::string bt_skey(int num) const;
    std::string commande_fournisseur(int num) const;
    std::string commande_reference(int num) const;
    std::string commande_prix(int num) const;
    int commande_prixint(int num) const;
    int commande_annee(int num) const;
    int commande_jour(int num) const;
    int commande_mois(int num) const;
    int bts_annee(int num) const;
    int bts_mois(int num) const;
    int index_bts();
    std::string commande_commentaire(int num) const;
    std::string commande_date(int num) const;
    std::string commande_destinataire(int num) const;
    std::string commande_skey(int num) const;
    void getlistmachinesbt(std::vector<std::string> &bt,std::string machine);
    void getlistmachinespieces(std::vector<int> &pieces,int machine);
    void getlistmachineplan(std::vector<std::string> &fichiers,int machine);
    void getlistmachinedoc(std::vector<std::string> &fichiers,int machine);
    void getlistmachinephoto(std::vector<std::string> &fichiers,int machine);
    void getlistmachinereference(QLabel *f,int num);
    void getlistmachinedate(QLabel *f,int num);
    void getlistmachinecommentaire(QLabel *f,int num);
    void getlistmachinefabricant(QLabel *f,int num);
    void getlisttech(std::vector<std::string> &tech);
    void getlistfournisseurs(std::vector<std::string> &four);
    void getlistfabricants(std::vector<std::string> &fab);
    void getlistcategories(std::vector<std::string> &cat);
    void getlisttypetaf(std::vector<std::string> &typetaf);
    void getlistdestinataires(std::vector<std::string> &dest);
    void getlistatelier(std::vector<std::string> &atelier);
    void getlistmachine(std::vector<std::string> &machine);
    void getlistmachineatelier(std::vector<std::string> &machine,std::string atelier);
    void getlistmachinespiece(std::vector<std::string> &machine,int num); // retourne liste machine utilisant la piece num = key piece
    int getpiece(int num_key);
    void addtypetaf(std::string f);
    void addatelier(std::string f);
    void addtech(std::string f);
    void addfournisseur(std::string f);
    void addcategorie(std::string f);
    void addfabricant(std::string f);
    void adddestinataire(std::string f);
    void supprfournisseur(std::string f);
    void supprfabricant(std::string f);
    void supprtech(std::string f);
    void supprcategorie(std::string f);
    void suppratelier(std::string f);
    void supprdestinataire(std::string f);
    void supprtypetaf(std::string f);
    void suppr_piece_machine(int mach, int num);
    void modified(bool m);
    void chargee(bool c);
    int findmachine(std::string mach);
    int commande_check_date(int num,std::string a,std::string b);
    int pieces_check_date(int num,std::string a,std::string b);
    int bt_check_date(int num,std::string a,std::string b);
    void modifierpiece(int num ,int key ,std::string tprix, std::string tfabricant,std::string tname,std::string treference,std::string tcommentaire, std::string tfour1,std::string tfour2, std::string tfour3,std::string tdoc,std::string tplan, std::string tphoto,std::string templacement, std::string tadresse, std::string tcategorie,std::string tdate,std::string tqty);
    void machine_addpieces(std::vector<int> &pieces,int num_mach);
    void get_machine(machine & mach,int num);
    void getfournisseur(fournisseurs & four, std::string name);
    void setfournisseur(fournisseurs & four);
    void set_machine(machine & mach,int num);
    void setdate_bt_param(std::string f);
    std::string getdate_bt_param();
    void setdate_commande_param(std::string f);
    std::string getdate_commande_param();
    void get_bt(bt & bon,int num);
    int findbt(int num);
    void set_bt(bt & bon,int num);
    void get_commande(commandes & bon,int num);
    int findcommande(int num);
    void set_commmande(commandes & bon,int num);

private:
    std::vector<pieces> basep;
    std::vector<machine> machines;
    std::vector<bt> bts;
    std::vector<commandes> m_commandes;

    std::vector<std::string>  m_fabricants;
    std::vector<fournisseurs>  m_fournisseurs;
    std::vector<std::string>  m_tech;
    std::vector<std::string>  m_typetaf;
    std::vector<std::string>  m_atelier;
    std::vector<std::string>  m_destinataires;
    std::vector<std::string>  m_categorie;

    traceur m_tracing;
    datee age;
    std::string m_path;
    std::string m_name;
    std::string date_bt;
    std::string date_commande;

    int indexpieces;
    int indexmachine;
    int indexbt;
    int indexcommandes;
    int corrompue;
    bool charg;
    bool modif;
};

#endif // BASE_H
