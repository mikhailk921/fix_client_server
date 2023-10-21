
#include "Application.h"
#include "quickfix/Session.h"

#include "quickfix/fix44/ExecutionReport.h"

void MyServerApplication::onCreate( const FIX::SessionID& sessionID ) {
    logger.info("The session has been created", true);
}
void MyServerApplication::onLogon( const FIX::SessionID& sessionID ) {
    logger.info("New onLogon message", true);
}
void MyServerApplication::onLogout( const FIX::SessionID& sessionID ) {
    logger.info("onLogout message", true);
}
void MyServerApplication::toAdmin( FIX::Message& message,
                           const FIX::SessionID& sessionID ) {
    logger.info("toAdmin message" + message.toString());
}
void MyServerApplication::toApp( FIX::Message& message,
                         const FIX::SessionID& sessionID ) throw ( FIX::DoNotSend ) {
    logger.info("toApp message" + message.toString());
}


void MyServerApplication::fromAdmin( const FIX::Message& message,
                             const FIX::SessionID& sessionID )
throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {
    logger.info("fromAdmin message: " + message.toString());
    if (FIX::MsgType_Logon == message.getHeader().getField(FIX::FIELD::MsgType)) {
        auto fixuser = message.getField(FIX::FIELD::Username);
        auto fixpasswd = message.getField(FIX::FIELD::Password);

        if (!isUserRegistered(fixuser, fixpasswd)) {
            logger.warning("The username or password is incorrect!", true);
            throw FIX::RejectLogon("The username or password is incorrect!");
        }
        logger.info("User " + fixuser + " verified successfully!", true);
    }
    if (FIX::MsgType_TestRequest == message.getHeader().getField(FIX::FIELD::MsgType)) {
        logger.info("!Test request message ");
        onMessage(message, sessionID);
        replyToTestRequest(sessionID);
    }
}

void MyServerApplication::fromApp( const FIX::Message& message,
                           const FIX::SessionID& sessionID )
throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
    logger.info("fromApp message" + message.toString());
    crack( message, sessionID ); }

void MyServerApplication::onMessage( const FIX44::TestRequest& message, const FIX::SessionID& sessionID) {

    logger.info("Received new message: TestRequest. Test reqID: " + message.getField(FIX::FIELD::TestReqID),
                true);
}

void MyServerApplication::replyToTestRequest(const FIX::SessionID& sessionID) {
    FIX44::TestRequest testRequest(FIX::TestReqID("ID"));

    testRequest.getHeader().setField(FIX::FIELD::SenderCompID, "TARGET");
    testRequest.getHeader().setField(FIX::FIELD::TargetCompID, "SENDER");
    testRequest.getHeader().setField( FIX::SendingTime());

    logger.info("Send reply message: TestRequest", true);
    FIX::Session::sendToTarget(testRequest, sessionID);
}


// User verification emulator
bool MyServerApplication::isUserRegistered(std::string& username, std::string& pass) {
    if (_registrated_users.find(username) != _registrated_users.end()) {
        // check pass
        return _registrated_users[username] == pass;
    } else {
        // user not found
        return false;
    }
}
