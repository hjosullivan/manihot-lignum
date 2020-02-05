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
open BL1;

//lsys.h impelemnts the rewriting
#include <lsys.h>

const double LSEG = 0.9;
const double RADIUS = 0.15;
const double RADIUS_TOP = 0.15;
const double A90  = PI_VALUE/2.0;
const double A45  = A90/2.0;
//The declare the modules your need 
//Fd(length,radius,radius_top)
module Fd(double,double,double);
module F(double);
//B: Bud()
module B();
module Pitch(double);
module Roll(double);

//Define the Start corresponding to the axiom
Start:
{

  produce Fd(LSEG*4.0,RADIUS,RADIUS_TOP) SB() Roll(-A90) Pitch(A45)B()EB() B();
 
}

B():
{
  produce Fd(LSEG,RADIUS,RADIUS_TOP) B();
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
close BL1;
