
#pragma once

#include <map>

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Utility.h"
#include "quickfix/Mutex.h"

#include "quickfix/fix44/NewOrderSingle.h"

class MyServerApplication: public FIX::Application, public FIX::MessageCracker {
public:
    MyServerApplication(): _test_value(0) {}

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

    std::string getTestValue() {
        return std::to_string(++_test_value);
    }
private:
    bool isUserRegistered(std::string& username, std::string& pass);

    int _test_value;

    std::map<std::string, std::string> _registrated_users = {
            {"admin", "admin"},
            {"admin2", "pass"},
            {"user", "user"},
            {"user2", "userpass"},
    };

};
