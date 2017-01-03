#include <gtest/gtest.h>
#include <QTemporaryFile>
#include "core/config.h"

using ct::core::Config;
using ct::core::Value;

TEST(LOAD, CONFIG_TEST) {
    QTemporaryFile file;
    Config c;
    if(file.open()) {
        std::string data = "[Connection.Cqg]\nuser_name=user\npassword=pass\nclient_id=cid\naccount_id=aid\n";
        file.write(data.data());
        file.close();
    }

    c.load(file.fileName().toStdString());
    auto conf = c.get_connection_config();
    EXPECT_EQ(conf.at(Value::CONNECTION_CQG_USER_NAME), "user");
    EXPECT_EQ(conf.at(Value::CONNECTION_CQG_PASSWORD), "pass");
    EXPECT_EQ(conf.at(Value::CONNECTION_CQG_CLIENT_ID), "cid");
    EXPECT_EQ(conf.at(Value::CONNECTION_CQG_ACCOUNT_ID), "aid");
}

TEST(SAVE, CONFIG_TEST) {
    QTemporaryFile file;
    Config c;
    std::map<Value, std::string> values;
    values[Value::CONNECTION_CQG_USER_NAME] = "user";
    values[Value::CONNECTION_CQG_PASSWORD] = "pass";
    values[Value::CONNECTION_CQG_CLIENT_ID] = "cid";
    values[Value::CONNECTION_CQG_ACCOUNT_ID] = "aid";
    c.set(values);
    if(file.open()) {
        c.save(file.fileName().toStdString());
        auto bytes = file.readAll();
        QString data(bytes);
        EXPECT_EQ(data.toStdString(), "[Connection.Cqg]\nuser_name=user\npassword=pass\nclient_id=cid\naccount_id=aid\n");
    }
}
