//
// Created by Ayman Ougri on 5/1/23.
//


#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/basic/kvp.hpp>
#include <bsoncxx/json.hpp>

#include <string>
#include <map>
#include <iostream>
#include <optional>

#include "util.h"

class MongoDBManager {
public:
    MongoDBManager() {
        std::map<std::string, std::string> env = load_env("../src/Backend/.env");
        try {
            const auto uri = mongocxx::uri{env["MONGO_URI"]};

            mongocxx::options::client client_options;
            const auto api = mongocxx::options::server_api{mongocxx::options::server_api::version::k_version_1};
            (void) client_options.server_api_opts(api);

            this->conn_ = mongocxx::client{uri, client_options};
            this->db_ = conn_["db"];
            this->vlfsrs_ = db_["vlfsrs"];
        } catch (const std::exception &e) {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }

    void insert(bsoncxx::view_or_value<bsoncxx::document::view, bsoncxx::document::value> document) {
        auto res = vlfsrs_.insert_one(document);
        if (res) {
            std::cout << "Inserted " << vlfsrs_.name() << " into " << db_.name() << std::endl;
        }
        assert(res);
    }


    std::optional<std::vector<bsoncxx::document::value>> get_all_docs() {

        auto cursor = vlfsrs_.find({});
        std::vector<bsoncxx::document::value> documents;
        for (auto doc: cursor) {
            (void) documents.emplace_back(doc);
        }

        std::sort(documents.begin(), documents.end(),
                  [](const bsoncxx::document::value &a, const bsoncxx::document::value &b) -> bool {
                      std::string aptNameA = a["aptName"].get_string().value.to_string();
                      std::string aptNameB = b["aptName"].get_string().value.to_string();

                      // Extract the numerical value from the aptName field
                      int numA = std::stoi(aptNameA.substr(aptNameA.find_first_of("0123456789")));
                      int numB = std::stoi(aptNameB.substr(aptNameB.find_first_of("0123456789")));

                      return numA < numB;
                  });

        return documents;


    }

    void ping() {
        const auto ping_cmd = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1));
        (void) this->db_.run_command(ping_cmd.view());
        std::cout << "Pinged!" << std::endl;
    }


    ~MongoDBManager() = default;

private:
    mongocxx::client conn_;
    mongocxx::database db_;
    mongocxx::collection vlfsrs_;


};