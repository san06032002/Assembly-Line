#ifndef SENECA_WORKSTATION_H
#define SENECA_WORKSTATION_H
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"
#include <deque>
namespace seneca {
    extern std::deque<CustomerOrder> g_pending;
    extern std::deque<CustomerOrder> g_completed;
    extern std::deque<CustomerOrder> g_incomplete;
    class Workstation :public Station {
        std::deque<CustomerOrder>m_orders{};
        Workstation* m_pNextStation{ nullptr };
    public:
        Workstation(const std::string src);
        void fill(std::ostream& os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation* station);
        Workstation* getNextStation() const;
        void display(std::ostream& os) const;
        Workstation& operator+=(CustomerOrder&& newOrder);
        Workstation(const Workstation& src) = delete;
        Workstation(Workstation&& src) = delete;
        Workstation& operator=(const Workstation& src) = delete;
        Workstation& operator=(Workstation&& src) = delete;
        ~Workstation() {}
};
}


#endif // !SENECA_WORKSTATION_H
