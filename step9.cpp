/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step9 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE: 23/10/2003
*  Modified: 14/11/2003
*
*******************************************************************/

/** include files **/
#include "step9.h"      // class step1
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Step9
* Description: 
********************************************************************/
Step9::Step9( const string &name )
: Atomic( name )
, _2_phosphoglycerate( addInputPort( "_2_phosphoglycerate" ) )
, enolase( addInputPort( "enolase" ) )
, phosphoenolpyruvic( addOutputPort( "phosphoenolpyruvic" ) )
, H2O( addOutputPort( "H2O" ) )
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
Model &Step9::initFunction()
{
	_2pgc = 0;
	ifenolase = false;
	counter = 0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Step9::externalFunction( const ExternalMessage &msg )
{

	if( msg.port() == _2_phosphoglycerate )
	{
		_2pgc = _2pgc + msg.value() ;

		if ( ifenolase == true )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	else if ( msg.port() == enolase )
	{
		ifenolase = true ;
	
		if ( _2pgc > 0 )
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
Model &Step9::internalFunction( const InternalMessage & )
{
    counter = 0;

	if  ( state() == passive ) 
	{
		passivate();
	}

	else
	{

		if ( (_2pgc >= 1) && (ifenolase == true ) )
		{
			counter = _2pgc;
			_2pgc = 0;
			
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
Model &Step9::outputFunction( const InternalMessage &msg )
{

	if ( counter != 0 )
	{
		sendOutput( msg.time(), H2O, counter ) ;
       	sendOutput( msg.time(), phosphoenolpyruvic, counter ) ;
	}
	
	return *this ;
}
