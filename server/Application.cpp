
#include "Application.h"
#include "quickfix/Session.h"

#include "quickfix/fix44/ExecutionReport.h"

void MyServerApplication::onCreate( const FIX::SessionID& sessionID ) {
    std::cout << "The session has been created" << std::endl;
}
void MyServerApplication::onLogon( const FIX::SessionID& sessionID ) {
    std::cout << "!New onLogon message" << std::endl;
}
void MyServerApplication::onLogout( const FIX::SessionID& sessionID ) {
    std::cout << "onLogout message" << std::endl;
}
void MyServerApplication::toAdmin( FIX::Message& message,
                           const FIX::SessionID& sessionID ) {}
void MyServerApplication::toApp( FIX::Message& message,
                         const FIX::SessionID& sessionID ) throw ( FIX::DoNotSend ) {}


void MyServerApplication::fromAdmin( const FIX::Message& message,
                             const FIX::SessionID& sessionID )
throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {
    if (FIX::MsgType_Logon == message.getHeader().getField(FIX::FIELD::MsgType)) {
        auto fixuser = message.getField(FIX::FIELD::Username);
        auto fixpasswd = message.getField(FIX::FIELD::Password);

        if (!isUserRegistered(fixuser, fixpasswd)) {
            throw FIX::RejectLogon("The username or password is incorrect!");
        }
        std::cout << "User " << fixuser << " verified successfully!" << std::endl;
    }
}

void MyServerApplication::fromApp( const FIX::Message& message,
                           const FIX::SessionID& sessionID )
throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
    crack( message, sessionID ); }


// User verification emulation
bool MyServerApplication::isUserRegistered(std::string& username, std::string& pass) {
    if (_registrated_users.find(username) != _registrated_users.end()) {
        // check pass
        return _registrated_users[username] == pass;
    } else {
        // user not found
        return false;
    }
}
