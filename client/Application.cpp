
#include "Application.h"

void MyApplication::onCreate( const FIX::SessionID& sessionId) {
    std::cout << std::endl << "Session created - " << sessionId << std::endl;
}

void MyApplication::onLogon(const FIX::SessionID& sessionId) {
    std::cout << std::endl << "Logon - " << sessionId << std::endl;
}

void MyApplication::onLogout( const FIX::SessionID& sessionId ) {
    std::cout << std::endl << "Logout - " << sessionId << std::endl;
}

void queryEnterOrder() {};
void queryCancelOrder() {};
void queryReplaceOrder() {};
void queryMarketDataRequest() {};

void MyApplication::toAdmin( FIX::Message& message, const FIX::SessionID& ) {
    std::cout << "Message to Admin: " << std::endl;
    if (message.getHeader().getField(35) == "A") {
        message.getHeader().setField(554, "password");
    }
}

void MyApplication::run() {
    while (true) {
        try {


            char action = queryAction();

            if ( action == '1' )
                queryEnterOrder();
            else if ( action == '2' )
                queryCancelOrder();
            else if ( action == '3' )
                queryReplaceOrder();
            else if ( action == '4' )
                queryMarketDataRequest();
            else if ( action == '5' )
                break;
        }
        catch ( std::exception & e )
        {
            std::cout << "Message Not Sent: " << e.what();
        }
    }
}

char MyApplication::queryAction() {
    char value;
    std::cout << std::endl
              << "1) onLogon" << std::endl
              << "2) onLogout" << std::endl
              << "3) Quit" << std::endl
              << "Action: ";
    std::cin >> value;
    std::cout << "Input: " << value << std::endl;
    switch ( value ) {
        case '1':
        case '2':
        case '3':
            return value;
        default: throw std::exception();
    }
}

void MyApplication::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )  throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
    crack( message, sessionID );
    std::cout << std::endl << "IN: " << message << std::endl;
}

void MyApplication::toApp( FIX::Message& message, const FIX::SessionID& sessionID ) throw( FIX::DoNotSend ) {
    try {
      FIX::PossDupFlag possDupFlag;
      message.getHeader().getField( possDupFlag );
      if ( possDupFlag ) throw FIX::DoNotSend();
    }
    catch ( FIX::FieldNotFound& ) {}

    std::cout << std::endl << "OUT: " << message << std::endl;
}

void MyApplication::onMessage( const FIX44::Logon& message, const FIX::SessionID& ) {

}
