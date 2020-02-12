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
open Maniot;

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
module Fd(double, double,double,double);
//Status = ALIVE,DEAD 
//B: Bud(AxisType,Age,PhysAge,Status)
module B(double,double,double,double,double);
module Pitch(double);
module Turn(double);
module Roll(double);
module HRoll();
//module Split();
module D(double,double);
ignore: Roll Pitch Turn HRoll;

//Define the Start corresponding to the axiom
Start:
{
  cout << init << endl;
  u.init(init);
  double pitch1 = ba(MIN_PITCH,MAX_PITCH,u);
  double pitch2 = ba(MIN_PITCH,MAX_PITCH,u);
  produce Fd(LSEG,RA1,RA1,A1) SB() Pitch(pitch1)  B(A2,1,1,ALIVE,0)EB() 
                              SB() Roll(PI_VALUE) Pitch(pitch2)  B(A2,1,1,ALIVE,0)EB()
                                   Roll(PI_VALUE/2.0) B(A1,1,1,DEAD,0);
}

//Bud produces tree segments and lateral buds
B(axis_type,age,phys_age,status,pitch_angle):
{
  double ran = u(1);
  double pitch1 = ba(MIN_PITCH,MAX_PITCH,u);
  double pitch2 = ba(MIN_PITCH,MAX_PITCH,u);
  if (status==ALIVE && axis_type == A1){
      produce Fd(LSEG,RA1,RA1,A1) SB() Pitch(pitch1)  B(A2,1,1,ALIVE,pitch_angle)EB() 
                                  SB() Roll(PI_VALUE) Pitch(pitch2)  B(A2,1,1,ALIVE,pitch_angle)EB()
                    Roll(PI_VALUE/2.0) B(A1,1,1,DEAD,pitch_angle);
   }
   else if (status == ALIVE && axis_type == A2){
   	double max_pitch_angle = MAX_FORK;
        if (pitch_angle >= 85.0*PI_VALUE/180.0){
            max_pitch_angle = 0.0;
	}
        double new_pitch_angle = pitch_angle + max_pitch_angle;
   	produce Fd(LA2, RA1, RA1, axis_type) SB() Turn(MIN_TURN) Pitch(max_pitch_angle)B(A3,1,1,ALIVE,new_pitch_angle)EB()
			      	       SB() Turn(-MIN_TURN) Pitch(-max_pitch_angle) B(A3,1,1,ALIVE,new_pitch_angle)EB()
				       B(axis_type,1,1,DEAD,new_pitch_angle);
   }
   else if (status == ALIVE && axis_type > A2){
   	double max_pitch_angle = MAX_FORK;
	if (pitch_angle >= 85.0*PI_VALUE/180.0){
	   max_pitch_angle = 0.0;
	}
	double new_pitch_angle = pitch_angle + max_pitch_angle;
   	produce Fd(LA3, RA1, RA1, axis_type) SB() Turn(MIN_TURN) Pitch(-max_pitch_angle) B(A4,1,1,ALIVE,new_pitch_angle) EB()
   	   	   	     		SB() Turn(-MIN_TURN) Pitch(-max_pitch_angle) B(A4,1,1,ALIVE,new_pitch_angle) EB()
					B(axis_type,1,1,DEAD,new_pitch_angle);
   }
   else{
   produce B(axis_type,age,phys_age,status,pitch_angle);
   }
}


//Left hand and right hand context or Bud
D(THICK,c) < B(axis_type,age,phys_age,status,pitch_angle) > Fd(l1,r1,rtop1,axis_type1):
{
if (THICK > 0.0)
produce Fd(l1,THICK,THICK,axis_type1)D(THICK/2.0,1.0);
}

//Left hand context for Segment symbol
D(THICK,c) < Fd(l1,r1,rtop1,axis_type1):
{  if (THICK > 0.0)
produce Fd(l1,THICK,THICK,axis_type1)D(THICK/2.0,1.0);
}

//Right hand context for Diameter symbol
D(THICK,c) > Fd(l1,r1,rtop1,axis_type1):
{  if (THICK > 0.0)
      produce Fd(l1,THICK,THICK,axis_type1)D(THICK/2.0,1.0);
}
//This is a ToDO for Jari: interpretation typically
//defines the graphical visualization of symbols. But
//we visualize LIGNUM and thus this is practically 
//unnecessary for us. However, "lc2" cannot compile
//L-files unless you have one  interpretation   

interpretation:



//Finally, "close" the "namespace"
close Maniot;
