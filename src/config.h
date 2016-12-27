#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>

enum class Value {
    CONNECTION_CQG_USER_NAME,
    CONNECTION_CQG_PASSWORD,
    CONNECTION_CQG_CLIENT_ID,
    CONNECTION_CQG_ACCOUNT_ID
};

class Config {
public:
    Config();
    void load(std::string path = Config::path);
    void save(std::string path = Config::path);
    void set(std::map<Value, std::string> values);
    void set(Value category, std::string value);
    std::unique_ptr<std::map<Value, std::string> > get_connection_config();
private:
    static std::string path;
    static std::map<Value, std::string>  value_to_key;
    std::map<Value, std::string> config;

    void put_value(Value value, boost::property_tree::ptree pt);
};

#endif // CONFIG_H
