#pragma once

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Mutex.h"

#include "quickfix/fix44/NewOrderSingle.h"
#include "quickfix/fix44/ExecutionReport.h"
#include "quickfix/fix44/OrderCancelRequest.h"
#include "quickfix/fix44/OrderCancelReject.h"
#include "quickfix/fix44/OrderCancelReplaceRequest.h"
#include "quickfix/fix44/MarketDataRequest.h"


class MyClientApplication : public FIX::Application, public FIX::MessageCracker {
public:
    MyClientApplication(std::string username, std::string pass): _username(username), _userpass(pass) {};

    void run();
    void onCreate( const FIX::SessionID& sessionId) override;
    void onLogon( const FIX::SessionID& sessionID ) override;
    void onLogout( const FIX::SessionID& sessionID ) override;

    void toAdmin( FIX::Message& message, const FIX::SessionID& ) override;
    void toApp( FIX::Message&, const FIX::SessionID& ) throw( FIX::DoNotSend ) override;

    void fromAdmin( const FIX::Message&, const FIX::SessionID& )
    throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) override {};

    void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
    throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) override;

    char queryAction();

private:
    std::string _username;
    std::string _userpass;
};
