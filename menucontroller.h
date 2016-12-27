#ifndef MENUCONTROLLER_H
#define MENUCONTROLLER_H

#include <QObject>
#include "config.h"

enum Provider {
    CQG = 100
};

class MenuController : public QObject {
    Q_OBJECT
public:
    explicit MenuController(QObject *parent = 0);
    MenuController(std::shared_ptr<Config> config): config(config) {}
public slots:
    void connect(Provider provider = Provider::CQG);
private:
    std::shared_ptr<Config> config;
};

#endif // MENUCONTROLLER_H
