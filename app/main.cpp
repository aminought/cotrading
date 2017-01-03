#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>
#include <boost/optional.hpp>
#include "core/chartcontroller.h"
#include "core/config.h"
#include "core/menucontroller.h"
#include "core/settingscontroller.h"
#include "trading/provider/providerconnection.h"
#include "coop/coopclient.h"
#include "coop/coopserver.h"

boost::optional<QObject*> find_object(QQmlApplicationEngine& engine, QString name);

int main(int argc, char *argv[]) {
    // QtCharts depends on QtWidgets, so need to instantiate QApplication instead of QGuiApplication
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));

    std::shared_ptr<ct::core::Config> config = std::make_shared<ct::core::Config>();
    config->load();

    std::shared_ptr<ct::trading::provider::ProviderConnection> provider_connection;

    auto chart = find_object(engine, "ctChart");
    if(!chart.is_initialized()) {
        qDebug() << "Chart not found";
        return EXIT_FAILURE;
    }
    auto chart_controller = std::make_shared<ct::core::ChartController>(nullptr, chart.get());

    std::unique_ptr<ct::coop::CoopServer> coop_server = std::make_unique<ct::coop::CoopServer>();
    std::unique_ptr<ct::coop::CoopClient> coop_client = std::make_unique<ct::coop::CoopClient>();
    std::shared_ptr<ct::coop::CoopConnection> coop_connection =
        std::make_shared<ct::coop::CoopConnection>(std::move(coop_server), std::move(coop_client), chart_controller);
    coop_connection->init_client();

    ct::core::MenuController menu_controller(config, provider_connection, chart_controller, coop_connection);
    ct::core::SettingsController settings_controller(config);

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
