#include <iostream>


#include "client.hpp"
#include "Application.h"
#include "quickfix/Initiator.h"
#include "quickfix/SocketInitiator.h"
#include "quickfix/FileStore.h"
#include "quickfix/FileLog.h"

int main() {
    const std::string confog_path = "client_config.cfg";

    FIX::SessionSettings settings(confog_path);
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
    application.run();
    initiator->stop();

}

