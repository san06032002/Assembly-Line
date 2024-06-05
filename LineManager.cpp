#include "LineManager.h"
#include <algorithm>
#include <fstream>
#include "Utilities.h"
namespace seneca {

    LineManager::LineManager(const std::string& file, const std::vector<Workstation*>& stations)
    {


        Utilities util;
        std::string tem;
        std::ifstream ifs(file);
        if (!ifs.is_open())
        {


            throw std::string("Unable to open file.");
        
        
        }
        while (!ifs.eof())
        {


            std::getline(ifs, tem);
            size_t nxtPos = 0;
            bool more = true;
            std::string currSta;
            std::string nxtSta;
            currSta = util.extractToken(tem, nxtPos, more);
            if (more)
            {


                nxtSta = util.extractToken(tem, nxtPos, more);
            
            
            }
            Workstation* currWorkSta;
            Workstation* nxtWorkSta;
            std::for_each(stations.begin(), stations.end(), [&](Workstation* station) 
            {


                if (currSta == station->getItemName())
                {


                    currWorkSta = station;
                
                
                
                }
            
                
                });
            if (!nxtSta.empty()) 
            {


                std::for_each(stations.begin(), stations.end(), [&](Workstation* station) 
                    {


                    if (nxtSta == station->getItemName())
                    {


                        nxtWorkSta = station;
                    
                    
                    }                   
                    
                    
                    });
                currWorkSta->setNextStation(nxtWorkSta);
            
            
            
            }
            
            m_activeLine.push_back(currWorkSta);
        

        
        }
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&](Workstation* station1)
            {


            if (std::none_of(m_activeLine.begin(), m_activeLine.end(), [&](const Workstation* station2) 
                {


                if (station2->getNextStation() != nullptr) 
                {


                    if (station1->getItemName() == station2->getNextStation()->getItemName()) 
                    {



                        return true;
                    }
                        
                }


       
                
                
                return false;
                
                
                
                }))



                m_firstStation = station1;
          
            
            
            });
        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations()
    {




        std::vector<Workstation*> workSta;
        workSta.push_back(m_firstStation);
        while (workSta.back()->getNextStation())
        {



            workSta.push_back(workSta.back()->getNextStation());
        
        
        
        }
       
        
        
        m_activeLine = workSta;
    
    
    
    }

    bool LineManager::run(std::ostream& os)
    
    
    {



        static int counter = 0;
        size_t tOrder = 0;
        os << "Line Manager Iteration: " << ++counter << std::endl;
        if (!g_pending.empty())
        {



            (*m_firstStation) += std::move(g_pending.front());
            g_pending.pop_front();
       
        
        }
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* station)
        {


            station->fill(os);
        
            
            
            
            });

        std::for_each(m_activeLine.begin(), m_activeLine.end(), [](Workstation* station) 
            {


            station->attemptToMoveOrder();
      
            
            });
        tOrder = (g_completed.size() + g_incomplete.size()) == m_cntCustomerOrder;
        return  tOrder;
   
    
    
    }



    void LineManager::display(std::ostream& os) const 
    {


        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](Workstation* workstation) 
            
            {


            workstation->display(os);
            
            
            });
   
    
    
    }
}