/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step3 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE of Creation: 21/10/2003
*  Modified: 9/11/2003
*  Modifiel: 13/11/2003
*  Modified: 08/12/2003
*
*******************************************************************/

/** include files **/
#include "step3.h"      // class step3
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Step3
* Description: 
********************************************************************/
Step3::Step3( const string &name )
: Atomic( name )
, fructose_6_phosphate( addInputPort( "fructose_6_phosphate" ) )
, ATPi( addInputPort( "ATPi" ) )
, PFK( addInputPort( "PFK" ) )
, fructose_16_bisphosphate( addOutputPort( "fructose_16_bisphosphate" ) )
, ADP( addOutputPort( "ADP" ) )
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
Model &Step3::initFunction()
{
	atpc = 0;
	f6pc = 0;
	ifpfk = false;
	counter = 0;

	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Step3::externalFunction( const ExternalMessage &msg )
{

	if( msg.port() == fructose_6_phosphate )
	{
		f6pc = f6pc + msg.value() ;
		if ( (atpc > 0 ) && (ifpfk == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	else if( msg.port() == ATPi )
	{
		atpc = atpc + msg.value() ;
		if ( (f6pc > 0 ) && (ifpfk == true ) )
			holdIn( active, Time::Zero );
		else
			holdIn(passive, Time::Zero );
	}

	else if ( msg.port() == PFK )
	{
		ifpfk = true ;
	
		if ( (f6pc > 0 ) && (atpc > 0) )
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
Model &Step3::internalFunction( const InternalMessage & )
{

	counter = 0;

	if  ( state() == passive ) 
	{
		passivate();
	}

	else
	{
		if ( (atpc >= 1) && (f6pc >= 1 ) && (ifpfk == true ) )
		{
			if (atpc > f6pc)
			{
				atpc = atpc - f6pc;
				counter = f6pc;
				f6pc = 0;
			}

			else if (atpc < f6pc)
			{
				f6pc = f6pc - atpc;
				counter = atpc;
				atpc = 0;
			}

			else if (atpc == f6pc)
			{
				counter = atpc;
				atpc = 0;
				f6pc = 0;
		
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
Model &Step3::outputFunction( const InternalMessage &msg )
{

	if ( counter != 0 )
	{
		sendOutput( msg.time(), ADP, counter ) ;
        sendOutput( msg.time(), fructose_16_bisphosphate, counter ) ;
	}
	return *this ;
}
