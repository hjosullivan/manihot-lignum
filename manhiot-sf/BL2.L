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
open BL2;

//lsys.h impelemnts the rewriting
#include <lsys.h>

const double LSEG = 1.5;
const double RADIUS = 0.15;
const double RADIUS_TOP = 0.15;
const double R2 = 0.10;
const double L020 = 0.70;
const double RTHIN = 0.05;
const double RTHIN_TOP = 0.05;
const double A90  = PI_VALUE/2.0;
const double A45  = 45.0*PI_VALUE/180.0;
static double sign = 1.0;
//declare the modules your need 
//Fd(length,radius,radius_top)
module Fd(double,double,double);
module F(double);
//B: Bud()
module B(double);
module Pitch(double);
module Roll(double);
module Turn(double);
//Define the Start corresponding to the axiom
Start:
{

  produce Fd(LSEG,RADIUS,RADIUS_TOP) SB() Pitch(A45)B(2)EB() B(1);
 
}

B(go):
{
  if (go ==1)
    produce Fd(LSEG,RADIUS,RADIUS_TOP) Roll(A90) SB() Pitch(A45)B(2) EB() B(go);
  else if (go==2){
     sign=-sign;
     produce Fd(L020,R2,R2) SB()Turn(sign*A45)B(go+1) EB() B(go);
  }
  else 
    produce Fd(L020,RTHIN,RTHIN_TOP) SB() EB() B(go);

}

//This is a ToDO for Jari: interpretation typically
//defines the graphical visualization of symbols. But
//we visualize LIGNUM and thus this is practically 
//unnecessary for us. However, "lc2" cannot compile
//L-files unless you have one  interpretation   

interpretation:

F(s) :
{
  ;
}

//Finally, "close" the "namespace"
close BL2;
