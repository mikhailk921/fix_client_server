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


class MyApplication : public FIX::Application, public FIX::MessageCracker {
public:
    void run();
    void onCreate( const FIX::SessionID& ) {};
    void onLogon( const FIX::SessionID& sessionID );
    void onLogout( const FIX::SessionID& sessionID );

    void toAdmin( FIX::Message&, const FIX::SessionID& ) {};
    void toApp( FIX::Message&, const FIX::SessionID& ) throw( FIX::DoNotSend );

    void fromAdmin( const FIX::Message&, const FIX::SessionID& ) throw( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon ) {};
    void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID ) throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType );

    void onMessage( const FIX44::ExecutionReport&, const FIX::SessionID& ) {};
    void onMessage( const FIX44::OrderCancelReject&, const FIX::SessionID& ) {};

    char queryAction();
};

