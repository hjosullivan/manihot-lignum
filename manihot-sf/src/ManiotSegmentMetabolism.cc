#include <Maniot.h>

class ManiotLeafPhotoFunctor {
public:
  ManiotLeafPhotoFunctor(const ParametricCurve& rce1):rce(rce1){}
  void operator ()(BroadLeaf<Ellipse>* leaf) {
    LGMdouble qabs = GetValue(*leaf,LGAQabs);
    LGMdouble pr = rce(qabs);
    leaf->photosynthesis(pr);
  }
  const ParametricCurve& rce;
};

//void ManiotSegment::photosynthesis()
//{
// //Radiation Conversion efficiency
//  ManiotTree& tree = dynamic_cast<ManiotTree&>(GetTree(*this));
//  const ParametricCurve& rce = GetFunction(tree, SMRCE);
//  list<BroadLeaf<Ellipse>*>& leaf_list = GetLeafList(*this);
//  for_each(leaf_list.begin(),leaf_list.end(),ManiotLeafPhotoFunctor(rce));
//}


class ManiotLeafRespFunctor {
public:
  ManiotLeafRespFunctor(LGMdouble mf1):mf(mf1){}
  LGMdouble operator ()(LGMdouble sum, BroadLeaf<Ellipse>* leaf) {
    sum += mf * GetValue(*leaf, LGAWf);
    return sum;
  }
  const LGMdouble mf;
};


//void ManiotSegment::respiration()
//{
//  //The Specific Leaf Area as a function of Qin
//  const ParametricCurve fsla = 
//    GetFunction(dynamic_cast<ManiotTree&>(GetTree(*this)),SMSLA);
//  //The respiration rate as a function of SLA
//  const ParametricCurve fmfsla = 
//    GetFunction(dynamic_cast<ManiotTree&>(GetTree(*this)),SMMFSLA);
//  LGMdouble qin = GetValue(*this,LGAQin);
//  LGMdouble sla = fsla(qin);
//  LGMdouble mfsla = fmfsla(sla);
//  //Leaf respiration
//  std::list<BroadLeaf<Ellipse>*>& leaf_list = GetLeafList(*this);
//  LGMdouble leafResp = accumulate(leaf_list.begin(),leaf_list.end(), 0.0,
//				  ManiotLeafRespFunctor(mfsla));

//  LGMdouble resp = leafResp;
//  //Sapwood respiration
//  resp += GetValue(GetTree(*this), LGPms) * GetValue(*this, LGAWs);
//  SetValue(*this, LGAM, resp);
//}

//void ManiotSegment::aging()
//{
//  //Sapwood senescence
//  LGMdouble Ahnew = (GetValue(*this,LGAAh)+
//		     GetValue(GetTree(*this),LGPss)*GetValue(*this,LGAAs));
//  LGMdouble Rhnew = sqrt(Ahnew/PI_VALUE);
//  SetValue(*this,LGARh,Rhnew);
//}

//Diameter  growth.   Be sure  this  algorithm  is  analogue, or  more
//precisly,  implements   the  same   diameter  growth  model   as  in
//TryManiotDiameterGrowth in  ManiotSegmentNewGrowth.cc. It is
//assumed that before calling this  method, 1) the segment lengths are
//iterated and  2) the leaves are  created and 3) The  LGAR is updated
//with ForwardR0 for the sequence of split segments.
//TcData& ManiotSegment::diameterGrowth(TcData& tcdata)
//{
//  DiameterGrowthData& data = dynamic_cast<DiameterGrowthData&>(tcdata);
//  if (GetValue(*this,LGAage) == 0.0){//New segment
    //The lengths and diameters of the newly created segments are set.
    //But  the the split  of the  segments requires  careful thinking.
    //Here    we    must     maintain    the    diameters    set    by
    //SetSegmentLength/TryDiameterGrowth   as   the   single   segment
    //iterated is now split. The problem is that the split forgets the
    //segment radiuses because it is  done in the L-system, except the
    //first one  in the sequence  of the segments.  The  L-system sets
    //its length which  is updated but R and Rh  are intact. The other
    //segments that follow are actually created as new segments, so we
    //only know their lengths. This  is why ForwardR0 is needed in the
    //main growth  loop in  main.cc.  If we  tried to set  the segment
    //diameter  based on  foliage,  the segment  would shrink.   There
    //would be a difference  between iterated single segment thickness
    //and the  the actual thicknesses  of the segments  resulting from
    //the  splitting of  the  single segment.   In  simple terms,  the
    //elongation does not continuously add number or increase the size
    //of the  leaves, but the appearance  of the leaves  is a discrete
    //event.  So a  certain amount of foliage supports  an interval of
    //sapwood  in SetSegmentLength.   And when  computing  the sapwood
    //requirement by foliage
    //Asf=Af/(GetValue(GetTree(*ts),LGPsf)*GetValue(GetTree(*ts),LGPyc))
    //in split segment parts, it  might (and will) shrink the segments
    //in diameter.   But the diameter growth model  should ensure that
    //the sapwood  mass needed  is the same  in both  cases, iterative
    //allocation  and actually  here  changing the  dimensions of  the
    //segments. 
    //
    //So  as the total area  LGAA is known based  on LGAR we
    //can easily  update the  missing LGArh by  setting its  radius to
    //LGAA*LGPxi.

    //Set the heartwood radius. Note: LGAA = PI*Rnew^2 = Atot
//    LGMdouble Rh = sqrt(GetValue(GetTree(*this),LGPxi)*
//			GetValue(*this,LGAA)/PI_VALUE);
//    SetValue(*this,LGARh,Rh);
    //The dimensions are  set.  Now pass down foliage  and the sapwood
    //(merely for bookeeping). Note there are now many new segments so
    //do not simply override old values in 'data'.
//    SetValue(data,DGWfnew,GetValue(data,DGWfnew)+GetValue(*this,LGAWf));
    //Total foliage
//    SetValue(data,DGWf,GetValue(data,DGWf)+GetValue(*this,LGAWf));
    //Sapwood mass used in diameter growth
//    SetValue(data,DGWs,GetValue(*this,LGAWs));
    //Sapwood requirement is the existing sapwood
//    SetValue(data,LGAAs,GetValue(*this,LGAAs));
//  }
//  else{//Age >=1
    //Sapwood requirement from above
//    LGMdouble Asu = GetValue(data,LGAAs);
    //Own heartwood
//    LGMdouble Ahown  = GetValue(*this,LGAAh);
    //Requirement   for   new    radius:   sapwood   above   +   own
    //heartwood. Note the old segments don't have leaves
//    LGMdouble Rnew = sqrt((Asu + Ahown)/PI_VALUE);
    //Choose the max of existing R and Rnew
//    Rnew = max(Rnew, GetValue(*this,LGAR));
    //New sapwood requirement,  thickness growth. If the subtraction
    //is negative, there is something wrong ion the model.
//    LGMdouble Asnew = PI_VALUE*pow(Rnew,2.0) -  GetValue(*this,LGAA);
//    SetValue(*this,LGAR,Rnew);
    //Down goes the sapwood area (sapwood requirment)
//    SetValue(data,LGAAs,GetValue(*this,LGAAs)); 
    //Mass of sapwood used in diamater growth
//    LGMdouble Wsnew = 
//      GetValue(GetTree(*this),LGPrhoW)*Asnew*GetValue(*this,LGAL);
//    SetValue(data,DGWs,GetValue(data,DGWs)+Wsnew);
    //Note: no need for updating foliage
//  }
//  return data;
//}















