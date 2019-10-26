#ifndef TRACE_H
#define TRACE_H
#include <iostream>


class trace
{
public:
    trace(std::string type,std::string key,std::string action,std::string param, std::string oldvalue, std::string newvalue, std::string date);
    std::string line();
    void set(std::string type,std::string key,std::string action,std::string param, std::string oldvalue, std::string newvalue, std::string date);
private:

    std::string m_type;
    std::string m_key;
    std::string m_action;
    std::string m_param;
    std::string m_oldvalue;
    std::string m_newvalue;
    std::string m_date;

};

#endif // TRACE_H
