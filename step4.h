/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step4 of Glycolysis
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

#ifndef __STEP4_H
#define __STEP4_H

#include <list>
#include "atomic.h"     // class Atomic

class Step4 : public Atomic
{
public:
	Step4( const string &name = "Step4" ); //Default constructor

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
	Port &DHP;
	
	Time preparationTime;

	double f16pc;
	bool ifaldolase;

	double counter;


};	// class Step4

// ** inline ** // 
inline
string Step4::className() const
{
	return "Step4" ;
}

#endif   //__STEP4_H
