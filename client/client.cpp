#include "Application.h"
#include "quickfix/Initiator.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"

#include <iostream>

void wait() {
    while(true) {
        FIX::process_sleep(1);
    }
}

int main(int argc, char** argv) {
    std::string config_path;
    if ( argc > 2 ) {
        throw std::runtime_error("Unexpected number of arguments. "
                                 "Expecting one argument, received: " + std::to_string(argc - 1));
    } else if ( argc == 2 ) {
        std::cout << "Client config file path: " << argv[ 1 ] << std::endl;
        config_path = argv[ 1 ];
    } else {
        std::cout << "Using default config file" << std::endl;
        config_path = "client_config.cfg";
    }

    FIX::SessionSettings settings(config_path);
    FIX::FileStoreFactory storeFactory(settings);
    FIX::ScreenLogFactory logFactory(settings);

    auto username = settings.get().getString("Username");
    auto pass = settings.get().getString("Password");

    std::cout << " username: " << username << std::endl;
    std::cout << " pass: " << pass << std::endl;

    auto application = MyClientApplication(username, pass);

    std::unique_ptr<FIX::Initiator> initiator = std::unique_ptr<FIX::Initiator>(
            new FIX::SocketInitiator( application, storeFactory, settings, logFactory ));

    // Start client
    initiator->start();

    auto sessionId = *initiator->getSessions().begin();
    while(initiator->getSession(sessionId) == nullptr) {
        FIX::process_sleep(1);
    }
    std::cout << "Session successfully connected!" << std::endl;
    auto session = initiator->getSession(sessionId);
    while(!session->isLoggedOn()) {
        FIX::process_sleep(1);
        std::cout << "Waiting Logon" << std::endl;
    }
    application.sendTestRequest44(*session);
    wait();
    initiator->stop();
}
