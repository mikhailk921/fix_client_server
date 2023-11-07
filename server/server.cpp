#include "quickfix/FileStore.h"
#include "quickfix/SocketAcceptor.h"
#include "quickfix/Log.h"
#include "quickfix/SessionSettings.h"
#include "Application.h"

#include <string>
#include <iostream>
#include <memory>
#include <csignal>

std::atomic<bool> quit(false);

void signal_handler(int) {
    std::cout << "Exit from server" << std::endl;
    quit.store(true);
}

void wait() {
    std::cout << "The server was started" << std::endl;
    while(!quit.load()) {
        FIX::process_sleep(1);
    }
}

int main(int argc, char** argv) {
    struct sigaction sa = {};
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = signal_handler;
    sigfillset(&sa.sa_mask);
    signal(SIGINT, &signal_handler);
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
        wait();
        acceptor->stop();

        return 0;
    }
    catch ( std::exception & e ) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}