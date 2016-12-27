#include "settingscontroller.h"
#include <iostream>
#include "cqgclient.h"
#include "cqgprovider.h"

SettingsController::SettingsController(QObject*) {

}

void SettingsController::saveConfig(QString user_name, QString password, QString client_id, QString account_id) {
    config->set(Value::CONNECTION_CQG_USER_NAME, user_name.toStdString());
    config->set(Value::CONNECTION_CQG_PASSWORD, password.toStdString());
    config->set(Value::CONNECTION_CQG_CLIENT_ID, client_id.toStdString());
    config->set(Value::CONNECTION_CQG_ACCOUNT_ID, account_id.toStdString());
    config->save();
}
