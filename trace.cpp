#include "trace.h"

trace::trace(std::string type,std::string key,std::string action, std::string param,std::string oldvalue, std::string newvalue, std::string date)
{
     m_type = type;
     m_key = key;
     m_action = action;
     m_param = param;
     m_oldvalue = oldvalue;
     m_newvalue = newvalue;
     m_date = date;

}

void trace::set(std::string type,std::string key,std::string action,std::string param, std::string oldvalue, std::string newvalue, std::string date)
{
     m_type = type;
     m_key = key;
     m_action = action;
     m_param = param;
     m_oldvalue = oldvalue;
     m_newvalue = newvalue;
     m_date = date;

}


std::string trace::line()
{
    std::string temp="";
    temp += m_type;
    temp += ";";
    temp += m_key;
    temp += ";";
    temp += m_action;
    temp += ";";
    temp += m_param;
    temp += ";";
    temp += m_oldvalue;
    temp += ";";
    temp += m_newvalue;
    temp += ";";
    temp += m_date;
    temp += ";";

    return temp;

}
