#include "menucontroller.h"
#include "cqgprovider.h"
#include "cqgclient.h"


void MenuController::connect(Provider provider) {
    if(provider == Provider::CQG) {
        auto conn_conf = config->get_connection_config();
        std::unique_ptr<CqgClient> client = std::make_unique<CqgClient>(
                                                conn_conf->operator[](Value::CONNECTION_CQG_USER_NAME),
                                                conn_conf->operator[](Value::CONNECTION_CQG_PASSWORD),
                                                conn_conf->operator[](Value::CONNECTION_CQG_CLIENT_ID),
                                                std::stoi(conn_conf->operator[](Value::CONNECTION_CQG_ACCOUNT_ID)));
        CqgProvider cqg(std::move(client));
        cqg.logon();
    }
}
