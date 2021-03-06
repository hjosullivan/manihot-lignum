//Defines ran3 etc
#include <mathsym.h>
using namespace cxxadt;

//Defines headers necessary for lsystem
#include <lengine.h>

//Start the namespace (compiles to "namespace Pine{")
//The matching "close" statement closes the namespace 
open ca90;

//Defines the lsystem rewriting process. 
#include <lsys.h>

module X();
module O();

derivation length: 9;

StartEach:
{
  cout << endl;
}

Start:
{
  produce O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()X()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O()O();
}

O()< O()>O():
{

  cout << "O" << flush;
  produce O();          
}

O()< O()>X():
{
  cout << "*" << flush;
  produce X();
}

O()< X()>O():
{
  cout << "O" << flush;
  produce O();
}

O()< X()>X():
{
  cout << "*" << flush;
  produce X();
}

X()< O()>O():
{
  cout << "*" << flush;
  produce X();
}

X()< O()>X():
{
  cout << "O" << flush;
  produce O();
}

X()<X()> O():
{
  cout << "*" << flush;
  produce X();
}

 X()<X()>X():
{
  cout << "O" << flush;
  produce O();
}

O():
{
  cout << "O" << flush;
  produce O();
}

//This interpretation  is a ToDo for me.
//Now you must define at least one dummy interpretation.
//I must study how to alter the l2c to avoid  interpretation. 
//Interpretation separates model/symbols from 
//their (graphics) interpretation but for us LIGNUM is visualized by 
//Mika.  
interpretation:

X():
{
  ;
}

//Closes the namespace (compiles simply to '}')
close ca90;
