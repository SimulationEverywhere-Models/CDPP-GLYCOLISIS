/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step8 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*		  mailto://roxana.djafarzadeh@worldheart.com
*
*  DATE: 23/10/2003
*  Modified 14/11/2003
*
*******************************************************************/

#ifndef __STEP8_H
#define __STEP8_H

#include <list>
#include "atomic.h"     // class Atomic

class Step8 : public Atomic
{
public:
	Step8( const string &name = "Step8" ); //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    // inputs
	const Port &_3_phosphoglycerate;
	const Port &PGM;
    // outputs
	Port &_2_phosphoglycerate;
	
	Time preparationTime;

	double _3pgc;
	bool ifpgm;

	double counter;

};	// class Step8

// ** inline ** // 
inline
string Step8::className() const
{
	return "Step8" ;
}

#endif   //__STEP8_H
