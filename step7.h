/*******************************************************************
*
*  DESCRIPTION: Atomic Model Step7 of Glycolysis
*
*  AUTHOR: Roxana Djafarzadeh
*
*  EMAIL: mailto://roxanadj@hotmail.com
*         mailto://rdjafar@site.uottawa.ca
*		  mailto://roxana.djafarzadeh@worldheart.com
*
*  DATE: 23/10/2003
*  Modified: 15/11/2003
*
*******************************************************************/

#ifndef __STEP7_H
#define __STEP7_H

#include <list>
#include "atomic.h"     // class Atomic

class Step7 : public Atomic
{
public:
	Step7( const string &name = "Step7" ); //Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
    // inputs
	const Port &_13_BPG; //1,3-bisphosphoglycerate
	const Port &ADP;
	const Port &PGK;	//phosphoglyceratekinase
    // outputs
	Port &_3_phosphoglycerate;	//3-phosphoglycerate
	Port &ATP;

	Time preparationTime;

	double _13bpgc;
	double adpc;
	bool ifpgk;

	double counter;

};	// class Step7

// ** inline ** // 
inline
string Step7::className() const
{
	return "Step7" ;
}

#endif   //__STEP7_H
