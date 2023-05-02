#include <iostream>
#include <string>
#include <map>
#include <mongocxx/v_noabi/mongocxx/instance.hpp>
#include <mongocxx/v_noabi/mongocxx/client.hpp>
#include <bsoncxx/v_noabi/bsoncxx/json.hpp>

#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/uri.hpp>


#include "Model/Unit.h"
#include "util.h"
#include "MongoDBManager.cpp"

int main()
{


    MongoDBManager manager = MongoDBManager();
   auto vec = manager.get_all_docs();
   for(const auto& view : *vec)
   {
       try
       {
           std::string id = view["_id"].get_oid().value.to_string();
           std::string aptName = view["aptName"].get_utf8().value.to_string();
           std::string filterSize = view["filterSize"].get_utf8().value.to_string();
           int v = view["__v"].get_int32().value;

           // Print the extracted field values
           std::cout << "id: " << id << std::endl;
           std::cout << "aptName: " << aptName << std::endl;
           std::cout << "filterSize: " << filterSize << std::endl;
           std::cout << "__v: " << v <<'\n\n\n\n' << std::endl;
       }
       catch (const std::exception &e)
       {
           continue;
       }


   }

    return 0;
}
