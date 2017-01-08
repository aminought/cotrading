#include "cqgconnection.h"
#include "cqgclient.h"
#include "cqgprovider.h"
#include <QDebug>


namespace ct {
namespace trading {
namespace provider {
namespace cqg {

std::shared_ptr<provider::QuotesProvider> CqgConnection::connect(const core::Config& config) {
    auto conn_conf = config.get_connection_config();

    auto validate_config = [&conn_conf] () {
        return !conn_conf.empty();
    };

    if(validate_config()) {
        auto user_name = conn_conf.at(core::Value::CONNECTION_CQG_USER_NAME);
        auto password = conn_conf.at(core::Value::CONNECTION_CQG_PASSWORD);
        auto client_id = conn_conf.at(core::Value::CONNECTION_CQG_CLIENT_ID);
        auto account_id = conn_conf.at(core::Value::CONNECTION_CQG_ACCOUNT_ID);

        auto validate_credentials = [&user_name, &password, &client_id, &account_id] () {
            try {
                std::stoi(account_id);
            } catch(std::invalid_argument) {
                return false;
            }
            if(user_name.empty() || password.empty() || client_id.empty() || account_id.empty()) return false;
            return true;
        };

        if(validate_credentials()) {
            std::unique_ptr<CqgClient> client = std::make_unique<CqgClient>(
                                                    std::move(user_name), std::move(password),
                                                    std::move(client_id), std::stoi(account_id));
            this->provider = std::make_shared<CqgProvider>(std::move(client));
            this->provider->logon();
            return this->provider;
        } else {
            qDebug() << "Wrong arguments";
        }
    } else {
        qDebug() << "Empty config";
    }
    return nullptr;
}

std::shared_ptr<QuotesProvider> CqgConnection::get_provider() {
    return this->provider;
}

}
}
}
}
