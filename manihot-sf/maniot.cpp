//Your  L-system will be similar to this. See 
//LEngine README for user caveats, e.g. please do not
//use C++ keywords in comments.
#include <iostream>
using namespace std;

#include <mathsym.h>
#include <ParametricCurve.h>
#include <Uniform.h>
using namespace cxxadt;

#include <LGMUnits.h>
using namespace Lignum;
#include <Maniot.h>
//First include lengine.h file for some necessary 
//declarations and definitions 
#include <lengine.h>
//Uniform distribution random number generator 

extern int init;
//Then wrap your L-system into a "namespace" so that you
//can have several tree sepecies in a program 
 namespace Maniot{ 


//lsys.h impelemnts the rewriting
#include <lsys.h>

Uniform u;
//Uniform random number between min and max
inline double ba(double min, double max, Uniform& u)
{
  return min + u(1)*(max-min);
}

inline double sign(Uniform& u)
{
  double r = u(1);
  if (r >= 0.5)
    return 1.0;
  else
    return -1.0;
}

//Branching angles in the main branch
const double MIN_PITCH = 40.0*PI_VALUE/180.0;
const double MAX_PITCH = 50.0*PI_VALUE/180.0;
const double MIN_TURN = 30.0*PI_VALUE/180.0;
const double MAX_TURN = 60.0*PI_VALUE/180.0;
const double MIN_FORK = 5.0*PI_VALUE/180.0;
const double MAX_FORK = 10.0*PI_VALUE/180.0;
//const double MIN_FORK_AU2 = 0.0*PI_VALUE/180.0;
//const double MAX_FORK_AU2 = 5.0*PI_VALUE/180.0;
//const double MIN_PIVOT = 0.0*PI_VALUE/180.0;
//const double MAX_PIVOT = 5.0*PI_VALUE/180.0;
//const double REITERATION_AGE = 10.0;
//const double AU2_AGE = 7.0;
//const double A2_MORT = 0.45;
//const double A3_MORT = 0.45;
//const double P_REITER = 0.1;
//const double P_AU2 = 0.3;
//Segment default dimenstions
const double LSEG = 0.40;
const double LA2 = 0.20;
const double LA3 = 0.10;
const double RA1 = 0.004;
//const double RAU2 = 0.002;
//const double RA2 = 0.002;
//const double RA3 = 0.002;
//const double GA1 = 0.005;
//const double GA2 = 0.003;
//const double GA3 = 0.002;
//Axis types
const double A1 = 1.0;
const double A2 = 2.0;
const double A3 = 3.0;
const double A4 = 4.0;
//const double AU2 = 4.0;
const double THICK = 0.01;
//The declare the modules your need 
//Fd(length,radius,radius_top,axis_type)
  const ModuleIdType Fd_id = 2;
//Status = ALIVE,DEAD 
//B: Bud(AxisType,Age,PhysAge,Status)
 const ModuleIdType B_id = 3;
 const ModuleIdType Pitch_id = 4;
 const ModuleIdType Turn_id = 5;
 const ModuleIdType Roll_id = 6;
 const ModuleIdType HRoll_id = 7;
// const ModuleIdType Split_id = 8;
 const ModuleIdType D_id = 9;
static const ModuleIdType __ignoreArr[] = {  Roll_id, Pitch_id, Turn_id, HRoll_id,0 };
int NumOfIgnored()
{ return sizeof(__ignoreArr)/sizeof(__ignoreArr[0])-1; }
ModuleIdType GetIgnored(int i)
{ return __ignoreArr[i]; }


//Define the Start corresponding to the axiom
void Start()
{
  cout << init << endl;
  u.init(init);
  double pitch1 = ba(MIN_PITCH,MAX_PITCH,u);
  double pitch2 = ba(MIN_PITCH,MAX_PITCH,u);
  { Produce((ModuleIdType)(Fd_id));Produce((double)(LSEG));Produce((double)(RA1));Produce((double)(RA1));Produce((double)(A1));Produce((ModuleIdType)(Fd_id)); Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(Pitch_id));Produce((double)(pitch1));Produce((ModuleIdType)(Pitch_id));  Produce((ModuleIdType)(B_id));Produce((double)(A2));Produce((double)(1));Produce((double)(1));Produce((double)(ALIVE));Produce((double)(0));Produce((ModuleIdType)(B_id));Produce((ModuleIdType)(EB_id)); 
                              Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(Roll_id));Produce((double)(PI_VALUE));Produce((ModuleIdType)(Roll_id)); Produce((ModuleIdType)(Pitch_id));Produce((double)(pitch2));Produce((ModuleIdType)(Pitch_id));  Produce((ModuleIdType)(B_id));Produce((double)(A2));Produce((double)(1));Produce((double)(1));Produce((double)(ALIVE));Produce((double)(0));Produce((ModuleIdType)(B_id));Produce((ModuleIdType)(EB_id));
                                   Produce((ModuleIdType)(Roll_id));Produce((double)(PI_VALUE/2.0));Produce((ModuleIdType)(Roll_id)); Produce((ModuleIdType)(B_id));Produce((double)(A1));Produce((double)(1));Produce((double)(1));Produce((double)(DEAD));Produce((double)(0));Produce((ModuleIdType)(B_id));}
}

//Bud produces tree segments and lateral buds
void _P1(double axis_type,double age,double phys_age,double status,double pitch_angle)
{
  double ran = u(1);
  double pitch1 = ba(MIN_PITCH,MAX_PITCH,u);
  double pitch2 = ba(MIN_PITCH,MAX_PITCH,u);
  if (status==ALIVE && axis_type == A1){
      { Produce((ModuleIdType)(Fd_id));Produce((double)(LSEG));Produce((double)(RA1));Produce((double)(RA1));Produce((double)(A1));Produce((ModuleIdType)(Fd_id)); Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(Pitch_id));Produce((double)(pitch1));Produce((ModuleIdType)(Pitch_id));  Produce((ModuleIdType)(B_id));Produce((double)(A2));Produce((double)(1));Produce((double)(1));Produce((double)(ALIVE));Produce((double)(pitch_angle));Produce((ModuleIdType)(B_id));Produce((ModuleIdType)(EB_id)); 
                                  Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(Roll_id));Produce((double)(PI_VALUE));Produce((ModuleIdType)(Roll_id)); Produce((ModuleIdType)(Pitch_id));Produce((double)(pitch2));Produce((ModuleIdType)(Pitch_id));  Produce((ModuleIdType)(B_id));Produce((double)(A2));Produce((double)(1));Produce((double)(1));Produce((double)(ALIVE));Produce((double)(pitch_angle));Produce((ModuleIdType)(B_id));Produce((ModuleIdType)(EB_id));
                    Produce((ModuleIdType)(Roll_id));Produce((double)(PI_VALUE/2.0));Produce((ModuleIdType)(Roll_id)); Produce((ModuleIdType)(B_id));Produce((double)(A1));Produce((double)(1));Produce((double)(1));Produce((double)(DEAD));Produce((double)(pitch_angle));Produce((ModuleIdType)(B_id));}
   }
   else if (status == ALIVE && axis_type == A2){
   	double max_pitch_angle = MAX_FORK;
        if (pitch_angle >= 85.0*PI_VALUE/180.0){
            max_pitch_angle = 0.0;
	}
        double new_pitch_angle = pitch_angle + max_pitch_angle;
   	{ Produce((ModuleIdType)(Fd_id));Produce((double)(LA2));Produce((double)( RA1));Produce((double)( RA1));Produce((double)( axis_type));Produce((ModuleIdType)(Fd_id)); Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(Turn_id));Produce((double)(MIN_TURN));Produce((ModuleIdType)(Turn_id)); Produce((ModuleIdType)(Pitch_id));Produce((double)(max_pitch_angle));Produce((ModuleIdType)(Pitch_id));Produce((ModuleIdType)(B_id));Produce((double)(A3));Produce((double)(1));Produce((double)(1));Produce((double)(ALIVE));Produce((double)(new_pitch_angle));Produce((ModuleIdType)(B_id));Produce((ModuleIdType)(EB_id));
			      	       Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(Turn_id));Produce((double)(-MIN_TURN));Produce((ModuleIdType)(Turn_id)); Produce((ModuleIdType)(Pitch_id));Produce((double)(-max_pitch_angle));Produce((ModuleIdType)(Pitch_id)); Produce((ModuleIdType)(B_id));Produce((double)(A3));Produce((double)(1));Produce((double)(1));Produce((double)(ALIVE));Produce((double)(new_pitch_angle));Produce((ModuleIdType)(B_id));Produce((ModuleIdType)(EB_id));
				       Produce((ModuleIdType)(B_id));Produce((double)(axis_type));Produce((double)(1));Produce((double)(1));Produce((double)(DEAD));Produce((double)(new_pitch_angle));Produce((ModuleIdType)(B_id));}
   }
   else if (status == ALIVE && axis_type > A2){
   	double max_pitch_angle = MAX_FORK;
	if (pitch_angle >= 85.0*PI_VALUE/180.0){
	   max_pitch_angle = 0.0;
	}
	double new_pitch_angle = pitch_angle + max_pitch_angle;
   	{ Produce((ModuleIdType)(Fd_id));Produce((double)(LA3));Produce((double)( RA1));Produce((double)( RA1));Produce((double)( axis_type));Produce((ModuleIdType)(Fd_id)); Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(Turn_id));Produce((double)(MIN_TURN));Produce((ModuleIdType)(Turn_id)); Produce((ModuleIdType)(Pitch_id));Produce((double)(-max_pitch_angle));Produce((ModuleIdType)(Pitch_id)); Produce((ModuleIdType)(B_id));Produce((double)(A4));Produce((double)(1));Produce((double)(1));Produce((double)(ALIVE));Produce((double)(new_pitch_angle));Produce((ModuleIdType)(B_id)); Produce((ModuleIdType)(EB_id));
   	   	   	     		Produce((ModuleIdType)(SB_id)); Produce((ModuleIdType)(Turn_id));Produce((double)(-MIN_TURN));Produce((ModuleIdType)(Turn_id)); Produce((ModuleIdType)(Pitch_id));Produce((double)(-max_pitch_angle));Produce((ModuleIdType)(Pitch_id)); Produce((ModuleIdType)(B_id));Produce((double)(A4));Produce((double)(1));Produce((double)(1));Produce((double)(ALIVE));Produce((double)(new_pitch_angle));Produce((ModuleIdType)(B_id)); Produce((ModuleIdType)(EB_id));
					Produce((ModuleIdType)(B_id));Produce((double)(axis_type));Produce((double)(1));Produce((double)(1));Produce((double)(DEAD));Produce((double)(new_pitch_angle));Produce((ModuleIdType)(B_id));}
   }
   else{
   { Produce((ModuleIdType)(B_id));Produce((double)(axis_type));Produce((double)(age));Produce((double)(phys_age));Produce((double)(status));Produce((double)(pitch_angle));Produce((ModuleIdType)(B_id));}
   }
}


//Left hand and right hand context or Bud
    void _P2(double THICK,double c,double axis_type,double age,double phys_age,double status,double pitch_angle,double l1,double r1,double rtop1,double axis_type1)
{
if (THICK > 0.0)
{ Produce((ModuleIdType)(Fd_id));Produce((double)(l1));Produce((double)(THICK));Produce((double)(THICK));Produce((double)(axis_type1));Produce((ModuleIdType)(Fd_id));Produce((ModuleIdType)(D_id));Produce((double)(THICK/2.0));Produce((double)(1.0));Produce((ModuleIdType)(D_id));}
}

//Left hand context for Segment symbol
  void _P3(double THICK,double c,double l1,double r1,double rtop1,double axis_type1)
{  if (THICK > 0.0)
{ Produce((ModuleIdType)(Fd_id));Produce((double)(l1));Produce((double)(THICK));Produce((double)(THICK));Produce((double)(axis_type1));Produce((ModuleIdType)(Fd_id));Produce((ModuleIdType)(D_id));Produce((double)(THICK/2.0));Produce((double)(1.0));Produce((ModuleIdType)(D_id));}
}

//Right hand context for Diameter symbol
  void _P4(double THICK,double c,double l1,double r1,double rtop1,double axis_type1)
{  if (THICK > 0.0)
      { Produce((ModuleIdType)(Fd_id));Produce((double)(l1));Produce((double)(THICK));Produce((double)(THICK));Produce((double)(axis_type1));Produce((ModuleIdType)(Fd_id));Produce((ModuleIdType)(D_id));Produce((double)(THICK/2.0));Produce((double)(1.0));Produce((ModuleIdType)(D_id));}
}
//This is a ToDO for Jari: interpretation typically
//defines the graphical visualization of symbols. But
//we visualize LIGNUM and thus this is practically 
//unnecessary for us. However, "lc2" cannot compile
//L-files unless you have one  interpretation   





//Finally, "close" the "namespace"
 

void _PC1(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
double p0;
memcpy(&p0, pArg, sizeof(double));
pArg += sizeof(double);
double p1;
memcpy(&p1, pArg, sizeof(double));
pArg += sizeof(double);
double p2;
memcpy(&p2, pArg, sizeof(double));
pArg += sizeof(double);
double p3;
memcpy(&p3, pArg, sizeof(double));
pArg += sizeof(double);
double p4;
memcpy(&p4, pArg, sizeof(double));
_P1(p0,p1,p2,p3,p4);
}


void _PC2(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->LCntxt.pArg(0);
double p0;
memcpy(&p0, pArg, sizeof(double));
pArg += sizeof(double);
double p1;
memcpy(&p1, pArg, sizeof(double));
pArg = pCD->Strct.pArg(0);
double p2;
memcpy(&p2, pArg, sizeof(double));
pArg += sizeof(double);
double p3;
memcpy(&p3, pArg, sizeof(double));
pArg += sizeof(double);
double p4;
memcpy(&p4, pArg, sizeof(double));
pArg += sizeof(double);
double p5;
memcpy(&p5, pArg, sizeof(double));
pArg += sizeof(double);
double p6;
memcpy(&p6, pArg, sizeof(double));
pArg = pCD->RCntxt.pArg(0);
double p7;
memcpy(&p7, pArg, sizeof(double));
pArg += sizeof(double);
double p8;
memcpy(&p8, pArg, sizeof(double));
pArg += sizeof(double);
double p9;
memcpy(&p9, pArg, sizeof(double));
pArg += sizeof(double);
double p10;
memcpy(&p10, pArg, sizeof(double));
_P2(p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10);
}


void _PC3(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->LCntxt.pArg(0);
double p0;
memcpy(&p0, pArg, sizeof(double));
pArg += sizeof(double);
double p1;
memcpy(&p1, pArg, sizeof(double));
pArg = pCD->Strct.pArg(0);
double p2;
memcpy(&p2, pArg, sizeof(double));
pArg += sizeof(double);
double p3;
memcpy(&p3, pArg, sizeof(double));
pArg += sizeof(double);
double p4;
memcpy(&p4, pArg, sizeof(double));
pArg += sizeof(double);
double p5;
memcpy(&p5, pArg, sizeof(double));
_P3(p0,p1,p2,p3,p4,p5);
}


void _PC4(const CallerData* pCD)
{
const char* pArg;
pArg = pCD->Strct.pArg(0);
double p0;
memcpy(&p0, pArg, sizeof(double));
pArg += sizeof(double);
double p1;
memcpy(&p1, pArg, sizeof(double));
pArg = pCD->RCntxt.pArg(0);
double p2;
memcpy(&p2, pArg, sizeof(double));
pArg += sizeof(double);
double p3;
memcpy(&p3, pArg, sizeof(double));
pArg += sizeof(double);
double p4;
memcpy(&p4, pArg, sizeof(double));
pArg += sizeof(double);
double p5;
memcpy(&p5, pArg, sizeof(double));
_P4(p0,p1,p2,p3,p4,p5);
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
	},
	{
		{
			{ D_id }, 1
		},
		{
			{ B_id }, 1
		},
		{
			{ Fd_id }, 1
		},
		_PC2
	},
	{
		{
			{ D_id }, 1
		},
		{
			{ Fd_id }, 1
		},
		{
			{ 0 }, 0
		},
		_PC3
	},
	{
		{
			{ 0 }, 0
		},
		{
			{ D_id }, 1
		},
		{
			{ Fd_id }, 1
		},
		_PC4
	}
};
static const ProductionPrototype iproto[] =
{

};
static const ModuleData moduleData[] =
{
{ "SB",  0 },
{ "EB",  0 },
{ "Fd", sizeof(double)+sizeof(double)+sizeof(double)+sizeof(double)},
{ "B", sizeof(double)+sizeof(double)+sizeof(double)+sizeof(double)+sizeof(double)},
{ "Pitch", sizeof(double)},
{ "Turn", sizeof(double)},
{ "Roll", sizeof(double)},
{ "HRoll",  0 },
{ "Split",  0 },
{ "D", sizeof(double)+sizeof(double)}
};


const ModuleData* GetModuleData(int i)
{ return &(moduleData[i]); }


int NumOfModules()
{ return 10; }
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
} //closing namespace
