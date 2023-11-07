
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

void MyClientApplication::toAdmin( FIX::Message& message, const FIX::SessionID& sess) {
    if (FIX::MsgType_Logon == message.getHeader().getField(FIX::FIELD::MsgType)) {
        message.getHeader().setField(FIX::Username(_username));
        message.getHeader().setField(FIX::Password(_userpass));
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
EXCEPT ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
    crack( message, sessionID );
    std::cout << std::endl << "IN: " << message << std::endl;
}

void MyClientApplication::toApp( FIX::Message& message, const FIX::SessionID& sessionID )
EXCEPT( FIX::DoNotSend ) {
    try {
      FIX::PossDupFlag possDupFlag;
      message.getHeader().getField( possDupFlag );
      if ( possDupFlag ) throw FIX::DoNotSend();
    }
    catch ( FIX::FieldNotFound& ) {}

    std::cout << std::endl << "OUT: " << message << std::endl;
}


void MyClientApplication::sendTestRequest44(const FIX::Session& session) {
    FIX44::TestRequest testRequest(FIX::TestReqID("ID"));

    testRequest.getHeader().setField(FIX::FIELD::SenderCompID, "TARGET");
    testRequest.getHeader().setField(FIX::FIELD::TargetCompID, "SENDER");
    testRequest.getHeader().setField( FIX::SendingTime());

    std::cout << "Send new message: TestRequest" << std::endl;
    FIX::Session::sendToTarget(testRequest, session.getSessionID());
}

void MyClientApplication::sendTestMessage(FIX::Session& session) {
    const FIX::ClOrdID clOrdID("342");
    const FIX::Side side(FIX::Side_BUY);
    const FIX::TransactTime transactTime = FIX::UtcTimeStamp::now();
    const FIX::OrdType aOrdType(FIX::OrdType_MARKET);

    FIX44::NewOrderSingle newOrder(clOrdID, side, transactTime, aOrdType);

    newOrder.getHeader().setField(session.getSessionID().getSenderCompID());
    newOrder.getHeader().setField(session.getSessionID().getTargetCompID());
    newOrder.getHeader().setField( FIX::SendingTime() );
    newOrder.getHeader().setField( FIX::MsgSeqNum(seqMessage) );

    std::cout << "Send new message: NewOrderSingle" << std::endl;
    FIX::Session::sendToTarget(newOrder, session.getSessionID());
}
