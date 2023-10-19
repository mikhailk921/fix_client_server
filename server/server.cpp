
#include "quickfix/FileStore.h"
#include "quickfix/SocketAcceptor.h"
#include "quickfix/Log.h"
#include "quickfix/SessionSettings.h"
#include "Application.h"

#include <string>
#include <iostream>
#include <memory>

void wait(std::unique_ptr<FIX::Acceptor>& acceptor) {
    std::cout << "Type Ctrl-C to quit" << std::endl;
    while(true) {
        FIX::process_sleep(1);
        if (acceptor->isLoggedOn())
            std::cout << "Check loggin: " << acceptor->isLoggedOn() << std::endl  << std::endl;
    }
}

int main( int argc, char** argv ) {
    try {
        const std::string confog_path = "server_config.cfg";

        FIX::SessionSettings settings(confog_path);

        Application serverApplication;
        FIX::FileStoreFactory storeFactory( settings );
        FIX::ScreenLogFactory logFactory( settings );

        auto acceptor = std::unique_ptr<FIX::Acceptor>(
                new FIX::SocketAcceptor ( serverApplication, storeFactory, settings, logFactory ));

        acceptor->start();
        wait(acceptor);
        acceptor->stop();

        return 0;
    }
    catch ( std::exception & e ) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}