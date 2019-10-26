#ifndef COMMANDES_H
#define COMMANDES_H
#include "date.h"
#include <QWidget>

class commandes
{
public:
    commandes();
   int key() const;
   std::string fournisseur() const;
   std::string destinataire() const;
   std::string reference() const;
   std::string commentaire() const;
   std::string prix() const;
   std::string skey() const;
   datee date()const;
   void setfournisseur(std::string f) ;
   void setdestinataire(std::string f) ;
   void setreference(std::string f) ;
   void setcommentaire(std::string f) ;
   void setprix(std::string f) ;
   void setdate(int y , int m, int  j);
   void setdate(std::string f);
   void setkey(int key);


private:
    int m_key;
    datee d;
    std::string m_fournisseur;
    std::string m_destinataire;
    std::string m_reference;
    std::string m_commentaire;
    int m_intprix;
};

#endif // COMMANDES_H
