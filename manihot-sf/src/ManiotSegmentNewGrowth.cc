#include <Maniot.h>


//Setting the segment length. Maniot.h for details

// double& SetManiotSegmentLength::operator()(double& qin,
// 					       TreeCompartment<ManiotSegment,ManiotBud>* tc)const
// {
//   if (ManiotSegment* ts = dynamic_cast<ManiotSegment*>(tc)){
//     if (GetValue(*ts,LGAage) != 0.0){
//       //Take the Qin, it will be passed to segment in front
//       qin = GetValue(*ts,LGAQin);
//     }
//     else if (GetValue(*ts,LGAage) == 0.0){
//       SetValue(*ts,LGAQin,qin);
//       ManiotTree& tree = dynamic_cast<ManiotTree&>(GetTree(*ts));
//       //Now get thee functions we need
//       //The fip function (relative light)
//       const ParametricCurve& fip = GetFunction(tree,LGMIP);
//       //The vigour index function
//       const ParametricCurve& fvi = GetFunction(tree,SMVI);
//       //The bud size function
//       const ParametricCurve& fbs = GetFunction(tree,SMBS);
//       //The bud flush function
//       const ParametricCurve& fbf = GetFunction(tree,SMBF);
//       //The apical dominance function
//       const ParametricCurve& fad = GetFunction(tree,SMAD);
//       //The minimum segment length cutter
//       const ParametricCurve& fmin = GetFunction(tree,SMMSL);
//       //Vigour index
//       double vi = GetValue(*ts,LGAvi);
//       //Relative light, TreeRefRadiation  is ball sensor reading, it is
//       //as for open grown tree
//       double B = GetValue(GetTree(*ts),TreeRefRadiation);
//       double apical = 0.0;
//       if (terminal){
// 	apical = 1;
// 	brp = 1.0;
//       }
//       else{
// 	apical = qin/B;
// 	//the realtive_bud_size is set in the axis
//       }
//       //The segment  length. Please  note that the  functions allocate
//       //the r e  l a t i v  e amount of carbon to  segment, i.e. their
//       //range must  be [0:1] and 1 is  the best. So when  we have many
//       //functions affecting  the segment length the natural  way is to
//       //have multiplicative model. You can have an additive model too,
//       //if you  want to give  weights to different functions.  But you
//       //must n o r m a l i z e the result to range [0:1].
//       double Lq = 0.0;
//       if (terminal)
// 	  Lq = max(0.0,(fvi(vi)*fip(qin/B)));
//       else//nonterminal has to count for apical dominance
// 	Lq = max(0.0,fvi(vi)*fip(qin/B)*fbs(brp)*fad(apical));
//       //Now the segment  length is somewhere [0:1]. Use  lambda 'l' to
//       //set the  segment length  in the real  world. The value  of 'l'
//       //will change in  each iteration, so at some  point 'l'will find
//       //P-M=0
//       double L_new = l*Lq;
//       L_new = max(L_new,0.0);
//       if (L_new < fmin(L_new))
// 	  L_new = 0.0;
//
//       SetValue(*ts,LGAL,L_new);
//       //Initial foliage, create leaves according to segment length
//       const ParametricCurve& fleaf_pairs =
// 	GetFunction(dynamic_cast<ManiotTree&>(GetTree(*ts)),SMLN);
//
//       int nleaf_pairs = static_cast<int>(fleaf_pairs(L_new));
//       //Calculate  the leaf  area (to  be) for  this  segment.  For
//       //sugar maple the leaves come  in pairs and their size varies
//       //(become smaller) along the segment.
//       double Af = 0.0;
//       const ParametricCurve& fleaf_size =
// 	GetFunction(dynamic_cast<ManiotTree&>(GetTree(*ts)),SMLS);
//       const ParametricCurve& fmaxleaf =
// 	GetFunction(dynamic_cast<ManiotTree&>(GetTree(*ts)),SMMAXLEAF);
//       MJ plane_sensor = GetFirmament(GetTree(*ts)).diffusePlaneSensor();
//       for (int i = 1; i <= nleaf_pairs; i++){
// 	//Relative    position:    1/nleaf_pairs,    2/nleaf_pairs,
// 	//...,nleaf_pairs/nleaf_pairs
// 	Af += 2.0*fleaf_size(i/nleaf_pairs)*fmaxleaf(plane_sensor);
//       }
//       //Sapwood requirment by foliage
//       double Asf = Af/(GetValue(GetTree(*ts),LGPsf)*
// 		       GetValue(GetTree(*ts),LGPyc));
//       //Calculate the segment (bottom  circle) area, assuming there is
//       //also initial  heartwood Ah: Atot =  Asf + Ah, Ah  = xi*Asf -->
//       //Atot = Asf �+ xi*Asf
//       double Atot = Asf + GetValue(GetTree(*ts),LGPxi)*Asf;
//       //Set the segment radius
//       double Rts = sqrt(Atot/PI_VALUE);
//       SetValue(*ts,LGAR,Rts);
//       //Set heartwood radius
//       double Rhts = sqrt(GetValue(GetTree(*ts),LGPxi)*Asf/PI_VALUE);
//       SetValue(*ts,LGARh,Rhts);
//       //Remember original sapwood area As0
//       SetValue(*ts,LGAAs0,GetValue(*ts,LGAAs));
//       //debugging
//       ts->n_of_leaves = 2.0*nleaf_pairs;
//       ts->a_leaves = Af;
//       ts->r_segment = GetValue(*ts,LGAR);
//       ts->vs_segment = GetValue(*ts,LGAVs);
//       ts->segment_length = GetValue(*ts,LGAL);
//     }
//   }//segment
//   //In Axis decide if terminal  or not: if non-terminal take the bud's
//   //relative position ([0:1]), if terminal set it to 1.0.
//   else if (Axis<ManiotSegment,ManiotBud>* axis =
// 	   dynamic_cast<Axis<ManiotSegment,ManiotBud>*>(tc)){
//     list<TreeCompartment<ManiotSegment,ManiotBud>*> & ls =
//       GetTreeCompartmentList(*axis);
//     //new brancing [TS0,BP,B], and the next ForEach goes to is the TS0
//     if (ls.size() == 3){
//       terminal = false;
//       ManiotBud* smb =
// 	dynamic_cast<ManiotBud*>(GetTerminatingBud(*axis));
//       SMBudData data = GetValue(*smb,SMD);
//       brp = GetValue(data,SMBRP);
//     }
//     //old branch [TS,BP,TS,....,TS0,BP,B], and eventually ForEach will
//     //reach TS0.
//     else{
//       terminal = true;
//       brp = 1.0;
//     }
//   }//axis
//   return qin;
// }
//
// Create leaves
vector<PositionVector>&
CreateManiotLeaves::operator()(vector<PositionVector>& pdv,
				   TreeCompartment<ManiotSegment,
				   ManiotBud>* tc)const
{
  if (ManiotBud* bud = dynamic_cast<ManiotBud*>(tc)){
    // set value for now
    SetValue(*bud, LGAstatus, 1.0);
    if (GetValue(*bud,LGAstatus) > 0.0){
       cout << "Living Bud" << endl;
       
      //Leaf to be created
      pdv.push_back(GetDirection(*bud));
      //Use state  counter in the symbol  B and in the  Bud to carry
      //the relative leaf size
      rlsize = GetValue(*bud,LGAstatus);
      ManiotBudData data = GetValue(*bud,SMD);
      //Leaf created, set status to 0
      SetValue(*bud,LGAstatus,0.0);
    }
  }
  else if (ManiotSegment* ts= dynamic_cast<ManiotSegment*>(tc)){
    Point origo(0,0,0);
    Point point = GetEndPoint(*ts);
    PositionVector up(0,0,1);
    PositionVector left(0,1,0);
    static Uniform u; //Uniform random  number [0,1] for  setting leaf
		      //normals; static makes it common throughout the
		      //program and not reinitialized in each call.
    int seed = 3267;
    if (GetValue(*ts,LGAL) == 0.0)
	pdv.clear();
    //const ParametricCurve& fmaxleaf =
    //	GetFunction(dynamic_cast<ManiotTree&>(GetTree(*ts)),SMMAXLEAF);
    //MJ plane_sensor = GetFirmament(GetTree(*ts)).diffusePlaneSensor();
    for (unsigned int i = 0; i <pdv.size(); i++){
      //The direction of the petiole
      PositionVector pdir = pdv[i];
      //The size of the leaf (set to constant for now)
      double Af = 0.2;
      //double Af = rlsize*fmaxleaf(plane_sensor);
      //Leaves are  created at the end  of the segment  where the buds
      //are,  second  argument  is  the  length of  the  petiole.  See
      //petiole length from Annals 01.
      ManiotTree& tree = dynamic_cast<ManiotTree&>(GetTree(*ts));
      //const ParametricCurve& fpl = GetFunction(tree,SMPL);
      // Set constant for petiole length
      double petiole_length = 0.07;
      //double  petiole_length = fpl(Af);
      Petiole petiole(point,point + petiole_length*(Point)pdir);
      //Randomize  the leaf blade  normal by  rotating in  around axis
      //that lies in the horizontal plane defined by cross product of
      //petiole direction and up-vector
      PositionVector raxis = Cross(pdir,up);
      if (raxis.length() < R_EPSILON)
	raxis = Cross(pdir,left);
      //Limit the rotation  of the leaf normal to  [-90,90] degrees so
      //that  the  leaf  normal  is  upward  random  (does  not  point
      //downwards). Recall to use radians with PositionVector.

      //Leaves are horizontal in low light conditions and have more
      //random orientation in good light conditions
      //LGMdouble lLevel = GetValue(tree,TreeQinMax)/GetValue(tree,
      //TreeRefRadiation);
      // Assign light level
      LGMdouble lLevel = 0.2;
      LGMdouble rAngle;
      if(lLevel < 0.1)
	rAngle = 25.0;
      else
        rAngle = 25.0+(lLevel-0.1)*(90.0-25.0)/0.9;

      double random_number = (-rAngle +rAngle*u(seed))*PI_VALUE/180.0;
      //We need the leaf normal
      PositionVector leaf_normal(0,0,1);
      leaf_normal.rotate(origo,raxis,random_number);
      //The orientation of the leaf in space is away from petiole
      PositionVector x1u(pdir.getX(),pdir.getY(),0.0);
      x1u.normalize();
      x1u.rotate(origo,raxis,random_number);
      const PositionVector petiole_end =
	static_cast<const PositionVector>(GetEndPoint(petiole));
      //Create the initial shape, we have leaves in different directions
      Ellipse shape(petiole_end,leaf_normal,x1u,r1,r2);
      BroadLeaf<Ellipse>* leaf =
	new BroadLeaf<Ellipse>(shape,petiole,
			       GetFirmament(GetTree(*tc)).numberOfRegions());
      // SetValue(*leaf,LGAdof,GetValue(GetTree(*tc),LGPdof));
      //SetValue(*leaf,LGAtauL,GetValue(GetTree(*tc),LGPtauL));
      //SetValue(*leaf,LGAsf,GetValue(GetTree(*tc),LGPsf));
      //Set the leaf  area (Af is the true  area, SetValue will update
      //the Ellipse area.
      SetValue(*leaf,LGAA,Af);
      //Insert leaf
      InsertLeaf(*ts,leaf);
    }
    //clear the vector not to create new leaves
    pdv.clear();
  }
  //Pass pdv downwards
  return pdv;
}

// DiameterGrowthData&
// TryManiotDiameterGrowth::operator()(DiameterGrowthData& data,
// 					TreeCompartment<ManiotSegment,
// 					ManiotBud>* tc)const
// {
//   if (ManiotSegment* ts = dynamic_cast<ManiotSegment*>(tc)){
//     if (GetValue(*ts,LGAage) == 0.0){//New segment
//       //Take    the   sapwood    area.    It   has    been   set    by
//       //SetManiotSegmentLength.
//       LGMdouble As = GetValue(*ts,LGAAs);
//       //In SetManiotSegmentLength the  sapwood requirement is
//       //As = Af/(LGPsf*LGPyc) --> Af = As*LGPsf*LGPyc
//       LGMdouble Af =
// 	As*GetValue(GetTree(*ts),LGPsf)*GetValue(GetTree(*ts),LGPyc);
//
//       //Collect the masses.
//       LGMdouble Wf = Af/GetValue(GetTree(*ts),LGPsf);
//       //Pass down  new foliage mass.  Note: SetManiotSegmentLength
//       //does  not creat  leaves,  it just  calculates  Af and  adjusts
//       //segment area accordingly (GetValue for LGAWf would return 0).
//       SetValue(data,DGWfnew,Wf);
//       //Total foliage
//       SetValue(data,DGWf,Wf);
//       //Sapwood mass
//       SetValue(data,DGWs,GetValue(*ts,LGAWs));
//       //Sapwood requirement is the existing sapwood
//       SetValue(data,LGAAs,GetValue(*ts,LGAAs));
//     }
//     else{//age >= 1
//       //Sapwood above
//       LGMdouble Asu = GetValue(data,LGAAs);
//       //Own heartwood
//       LGMdouble Ahown  = GetValue(*ts,LGAAh);
//       //Requirement   for   new    radius:   sapwood   above   +   own
//       //heartwood. Note the old segments don't have leaves
//       LGMdouble Rnew = sqrt((Asu + Ahown)/PI_VALUE);
//       //Choose the max of existing R and Rnew
//       Rnew = max(Rnew, GetValue(*ts,LGAR));
//       //New sapwood requirement,  thickness growth. If the subtraction
//       //is negative, there is something wrong ion the model.
//       LGMdouble Asnew = PI_VALUE*pow(Rnew,2.0) -  GetValue(*ts,LGAA);
//       //Mass of the new sapwood
//       LGMdouble Wsnew =
// 	GetValue(GetTree(*ts),LGPrhoW)*Asnew*GetValue(*ts,LGAL);
//       //Down goes new plus existing sapwood area (sapwood requirment)
//       SetValue(data,LGAAs,Asnew+GetValue(*ts,LGAAs));
//       //Mass of sapwood used in diamater growth
//       SetValue(data,DGWs,GetValue(data,DGWs)+Wsnew);
//       //Note: no need for updating foliage
//     }
//   }
//   return data;
// }
