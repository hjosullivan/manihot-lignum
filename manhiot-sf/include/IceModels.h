#ifndef ICE_MODELS_H
#define ICE_MODELS_H

//The Simple Ice Model assume simple regression between the radial ice
//thickness  (thickness of  the  ice  on a  segment)  and the  segment
//diameter in mm.
class SimpleIceModel{
public:
  double operator()(double Dsegmm)const
  {
    return max(-0.073910*Dsegmm+9.506872,0.0);
  }
};

//This Gompertz function is intended to model kg/m of ice
//on segment. For example segment with radius 0.01m (1cm)
//will have 0.6 kg/m of ice. 
class IceModel2{
public:
  double operator()(double Rsegm)const
  {
    return max(10000.0*exp(-13.0*exp(-30.0*Rsegm)),0.0);
  }
};
#endif
    
