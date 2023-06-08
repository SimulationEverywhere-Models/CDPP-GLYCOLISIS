/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step2 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*		  mailto://roxana.djafarzadeh@worldheart.com
*
*  DATE: 21/10/2003
*  Modified: 13/11/2003
*
*******************************************************************/

#ifndef __STEP2_H
#define __STEP2_H

#include <list>
#include "atomic.h"     // class Atomic

class Step2 : public Atomic
{
public:
	Step2( const string &name = "Step2" ); //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    // inputs
	const Port &glucose_6_phosphate;
	const Port &phosphoglucoisomerase;
    // outputs
	Port &fructose_6_phosphate;
	
	Time preparationTime;
	double g6pc;
	bool ifpgisomerase;
	double counter;


};	// class Step2

// ** inline ** // 
inline
string Step2::className() const
{
	return "Step2" ;
}

#endif   //__STEP2_H
