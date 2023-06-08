/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step3 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*
*  DATE: 27/10/2003
*  Modified: 15/11/2003
*
*******************************************************************/

#ifndef __STEP6_H
#define __STEP6_H

#include <list>
#include "atomic.h"     // class Atomic

class Step6 : public Atomic
{
public:
	Step6( const string &name = "Step6" ); //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    // inputs
	const Port &GDP;
	const Port &NAD;
	const Port &P;
	const Port &G3PD;
    // outputs
	Port &_13_BPG;
	Port &NADH;
	Port &H;

	Time preparationTime;
	double gdpc;
	double nadc;
	double pc;
	bool ifg3pd;

	double counter;

};	// class Step6

// ** inline ** // 
inline
string Step6::className() const
{
	return "Step6" ;
}

#endif   //__STEP6_H
