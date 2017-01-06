#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QString>
#include "config.h"

namespace ct {
namespace core {

class SettingsController: public QObject {
    Q_OBJECT
public:
    explicit SettingsController(QObject* parent = 0);
    explicit SettingsController(std::shared_ptr<Config> config): config(config) {}
public slots:
    void save_config(const QString& user_name, const QString& password, const QString& client_id, const QString& account_id);
    QString load_user_name();
    QString load_password();
    QString load_client_id();
    QString load_account_id();
private:
    QString get(Value value);
    std::shared_ptr<Config> config;
};

}
}

#endif // SETTINGS_H
