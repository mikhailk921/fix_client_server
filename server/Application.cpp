
#include "Application.h"
#include "quickfix/Session.h"

#include "quickfix/fix44/ExecutionReport.h"

void Application::onCreate( const FIX::SessionID& sessionID ) {
    std::cout << "The session has been created" << std::endl;
}
void Application::onLogon( const FIX::SessionID& sessionID ) {
    std::cout << "New onLogon message" << std::endl;
}
void Application::onLogout( const FIX::SessionID& sessionID ) {
    std::cout << "onLogout message" << std::endl;
}
void Application::toAdmin( FIX::Message& message,
                           const FIX::SessionID& sessionID ) {}
void Application::toApp( FIX::Message& message,
                         const FIX::SessionID& sessionID ) throw ( FIX::DoNotSend ) {}

void Application::fromAdmin( const FIX::Message& message,
                             const FIX::SessionID& sessionID )
throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {
    if (FIX::MsgType_Logon == message.getHeader().getField(FIX::FIELD::MsgType)) {
        FIX::Password fixpasswd = message.getField(FIX::FIELD::Password);
        FIX::Username fixuser = message.getField(FIX::FIELD::Username);
        std::cout << "USER: " << fixuser << std::endl;
        std::cout << "PASS: " << fixpasswd << std::endl;
        if (fixuser != "admin" || fixpasswd != "admin_pass") {
            throw FIX::RejectLogon("The user or password is incorrect!");
        }
    }
}

void Application::fromApp( const FIX::Message& message,
                           const FIX::SessionID& sessionID )
throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
    crack( message, sessionID ); }
