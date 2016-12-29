#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include "settingscontroller.h"
#include "menucontroller.h"
#include "config.h"
#include "providerconnection.h"
#include "quotesprovider.h"

int main(int argc, char *argv[]) {
    // QtCharts depends on QtWidgets, so need to instantiate QApplication instead of QGuiApplication
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    std::shared_ptr<Config> config = std::make_shared<Config>();
    config->load();

    std::shared_ptr<ProviderConnection> provider_connection(nullptr);

    MenuController menu_controller(config, provider_connection);
    SettingsController settings_controller(config);

    engine.rootContext()->setContextProperty("_menu_controller", &menu_controller);
    engine.rootContext()->setContextProperty("_settings_controller", &settings_controller);

    return app.exec();
}
