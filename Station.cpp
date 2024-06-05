
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include "Station.h"
#include "Utilities.h"
namespace seneca
{
    int Station::id_generator = 1;
    size_t Station::m_widthField = 0;
    Station::Station(const std::string& oneLine)
    {


        std::string sString = "";
        Utilities util = Utilities();
        bool valid = false;
        size_t pos = 0;
        try
        {


            s_name = util.extractToken(oneLine, pos, valid);
            if (s_name.size() > m_widthField)
            {
                m_widthField = s_name.size();
            }
            util.setFieldWidth(m_widthField);
            if (valid == true)
            {
                sString = util.extractToken(oneLine, pos, valid);
                s_nextSerialNum = std::stoi(sString);
                sString = util.extractToken(oneLine, pos, valid);
                s_quantity = std::stoi(sString);
                s_description = util.extractToken(oneLine, pos, valid);
                s_id = id_generator;
                id_generator++;


            
            
            
            }
       
        
        }
        catch (const char* msg)
        {


            std::cout << "Error: " << msg << std::endl;


        }





    }
    const std::string& Station::getItemName() const 
    {


        return s_name;
    
    
    
    }
    size_t Station::getNextSerialNumber() 
    {


        s_nextSerialNum++;
        return s_nextSerialNum - 1;
    
    
    
    }
    size_t Station::getQuantity() const 
    {


        return s_quantity;
    
    
    
    }
    void Station::updateQuantity() 
    {



        s_quantity--;
    
    
    
    }
    void Station::display(std::ostream& os, bool full) const 
    {



        os << std::right;
        os << std::setw(3);
        os << std::setfill('0');
        os << s_id;
        os << " | " << std::left;
        os << std::setw(m_widthField + 1);
        os << std::setfill(' ');
        os << s_name << "| " << std::right << std::setfill('0') << std::setw(6);
        os << s_nextSerialNum << std::setfill(' ') << " | ";
        if (!full)
        {


            os << std::endl;


        }
        else
        {


            os << std::setw(4) << s_quantity << " | " << std::left << s_description << std::endl;
        
        
        
        }
   
    
    
    
    }
}