#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "settingscontroller.h"
#include "menucontroller.h"
#include "config.h"
#include "providerconnection.h"
#include "quotesprovider.h"
#include "chartcontroller.h"

int main(int argc, char *argv[]) {
    // QtCharts depends on QtWidgets, so need to instantiate QApplication instead of QGuiApplication
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    std::shared_ptr<Config> config = std::make_shared<Config>();
    config->load();

    std::shared_ptr<ProviderConnection> provider_connection;
    auto chart_controller = new ChartController();

    MenuController menu_controller(config, provider_connection, chart_controller);
    SettingsController settings_controller(config);

    engine.rootContext()->setContextProperty("_menu_controller", &menu_controller);
    engine.rootContext()->setContextProperty("_settings_controller", &settings_controller);
    engine.rootContext()->setContextProperty("_chart_controller", chart_controller);

    auto result_code = app.exec();

    delete chart_controller;

    return result_code;
}
