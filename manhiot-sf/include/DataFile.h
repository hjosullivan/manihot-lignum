#ifndef DATA_FILE_H
#define DATA_FILE_H
class DataFile{
public:
  DataFile():age(0.0),H1(0.0),H2(0.0),Dbh(0.0),Dbase(0.0),
	     Wr1(0.0),Wr2(0.0),NLeaf1(0.0),NLeaf2(0.0),
	     Wf1(0.0),Wf2(0.0),Af1(0.0),Af2(0.0),Cscheme(0.0),
	     Ptree(0.0),Mtree(0.0),NetP(0.0),
	     Pprod(0.0),NetPprod(0.0),Cpool1(0.0),
	     Cpool2(0.0),netCprev(0.0),Pnew(0.0),newNetProd(0.0),
	     Cneeded(0.0){}
  double age;
  double H1; //Height before growth
  double H2; //       after
  double Dbh; //D1.3 after growth
  double Dbase; //Dbase after growth
  double Wr1; //Root mass before growth
  double Wr2; //          after
  double NLeaf1; //Number of leaves before growth
  double NLeaf2; //                 after
  double Wf1; //Foliage mass before growth
  double Wf2; //             after
  double Af1;//Foliage area before growth
  double Af2;//             after
  double Cscheme;//C allocation scheme used
  double Ptree; //Tree photosynthesis
  double Mtree; //Tree respiration
  double NetP;  //Ptree - Mtree
  double Pprod;//Ptree after use of C pool 
  double NetPprod;//Net C for growth: Pprod-Mtree 
  double Cpool1; //Cpool before growth
  double Cpool2; //Cpool after growth
  double netCprev; //Net C for growth from previous year 
  double Pnew; //Methods 3 and 5 put part of P to C pool directly
  double newNetProd;//Methods 3 and 5, this is the Net C (Pnew-M) for growth 
  double Cneeded; // follow the use of C pool methods 2,3,4 and 5
};
#endif 
