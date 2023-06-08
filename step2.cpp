/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step2 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE: 21/10/2003
*  Modified: 13/11/2003
*
*******************************************************************/

/** include files **/
#include "step2.h"      // class step2
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Step2
* Description: 
********************************************************************/
Step2::Step2( const string &name )
: Atomic( name )
, glucose_6_phosphate( addInputPort( "glucose_6_phosphate" ) )
, phosphoglucoisomerase( addInputPort( "phosphoglucoisomerase" ) )
, fructose_6_phosphate( addOutputPort( "fructose_6_phosphate" ) )
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
Model &Step2::initFunction()
{
	g6pc = 0;
	ifpgisomerase = false;
    counter = 0;
	
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Step2::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == glucose_6_phosphate )
	{
		g6pc = g6pc + msg.value() ;
		if ( ifpgisomerase == true ) 
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	else if ( msg.port() == phosphoglucoisomerase )
	{
		ifpgisomerase = true ;
	
		if (g6pc > 0 ) 
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
Model &Step2::internalFunction( const InternalMessage & )
{

	counter = 0;
	if  ( state() == passive ) 
	{
		passivate();
	}
	else
	{
		if ( (g6pc >= 1) && (ifpgisomerase == true ) )
		{
			counter = g6pc;
			g6pc = 0;
				
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
Model &Step2::outputFunction( const InternalMessage &msg )
{

	if ( counter != 0 )
	{
		sendOutput( msg.time(), fructose_6_phosphate, counter ) ;
	}
	
	return *this ;
}
