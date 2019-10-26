#ifndef PIECES_H
#define PIECES_H
#include "date.h"
#include <QWidget>

class pieces
{
public:
    pieces();
    pieces(pieces const&);
    pieces(int key,int prix, std::string fabricant,std::string name,std::string reference,std::string commentaire);
     int key() const;
     int qty() const;
    int prix() const;
    std::string fabricant() const;
    std::string name() const;
    std::string reference() const;
    std::string commentaire() const;
    std::string fournisseur1() const;
    std::string fournisseur2() const;
    std::string fournisseur3() const;
    std::string liendoc() const;
    std::string lienplan() const;
    std::string lienphoto() const;
    std::string emplacement() const;
    std::string adresse() const;
    std::string categorie() const;
    void setemplacement(std::string name);
    void setadresse(std::string name);
    void setcategorie(std::string name);
    void setfournisseur1(std::string f) ;
    void setfournisseur2(std::string f) ;
    void setfournisseur3(std::string f) ;
    void setliendoc(std::string f) ;
    void setlienplan(std::string f) ;
    void setlienphoto(std::string f) ;
    datee date()const;
    void setdate(int y , int m, int  j);
    void setkey(int key);
    void setqty(int qty);
    void setprix(int prix);
    void setfabricant(std::string fab);
    void setname(std::string name);
    void setreference(std::string ref);
    void setcommentaire(std::string comm);
    void modifierpiece(int key,int prix,int qty, std::string fabricant, std::string name,std::string reference,std::string commentaire,int y,int m, int j, std::string four1, std::string four2, std::string four3, std::string emplacement, std::string adresse, std::string categorie, std::string liendoc, std::string lienplan, std::string lienphoto);
private:
    int m_key;
    int m_prix;
    int m_qty;
    datee d;
    std::string m_emplacement;
    std::string m_adresse;
    std::string m_categorie;
    std::string m_fabricant;
    std::string m_name;
    std::string m_reference;
    std::string m_commentaire;
    std::string m_liendoc;
    std::string m_lienplan;
    std::string m_lienphoto;
    std::string m_fournisseur1;
    std::string m_fournisseur2;
    std::string m_fournisseur3;

};

#endif // PIECES_H
