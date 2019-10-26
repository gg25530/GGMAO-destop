#include "traceur.h"
#include "trace.h"

#include <fstream>
#include <sstream>


traceur::traceur(std::string path)
{
 m_path = path;
 m_path += "/traceur.txt";
 m_tablo.clear();

}

traceur::traceur()
{
 m_path = "";
 m_path += "/traceur.txt";
 m_tablo.clear();

}

void traceur::setpath(std::string path)
{
 m_path = path;
 m_path += "/traceur.txt";
 m_tablo.clear();

}



bool traceur::add(trace a)
{
    bool write=false;
    std::ofstream flux(m_path, std::ios::out | std::ios::app);
    if(flux)
    {
        flux << a.line();
        flux << std::endl;
        write = true;
    }
    else {}
    flux.close();
    return write;
}

void traceur::get_all(std::vector<trace> & tab)
{

    std::ifstream flux(m_path);
    std::string ligne="";
    std::stringstream ss;
    std::string sousChaine;
    std::vector<std::string> elements;

    if(flux)
    {
        m_tablo.clear();
        while (getline(flux, ligne))
        {

            ss.clear();
            ss << ligne;
            elements.clear();
            while (getline(ss, sousChaine,';'))
            {


            elements.push_back(sousChaine);
            }
            if(elements.size() == 7)
            {
                trace a(elements[0],elements[1],elements[2],elements[3],elements[4],elements[5],elements[6]);
                m_tablo.push_back(a);
            }

        }
    }
    else {}
    flux.close();

}


void traceur::get_type(std::string type,std::vector<trace> & tab)
{

}


void traceur::get_element(std::string type, std::string key,std::vector<trace> & tab)
{

}

