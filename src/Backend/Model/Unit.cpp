//
// Created by Ayman Ougri on 5/1/23.
//

#include "Unit.h"
#include "../util.h"
#include <bsoncxx/builder/basic/document.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

Unit::Unit(const std::string& p_number, const std::string& p_fsize)
{
    this->m_fsize = p_fsize;
    this->m_number = p_number;
}

bsoncxx::document::value Unit::toJson()
{
    std::string date = formatDate(std::chrono::system_clock::now());
    return make_document(
            kvp("aptName", this->m_number),
            kvp("filterSize", this->m_fsize),
            kvp("dateOfCreation", date)
    );
}
