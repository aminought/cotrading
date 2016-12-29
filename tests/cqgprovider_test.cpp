#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cqgprovider.h"
#include "cqgclient.h"
#include <QFile>
#include <QString>
#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

class MockClient: public CqgClient {
public:
    MOCK_CONST_METHOD0(get_user_name, std::string());
    MOCK_CONST_METHOD0(get_password, std::string());
    MOCK_CONST_METHOD0(get_client_id, std::string());
    MOCK_METHOD0(connect, void());
    MOCK_METHOD1(send_and_receive, std::string(std::string));
};

using ::testing::Return;
using ::testing::_;

TEST(LOG0N, CQGPROVIDER_TEST) {
    auto client = std::make_shared<MockClient>();

    QFile file(":/logon_answer.txt");
    std::string answer;
    if(file.open(QIODevice::ReadOnly)) {
        auto bytes = file.readAll();
        auto str = bytes.toStdString();
        answer.append(str);
    }

    EXPECT_CALL(*client.get(), get_user_name()).WillOnce(Return("user"));
    EXPECT_CALL(*client.get(), get_password()).WillOnce(Return("password"));
    EXPECT_CALL(*client.get(), get_client_id()).WillRepeatedly(Return("cid"));
    EXPECT_CALL(*client.get(), send_and_receive(_)).WillOnce(Return(answer));

    auto provider = CqgProvider(client);
    provider.logon();

    auto session = client->get_session().lock();
    EXPECT_EQ("gJD9KRdT+g0gmtxNAefd0BeREd8dS5tbddeBJt/zi4I", session->get_token());
    EXPECT_EQ(boost::posix_time::ptime(boost::posix_time::time_from_string("2016-12-24 02:31:51")),
              session->get_base_time());
}
