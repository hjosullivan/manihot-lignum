//Your  L-system will be similar to this. See 
//LEngine README for user caveats, e.g. please do not
//use C++ keywords in comments.
#include <iostream>
using namespace std;

#include <mathsym.h>
#include <ParametricCurve.h>
using namespace cxxadt;

#include <LGMUnits.h>
using namespace Lignum;

#include <Maniot.h>
//First include lengine.h file for some necessary 
//declarations and definitions 
#include <lengine.h>

//Then wrap your L-system into a "namespace" so that you
//can have several tree sepecies in a program 
 namespace BL1{ 


//lsys.h impelemnts the rewriting
#include <lsys.h>

const double LSEG = 0.9;
const double RADIUS = 0.15;
const double RADIUS_TOP = 0.15;
const double A90  = PI_VALUE/2.0;
const double A45  = A90/2.0;
//The declare the modules your need 
//Fd(length,radius,radius_top)
 const ModuleIdType Fd_id = 2;
 const ModuleIdType F_id = 3;
//B: Bud()
 const ModuleIdType B_id = 4;
 const ModuleIdType Pitch_id = 5;
 const ModuleIdType Roll_id = 6;

//Define the Start corresponding to the axiom
void Start()
{

  { Produce((ModuleIdType)(Fd_id));Produce((double)(LSEG*4.0));Produce((double)(RADIUS));Produce((double)(RADIUS_TOP));Produce((ModuleIdType)(Fd_id)); Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(Roll_id));Produce((double)(-A90));Produce((ModuleIdType)(Roll_id)); Produce((ModuleIdType)(Pitch_id));Produce((double)(A45));Produce((ModuleIdType)(Pitch_id));Produce((ModuleIdType)(B_id));Produce((ModuleIdType)(EB_id)); Produce((ModuleIdType)(B_id));}
 
}

void _P1()
{
  { Produce((ModuleIdType)(Fd_id));Produce((double)(LSEG));Produce((double)(RADIUS));Produce((double)(RADIUS_TOP));Produce((ModuleIdType)(Fd_id)); Produce((ModuleIdType)(B_id));}
}

//This is a ToDO for Jari: interpretation typically
//defines the graphical visualization of symbols. But
//we visualize LIGNUM and thus this is practically 
//unnecessary for us. However, "lc2" cannot compile
//L-files unless you have one  interpretation   



 void _I2(double s)
{
  ;
}

//Finally, "close" the "namespace"
 

void _PC1(const CallerData* pCD)
{
_P1();
}


void _IC2(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
double p0;
memcpy(&p0, pArg, sizeof(double));
_I2(p0);
}

static const ProductionPrototype proto[] =
{
	{
		{
			{ 0 }, 0
		},
		{
			{ B_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC1
	}
};
static const ProductionPrototype iproto[] =
{
	{
		{
			{ 0 }, 0
		},
		{
			{ F_id }, 1
		},
		{
			{ 0 }, 0
		},
		_IC2
	}
};
static const ModuleData moduleData[] =
{
{ "SB",  0 },
{ "EB",  0 },
{ "Fd", sizeof(double)+sizeof(double)+sizeof(double)},
{ "F", sizeof(double)},
{ "B",  0 },
{ "Pitch", sizeof(double)},
{ "Roll", sizeof(double)}
};


const ModuleData* GetModuleData(int i)
{ return &(moduleData[i]); }


int NumOfModules()
{ return 7; }
void StartEach() {}
void EndEach() {}
void End() {}

int NumOfProductions()
{ return sizeof(proto)/sizeof(proto[0]); }
const ProductionPrototype& GetProductionPrototype(int i)
{ return proto[i]; }

int NumOfIProductions()
{ return sizeof(iproto)/sizeof(iproto[0]); }
const ProductionPrototype& GetIProductionPrototype(int i)
{ return iproto[i]; }
int NumOfConsidered() { return 0; }
ModuleIdType GetConsidered(int) { return -1; }
int NumOfIgnored() { return 0; }
ModuleIdType GetIgnored(int) { return -1; }
} //closing namespace
