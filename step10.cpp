/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step10 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE: 23/10/2003
*  Modified: 13/11/2003
*
*******************************************************************/

/** include files **/
#include "step10.h"     // class step10
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Step10
* Description: 
********************************************************************/
Step10::Step10( const string &name )
: Atomic( name )
, phosphoenolpyruvic( addInputPort( "phosphoenolpyruvic" ) )
, ADP( addInputPort( "ADP" ) )
, pyruvate_kinase( addInputPort( "pyruvate_kinase" ) )
, pyruvate( addOutputPort( "pyruvate" ) )
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
Model &Step10::initFunction()
{
	pepc = 0;
	adpc = 0;
	ifpk = false;
	counter = 0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Step10::externalFunction( const ExternalMessage &msg )
{

	if( msg.port() == phosphoenolpyruvic )
	{
		pepc = pepc + msg.value() ;
		if ( (adpc > 0 ) && (ifpk == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	else if( msg.port() == ADP )
	{
		adpc = adpc + msg.value() ;
		if ( (pepc > 0 ) && (ifpk == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	else if ( msg.port() == pyruvate_kinase )
	{
		ifpk = true ;
	
		if ( (pepc > 0 ) && (adpc > 0) )
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
Model &Step10::internalFunction( const InternalMessage & )
{
	counter = 0;
	
	if  ( state() == passive ) 
	{
		passivate();
	}
	
	else
	{
		if ( (pepc >= 1) && (adpc >= 1 ) && (ifpk == true ) )
		{
			if (pepc > adpc)
			{
				pepc = pepc - adpc;
				counter = adpc;
				adpc = 0;
			}

			else if (pepc < adpc)
			{
				adpc = adpc - pepc;
				counter = pepc;
				pepc = 0;
			}

			else if (pepc == adpc)
			{
				counter = pepc;
				pepc = 0;
				adpc = 0;
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
Model &Step10::outputFunction( const InternalMessage &msg )
{
	if ( counter != 0 )
	{
		sendOutput( msg.time(), ATP, counter ) ;
        sendOutput( msg.time(), pyruvate, counter ) ;
	}

	return *this ;
}
