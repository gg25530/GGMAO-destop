#include "pieces.h"
#include "date.h"

pieces::pieces()
{
     m_key = 0;
     m_prix = 0;
     m_qty =0;
     m_fabricant = "";
     m_name = "";
     m_reference = "";
     m_commentaire = "";
     m_emplacement = "";
     m_adresse = "";
     m_categorie = "";
    d.set(2018,1,1);
     m_liendoc = "";
     m_lienplan = "";
     m_lienphoto = "";
     m_fournisseur1 = "";
     m_fournisseur2 = "";
     m_fournisseur3 = "";
}

    pieces::pieces(pieces const &p)
    {
         m_key = p.key();
         m_prix = p.prix();
         m_qty = p.qty();
         m_fabricant = p.fabricant();
         m_name = p.name();
         m_reference = p.reference();
         m_commentaire = p.commentaire();
         m_emplacement = p.emplacement();
         m_adresse = p.adresse();
         m_categorie = p.categorie();
        d = p.date();
        m_liendoc = p.liendoc();
        m_lienplan = p.lienplan();
        m_lienphoto = p.lienphoto();
        m_fournisseur1 = p.fournisseur1();
        m_fournisseur2 = p.fournisseur2();
        m_fournisseur3 = p.fournisseur3();

    }

pieces::pieces(int key,int prix, std::string fabricant,std::string name,std::string reference,std::string commentaire)
{
     m_key = key;
     m_prix = prix;
     m_qty =0;
     m_fabricant = fabricant;
     m_name = name;
     m_reference = reference;
     m_commentaire = commentaire;
     m_emplacement = "";
     m_adresse = "";
     m_categorie = "";
    d.set(2018,1,1);
    m_liendoc = "";
    m_lienplan = "";
    m_lienphoto = "";
    m_fournisseur1 = "";
    m_fournisseur2 = "";
    m_fournisseur3 = "";
}

void pieces::modifierpiece(int key,int prix,int qty, std::string fabricant,std::string name,std::string reference,std::string commentaire,int y, int m, int j, std::string four1, std::string four2, std::string four3, std::string emplacement, std::string adresse, std::string categorie, std::string liendoc, std::string lienplan, std::string lienphoto)
{
     m_key = key;
     m_prix = prix;
     m_qty = qty;
     m_fabricant = fabricant;
     m_name = name;
     m_reference = reference;
     m_commentaire = commentaire;
     m_emplacement = emplacement;
     m_adresse = adresse;
     m_categorie = categorie;
     d.set(y,m,j);
     m_liendoc = liendoc;
     m_lienplan = lienplan;
     m_lienphoto = lienphoto;
     m_fournisseur1 = four1;
     m_fournisseur2 = four2;
     m_fournisseur3 = four3;
}


int pieces::key() const
{
return m_key;
}

int pieces::prix() const
{
return m_prix;
}

int pieces::qty() const
{
return m_qty;
}

std::string pieces::fabricant() const
{
return m_fabricant;
}

std::string pieces::name() const
{
return m_name;
}

std::string pieces::reference() const
{
return m_reference;
}
std::string pieces::commentaire() const
{
return m_commentaire;
}

std::string pieces::emplacement() const
{
return m_emplacement;
}


std::string pieces::adresse() const
{
return m_adresse;
}


std::string pieces::categorie() const
{
return m_categorie;
}


void pieces::setemplacement(std::string name)
{
    m_emplacement = name;
}


void pieces::setadresse(std::string name)
{
    m_adresse = name;
}


void pieces::setcategorie(std::string name)
{
m_categorie = name;
}



void pieces::setkey(int key)
{
m_key =key;
}

void pieces::setprix(int prix)
{
m_prix = prix;
}

void pieces::setqty(int qty)
{
m_qty = qty;
}

void pieces::setfabricant(std::string fab)
{
m_fabricant = fab;
}

void pieces::setname(std::string name)
{
m_name = name;
}

void pieces::setreference(std::string ref)
{
m_reference = ref ;
}

void pieces::setcommentaire(std::string comm)

{
m_commentaire = comm;
}

datee pieces::date() const
{
    return d;
}

void pieces::setdate(int y , int m, int  j)
{
    d.set(y,m,j);
}

std::string pieces::fournisseur1() const
{
return m_fournisseur1;
}
std::string pieces::fournisseur2() const
{
return m_fournisseur2;
}
std::string pieces::fournisseur3() const
{
return m_fournisseur3;
}
std::string pieces::liendoc() const
{
return m_liendoc;
}
std::string pieces::lienplan() const
{
return m_lienplan;
}
std::string pieces::lienphoto() const
{
return m_lienphoto;
}
void pieces::setfournisseur1(std::string f)
{
    m_fournisseur1 = f;
}
void pieces::setfournisseur2(std::string f)
{
    m_fournisseur2 = f;
}
void pieces::setfournisseur3(std::string f)
{
    m_fournisseur3 = f;
}
void pieces::setliendoc(std::string f)
{
    m_liendoc = f;
}
void pieces::setlienplan(std::string f)
{
    m_lienplan = f;
}
void pieces::setlienphoto(std::string f)
{
    m_lienphoto = f;
}
