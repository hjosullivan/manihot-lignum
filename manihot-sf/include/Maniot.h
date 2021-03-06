#ifndef MANIOT_H
#define MANIOT_H

#include <Lignum.h>
#include <BMComponent.h>
class ManiotBud;
class ManiotSegment;
class BMManiotBud;
class BMManiotSegment;

//SMBD=SugarMapleBudData
//SMBRP=SugarMapleBudRelativePosition
//SMD=SugarMapleData
enum SMBD {SMBRP,SMD};

//SMLN=SugarMapleLeafNumber
//SMAD=SugarMapleApicalDominance
//SMBF=SugarMapleBudFlush
//SMBS=SugarMapleBudSize
//SMMAXLEAF=SugarMapleMaxLeaf
//SMMFSLA=SugarMapleFoliageRespirationAsAFunctionOfSLA
//SMLN=SugarMapleLeafNumber
//SMLS=SugarMapleLeafSize
//SMMSL=SugarMapleMinimumSegmentLength
//SMPL=SugarMaplePetioleLength
//SMPRCE=SugarMapleRadiationConversionEfficiency
//SMSLA= SugarMapleSpecific LeafArea
//SMVI=SugarMapleVigorIndex
enum SMFN {SMAD,SMBF,SMBS,SMMAXLEAF,SMMFSLA,SMLN,SMLS,
           SMMSL,SMPL,SMRCE,SMSLA,SMVI};

//Carbon pool: GetValue(tree,SMCpool), SetValue(tree,SMCpool,value)
enum SMCPOOL {SMCpool};

//Bud data
//The  class  ManiotBudData  is  a  structure that  is  used  to  exchange
//information   in  L-system   for  sugar   maple  and   Lignum  model
//implementing th metabolism for sugar maple. The implementation might
//be an overkill (the easiest way would probably be a simple structure
//and access  the fields directly). The structure  carries 1) LGAstate
//2) LGAstatus  3)  LGAomega and  the  4)  direction  to of  the  bud.
//SugarMapleBud  has  SetValue/GetValue   to  be  used  internally  by
//lstringToLignum and  lignumToLstring. And here are  the caveats when
//using structures. 1) Use structures  or classes in an L-system file,
//do not  use pointers or references  to structures or  a classes (the
//l2c compiler  cannot translate  them).  2) Use  basic types  as data
//members,   e.g.   int,  double   etc.   Do   not  use   pointers  or
//references. The size of the class or structure needs to be known and
//pointers will cause  surprises. In practise do not  have for example
//PositionVector as  a data member.  In PositionVector  the (x,y,z) is
//represented in a  vector<double> v and as it is  a vector defined in
//STL, the sizeof(v) is something else than the size of three floating
//point numbers  we need to  know. The class  Point should do  (it has
//explicitly double x,y, and z);  I have not tried with nested classes
//though. 3) If  you want to pass the information  of the direction of
//the bud in  a structure like in ManiotBudData,  recall the SetValue will
//override the work  of the turtle. Here for  example the direction of
//the bud is  passed back to L-system with  GetValue but not retrieved
//from L-system to bud with SetValue.  4) Finally, if you add new data
//members  to  ManiotBudData  remember  to  recompile  also  the  L-system
//file. Otherwise strange errors  will occure.  After all, having said
//the above, what is  needed at the minimum is a BUD  b, a structure S
//s,  symbol  B(S)  in  an  L-system and  a  name  (enumeration)  with
//SetValue(b,s,name) and s = GetValue(b,name).
class ManiotBudData{
  friend LGMdouble GetValue(const ManiotBudData& data,LGMAD name);
  friend LGMdouble SetValue(ManiotBudData& data,LGMAD name,LGMdouble value);
  friend LGMdouble GetValue(const ManiotBudData& data,SMBD name);
  friend LGMdouble SetValue(ManiotBudData& data,SMBD name,LGMdouble value);

  friend PositionVector GetDirection(const ManiotBudData& data);
  friend void SetDirection(ManiotBudData& data,const PositionVector& d);
 public:
  ManiotBudData()
    :state(ALIVE),status(1.0),omega(1.0),brp(1.0),
    x(0.0),y(0.0),z(1.0){}
  //Copy constructor
  ManiotBudData(const ManiotBudData& d)
    :state(d.state),status(d.status),omega(d.omega),brp(d.brp),
    x(d.x),y(d.y),z(d.z){}
  ManiotBudData(LGMdouble state1,LGMdouble status1,LGMdouble omega1,
	    LGMdouble brp1)
    :state(state1),status(status1),omega(omega1),brp(brp1),
    x(0.0),y(0.0),z(1.0){}
  ManiotBudData(LGMdouble state1,LGMdouble status1,LGMdouble omega1,
	    LGMdouble brp1,const PositionVector& d)
    :state(state1),status(status1),omega(omega1),
    brp(brp1){SetDirection(*this,d);}
  //The assignment
  ManiotBudData& operator=(const ManiotBudData& data)
    {
      state = data.state;
      status = data.status;
      omega = data.omega;
      brp = data.brp;
      //Direction
      x = data.x;
      y = data.y;
      z = data.z;
      return *this;
    }
 private:
  LGMdouble state;  //Dead, alive, dormant
  LGMdouble status; //[0:1] meaning relative leaf size
  LGMdouble omega;  //branching order
  LGMdouble brp;    //[0:1] meaning  the relative position  of the bud
  //in a segment
  //Direction is explicitely three floating point numbers;
  LGMdouble x;
  LGMdouble y;
  LGMdouble z;
};

inline LGMdouble GetValue(const ManiotBudData& data,LGMAD name)
{
  if (name == LGAstate)
    return data.state;
  else if (name == LGAstatus)
    return data.status;
  else if (name == LGAomega)
    return data.omega;
  else{
    cout << "ManiotBudData unknown attribute: " << name << endl;
    return 0.0;
  }
}

inline LGMdouble SetValue(ManiotBudData& data,LGMAD name,LGMdouble value)
{
  LGMdouble old_value = GetValue(data,name);
  if (name == LGAstate)
    data.state = value;
  else if (name == LGAstatus)
    data.status = value;
  else if (name == LGAomega)
    data.omega = value;
  else{
    cout << "ManiotBudData unknown attribute: " << name << endl;
  }
  return old_value;
}

inline LGMdouble GetValue(const ManiotBudData& data,SMBD name)
{
  if (name == SMBRP)
    return data.brp;
  else
    cout << "ManiotBudData GetValue unknown SMBD attribute: " << name << endl;
  return data.brp;
}

inline LGMdouble SetValue(ManiotBudData& data,SMBD name,LGMdouble value)
{
  LGMdouble old_value = GetValue(data,name);
  if (name == SMBRP)
    data.brp = value;
  return old_value;
}


inline PositionVector GetDirection(const ManiotBudData& data)
{
  return PositionVector(data.x,data.y,data.z);
}

inline void SetDirection(ManiotBudData& data,const PositionVector& d)
{
  data.x = d.getX();
  data.y = d.getY();
  data.z = d.getZ();
}

// Maniot tree
class ManiotTree: public Tree<ManiotSegment,ManiotBud>{
  friend const ParametricCurve& GetFunction(const ManiotTree& t,SMFN name){
    switch (name){
    case SMAD://Apical Dominance
      return t.apical_dominance;
    case SMBF://Bud Flush
      return t.bud_flush;
    case SMBS://Bud Size
      return t.bud_size;
    case SMMAXLEAF://max leaf size
      return t.max_leaf;
    case SMMFSLA://leaf respiration rate as a function of SLA
      return t.mf_sla;
    case SMLN://Leaf pair Number
      return t.leaf_number;
    case SMLS://Leaf Size
      return t.leaf_size;
    case SMMSL://Minimum segment length
      return t.min_segment_length;
    case SMPL://Petiole length
      return t.petiole_length;
    case SMRCE://Radiation conversion efficiency
      return t.rce;
    case SMSLA://Specific leaf area
      return t.sla;
    case SMVI://Vigor index
      return t.vigor_index;
    default:
      cout << "ManiotTree Unknown Function: " << name << endl;
      throw ParametricCurve();
    }
  }
 public:
  ManiotTree(const Point& p, const PositionVector d)
    :Tree<ManiotSegment,ManiotBud>(p,d){}
 private:
  ParametricCurve leaf_number; //f(segment length), domain R, range N0,
  //number of leaf pairs.
  ParametricCurve leaf_size;   //f(relative   position   in   segment)
  //domain  [0:1], range  [0:1], relative
  //leaf size.
  ParametricCurve bud_size;    //f(rel pos  in segment), domain [0:1],
  //range [0:1], relative bud size.
  ParametricCurve bud_flush;   //f(I)    domain   [0:1],    range   [0:1],
  //probability a bud to flush.
  ParametricCurve apical_dominance; //f(I)  domain   [0:1],  range  [0:1],
  //apical dominance.
  ParametricCurve vigor_index; //f(vi),  domain  [0:1],  range  [0:1],
  //function of vigor index
  ParametricCurve min_segment_length; //The minimum segment length
  ParametricCurve petiole_length; //The  petiole  length  as a  f(Af),
  //leaf size.
  ParametricCurve rce;           //f(I)   domain   R   range   R,   the
  //photosynthetic    efficiency   i.e.,
  //radiation    conversion   efficency:
  //photosynthesis       divided      by
  //intercepted  radiation  in different
  //light climates
  ParametricCurve sla; //Specific leaf area as a function of Qin
  ParametricCurve max_leaf; //Max leaf as a function of light Qin
  ParametricCurve mf_sla;//Leaf respiration rate as a function of SLA
  KGC carbon_pool; //Reserve   of   carbon,    i.e.    part   of   net
  //photosynthates can be put aside to be used later
};


//Maniot segment
class ManiotSegment:
  public HwTreeSegment<ManiotSegment,ManiotBud,Ellipse>{
 public:
  //Constructor  for Sugar  maple  segment. The  argument  list is  as
  //assumed  by L-system. If  you need  additional arguments  add them
  //after the last one (the tree) and provide default values
  ManiotSegment(const Point& p,const PositionVector& d,const LGMdouble go,
		    const METER l,const METER r,const METER rn,
		    Tree<ManiotSegment,ManiotBud>* t)
    :HwTreeSegment<ManiotSegment,ManiotBud,Ellipse>(p,d,go,l,r,rn,t){}
};

//Maniot bud
class ManiotBud: public Bud<ManiotSegment,ManiotBud>{
  friend ManiotBudData SetValue(ManiotBud& b,SMBD name,const ManiotBudData& d);
  friend ManiotBudData GetValue(const ManiotBud& b,SMBD name);
  public: 
  //Constructor for Sugar maple bud.   The argument list is as assumed
  //by L-system. If  you need additional arguments add  them after the
  //last one (the tree) and provide default values
  ManiotBud(const Point& p,const PositionVector& d,const LGMdouble omega, 
	    Tree<ManiotSegment,ManiotBud>* tree)
    :Bud<ManiotSegment,ManiotBud>(p,d,omega,tree), brp(0.0){}
  private:
  LGMdouble brp; //[0:1] meaning the relative position of the bud in a
  //segment
  };

//Create leaves
class CreateManiotLeaves{
 public:
  CreateManiotLeaves(METER semi_major, METER semi_minor)
    :r1(semi_major),r2(semi_minor),rlsize(0.0){}
  vector<PositionVector>&
    operator()(vector<PositionVector>& v,
	       TreeCompartment<ManiotSegment,ManiotBud>* tc)const;
  double r1; //Relative length of the semi major axis of the leaf ellipse
  double r2; //Relative length of the semi minor axis of the leaf ellipse
  mutable double rlsize; //Relative leaf size
};

//SetValue and GetValue for the structure ManiotBudData in L-systems
inline  ManiotBudData SetValue(ManiotBud& b, SMBD name, const ManiotBudData& data)
{
  ManiotBudData old_data = GetValue(b,name);
  if (name == SMD){
    SetValue(b,LGAstate,GetValue(data,LGAstate));
    SetValue(b,LGAstatus,GetValue(data,LGAstatus));
    SetValue(b,LGAomega,GetValue(data,LGAomega));
    b.brp = GetValue(data,SMBRP);
    //Do not  update the direction, if  you do, you  will override the
    //work of the turtle.
  }
  else{
    cout << "Sugar Maple Bud SetValue error, no structure: "
	 << name << endl;
  }
  return old_data;
}

inline ManiotBudData GetValue(const ManiotBud& b, SMBD  name)
{
  ManiotBudData data(ALIVE,0.0,0.0,0.0);
  if (name == SMD){
    SetValue(data,LGAstate,GetValue(b,LGAstate));
    SetValue(data,LGAstatus,GetValue(b,LGAstatus));
    SetValue(data,LGAomega,GetValue(b,LGAomega));
    SetValue(data,SMBRP,b.brp);
    SetDirection(data,GetDirection(b));
  }
  else{
    cout << "Sugar Maple Bud Data GetValue error, no structure: "
	 << name << endl;
  }
  return data;
}

#endif
