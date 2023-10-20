
#include "Application.h"

void MyClientApplication::onCreate( const FIX::SessionID& sessionId) {
    std::cout << std::endl << "Session created - " << sessionId << std::endl;
}

void MyClientApplication::onLogon(const FIX::SessionID& sessionId) {
    std::cout << std::endl << "Logon - " << sessionId << std::endl;
}

void MyClientApplication::onLogout( const FIX::SessionID& sessionId ) {
    std::cout << std::endl << "Logout - " << sessionId << std::endl;
}

void MyClientApplication::toAdmin( FIX::Message& message, const FIX::SessionID& ) {
    if (FIX::MsgType_Logon == message.getHeader().getField(FIX::FIELD::MsgType)) {
        message.getHeader().setField(FIX::Username("admin"));
        message.getHeader().setField(FIX::Password("admin_passd"));
        std::cout << "Logon message: " << message.toString() << std::endl;
    }
}

void MyClientApplication::run() {
    while (true) {
        try {
            char action = queryAction();
            if (action == 'q')
                break;
        } catch ( std::exception & e ) {
            std::cout << "Exception: " << e.what();
        }
    }
}

char MyClientApplication::queryAction() {
    char value;
    std::cout << std::endl
              << "q) quit" << std::endl
              << "Action: ";
    std::cin >> value;
    std::cout << "Input: " << value << std::endl;
    if ( value == 'q') {
        return value;
    } else {
        throw std::exception();
    }
}

void MyClientApplication::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
    crack( message, sessionID );
    std::cout << std::endl << "IN: " << message << std::endl;
}

void MyClientApplication::toApp( FIX::Message& message, const FIX::SessionID& sessionID )
throw( FIX::DoNotSend ) {
    try {
      FIX::PossDupFlag possDupFlag;
      message.getHeader().getField( possDupFlag );
      if ( possDupFlag ) throw FIX::DoNotSend();
    }
    catch ( FIX::FieldNotFound& ) {}

    std::cout << std::endl << "OUT: " << message << std::endl;
}
