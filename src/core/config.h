#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>
#include <boost/property_tree/ptree.hpp>

namespace ct {
namespace core {

enum class Value {
    CONNECTION_CQG_USER_NAME,
    CONNECTION_CQG_PASSWORD,
    CONNECTION_CQG_CLIENT_ID,
    CONNECTION_CQG_ACCOUNT_ID
};

class Config {
public:
    Config();
    void load(const std::string& path = Config::path);
    void save(const std::string& path = Config::path) const;
    void set(const std::map<Value, std::string>& values);
    void set(Value category, const std::string& value);
    std::map<Value, std::string> get_connection_config() const;
private:
    static std::string path;
    static std::map<Value, std::string> value_to_key;
    std::map<Value, std::string> config;
};

}
}

#endif // CONFIG_H
