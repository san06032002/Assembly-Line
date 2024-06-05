#include "CustomerOrder.h"
#include "Utilities.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
namespace seneca {
    size_t CustomerOrder::m_widthField = 0;

    CustomerOrder::CustomerOrder(const std::string& str)
    {


        Utilities util{};
        size_t pos = 0;
        bool more = true;

        m_name = util.extractToken(str, pos, more);
        m_product = util.extractToken(str, pos, more);
        m_cntItem = std::count(str.begin(), str.end(), util.getDelimiter()) - 1;
        if (m_cntItem == 0) 
        {


            return;
        
        
        }
        m_lstItem = new Item * [m_cntItem];
        for (size_t i = 0; i < m_cntItem; i++)
        {


            m_lstItem[i] = new Item(util.extractToken(str, pos, more));
            if (util.getFieldWidth() > m_widthField)
            {


                m_widthField = util.getFieldWidth();
    
            
            }         
        
        
        }
    
    
    
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& src) 
    {


        throw std::string("ERROR!");
    
    
    
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& src) noexcept 
    {


        *this = std::move(src);
    
    
    
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& src) noexcept 
    {




        if (this != &src)
        {





           for (size_t i = 0; i < m_cntItem; i++) 
           {




              if (m_lstItem[i] != nullptr) 
              
              {




                       
                        delete m_lstItem[i];
              
              
              
              
              }
           
           
           
           
           }
            delete[] m_lstItem;
            m_name = src.m_name;
            m_product = src.m_product;
            m_cntItem = src.m_cntItem;
            m_lstItem = src.m_lstItem;
           
            
            src.m_name = "";
            src.m_product = "";
            src.m_cntItem = 0;
            src.m_lstItem = nullptr;
        
        
        
        }
       
        
        return *this;
   
    
    
    
    }

    CustomerOrder::~CustomerOrder()
    {



        for (size_t i = 0; i < m_cntItem; i++)
        {


            delete m_lstItem[i];
        
        
        }
    
        
        delete[] m_lstItem;
    
    
    
    }

    bool CustomerOrder::isOrderFilled() const 
    {


        for (size_t i = 0; i < m_cntItem; i++)
        {


            if (!m_lstItem[i]->m_isFilled) 
            
            {



                return false;
            
            
            
            
            }    
    
        } 
        return true;
    
    
    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const 
    {


        for (size_t i = 0; i < m_cntItem; i++) 
        {



            if ((!m_lstItem[i]->m_isFilled) && (m_lstItem[i]->m_itemName == itemName))
            {


                return false;
            
            
            
            }
        
        
        
        }
        return true;
    
    
    
    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os) 
    {



        for (size_t i = 0; i < m_cntItem; i++) 

        {
            
            
            if (station.getItemName() == m_lstItem[i]->m_itemName && !m_lstItem[i]->m_isFilled)
            {



                if (station.getQuantity() > 0)
                {



                    m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();
                    m_lstItem[i]->m_isFilled = true;
                    station.updateQuantity();
                    os << "    Filled " << m_name;
                    os << ", " << m_product;
                    os << " [" << m_lstItem[i]->m_itemName << "]";
                    os << std::endl;
                    break;
                
                
                }
                else 
                {


                    os << "    Unable to fill ";
                    os << m_name << ", ";
                    os << m_product;
                    os << " [" << m_lstItem[i]->m_itemName;
                    os << "]" << std::endl;
                
                
                }
            
            
            }
        
        
        }
    }

    void CustomerOrder::display(std::ostream& os) const 
    {


        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0; i < m_cntItem; i++)
        {


            os << "[";
            os << std::setfill('0');
            os << std::setw(6);
            os << std::right << m_lstItem[i]->m_serialNumber << "] ";

            os << std::left << std::setfill(' ');
            os << std::setw(m_widthField) << m_lstItem[i]->m_itemName << " - ";
            os << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED");
            os << std::endl;
     
        
        }
   
    
    }




}