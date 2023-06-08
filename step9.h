/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step9 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*		  mailto://roxana.djafarzadeh@worldheart.com
*
*  DATE: 23/10/2003
*  Modified: 14/11/2003
*
*******************************************************************/

#ifndef __STEP9_H
#define __STEP9_H

#include <list>
#include "atomic.h"     // class Atomic

class Step9 : public Atomic
{
public:
	Step9( const string &name = "Step9" ); //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    // inputs
	const Port &_2_phosphoglycerate;
	const Port &enolase;
	// outputs
	Port &phosphoenolpyruvic;
	Port &H2O;

	Time preparationTime;
	double _2pgc;
	bool ifenolase;

	double counter;

};	// class Step9

// ** inline ** // 
inline
string Step9::className() const
{
	return "Step9" ;
}

#endif   //__STEP9_H
