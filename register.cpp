/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "step1.h"      // class Step1
#include "step2.h"      // class Step2
#include "step3.h"      // class Step3
#include "step4.h"      // class Step4
#include "step5.h"      // class Step5
#include "step6.h"      // class Step6
#include "step7.h"      // class Step7
#include "step8.h"      // class Step8
#include "step9.h"      // class Step9
#include "step10.h"     // class Step10


void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Step10>() , "Step10" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Step9>() , "Step9" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Step8>() , "Step8" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Step7>() , "Step7" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Step6>() , "Step6" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Step5>() , "Step5" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Step4>() , "Step4" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Step3>() , "Step3" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Step2>() , "Step2" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Step1>() , "Step1" ) ;
}
