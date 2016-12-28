#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "settingscontroller.h"
#include "menucontroller.h"
#include "config.h"

int main(int argc, char *argv[]) {
    // QtCharts depends on QtWidgets, so need to instantiate QApplication instead of QGuiApplication
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    std::shared_ptr<Config> config = std::make_shared<Config>();
    config->load();

    MenuController menu_controller(config);
    SettingsController settings(config);

    engine.rootContext()->setContextProperty("_menu_controller", &menu_controller);
    engine.rootContext()->setContextProperty("_settings_controller", &settings);

    return app.exec();
}
