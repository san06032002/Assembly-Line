

#ifndef SENECA_STATION_H
#define SENECA_STATION_H


#include <iostream>
namespace seneca
{
    class Station
    {
        int s_id;
        std::string s_name;
        std::string s_description;
        size_t s_nextSerialNum;
        size_t s_quantity;
        static size_t m_widthField;
        static int id_generator;
    public:
        Station(const std::string& oneLine);
        const std::string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}
#endif // !SENECA_STATION_H