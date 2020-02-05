#ifndef BMCOMPONENT_H
#define BMCOMPONENT_H
//Green et al Ch4 Mechanical properties  of wood 
//E red maple 9.600 Mpa (green)  1.13x10^10 N/m^2  (12%) 
//E sugar maple (green) 10 700  MPa = 10 700 MN/m^2=10 700 * 10^6N/m^2 = 1.07*10^10N/m^2
//E sugar maple (Wikipedia) 12.656 GPa 12.656 GN/m^2 = 12.656*10^9N/m^2
const double E_acer_saccharum = 1.07e+10;
//const double E_acer_saccharum = 12.656e+9;
enum BMAD {BMAslpm,BMAsl,BMAcM,BMApM,BMAclpm,BMAcl,BMAcm,BMApl,BMApm,
	   BMAE,BMAI,BMAZ,BMAM,BMAba,BMAdefl};
//BMAslpm = Self load per meter
//BMAsl   = Self load
//BMAcM   = Bending moment caused by constant load
//BMApM   = Bending moment caused by point load
//BMAclpm = Constant load per meter
//BMAcl   = Constant load
//BMAcm   = Constant mass
//BMApl   = Coint load
//BMApm   = Point mass
//BMAE    = Young's modulus (material property)
//BMAI    = Area moment of inertia
//BMAZ    = Section modulus
//BMAba   = Bending angle 
//BMAdefl = Deflection

class BMComponent{
  friend double GetValue(const BMComponent& bmc, const BMAD name);
  friend double SetValue(BMComponent& bmc,const BMAD name, double value);
  friend void SetParentDirection(BMComponent& bmc,const PositionVector& d);
  friend PositionVector GetParentDirection(const BMComponent& bmc); 
public:
  BMComponent(double radius)
    :self_load_per_meter(0.0),self_load(0.0),
     constant_load_per_meter(0.0),constant_load(0.0),point_load(0.0),
     E(0.0),I(0.0),Z(0.0),M_point(0.0),M_constant(0.0),
     bending_angle(0.0),deflection(0.0)
  {
    I = PI_VALUE*pow(radius,4.0)/4.0;
    Z = PI_VALUE*pow(radius,3.0)/4.0;
  }
  double areaMomentOfInertia(double radius){
    return PI_VALUE*pow(radius,4.0)/4.0;
  }
  double sectionModulus(double radius){
    return PI_VALUE*pow(radius,3.0)/4.0;
  }
private:
  double self_load_per_meter;//segment own load per meter [N/m]
  double self_load;//segment own constant load [N]
  double constant_load_per_meter;//load of ice and snow per meter [N/m]
  double constant_load;//ice and snow on the segment [N]
  double point_load; //point load at the end of segment plus the load caused
		     //by following segments [N]
  double constant_mass;//constant mass on the segment [kg]
  double point_mass;//point mass at the end of segment [kg] 
  double E;//Young's modulus (material property) [N/m^2]
  double I;//Area moment of inertia [m^4]
  double Z;//Section modulus [m^3]
  double M_point;//Bending  moment  of point  loads  of the  following
		 //segments [Nm]
  double M_constant;//Bending   moment  of   constant  loads   of  the
		    //following segments [Nm]
  double bending_angle;//Bending angle of the segment [radian]
  double deflection;//deflection of the segment [m]
  PositionVector d;//direction of the mother segment
};

inline
double GetValue(const BMComponent& bmc, const BMAD name)
{
  if (name == BMAslpm)
    return bmc.self_load_per_meter;
  else if (name == BMAsl)
    return bmc.self_load;
  else if (name == BMAclpm)
    return bmc.constant_load_per_meter;
  else if (name == BMAcl)
    return bmc.constant_load;
  else if (name == BMAcM)
    return bmc.M_constant;
  else if (name == BMApM)
    return bmc.M_point;
  else if(name == BMAcm)
    return bmc.constant_mass;
  else if (name == BMApl)
    return bmc.point_load;
  else if (name == BMApm)
    return bmc.point_mass;
  else if (name == BMAE)
    return bmc.E;
  else if (name == BMAI)
    return bmc.I;
  else if (name == BMAZ)
    return bmc.Z;
  else if (name == BMAba)
    return bmc.bending_angle;
  else if (name == BMAdefl)
    return bmc.deflection;
  else{
    cerr << "BMComponent GetValue unknown name " << name <<endl;
    cerr << "Returning 0" <<endl;
    return 0;
  }
}

inline double SetValue(BMComponent& bmc, const BMAD name, const double value)
{
  double old_value = GetValue(bmc,name);
  if (name == BMAslpm)
    bmc.self_load_per_meter = value;
  else if (name == BMAsl)
    bmc.self_load = value;
  else if (name == BMAclpm)
    bmc.constant_load_per_meter = value;
  else if (name == BMAcl)
    bmc.constant_load = value;
  else if (name == BMAcM)
    bmc.M_constant = value;
  else if (name == BMApM)
    bmc.M_point = value;
  else if (name == BMAcm)
    bmc.constant_mass = value;
  else if (name == BMApl)
    bmc.point_load = value;
  else if (name == BMApm)
    bmc.point_mass = value; 
  else if (name == BMAE)
    bmc.E = value;
  else if (name == BMAI)
    bmc.I = value;
  else if (name == BMAZ)
    bmc.Z = value;
  else if (name == BMAba)
    bmc.bending_angle = value;
  else if (name == BMAdefl)
    bmc.deflection = value;
  return old_value;
}

inline 
void SetParentDirection(BMComponent& bmc, const PositionVector& d)
{
  bmc.d = d;
}
inline 
PositionVector GetParentDirection(const BMComponent& bmc)
{
  return bmc.d;
}

class BendingData{
public:
  double M;//Bending moment to segment behind
  double point_load;//Point load to segment behind
  double length;//Length of the lever arm causing bending moment
};

//Bending moment caused by a point load (N) at the end of segment of length l
inline
double BendingMomentPointLoad(double F, double l)
{
  return F*l;
}

//Bending moment caused by a constant load (N/m) on the segment of length l
inline
double BendingMomentConstantLoad(double F, double l)
{
  if (l > 0.0)
    return (F*pow(l,2.0))/2.0;
  else
    return 0.0;
}



//The following six function  calculate bending angles and deflections
//of   a   segment   under   three  different   loadings.    See   Den
//Hartog. 1949. Strength of materials pp. 85-88. Angles are in radians
//and deflections are in meters.

//Bending angle in radians caused by  bending moment M to segment of length l
//Note: the bending moment M measures as Nm.
inline
double BendingMomentAngle(double M, double l, double E, double I)
{
  return (M*l)/(E*I);
}

//Deflection caused by bending moment to a segment of length l
//Note: the bending moment measures as Nm
inline
double BendingMomentDeflection(double M, double l, double E, double I)
{
  if (l > 0.0)
    return (M*pow(l,2.0))/(2.0*E*I);
  else
    return 0.0;
}

//Bending angle caused by point load F to a segment of length l
//Note: the point load measures in N
inline
double PointLoadAngle(double F, double l, double E, double I)
{
  if (l > 0.0){
    return (F*pow(l,2.0))/(2.0*E*I);
  }
  else
    return 0.0;

}

//Deflection caused by point load F to a segment of length l
inline
double PointLoadDeflection(double F, double l, double E, double I)
{
  if (l > 0.0)
    return (F*pow(l,3.0))/(3.0*E*I);
  else
    return 0.0;
}

//Bending angle caused by constant load F to a segment of length l
//Note: the constant load F measures as N/m
inline
double ConstantLoadAngle(double F, double l, double E, double I)
{
  if (l > 0.0)
    return (F*pow(l,3.0))/(6.0*E*I);
  else
    return 0.0;
}

//Deflection caused by constant load F to a segment of length l
//Note: the constant load F measures as N/m
inline
double ConstantLoadDeflection(double F, double l, double E, double I)
{
  if (l > 0.0)
    return (F*pow(l,4.0))/(8.0*E*I);
  else
    return 0.0;
}


#endif
