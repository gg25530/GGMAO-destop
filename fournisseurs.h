#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H



#include <QWidget>

class fournisseurs
{
public:
    fournisseurs();
    fournisseurs(std::string name,std::string num_bureau,std::string num_portable,std::string name_commercial,std::string commentaire,std::string num_client,std::string num_contrat,std::string mail_1,std::string mail_2,std::string adresse_postale);
    std::string name() const;
    std::string num_bureau() const;
    std::string num_portable() const;
    std::string name_commercial() const;
    std::string commentaire() const;
    std::string num_client() const;
    std::string num_contrat() const;
    std::string mail_1() const;
    std::string mail_2() const;
    std::string adresse_postale() const;
    void setname(std::string f) ;
    void setnum_bureau(std::string f) ;
    void setnum_portable(std::string f) ;
    void setname_commercial(std::string f) ;
    void setcommentaire(std::string f) ;
    void setnum_client(std::string f) ;
    void setnum_contrat(std::string f) ;
    void setmail_1(std::string f) ;
    void setmail_2(std::string f) ;
    void setadresse_postale(std::string f) ;


private:
    std::string m_name;
    std::string m_num_bureau;
    std::string m_num_portable;
    std::string m_name_commercial;
    std::string m_commentaire;
    std::string m_num_client;
    std::string m_num_contrat;
    std::string m_adresse_mail_1;
    std::string m_adresse_mail_2;
    std::string m_adresse_postale;


};

#endif // FOURNISSEURS_H
