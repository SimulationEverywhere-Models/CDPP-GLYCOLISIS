/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step10 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*		  mailto://roxana.djafarzadeh@worldheart.com
*
*  DATE: 23/10/2003
*
*******************************************************************/

#ifndef __STEP10_H
#define __STEP10_H

#include <list>
#include "atomic.h"     // class Atomic

class Step10 : public Atomic
{
public:
	Step10( const string &name = "Step10" ); //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    // inputs
	const Port &phosphoenolpyruvic;
	const Port &ADP;
	const Port &pyruvate_kinase;
    // outputs
	Port &pyruvate;
	Port &ATP;

	Time preparationTime;

	double pepc;
	double adpc;
	bool ifpk;
    double counter;

};	// class Step10

// ** inline ** // 
inline
string Step10::className() const
{
	return "Step10" ;
}

#endif   //__STEP3_H
