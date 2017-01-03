#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <boost/optional.hpp>
#include "settingscontroller.h"
#include "menucontroller.h"
#include "config.h"
#include "providerconnection.h"
#include "quotesprovider.h"
#include "chartcontroller.h"
#include "coopconnection.h"
#include "coopserver.h"
#include "coopclient.h"

boost::optional<QObject*> find_object(QQmlApplicationEngine& engine, QString name);

int main(int argc, char *argv[]) {
    // QtCharts depends on QtWidgets, so need to instantiate QApplication instead of QGuiApplication
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    std::shared_ptr<Config> config = std::make_shared<Config>();
    config->load();

    std::shared_ptr<ProviderConnection> provider_connection;

    auto chart = find_object(engine, "ctChart");
    if(!chart.is_initialized()) {
        qDebug() << "Chart not found";
        return EXIT_FAILURE;
    }
    auto chart_controller = std::make_shared<ChartController>(nullptr, chart.get());

    std::unique_ptr<CoopServer> coop_server = std::make_unique<CoopServer>();
    std::unique_ptr<CoopClient> coop_client = std::make_unique<CoopClient>();
    std::shared_ptr<CoopConnection> coop_connection =
        std::make_shared<CoopConnection>(std::move(coop_server), std::move(coop_client), chart_controller);
    coop_connection->init_client();

    MenuController menu_controller(config, provider_connection, chart_controller, coop_connection);
    SettingsController settings_controller(config);

    engine.rootContext()->setContextProperty("_menu_controller", &menu_controller);
    engine.rootContext()->setContextProperty("_settings_controller", &settings_controller);
    engine.rootContext()->setContextProperty("_chart_controller", &*chart_controller);

    return app.exec();
}

boost::optional<QObject*> find_object(QQmlApplicationEngine& engine, QString name) {
    auto objects = engine.rootObjects();
    for(auto object: objects) {
        auto child = object->findChild<QObject*>(name);
        if(child != nullptr) {
            return child;
        }
    }
    return {};
}
