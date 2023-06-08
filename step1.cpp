/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step1 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE of Creation: 21/10/2003
*  Modified: 24/11/2003
*  Modified: 08/12/2003
*
*******************************************************************/

/** include files **/
#include "step1.h"      // class step1
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Step1
* Description: 
********************************************************************/
Step1::Step1( const string &name )
: Atomic( name )
, glucose( addInputPort( "glucose" ) )
, ATPi( addInputPort( "ATPi" ) )
, hexokinase( addInputPort( "hexokinase" ) )
, glucose_6_phosphate( addOutputPort( "glucose_6_phosphate" ) )
, ADP( addOutputPort( "ADP" ) )
, H( addOutputPort( "H" ) )
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
Model &Step1::initFunction()
{
	atpc = 0;
	glucosec = 0;
	ifhex = false;
	counter = 0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Step1::externalFunction( const ExternalMessage &msg )
{

	if( msg.port() == glucose )
	{
		glucosec = glucosec + msg.value() ;
	
		if ( (atpc > 0 ) && (ifhex == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}


	else if( msg.port() == ATPi )
	{
		atpc = atpc + msg.value() ;

		if ( (glucosec > 0 ) && (ifhex == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}


	else if ( msg.port() == hexokinase )
	{
		ifhex = true ;
	
		if ( (glucosec > 0 ) && (atpc > 0) )
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
Model &Step1::internalFunction( const InternalMessage & )
{
    counter = 0;
	if  ( state() == passive ) 
	{
		passivate();
	}
	else
	{
		
		if ( (atpc >= 1) && (glucosec >= 1 ) && (ifhex == true ) )
		{
			if (atpc > glucosec)
			{
				atpc = atpc - glucosec;
				counter = glucosec;
				glucosec = 0;
			}

			else if (atpc < glucosec)
			{
				glucosec = glucosec - atpc;
				counter = atpc;
				atpc = 0;
			}

			else if (atpc == glucosec)
			{
				counter = atpc;
				atpc = 0;
				glucosec = 0;
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
Model &Step1::outputFunction( const InternalMessage &msg )
{

	if ( counter != 0 )
	{
		sendOutput( msg.time(), ADP, counter );
        sendOutput( msg.time(), glucose_6_phosphate, counter );
		sendOutput( msg.time(), H, counter );
	}
	
	return *this ;
}