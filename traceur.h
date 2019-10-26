#ifndef TRACEUR_H
#define TRACEUR_H
#include <iostream>
#include <vector>
#include "trace.h"

class traceur
{
public:
    traceur(std::string path);
    traceur();
    void setpath(std::string path);
    bool add(trace a);
    void get_all(std::vector<trace> & tab);
    void get_type(std::string type,std::vector<trace> & tab);
    void get_element(std::string type, std::string key,std::vector<trace> & tab);
private:

    std::vector<trace> m_tablo;
    std::string m_path;

};

#endif // TRACEUR_H
