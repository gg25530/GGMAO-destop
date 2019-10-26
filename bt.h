#ifndef BT_H
#define BT_H
#include "date.h"
#include <QWidget>

class bt
{
public:
    bt();
    bt(int key, float time, std::vector<int> &p, datee dd, std::string machine, std::string tech,  std::string type, std::string commentaire, std::string atelier, std::string zone, std::string groupe, std::string photo1,std::string photo2,std::string photo3,std::string photo4);

    int key() const;
    std::string tech() const;
    std::string skey() const;
    std::string slu() const;
    std::string machine() const;
    std::string type() const;
    std::string atelier() const;
    std::string commentaire() const;
    std::string zone() const;
    std::string groupe() const;
    std::string photo1() const;
    std::string photo2() const;
    std::string photo3() const;
    std::string photo4() const;

    datee date()const;
    bool lu() const;
    std::string time() const;
    void getpieces(std::vector<int> &tab) ;
    void settech(std::string f) ;
    void setmachine(std::string f) ;
    void settype(std::string f) ;
    void setatelier(std::string f) ;
    void setzone(std::string f) ;
    void setgroupe(std::string f) ;
    void setphoto1(std::string f) ;
    void setphoto2(std::string f) ;
    void setphoto3(std::string f) ;
    void setphoto4(std::string f) ;
    void setdate(int y , int m, int  j);
    void setdate(std::string f);
    void setkey(int key);
    void addpiece(int key);
    void delpiece(int key);
    void setcommentaire(std::string comm);
    void clearpieces();
    void setlu(std::string lu);
    void settime(std::string time);
private:
    int m_key;
    float m_time;
    std::vector<int> pieces;
    datee d;
    std::string m_machine;
    std::string m_tech;
    std::string m_type;
    std::string m_commentaire;
    std::string m_atelier;
    std::string m_zone;
    std::string m_groupe;
    std::string m_photo1;
    std::string m_photo2;
    std::string m_photo3;
    std::string m_photo4;
    bool m_lu;
};

#endif // BT_H
