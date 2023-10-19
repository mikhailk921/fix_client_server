#include <iostream>


#include "client.hpp"
#include "Application.h"
#include "quickfix/Initiator.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"

int main()
{

    std::cout << "test1" << std::endl;

    auto application = MyApplication();

    const std::string confog_path = "client_config.cfg";

    FIX::SessionSettings settings(confog_path);
    FIX::FileStoreFactory storeFactory(settings);
    FIX::ScreenLogFactory logFactory(settings);


    std::unique_ptr<FIX::Initiator> initiator = std::unique_ptr<FIX::Initiator>(
            new FIX::SocketInitiator( application, storeFactory, settings, logFactory ));

    initiator->start();
    auto sessionId = *initiator->getSessions().begin();
    auto session = initiator->getSession(sessionId);
    std::cout << "Start logon " << std::endl;
    session->logon();
    std::cout << "check sent logon " << session->sentLogon() << std::endl;
    std::cout << "initiator isLoggedOn() " << session->isLoggedOn() << std::endl;
//    for (const auto& sessionId : initiator->getSessions()) {
//        auto session = initiator->getSession(sessionId);
//        session->lookupSession(sessionId)->logon();
//     }

    application.run();
    initiator->stop();

}

