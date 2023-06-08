/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step4 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE: 22/10/2003
*  Modified: 13/11/2003
*
*******************************************************************/

/** include files **/
#include "step4.h"      // class step1
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Step4
* Description: 
********************************************************************/
Step4::Step4( const string &name )
: Atomic( name )
, fructose_16_bisphosphate( addInputPort( "fructose_16_bisphosphate" ) )
, aldolase( addInputPort( "aldolase" ) )
, DHP( addOutputPort( "DHP" ) )
, preparationTime( 0, 0, 10, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: 
* Precondition: 
********************************************************************/
Model &Step4::initFunction()
{
	f16pc = 0;
	ifaldolase = false;
    counter = 0;
	
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Step4::externalFunction( const ExternalMessage &msg )
{
	
	if( msg.port() == fructose_16_bisphosphate )
	{
		f16pc = f16pc + msg.value();
		
		if ( ifaldolase == true ) 
			holdIn(active, Time::Zero);
		else
			holdIn(passive, Time::Zero);
	}

	else if ( msg.port() == aldolase )
	{
		ifaldolase = true ;
	
		if ( f16pc > 0 ) 
			holdIn(active, Time::Zero);
		else
			holdIn(passive, Time::Zero);
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Step4::internalFunction( const InternalMessage & )
{
	counter = 0;

	if  ( state() == passive ) 
	{
		passivate();
	}

	else
	{
		if ( (f16pc >= 1) && (ifaldolase == true ) )
		{
			counter = f16pc;
			f16pc = 0;
		
			holdIn(passive, Time::Zero );
		}
		else
		{
			passivate();
		}
	}

	return *this;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Step4::outputFunction( const InternalMessage &msg )
{
	
	if ( counter != 0 )
	{
		sendOutput( msg.time(), DHP, counter );
	}
		
	return *this;

}
