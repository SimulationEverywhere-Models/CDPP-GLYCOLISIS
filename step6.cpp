/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step3 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE: 27/10/2003
*  Modified: 15/11/2003
*
*******************************************************************/

/** include files **/
#include "step6.h"      // class step6
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Step6
* Description: 
********************************************************************/
Step6::Step6( const string &name )
: Atomic( name )
, GDP( addInputPort( "GDP" ) )
, NAD( addInputPort( "NAD" ) )
, P( addInputPort( "P" ) )
, G3PD( addInputPort( "G3PD" ) )
, _13_BPG( addOutputPort( "_13_BPG" ) )
, NADH( addOutputPort( "NADH" ) )
, H( addOutputPort( "H" ) )
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
Model &Step6::initFunction()
{
	gdpc = 0;
	nadc = 0;
	pc = 0;
	ifg3pd = false;

	counter = 0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Step6::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == GDP )
	{
		gdpc = gdpc + msg.value() ;
		if ( (nadc > 0 ) && (pc > 0 ) && (ifg3pd == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );

	}

	else if( msg.port() == NAD )
	{
		nadc = nadc + msg.value() ;
		if ( (gdpc > 0 ) && (pc > 0 ) && (ifg3pd == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	else if( msg.port() == P )
	{
		pc = pc + msg.value() ;
		if ( (gdpc > 0 ) && (nadc > 0 ) && (ifg3pd == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	else if ( msg.port() == G3PD )
	{
		ifg3pd = true ;
	
		if ( (gdpc > 0 ) && (nadc > 0 ) && (pc > 0 ) )
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
Model &Step6::internalFunction( const InternalMessage & )
{

	counter = 0;

	if  ( state() == passive ) 
	{
		passivate();
	}
	else
	{

		if ( (gdpc >= 1) && (nadc >= 1 ) && (pc >= 1 ) && (ifg3pd == true ) )
		{

			if ( (gdpc>=nadc) && (nadc>=pc) )
			{
				gdpc = gdpc - pc;
				nadc = nadc - pc;
				counter = pc;			
				pc = 0;
			}

			else if ( (gdpc>=pc) && (pc>=nadc) )
			{
				gdpc = gdpc - nadc;
				pc = pc - nadc;
				counter = nadc;
				nadc = 0;
			}

			else if ( (nadc>=gdpc) && (gdpc>=pc) )
			{		
				gdpc = gdpc - pc;
				nadc = nadc - pc;
				counter = pc;				
				pc = 0;
			}

			else if ( (nadc>=pc) && (pc>=gdpc) )
			{
				nadc = nadc - gdpc;
				pc = pc - gdpc;
				counter = gdpc;				
				gdpc = 0;
			}

			else if ( (pc>=gdpc) && (gdpc>=nadc) )
			{
				gdpc = gdpc - nadc;
				pc = pc - nadc;
				counter = nadc;		
				nadc = 0;
			}

			else if ( (pc>=nadc) && (nadc>=gdpc) )
			{
				nadc = nadc - gdpc;
				pc = pc - gdpc;
				counter = gdpc;
				gdpc = 0;
			}

			else if ( (gdpc == nadc) && (gdpc == pc) )
			{
				counter = gdpc;
				gdpc = 0;
				nadc = 0;
				pc = 0;
			}

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
Model &Step6::outputFunction( const InternalMessage &msg )
{
	
	if ( counter != 0 )
	{
		sendOutput( msg.time(), _13_BPG, counter );
        sendOutput( msg.time(), NADH, counter );
		sendOutput( msg.time(), H, counter );
	}
	
	return *this;

}
