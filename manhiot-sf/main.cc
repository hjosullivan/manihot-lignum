
//Include Lignum implementation 
#include <algorithm>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <Lignum.h>
#include <Bisection.h>
#include <CompareLeaves.h>
//Include the implementation of the tree segment and bud
#include <Maniot.h>
#include <BMFunctors.h>
#include <IceModels.h>
#include <DataFile.h>
#include <Polygon.h>

//Includes all kinds of stuff, turtle graphics etc.
#include <lengine.h>

#include <XMLTree.h>

//and L-system for sugarmaple, sugarmaple.L
namespace BL1{
#include <LSystem.h>
}

namespace BL2{
#include <LSystem.h>
}

namespace Maniot{
#include <LSystem.h>
}

void Usage()
{
  cout << "Usage: ./maniot -iter  <num> -r <seed> -load <num> -model <num> -x <num> -y <num> -L <num> -xml <name>" << endl;
  exit(0);
}

//Initialize random number generator
int init = 1;
int main(int argc, char** argv)
{
  int iterations = 0;
  int model = 0;
  double cm = -1.0;
  double x = 0.0;
  double y = 0.0;
  int L = 0;
  string argument;
  string file;
  if (argc < 6){
    Usage();
    exit(0);
  }
  vector<double> v(200);
  for (int i=0; i < 200; i++)
    v[i] = i;
  list<double> l;
  for (int i=0; i < 200; i++)
    l.push_back(i);

  ParseCommandLine(argc,argv,"-iter",argument);
  if (!argument.empty())
    iterations = atoi(argument.c_str());
  argument.clear();
  ParseCommandLine(argc,argv,"-load",argument);
  if (!argument.empty())
    cm = atof(argument.c_str());
  argument.clear();
  ParseCommandLine(argc,argv,"-model",argument);
  if (!argument.empty())
    model = atoi(argument.c_str());
  argument.clear();
  ParseCommandLine(argc,argv,"-x",argument);
  if (!argument.empty())
    x = atof(argument.c_str());
  argument.clear();
  ParseCommandLine(argc,argv,"-y",argument);
  if (!argument.empty())
    y = atof(argument.c_str());
  argument.clear();
  ParseCommandLine(argc,argv,"-L",argument);
  if (!argument.empty())
    L = atoi(argument.c_str());
  argument.clear();
  ParseCommandLine(argc,argv,"-xml",file);
  argument.clear();
  //The random number generator to vary tree architectures
  ParseCommandLine(argc,argv,"-r",argument);
  if (!argument.empty())
    init = -atoi(argument.c_str());
  argument.clear();
  
  BMManiotTree maniot1(Point(x,y,0),PositionVector(0,0,1.0));  
  BMManiotTree maniot3(Point(x,y,0),PositionVector(0,0,1.0));  

  BL1::LSystem<BMManiotSegment,BMManiotBud> maniotl1;
  BL2::LSystem<BMManiotSegment,BMManiotBud> maniotl2;
  Maniot::LSystem<BMManiotSegment,BMManiotBud> maniotl3;
  SetValue(maniot3,LGPrhoW,676.0);
  //Expand axiom, first initial structure
  maniotl1.start();
  maniotl1.lstringToLignum(maniot1);
  maniotl2.start();
  maniotl2.lstringToLignum(maniot1);
  maniotl3.start();
  maniotl3.lstringToLignum(maniot3);
  
  cout << "L == " << L <<endl;
  cout << "Iterations " << iterations << endl;
  for (int iter=0; iter < iterations; iter++){
    maniotl3.derive();
    cout << "Iter: " << iter << " Expand done" << endl;
    //update sugar maniot structure
    maniotl3.lstringToLignum(maniot3);
    //cout << "lstringToLignum done" << endl;
    maniotl3.lignumToLstring(maniot3);
      //cout << "lignumToLString done" << endl; 
  }
  //Clean up.
  maniotl1.end();
  maniotl2.end();
  if (!file.empty()){
    XMLDomTreeWriter<BMManiotSegment, BMManiotBud> writer;
    if (L < 3)
      writer.writeTreeToXML(maniot1, file);
    else
      writer.writeTreeToXML(maniot3, file);
  }
  exit(0);
}
