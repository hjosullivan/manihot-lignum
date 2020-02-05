#ifndef BMFUNCTORS_H
#define BMFUNCTORS_H
#include <Turtle.h>

template <class TS, class BUD>
class PropagateUpAdjustSegmentDiameter{
public:
  double operator()(double c,TreeCompartment<TS,BUD>* tc)const
  {
    if (dynamic_cast<Axis<TS,BUD>*>(tc)){
	c = 3.0;
    }
    else if (TS* ts = dynamic_cast<TS*>(tc)){
      if (c > 0.0 && GetValue(*ts,LGAomega) == 2.0){
	SetValue(*ts,LGAR,GetValue(*ts,LGAR)*c);
	SetValue(*ts,LGARTop,GetValue(*ts,LGARTop)*c);
      } 
    }
    return c-1.0;
  }
};

template <class TS, class BUD>
class PropagateUpParentDirection{
public:
  PositionVector& operator()(PositionVector& d,TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      //Set the parent segment direction
      SetParentDirection(*ts,d);
      //Pass forward segment direction  in the tree to next connecting
      //segments
      d = GetDirection(*ts);
    }
    return d;
  }
};

//Set material property, also known as Young's modulus
template <class TS, class BUD>
class InsertMaterialProperty{
public:
  double operator()(double E,TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*> (tc)){
      SetValue(*ts,BMAE,E);
    }
    return E;
  }
};

template <class TS, class BUD>
class UpdateAreaMomentOfInertia{
public:
  void operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*> (tc)){
      double I = ts->areaMomentOfInertia(GetValue(*ts,LGAR));
      SetValue(*ts,BMAI,I);
    }
  }
};

template <class TS, class BUD>
class InsertConstantMass{
public:
  double operator()(double cm,TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*> (tc)){
      SetValue(*ts,BMAcm,cm);
    }
    return cm;
  }
};

template <class TS, class BUD>
class InsertPointMass{
public:
  double operator()(double pm,TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*> (tc)){
      SetValue(*ts,BMApm,pm);
    }
    return pm;
  }
};

//The ice thickness model. The  functor assumes the MODEL is a functor
//the  returns  the radial  ice  thickness  as  a function  of  branch
//DIAMETER. NOTE: It  seems that the diameter is  useful to express in
//mm in  the MODEL because the  ice thickness is useful  to express in
//mm.
template <class TS, class BUD, class MODEL>
class InsertIceMass{
public:
  void operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      double Vseg = GetValue(*ts,LGAV);
      double Lseg = GetValue(*ts,LGAL);
      double Rseg = GetValue(*ts,LGAR);
      //The radial ice thicknes, i.e. the thickness of the ice on the
      //segment. Change the segment diameter from meters to mm.
      double rit = max(m(2.0*Rseg*1000.0),0.0);
      //The total radius including ice. Change mm of rit back to meters. 
      double Rtot = Rseg+rit/1000.0;
      double Vtot = PI_VALUE*pow(Rtot,2.0)*Lseg;
      //Volume of the ice
      double Vice = Vtot-Vseg;
      //The mass of the ice
      double Mice = Rho_ICE*Vice;
      SetValue(*ts,BMAcm,Mice);
    }
  }
private:
  MODEL m;//The ice mass model
};

template <class TS, class BUD, class MODEL>
class InsertIceMass2{
public:
  void operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      //double Vseg = GetValue(*ts,LGAV);
      double Lseg = GetValue(*ts,LGAL);
      double Rseg = GetValue(*ts,LGAR);
      //Constant mass per meter (kg/m)
      double cmpm = max(m(Rseg),0.0);
      //The total mass of the ice 
      double Mice = cmpm*Lseg;
      SetValue(*ts,BMAcm,Mice);
    }
  }
private:
  MODEL m;//The ice mass model
};

//After the masses have been inserted into segments
//calculate the loads in each segment. 
template <class TS, class BUD>
class CalculateSegmentLoad{
public:
  void operator()(TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      double ws = GetValue(GetTree(*ts),LGPrhoW)*GetValue(*ts,LGAV);
      //Load caused by self mass ws
      SetValue(*ts,BMAsl,G0_VALUE*ws);
      //Self load per meter
      SetValue(*ts,BMAslpm,GetValue(*ts,BMAsl)/GetValue(*ts,LGAL));
      double cm = GetValue(*ts,BMAcm);
      //Load caused by a constant mass cm on the segment
      SetValue(*ts,BMAcl,G0_VALUE*cm);
      //Constant load per meter
      SetValue(*ts,BMAclpm,GetValue(*ts,BMAcl)/GetValue(*ts,LGAL));
      double pm = GetValue(*ts,BMApm);
      //Load caused by a point mass pm at the end of segment
      SetValue(*ts,BMApl,GetValue(*ts,BMApl)+G0_VALUE*pm);
    }
  }
};
      
//Accumulate the point loads from the  tip of the branches to the base
//of the tree
template <class TS,class BUD>
class AccumulatePointLoad{
public:
  double operator()(double pl,TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      //First add the coming point load to the existing point load
      double pload = GetValue(*ts,BMApl);
      pload = pload+pl;
      SetValue(*ts,BMApl,pload);
      //Constant self load 
      double sload = GetValue(*ts,BMAsl);
      //Constant load on the segment
      double cload = GetValue(*ts,BMAcl);
      //Point load at the end of segment
      pload = GetValue(*ts,BMApl);
      //Total new constant load to be passed to the previous segment
      pl = sload+cload+pload;
    }
    return pl;
  }
};

//Calculate and pass down bending moment caused by constant load
template <class TS, class BUD>
class AccumulateConstantLoadBendingMoment{
public:
  double operator()(double cbm,TreeCompartment<TS,BUD>* tc)const
  {
     if (TS* ts = dynamic_cast<TS*>(tc)){
       //Bending moment coming above
       SetValue(*ts,BMAcM,cbm);
       //Calculate lever arm  which is the length of  the projetion of
       //this segment onto the extension of the mother segment
       double dot = Dot(GetDirection(*ts),GetParentDirection(*ts));
       //If obtuse angle consider the complement acute  angle: PI - acos(dot)
       if (dot < 0.0){
	 double angle = PI_VALUE - acos(dot);
	 //When obtuse angle this section will change the direction of the
	 //lever arm force compared with acute angle
	 dot = -cos(angle);
       }
       //The length of the projection
       PositionVector d = GetDirection(*ts)*dot;
       double projection = d.length();
       //Bending moment by the self load
       double self_load_bm = BendingMomentConstantLoad(GetValue(*ts,BMAslpm),
						       projection);
       //Bending moment constant load
       double constant_load_bm = BendingMomentConstantLoad(GetValue(*ts,BMAclpm),
							   projection);
       return self_load_bm+constant_load_bm;
     }
     return cbm;
  }
};

//Calculate and pass down bending moment caused by point load
template <class TS, class BUD>
class AccumulatePointLoadBendingMoment{
public:
  double operator()(double pbm,TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      //Bending moment coming above
      SetValue(*ts,BMApM,pbm);
      //Calculate lever arm  which is the length of  the projetion of
      //this segment onto the extension of the mother segment
      double dot = Dot(GetDirection(*ts),GetParentDirection(*ts));
      //If obtuse angle consider the complement acute  angle: PI - acos(dot)
       if (dot < 0.0){
	 double angle = PI_VALUE - acos(dot);
	 //When obtuse angle this section will change the direction of the
	 //lever arm force compared with acute angle
	 dot = -cos(angle);
       }
      //The length of the projection
      PositionVector d = GetDirection(*ts)*dot;
      double projection = d.length();

      double pl = GetValue(*ts,BMApl);
      pbm = BendingMomentPointLoad(pl,projection);
      //cout << "PROJ " << projection << " BMPL " << pbm << endl;
    }
    return pbm;
  }
};

//Calculate bending angles and deflections
template <class TS, class BUD>
class BendingAngleAndDeflection{
public:
  Point& operator()(Point& p ,TreeCompartment<TS,BUD>* tc)const
  {
    if (TS* ts = dynamic_cast<TS*>(tc)){
      SetPoint(*ts,p);
      //Calculate the loads and moments perpendicular to the segment
      PositionVector down(0,0,-1.0);
      double dot = Dot(GetDirection(*ts),down);
      double alpha = acos(dot);
      //The angle between 'down' and the direction perpendicular to segment
      double cosbeta=0.0;
      double beta =0.0;
      //Calculate  beta,  the angle  between  down  and the  direction
      //perpendicular to segment
      if (dot >= 0.0){
	//Acute angle, dot > 0.0
	beta = PI_VALUE/2.0 - alpha;
      }
      else{
	//Obtuse angle
	beta = alpha - PI_VALUE/2.0;
      }
      //Special case: if the segment is up or down, no bending force
      if (fabs(dot) == 1.0)
	cosbeta = 0.0;
      else
	cosbeta = cos(beta);
      //The magnitude of the point load perpendicular to segment
      double plperpendicular = GetValue(*ts,BMApl)*cosbeta;
      //The magnitude of the self load perpendicular to segment
      double slperpendicular = GetValue(*ts,BMAsl)*cosbeta;
      //The magnitude of the constant load perpendicular to segment
      double clperpendicular = GetValue(*ts,BMAcl)*cosbeta;
      //The   magnitude  of   the   bending  moment   by  point   load
      //perpendicular to segment
      double plmperpendicular = GetValue(*ts,BMApM)*cosbeta;
      //The magnitude of the bending moment by constant load perpendicular
      //to segment
      double clmperpendicular = GetValue(*ts,BMAcM)*cosbeta;
      //Bending angle caused by  point load perpendicular to segment
      double l = GetValue(*ts,LGAL);
      double E = GetValue(*ts,BMAE);
      double I = GetValue(*ts,BMAI);
      //cout << l << " " << GetValue(*ts,LGAR) << " " << cosbeta << " " << E << " " << I <<endl;
      //cout << GetValue(*ts,BMApl) << " " <<  GetValue(*ts,BMAsl) << " " << GetValue(*ts,BMAcl) 
      //	   << " " <<  GetValue(*ts,BMApM) << endl;

      double pla1 = PointLoadAngle(plperpendicular,l,E,I);
      //Bending angle caused by  self load perpendicular to segment
      double pla2 = ConstantLoadAngle(slperpendicular,l,E,I);
      //Bending angle caused by  self load perpendicular to segment
      double pla3 = ConstantLoadAngle(clperpendicular,l,E,I);
      //Bending  angle  caused  by  bending  moment  perpendicular  to
      //segment, point load
      double pla4 = BendingMomentAngle(plmperpendicular,l,E,I);
      //Bending  angle  caused  by  bending  moment  perpendicular  to
      //segment, constant load
      double pla5 = BendingMomentAngle(clmperpendicular,l,E,I);
      //Total bending angle 
      double angletot = pla1+pla2+pla3+pla4+pla5;
      //Deflections
      //Point load
      double def1 = PointLoadDeflection(plperpendicular,l,E,I);
      //Self load
      double def2 = ConstantLoadDeflection(slperpendicular,l,E,I);
      //Constant load
      double def3 = ConstantLoadDeflection(clperpendicular,l,E,I);
      //Bending moment, point load
      double def4 = BendingMomentDeflection(plmperpendicular,l,E,I);
      //Bending moment, constant load
      double def5 = BendingMomentDeflection(clmperpendicular,l,E,I);
      //Total deflection
      double deftot = def1+def2+def3+def4+def5;
      SetValue(*ts,BMAba,angletot);
      SetValue(*ts,BMAdefl,deftot);
      //Construct a turtle using segment direction
      PositionVector d = GetDirection(*ts);
      //cout << "D1: " << d <<endl;
      PositionVector up(0,0,1);
      PositionVector left = Cross(d,up);
      if (left.length() < R_EPSILON)
	left = Cross(d,PositionVector(1,0,0));
      Turtle t(Point(0,0,0),d,left);
      //Pitch the turtle downwards
      t.pitch(-angletot);
      PositionVector dir = GetHeading(t);
      //cout << "D2: " << dir <<endl;
      //Set the new Z-coordinate for the segment direction
      PositionVector dnew(dir);
      dnew.normalize();
      SetDirection(*ts,dnew);
      //cout << "D3: " << GetDirection(*ts) <<endl;
      //Get the end point of the segment
      p = GetEndPoint(*ts);
      //cout << GetValue(*ts,LGAR) << " " << GetValue(*ts,LGARh) << " " << GetValue(*ts,LGAWs) << " " 
      //<< GetValue(*ts,LGAV) << " " << GetValue(GetTree(*ts),LGPrhoW)*GetValue(*ts,LGAV) << endl;
      //cout << "I " << GetValue(*ts,BMAI) << " " << ts->areaMomentOfInertia( GetValue(*ts,LGAR)) << endl;
      if (angletot*180.0/PI_VALUE > 0)
      	cout << GetValue(*ts,LGAomega) << " R " << GetValue(*ts,LGAR) << " L " << GetValue(*ts,LGAL) 
	     << " Ws " << GetValue(GetTree(*ts),LGPrhoW)*GetValue(*ts,LGAV)  
      	     << " I " << GetValue(*ts,BMAI) << " E " << GetValue(*ts,BMAE) << " Angle " << angletot << " " 
      	     << angletot*180.0/PI_VALUE << " Deflection " << deftot << " PL " << plperpendicular <<" "
      	     << " SL " << slperpendicular << " CL " << clperpendicular << " BMPL "<< plmperpendicular 
	     << " BMCL " << clmperpendicular << " beta " << beta << " " <<  beta*180.0/PI_VALUE << " cosbeta " << cosbeta <<endl;
	  
    }
    return p;
  }
};
      
#endif      
