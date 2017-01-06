#include "settingscontroller.h"


namespace ct {
namespace core {

SettingsController::SettingsController(QObject*) {

}

void SettingsController::save_config(const QString& user_name, const QString& password,
                                     const QString& client_id, const QString& account_id) {
    config->set(Value::CONNECTION_CQG_USER_NAME, user_name.toStdString());
    config->set(Value::CONNECTION_CQG_PASSWORD, password.toStdString());
    config->set(Value::CONNECTION_CQG_CLIENT_ID, client_id.toStdString());
    config->set(Value::CONNECTION_CQG_ACCOUNT_ID, account_id.toStdString());
    config->save();
}

QString SettingsController::load_user_name() {
    return get(Value::CONNECTION_CQG_USER_NAME);
}

QString SettingsController::load_password() {
    return get(Value::CONNECTION_CQG_PASSWORD);
}

QString SettingsController::load_client_id() {
    return get(Value::CONNECTION_CQG_CLIENT_ID);
}

QString SettingsController::load_account_id() {
    return get(Value::CONNECTION_CQG_ACCOUNT_ID);
}

QString SettingsController::get(Value value) {
    return config->get_connection_config().at(value).data();
}

}
}
