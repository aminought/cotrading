#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "settingscontroller.h"
#include "menucontroller.h"
#include "config.h"
#include "providerconnection.h"
#include "quotesprovider.h"
#include "chartcontroller.h"
#include "coopconnection.h"
#include "coopserver.h"
#include "coopclient.h"
#include <QDebug>

QObject* find_chart(QQmlApplicationEngine& engine);

int main(int argc, char *argv[]) {
    // QtCharts depends on QtWidgets, so need to instantiate QApplication instead of QGuiApplication
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    std::shared_ptr<Config> config = std::make_shared<Config>();
    config->load();

    std::shared_ptr<ProviderConnection> provider_connection;
    auto chart_controller = new ChartController();

    auto chart = find_chart(engine);

    std::unique_ptr<CoopServer> coop_server = std::make_unique<CoopServer>();
    std::unique_ptr<CoopClient> coop_client = std::make_unique<CoopClient>(chart);
    std::shared_ptr<CoopConnection> coop_connection =
        std::make_shared<CoopConnection>(std::move(coop_server), std::move(coop_client));

    MenuController menu_controller(config, provider_connection, chart_controller, coop_connection);
    SettingsController settings_controller(config);

    engine.rootContext()->setContextProperty("_menu_controller", &menu_controller);
    engine.rootContext()->setContextProperty("_settings_controller", &settings_controller);
    engine.rootContext()->setContextProperty("_chart_controller", chart_controller);

    auto result_code = app.exec();

    delete chart_controller;

    return result_code;
}

QObject* find_chart(QQmlApplicationEngine& engine) {
    auto objects = engine.rootObjects();
    for(auto object: objects) {
        auto child = object->findChild<QObject*>("ctChart");
        if(child != nullptr) {
            return child;
        }
    }
    return nullptr;
}
