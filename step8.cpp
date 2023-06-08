/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step8 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE: 23/10/2003
*  Modified: 15/11/2003
*
*******************************************************************/

/** include files **/
#include "step8.h"      // class step2
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Step8
* Description: 
********************************************************************/
Step8::Step8( const string &name )
: Atomic( name )
, _3_phosphoglycerate( addInputPort( "_3_phosphoglycerate" ) )
, PGM( addInputPort( "PGM" ) )
, _2_phosphoglycerate( addOutputPort( "_2_phosphoglycerate" ) )
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
Model &Step8::initFunction()
{
	_3pgc = 0;
	ifpgm = false;
	counter = 0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Step8::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == _3_phosphoglycerate )
	{
		_3pgc = _3pgc + msg.value() ;

		if ( ifpgm == true ) 
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );

	}

	else if ( msg.port() == PGM )
	{
		ifpgm = true ;
	
		if (_3pgc > 0 ) 
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
Model &Step8::internalFunction( const InternalMessage & )
{
	counter = 0;

	if  ( state() == passive ) 
	{
		passivate();
	}

	else
	{
		if ( (_3pgc >= 1) && (ifpgm == true ) )
		{
			counter = _3pgc;
			_3pgc = 0;
				
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
Model &Step8::outputFunction( const InternalMessage &msg )
{

	if ( counter != 0 )
	{
        sendOutput( msg.time(), _2_phosphoglycerate, counter ) ;
	}
	
	return *this ;
}
