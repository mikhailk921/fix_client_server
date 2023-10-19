
#include "Application.h"
#include "quickfix/Session.h"

#include "quickfix/fix44/ExecutionReport.h"

void Application::onCreate( const FIX::SessionID& sessionID ) {}
void Application::onLogon( const FIX::SessionID& sessionID ) {
    std::cout << "onLogon message" << std::endl;
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
    std::cout << message.toString() << std::endl;
}

void Application::fromApp( const FIX::Message& message,
                           const FIX::SessionID& sessionID )
throw ( FIX::FieldNotFound, FIX::IncorrectDataFormat, FIX::IncorrectTagValue, FIX::UnsupportedMessageType ) {
    crack( message, sessionID ); }

void Application::onMessage( const FIX44::NewOrderSingle& message,
                             const FIX::SessionID& sessionID ) {
    FIX::Symbol symbol;
    FIX::Side side;
    FIX::OrdType ordType;
    FIX::OrderQty orderQty;
    FIX::Price price;
    FIX::ClOrdID clOrdID;
    FIX::Account account;

    message.get( ordType );

    if ( ordType != FIX::OrdType_LIMIT )
        throw FIX::IncorrectTagValue( ordType.getTag() );

    message.get( symbol );
    message.get( side );
    message.get( orderQty );
    message.get( price );
    message.get( clOrdID );

    FIX44::ExecutionReport executionReport = FIX44::ExecutionReport
            ( FIX::OrderID( genOrderID() ),
              FIX::ExecID( genExecID() ),
              FIX::ExecType( FIX::ExecType_TRADE ),
              FIX::OrdStatus( FIX::OrdStatus_FILLED ),
              side,
              FIX::LeavesQty( 0 ),
              FIX::CumQty( orderQty ),
              FIX::AvgPx( price ) );

    executionReport.set( clOrdID );
    executionReport.set( symbol );
    executionReport.set( orderQty );
    executionReport.set( FIX::LastQty( orderQty ) );
    executionReport.set( FIX::LastPx( price ) );

    if( message.isSet(account) )
        executionReport.setField( message.get(account) );

    try {
        FIX::Session::sendToTarget( executionReport, sessionID );
    }
    catch ( FIX::SessionNotFound& ) {}
}
