
#include "Application.h"
#include "quickfix/Session.h"
#include "quickfix/fix44/ExecutionReport.h"

void MyServerApplication::onCreate( const FIX::SessionID& sessionID ) {
    logger.info("The session has been created", LOGGER_PRINT_TO_OUT);
}
void MyServerApplication::onLogon( const FIX::SessionID& sessionID ) {
    logger.info("New onLogon message", LOGGER_PRINT_TO_OUT);
}
void MyServerApplication::onLogout( const FIX::SessionID& sessionID ) {
    logger.info("onLogout message", LOGGER_PRINT_TO_OUT);
}
void MyServerApplication::toAdmin( FIX::Message& message, const FIX::SessionID& sessionID ) {
    logger.info("toAdmin message" + message.toString());
}
void MyServerApplication::toApp( FIX::Message& message,
                         const FIX::SessionID& sessionID ) EXCEPT ( FIX::DoNotSend ) {
    logger.info("toApp message" + message.toString());
}


void MyServerApplication::fromAdmin( const FIX::Message& message, const FIX::SessionID& sessionID )
EXCEPT ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {
    logger.info("fromAdmin message: " + message.toString());
    if (FIX::MsgType_Logon == message.getHeader().getField(FIX::FIELD::MsgType)) {
        verifyLogonUser(message);
    } else if (FIX::MsgType_TestRequest == message.getHeader().getField(FIX::FIELD::MsgType)) {
        logger.info("Test request message ");
        onMessage(message, sessionID);
        replyToTestRequest(sessionID);
    }
}

void MyServerApplication::fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
EXCEPT ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
    logger.info("fromApp message" + message.toString());
    crack( message, sessionID ); }

void MyServerApplication::onMessage( const FIX44::TestRequest& message, const FIX::SessionID& sessionID) {
    logger.info("Received new message: TestRequest. Test reqID: " + message.getField(FIX::FIELD::TestReqID),
                LOGGER_PRINT_TO_OUT);
}

void MyServerApplication::verifyLogonUser(const FIX::Message& message) {
    const auto& fixuser = message.getField(FIX::FIELD::Username);
    const auto& fixpasswd = message.getField(FIX::FIELD::Password);

    if (!isUserRegistered(fixuser, fixpasswd)) {
        logger.warning("The username or password is incorrect!", LOGGER_PRINT_TO_OUT);
        throw FIX::RejectLogon("The username or password is incorrect!");
    }
    logger.info("User " + fixuser + " verified successfully!", LOGGER_PRINT_TO_OUT);
}

void MyServerApplication::replyToTestRequest(const FIX::SessionID& sessionID) {
    FIX44::TestRequest testRequest(FIX::TestReqID("ID"));

    testRequest.getHeader().setField(FIX::FIELD::SenderCompID, "TARGET");
    testRequest.getHeader().setField(FIX::FIELD::TargetCompID, "SENDER");
    testRequest.getHeader().setField( FIX::SendingTime());

    logger.info("Send reply message: TestRequest", LOGGER_PRINT_TO_OUT);
    FIX::Session::sendToTarget(testRequest, sessionID);
}


// User verification emulator
bool MyServerApplication::isUserRegistered(const std::string& username, const std::string& pass) {
    if (_registrated_users.find(username) != _registrated_users.end()) {
        // check pass
        return _registrated_users[username] == pass;
    } else {
        // user not found
        return false;
    }
}
