
#pragma once

#include <map>

#include "logger.h"

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Utility.h"
#include "quickfix/Mutex.h"

#include "quickfix/fix44/TestRequest.h"

class MyServerApplication: public FIX::Application, public FIX::MessageCracker {
public:
    MyServerApplication(): logger(Logger("Server logger", LogLevel::Info)) {};

    // Application overloads
    void onCreate( const FIX::SessionID& ) override;
    void onLogon( const FIX::SessionID& sessionID ) override;
    void onLogout( const FIX::SessionID& sessionID ) override;
    void toAdmin( FIX::Message&, const FIX::SessionID& ) override;
    void toApp( FIX::Message&, const FIX::SessionID& ) throw ( FIX::DoNotSend ) override;

    void fromAdmin( const FIX::Message&, const FIX::SessionID& )
    throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) override;

    void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
    throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) override;

    void onMessage( const FIX44::TestRequest& message, const FIX::SessionID& sessionID);

private:
    void replyToTestRequest(const FIX::SessionID& sessionID);
    bool isUserRegistered(std::string& username, std::string& pass);

    std::map<std::string, std::string> _registrated_users = {
            {"admin", "admin"},
            {"admin2", "pass"},
            {"user", "user"},
            {"user2", "userpass"},
    };

    Logger logger;
};
