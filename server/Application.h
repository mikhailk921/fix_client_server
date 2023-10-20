
#pragma once

#include "quickfix/Application.h"
#include "quickfix/MessageCracker.h"
#include "quickfix/Values.h"
#include "quickfix/Utility.h"
#include "quickfix/Mutex.h"

#include "quickfix/fix44/NewOrderSingle.h"

class Application: public FIX::Application, public FIX::MessageCracker {
public:
    Application(): m_orderID(0), m_execID(0) {}

    // Application overloads
    void onCreate( const FIX::SessionID& );
    void onLogon( const FIX::SessionID& sessionID );
    void onLogout( const FIX::SessionID& sessionID );
    void toAdmin( FIX::Message&, const FIX::SessionID& );
    void toApp( FIX::Message&, const FIX::SessionID& ) throw ( FIX::DoNotSend );

    void fromAdmin( const FIX::Message&, const FIX::SessionID& )
    throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::RejectLogon );

    void fromApp( const FIX::Message& message, const FIX::SessionID& sessionID )
    throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType );

    std::string genOrderID() {
        return std::to_string(++m_orderID);
    }
    std::string genExecID() {
        return std::to_string(++m_execID);
    }
private:
    int m_orderID, m_execID;
};
