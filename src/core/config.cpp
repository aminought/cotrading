#include "config.h"
#include <boost/property_tree/ini_parser.hpp>
#include <QFile>
#include <QString>


namespace ct {
namespace core {

std::string Config::path = "config.ini";

std::map<Value, std::string> Config::value_to_key;

Config::Config() {
    value_to_key[Value::CONNECTION_CQG_USER_NAME] = "Connection.Cqg/user_name";
    value_to_key[Value::CONNECTION_CQG_PASSWORD] = "Connection.Cqg/password";
    value_to_key[Value::CONNECTION_CQG_CLIENT_ID] = "Connection.Cqg/client_id";
    value_to_key[Value::CONNECTION_CQG_ACCOUNT_ID] = "Connection.Cqg/account_id";
}

namespace ptree = boost::property_tree;

void Config::load(const std::string& path) {
    try {
        ptree::ptree pt;
        ptree::ini_parser::read_ini(path, pt);
        for(auto const& pair: value_to_key) {
            auto value = pt.get<std::string>(ptree::ptree::path_type(pair.second, '/'));
            config[pair.first] = value;
        }
    } catch(ptree::ini_parser_error&) {
        QFile file(QString(this->path.data()));
    }
}

void Config::save(const std::string& path) const {
    ptree::ptree pt;
    for(auto const& c: config) {
        pt.put(ptree::ptree::path_type(value_to_key[c.first], '/'), c.second);
    }
    ptree::ini_parser::write_ini(path, pt);
}

void Config::set(const std::map<Value, std::string>& values) {
    for(auto const& v: values) {
        config[v.first] = v.second;
    }
}

void Config::set(Value category, const std::string& value) {
    config[category] = value;
}

std::map<Value, std::string> Config::get_connection_config() const {
    auto conf = std::map<Value, std::string>();
    for(auto const pair: config) {
        if(value_to_key[pair.first].find("Connection") == 0) {
            conf.insert(pair);
        }
    }
    return conf;
}

}
}