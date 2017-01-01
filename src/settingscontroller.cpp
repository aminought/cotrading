#include "settingscontroller.h"
#include <iostream>
#include "cqgclient.h"
#include "cqgprovider.h"

SettingsController::SettingsController(QObject*) {

}

void SettingsController::save_config(QString user_name, QString password, QString client_id, QString account_id) {
    config->set(Value::CONNECTION_CQG_USER_NAME, user_name.toStdString());
    config->set(Value::CONNECTION_CQG_PASSWORD, password.toStdString());
    config->set(Value::CONNECTION_CQG_CLIENT_ID, client_id.toStdString());
    config->set(Value::CONNECTION_CQG_ACCOUNT_ID, account_id.toStdString());
    config->save();
}

QString SettingsController::load_user_name() {
    return config->get_connection_config()->at(Value::CONNECTION_CQG_USER_NAME).data();
}

QString SettingsController::load_password() {
    return config->get_connection_config()->at(Value::CONNECTION_CQG_PASSWORD).data();
}

QString SettingsController::load_client_id() {
    return config->get_connection_config()->at(Value::CONNECTION_CQG_CLIENT_ID).data();
}

QString SettingsController::load_account_id() {
    return config->get_connection_config()->at(Value::CONNECTION_CQG_ACCOUNT_ID).data();
}
