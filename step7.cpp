/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step7 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE: 23/10/2003
*  Modified: 15/10/2003
*
*******************************************************************/

/** include files **/
#include "step7.h"      // class step7
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Step7
* Description: 
********************************************************************/
Step7::Step7( const string &name )
: Atomic( name )
, _13_BPG( addInputPort( "_13_BPG" ) )
, ADP( addInputPort( "ADP" ) )
, PGK( addInputPort( "PGK" ) )
, _3_phosphoglycerate( addOutputPort( "_3_phosphoglycerate" ) )
, ATP( addOutputPort( "ATP" ) )
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
Model &Step7::initFunction()
{
	_13bpgc = 0;
	adpc = 0;
	ifpgk = false;
	counter = 0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Step7::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == _13_BPG )
	{
		_13bpgc = _13bpgc + msg.value() ;

		if ( (adpc > 0 ) && (ifpgk == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	else if( msg.port() == ADP )
	{
		adpc = adpc + msg.value() ;

		if ( (_13bpgc > 0 ) && (ifpgk == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	else if ( msg.port() == PGK )
	{
		ifpgk = true ;
	
		if ( (_13bpgc > 0 ) && (adpc > 0) )
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
Model &Step7::internalFunction( const InternalMessage & )
{

	counter = 0;

	if  ( state() == passive ) 
	{
		passivate();
	}

	else
	{
		if ( (_13bpgc >= 1) && (adpc >= 1 ) && (ifpgk == true ) )
		{
			if (_13bpgc > adpc)
			{
				_13bpgc = _13bpgc - adpc;
				counter = adpc;
				adpc = 0;
			}

			else if (_13bpgc < adpc)
			{
				adpc = adpc - _13bpgc;
				counter = _13bpgc;
				_13bpgc = 0;
			}

			else if (_13bpgc == adpc)
			{
				counter = adpc;
				adpc = 0;
				_13bpgc = 0;
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
Model &Step7::outputFunction( const InternalMessage &msg )
{

	if ( counter != 0 )
	{
		sendOutput( msg.time(), _3_phosphoglycerate, counter ) ;
        sendOutput( msg.time(), ATP, counter ) ;
	}
	
	return *this ;

}
