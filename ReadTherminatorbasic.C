//Basic Macro to read file event0.root from Therminator
//author Ivonne Alicia Maldonado Cervantes
//ivonne.alicia.maldonado@gmail.com
//FCFM - UAS
{
	//Options for Histogram
Int_t nbin = 50; //number of bins
Int_t xmin = 0; //minimum x
Int_t xmax = 1000.0; //maximum x
Float_t pt1 = 0;
Float_t pt2 = 0;
TH1F *pt1H = new TH1F("pt1","pt1",nbin,xmin,xmax);
TH1F *pt2H = new TH1F("pt2","pt2",nbin,xmin,xmax);

gROOT->Reset();
TChain mychain1("particles");
mychain1.Add("dataSingleFreezeOut/event*.root"); //archivo a leer
TChain mychain2("particles");
mychain2.Add("dataBlastWaveVT/event*.root"); //archivo a leer

struct particula_t
{
	Float_t px,py,pz,e,x,y,z,t,pid,mass,fatherpid,rootpid,event;
} PARTICLE;

particula_t particle;
mychain1.SetBranchAddress("part",&particle);
mychain2.SetBranchAddress("part",&particle);
Int_t nevent1 = mychain1.GetEntries();
Int_t nevent2 = mychain2.GetEntries();
for (Int_t i=0;i<nevent1;i++)
{
	mychain1.GetEvent(i);
	pt1 = TMath::Sqrt(TMath::Power(particle.px,2) + TMath::Power(particle.py,2)); //particle.px + particle.py;
        if(particle.fatherpid ==3122 && particle.pid != 111){
        //if(TMath::Abs(particle.pid) == 211) ptpiH->Fill(pt);
				//if(TMath::Abs(particle.pid) == 2212)
				pt1H->Fill(pt1);
	 }
	 mychain2.GetEvent(i);
	 pt2 = TMath::Sqrt(TMath::Power(particle.px,2) + TMath::Power(particle.py,2)); //particle.px + particle.py;
	 	if(particle.fatherpid ==3122 && particle.pid != 111){
    pt2H->Fill(pt2);
}	
//} // if pid
} // loop for

TCanvas* c1 = new TCanvas("c1","Therminator test basic example",800,800);
//gStyle->SetOptStat(false);
c1->SetRightMargin(0.05);
c1->SetTopMargin(0.1);
c1->SetFillColor(0);
c1->SetLogy();

pt1H->Draw();

pt2H->Draw("sames");
pt2H->SetLineColor(2);

}
