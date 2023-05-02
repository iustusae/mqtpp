//
// Created by Ayman Ougri on 5/1/23.
//

#ifndef MQT_UNIT_H
#define MQT_UNIT_H

#include <string>
#include <bsoncxx/document/value.hpp>

class Unit {
public:
    std::string m_number;
    std::string m_fsize;

    Unit(const std::string& p_number, const std::string& p_fsize);
    bsoncxx::document::value toJson();
private:
    std::string m_id;
};

#endif //MQT_UNIT_H
