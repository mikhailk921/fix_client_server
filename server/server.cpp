#include "quickfix/FileStore.h"
#include "quickfix/SocketAcceptor.h"
#include "quickfix/Log.h"
#include "quickfix/SessionSettings.h"
#include "Application.h"

#include <string>
#include <iostream>
#include <memory>

void wait([[maybe_unused]] std::unique_ptr<FIX::Acceptor>& acceptor) {
    std::cout << "The server was started" << std::endl;
    while(true) {
        FIX::process_sleep(1);
    }
}

int main(int argc, char** argv) {
    try {
        std::string config_path;
        if ( argc > 2 ) {
            throw std::runtime_error("Unexpected number of arguments. "
                                     "Expecting one argument, received: " + std::to_string(argc - 1));
        } else if ( argc == 2 ) {
            std::cout << "Server config file path: " << argv[ 1 ] << std::endl;
            config_path = argv[ 1 ];
        } else {
            std::cout << "Using default config file" << std::endl;
            config_path = "server_config.cfg";
        }

        FIX::SessionSettings settings(config_path);

        MyServerApplication serverApplication;
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