/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step5 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*		  mailto://roxana.djafarzadeh@worldheart.com
*
*  DATE: 22/10/2003
*
*******************************************************************/

#ifndef __STEP5_H
#define __STEP5_H

#include <list>
#include "atomic.h"     // class Atomic

class Step5 : public Atomic
{
public:
	Step5( const string &name = "Step5" ); //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    // inputs
	const Port &fructose_16_bisphosphate;
	const Port &aldolase;
    // outputs
	Port &GDP;
	
	Time preparationTime;

	double f16pc;
	bool ifaldolase;
	double counter;


};	// class Step5

// ** inline ** // 
inline
string Step5::className() const
{
	return "Step5" ;
}

#endif   //__STEP5_H
