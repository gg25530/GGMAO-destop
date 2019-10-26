#ifndef MACHINE_H
#define MACHINE_H
#include "date.h"
#include <QWidget>

class machine
{
public:
    machine();
   int key() const;
   std::string fabricant() const;
   std::string name() const;
   std::string atelier() const;
   std::string reference() const;
   std::string commentaire() const;
   std::string liendoc1() const;
   std::string lienplan1() const;
   std::string lienphoto1() const;
   std::string liendoc2() const;
   std::string lienplan2() const;
   std::string lienphoto2() const;
   std::string liendoc3() const;
   std::string lienplan3() const;
   std::string lienphoto3() const;
   std::string liendoc4() const;
   std::string lienplan4() const;
   std::string lienphoto4() const;
   datee date()const;
   void getpieces(std::vector<int> &tab) ;
   void setatelier(std::string f) ;
   void setliendoc1(std::string f) ;
   void setlienplan1(std::string f) ;
   void setlienphoto1(std::string f) ;
   void setliendoc2(std::string f) ;
   void setlienplan2(std::string f) ;
   void setlienphoto2(std::string f) ;
   void setliendoc3(std::string f) ;
   void setlienplan3(std::string f) ;
   void setlienphoto3(std::string f) ;
   void setliendoc4(std::string f) ;
   void setlienplan4(std::string f) ;
   void setlienphoto4(std::string f) ;
   void setdate(int y , int m, int  j);
   void setdate(std::string f);
   void setkey(int key);
   void addpiece(int key);
   void delpiece(int key);
   void setfabricant(std::string fab);
   void setname(std::string name);
   void setreference(std::string ref);
   void setcommentaire(std::string comm);
   void clearpieces();

private:
    int m_key;
    std::vector<int> pieces;
    datee d;
    std::string m_fabricant;
    std::string m_name;
    std::string m_serial;
    std::string m_commentaire;
    std::string m_liendoc1;
    std::string m_lienplan1;
    std::string m_lienphoto1;
    std::string m_liendoc2;
    std::string m_lienplan2;
    std::string m_lienphoto2;
    std::string m_liendoc3;
    std::string m_lienplan3;
    std::string m_lienphoto3;
    std::string m_liendoc4;
    std::string m_lienplan4;
    std::string m_lienphoto4;
    std::string m_atelier;
    std::string m_zone;
    std::string m_groupe;

};

#endif // MACHINE_H
