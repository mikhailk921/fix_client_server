
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

FIX::Message createAdminMessage(int sequence) {
    FIX44::TestRequest msg(FIX::TestReqID("ID"));

    msg.getHeader().setField(FIX::FIELD::SenderCompID, "TARGET");
    msg.getHeader().setField(FIX::FIELD::TargetCompID, "SENDER");
    msg.getHeader().setField(FIX::FIELD::MsgSeqNum, FIX::IntConvertor::convert(sequence));
    // msg.getHeader().setField(FIX::FIELD::SendingTime, FIX::time_localtime(FIX::time_gmtime("3"))) .setUtcTimeStamp(, LocalDateTime.now(ZoneOffset.UTC));
    return msg;
}

FIX44::TestRequest MyClientApplication::prepareTestRequest44()
{
    FIX44::TestRequest testRequest = createAdminMessage(2);
    return testRequest;
}
