/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step5 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE: 22/10/2003
*  Modified: 15/11/2003
*
*******************************************************************/

/** include files **/
#include "step5.h"      // class step5
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Step5
* Description: 
********************************************************************/
Step5::Step5( const string &name )
: Atomic( name )
, fructose_16_bisphosphate( addInputPort( "fructose_16_bisphosphate" ) )
, aldolase( addInputPort( "aldolase" ) )
, GDP( addOutputPort( "GDP" ) )
, preparationTime( 0, 0, 10, 0 )
{
	string time( MainSimulator::Instance().getParameter( description(), "preparation" ) ) ;

	if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Step5::initFunction()
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
Model &Step5::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == fructose_16_bisphosphate )
	{
		f16pc = f16pc + msg.value() ;
		if ( ifaldolase == true ) 
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );

	}

	else if ( msg.port() == aldolase )
	{
		ifaldolase = true ;
	
		if (f16pc > 0 ) 
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Step5::internalFunction( const InternalMessage & )
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
	
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Step5::outputFunction( const InternalMessage &msg )
{
	
	if ( counter != 0 )
	{
		sendOutput( msg.time(), GDP, counter );
	}

	return *this ;
}
