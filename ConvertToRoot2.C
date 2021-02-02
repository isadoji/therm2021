void ConvertToRoot2(char* in_name="phsd0.dat",char* out_name="phsd.root",int nevt=1000,int print=0){
  //Author: Anders Knospe, anders.knospe@cern.ch
  //Date: 21 November 2014
  /*
    This macro converts a phsd.dat file to a ROOT tree.  The arguments are:
    in_name: The name of the input phsd.dat file to be converted
    out_name: The name of the output .root file to which the tree will be written
    nevt: the number of events (ISUB*IRUN) contained that should be read from the input file
    print: a flag that controls how much information is printed to the screen during the conversion
           if print=0: nothing will be printed
           if print=1: only the event header will be printed
           if print=2: the event header will be printed, along with all information for every particle
    This macro will only work with a very specific format of phsd.dat file.  It requires this form:
    N ISUB IRUN b IBweight
      NP PSI(2) EPSILON(2) PSI(3) EPSILON(3) PSI(4) EPSILON(4) PSI(5) EPSILON(5)
        ID Q PX PY PZ P0 IPI(I,5) IPI(I,3)
    The exact amount of whitespace can be changed without causing problems.  Also, keep in mind that it stores floating-point numbers as floats (single precision) rather than doubles (double precision).  If more precision is desired, the macro will need to be modified.  The mapping between the .dat file and the branches of the tree is as follows:
    N -> n: total number of particles
    ISUB -> isub
    IRUN -> irun
    b -> b
    IBweight -> ibw
    NP -> np: number of participants
    PSI(n) -> psi[n-2]: psi is an array with four components
    EPSILON(n) -> epsilon[n-2]: epsilon is an array with four components
      The properties of each particle are stored in arrays with length np (array indices count from 0 to n-1).
    ID of particle j -> id[j]
    Q of particle j -> q[j] (stored as a 16-bit integer to save space)
    PX of particle j -> px[j]
    PY of particle j -> py[j]
    PZ of particle j -> pz[j]
    P0 of particle j -> e[j]
    IPI(I,5) of particle j -> code1[j]
    IPI(I,3) of particle j -> code2[j]
    Usage: From the command line do
        root -q -b [path to this macro]/ConvertToRoot.C\(\"[name of input file]\",\"[name of output file]\",[number of events],[print flag]\"\)
        An example:
        root -q -b ~/path/to/some/directory/ConvertToRoot.C\(\"/path/to/data/file/phsd.dat\",\"/some/path/phsd.root\",200,1\)
    Look at the documentation for the ROOT TTree class for more information on this data structure.
  */
  if(nevt<1){cerr<<"ERROR: requested number of events = "<<nevt<<endl; return;}
  cout<<"converting "<<in_name<<" to root file "<<out_name<<", "<<nevt<<" events"<<endl;
  int je,jp,np,isub,irun,n,id[100000],Q,code1[100000],code2[100000];
  short q[100000];
  float b,ibw,psi[4],epsilon[4],e[100000],px[100000],py[100000],pz[100000];
  FILE* fin=fopen(in_name,"r");
  TFile* fout=new TFile(out_name,"RECREATE","TreeFile");
  TTree* t=new TTree("phsd","");
  t->Branch("isub",&isub,"isub/I");
  t->Branch("irun",&irun,"irun/I");
  t->Branch("b",&b,"b/F");
  t->Branch("ibw",&ibw,"ibw/F");
  t->Branch("psi",psi,"psi[4]/F");
  t->Branch("epsilon",epsilon,"epsilon[4]/F");
  t->Branch("np",&np,"np/I");
  t->Branch("n",&n,"n/I");
  t->Branch("id",id,"id[n]/I");
  t->Branch("q",q,"q[n]/S");
  t->Branch("e",e,"e[n]/F");
  t->Branch("px",px,"px[n]/F");
  t->Branch("py",py,"py[n]/F");
  t->Branch("pz",pz,"pz[n]/F");
  t->Branch("code1",code1,"code1[n]/I");
  t->Branch("code2",code2,"code2[n]/I");
  for(je=0;je<nevt;je++){
    if(fscanf(fin,"%i %i %i %f %f",&n,&isub,&irun,&b,&ibw)<0){
      cerr<<"WARNING: "<<nevt<<" events requested, only "<<je<<" events read"<<endl;
      break;
    }
    if(print) printf("%i %i %i %1.7e %1.7e\n",n,isub,irun,b,ibw);
    if(fscanf(fin,"%i %f %f %f %f %f %f %f %f",&np,&psi[0],&epsilon[0],&psi[1],&epsilon[1],&psi[2],&epsilon[2],&psi[3],&epsilon[3])<0){
      cerr<<"WARNING: "<<nevt<<" events requested, only "<<je<<" events read"<<endl;
      break;
    }
    if(print) printf("  %i %1.7e %1.7e %1.7e %1.7e %1.7e %1.7e %1.7e %1.7e\n",np,psi[0],epsilon[0],psi[1],epsilon[1],psi[2],epsilon[2],psi[3],epsilon[3]);
    if(n>100000){
      cerr<<"WARNING: There are too many particles in event (ISUB="<<isub<<", IRUN="<<irun<<").  Only the first 100000 will be stored.  Increase the sizes of the arrays."<<endl;
      n=100000;
    }
    for(jp=0;jp<n;jp++){
      if(fscanf(fin,"%i %i %f %f %f %f %i %i",&id[jp],&Q,&px[jp],&py[jp],&pz[jp],&e[jp],&code1[jp],&code2[jp])<0){
	cerr<<"WARNING: expected "<<n<<" particles in last event, but only read "<<jp<<endl;
	break;
      }
      if(print>1) printf("    %i %i %1.7e %1.7e %1.7e %1.7e %i %i\n",id[jp],Q,px[jp],py[jp],pz[jp],e[jp],code1[jp],code2[jp]);
      q[jp]=(short) Q;
    }
    t->Fill();
  }
  fout->cd();
  t->Write();
  fclose(fin);
  fout->Close();
  cout<<"done converting"<<endl;
}
