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
*  modified: 13/11/2003
*  Modified: 08/12/2003
*
*******************************************************************/

#ifndef __STEP3_H
#define __STEP3_H

#include <list>
#include "atomic.h"     // class Atomic

class Step3 : public Atomic
{
public:
	Step3( const string &name = "Step3" ); //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    // inputs
	const Port &fructose_6_phosphate;
	const Port &ATPi;
	const Port &PFK;
    // outputs
	Port &fructose_16_bisphosphate;
	Port &ADP;

	Time preparationTime;

	double f6pc;
	double atpc;
	bool   ifpfk;
	
	double counter;

};	// class Step3

// ** inline ** // 
inline
string Step3::className() const
{
	return "Step3" ;
}

#endif   //__STEP3_H
