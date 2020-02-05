#ifndef MANIOT_H
#define MANIOT_H

#include <Lignum.h>
#include <BMComponent.h>
class ManiotBud;
class ManiotSegment;
class BMManiotBud;
class BMManiotSegment;

//Sugar maple tree
class ManiotTree: public Tree<ManiotSegment,ManiotBud>{
 public:
  ManiotTree(const Point& p, const PositionVector d)
    :Tree<ManiotSegment,ManiotBud>(p,d){}
};

class BMManiotTree: public Tree<BMManiotSegment,BMManiotBud>{
 public:
  BMManiotTree(const Point& p, const PositionVector d)
    :Tree<BMManiotSegment,BMManiotBud>(p,d){}
};

//Sugar maple segment
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

class BMManiotSegment:
  public HwTreeSegment<BMManiotSegment,BMManiotBud,Ellipse>,public BMComponent{
public:
  //Constructor  for Sugar  maple  segment. The  argument  list is  as
  //assumed  by L-system. If  you need  additional arguments  add them
  //after the last one (the tree) and provide default values
  BMManiotSegment(const Point& p,const PositionVector& d,const LGMdouble go,
		      const METER l,const METER r,const METER rn,
		      Tree<BMManiotSegment,BMManiotBud>* t)
    :HwTreeSegment<BMManiotSegment,BMManiotBud,Ellipse>(p,d,go,l,r,rn,t),
     BMComponent(r){}
};

class BMManiotBud: public Bud<BMManiotSegment,BMManiotBud>{
 public:
  //Constructor for Sugar maple bud.   The argument list is as assumed
  //by L-system. If  you need additional arguments add  them after the
  //last one (the tree) and provide default values
  BMManiotBud(const Point& p,const PositionVector& d,const LGMdouble omega, 
		Tree<BMManiotSegment,BMManiotBud>* tree)
    :Bud<BMManiotSegment,BMManiotBud>(p,d,omega,tree){}
};

//Sugar maple bud
class ManiotBud: public Bud<ManiotSegment,ManiotBud>{
 public:
  //Constructor for Sugar maple bud.   The argument list is as assumed
  //by L-system. If  you need additional arguments add  them after the
  //last one (the tree) and provide default values
  ManiotBud(const Point& p,const PositionVector& d,const LGMdouble omega, 
		Tree<ManiotSegment,ManiotBud>* tree)
    :Bud<ManiotSegment,ManiotBud>(p,d,omega,tree){}
};

#endif
