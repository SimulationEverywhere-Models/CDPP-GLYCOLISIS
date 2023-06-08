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
*  Modified: 12/11/2003
*
*******************************************************************/

#ifndef __STEP1_H
#define __STEP1_H

#include <list>
#include "atomic.h"     // class Atomic

class Step1 : public Atomic
{
public:
	Step1( const string &name = "Step1" ); //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    // inputs
	const Port &glucose;
	const Port &ATPi;
	const Port &hexokinase;
    // outputs
	Port &glucose_6_phosphate;
	Port &ADP;
	Port &H;

	Time preparationTime;
	double atpc;
	double glucosec;
	bool ifhex;
    double counter;

};	// class Step1

// ** inline ** // 
inline
string Step1::className() const
{
	return "Step1" ;
}

#endif   //__STEP1_H
