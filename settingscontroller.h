#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include "config.h"


class SettingsController: public QObject {
    Q_OBJECT
public:
    explicit SettingsController(QObject* parent = 0);
    SettingsController(std::shared_ptr<Config> config): config(config) {}
public slots:
    void saveConfig(QString user_name, QString password, QString client_id, QString account_id);
private:
    std::shared_ptr<Config> config;
};

#endif // SETTINGS_H
