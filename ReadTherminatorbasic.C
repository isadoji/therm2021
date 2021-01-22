//Basic Macro to read file event0.root from Therminator
//author Ivonne Alicia Maldonado Cervantes
//ivonne.alicia.maldonado@gmail.com
//FCFM - UAS
{


Float_t p,pt ,eta,p2,pt2,eta2= 0;
TH1F *ptH = new TH1F("pt","",100,0,10);
TH1F *pH = new TH1F("p","",200,0,20);
TH1F *eH = new TH1F("e","",200,0,20);
TH1F *etaH = new TH1F("eta","",200,-10,10);
TH1F *pt2H = new TH1F("pt2","",100,0,10);
TH1F *p2H = new TH1F("p2","",200,0,20);
TH1F *e2H = new TH1F("e2","",200,0,20);
TH1F *eta2H = new TH1F("eta2","",200,-10,10);
gROOT->Reset();
TChain mychain("particles");
mychain.Add("dataSingleFreezeOut/event0.root"); //archivo a leer 500*20
TChain mychain2("particles");
mychain2.Add("dataBlastWaveVT/event0.root"); //archivo a leer
Int_t nev=500;
struct particula_t
{
	Float_t px,py,pz,e,x,y,z,t,pid,mass,fatherpid,rootpid,event;
} PARTICLE;

particula_t particle;
mychain.SetBranchAddress("part",&particle);
mychain2.SetBranchAddress("part",&particle);
Int_t nevent = mychain.GetEntries();
Int_t nevent2 = mychain2.GetEntries();
for (Int_t i=0;i<nevent;i++)
{
	/*1. primordial particle has “pid” = “fatherpid” = “rootpid”
	2. the particle coming from the decay of primordial particle has “rootpid” =“fatherpid” and its own, different “pid”
	3. the particle coming from a cascade decay has its own “pid”, a PID of its immediate parent th “fatherpid”, and the
	PID of the original primordial resonance – “rootpid”.*/
	mychain.GetEvent(i);
	if(particle.fatherpid !=  particle.pid && particle.pid !=  particle.rootpid ) continue;

	p = TMath::Sqrt(TMath::Power(particle.px,2) + TMath::Power(particle.py,2)+ TMath::Power(particle.pz,2)); //particle.px + particle.py;
	pt = TMath::Sqrt(TMath::Power(particle.px,2) + TMath::Power(particle.py,2)); //particle.px + particle.py;
  eta = 0.5*TMath::Log((p+particle.pz)/(p-particle.pz));
  //if(particle.pid != 2212)continue;
  //if(TMath::Abs(eta) >0.5)continue;
	ptH->Fill(pt);
	pH->Fill(p);
	eH->Fill(particle.e);
	etaH->Fill(eta);
	}
for (Int_t i=0;i<nevent2;i++)
{
	mychain2.GetEvent(i);
	if(particle.fatherpid !=  particle.pid && particle.pid !=  particle.rootpid ) continue;
	p2 = TMath::Sqrt(TMath::Power(particle.px,2) + TMath::Power(particle.py,2)+ TMath::Power(particle.pz,2)); //particle.px + particle.py;
	pt2 = TMath::Sqrt(TMath::Power(particle.px,2) + TMath::Power(particle.py,2)); //particle.px + particle.py;
  eta2 = 0.5*TMath::Log((p2+particle.pz)/(p2-particle.pz));
  //if(particle.pid != 2212)continue;
  //if(TMath::Abs(eta2) >0.5)continue;
  pt2H->Fill(pt2);
	p2H->Fill(p2);
	e2H->Fill(particle.e);
	eta2H->Fill(eta2);
	}

TCanvas* c1 = new TCanvas("c1","Therminator test basic example",800,800);
gStyle->SetOptStat(false);
c1->SetRightMargin(0.05);
c1->SetTopMargin(0.1);
c1->SetFillColor(0);
//c1->SetLogy();
c1->Divide(2,2);
c1->cd(1);
gPad->SetLogy();
ptH->Scale(10/(2*3.14*Float_t(nev)));
pt2H->Scale(10/(2*3.14*Float_t(nev)));
ptH->Draw();
pt2H->Draw("sames");
pt2H->SetLineColor(2);
ptH->SetXTitle("p_{T} [GeV]");
ptH->GetXaxis()->CenterTitle(true);
ptH->GetXaxis()->SetTitleSize(0.04);
ptH->GetXaxis()->SetLabelSize(0.03);
ptH->GetXaxis()->SetTitleOffset(1.2);
ptH->SetYTitle("1/N_{ev} dN/dp_T");
ptH->GetYaxis()->CenterTitle(true);
ptH->GetYaxis()->SetTitleSize(0.04);
ptH->GetYaxis()->SetLabelSize(0.03);
ptH->GetYaxis()->SetTitleOffset(1.2);

c1->cd(2);
gPad->SetLogy();
pH->Scale(10/Float_t(nev));
p2H->Scale(10/Float_t(nev));
pH->Draw();
p2H->Draw("sames");
p2H->SetLineColor(2);
pH->SetXTitle("p [GeV]");
pH->GetXaxis()->CenterTitle(true);
pH->GetXaxis()->SetTitleSize(0.04);
pH->GetXaxis()->SetLabelSize(0.03);
pH->GetXaxis()->SetTitleOffset(1.2);
pH->SetYTitle("1/N_{ev} dN/dp");
pH->GetYaxis()->CenterTitle(true);
pH->GetYaxis()->SetTitleSize(0.04);
pH->GetYaxis()->SetLabelSize(0.03);
pH->GetYaxis()->SetTitleOffset(1.2);
TLegend *leg = new TLegend(0.4,0.7,0.88,0.88);
leg->SetTextFont(62);
leg->SetTextSize(0.022);
leg->SetLineColor(0);
leg->SetLineStyle(0);
leg->SetLineWidth(1);
leg->SetFillColor(0);
leg->SetFillStyle(1001);
leg->AddEntry("","Therminator Au-Au #sqrt{s_{NN}} = 200 GeV","");
leg->AddEntry(pH,"SingleFreezeOut","l");
leg->AddEntry(p2H,"BlastWaveVT","l");

leg->Draw();
c1->cd(3);
gPad->SetLogy();
eH->Scale(10/Float_t(nev));
e2H->Scale(10/Float_t(nev));
eH->Draw();
e2H->Draw("sames");
e2H->SetLineColor(2);
eH->SetXTitle("E [GeV]");
eH->GetXaxis()->CenterTitle(true);
eH->GetXaxis()->SetTitleSize(0.04);
eH->GetXaxis()->SetLabelSize(0.03);
eH->GetXaxis()->SetTitleOffset(1.2);
eH->SetYTitle("1/N_{ev} dN/dE");
eH->GetYaxis()->CenterTitle(true);
eH->GetYaxis()->SetTitleSize(0.04);
eH->GetYaxis()->SetLabelSize(0.03);
eH->GetYaxis()->SetTitleOffset(1.2);
c1->cd(4);
//gPad->SetLogy();
etaH->Scale(10/Float_t(nev));
eta2H->Scale(10/Float_t(nev));
etaH->Draw();
eta2H->Draw("sames");
eta2H->SetLineColor(2);
etaH->SetXTitle("#eta");
etaH->GetXaxis()->CenterTitle(true);
etaH->GetXaxis()->SetTitleSize(0.04);
etaH->GetXaxis()->SetLabelSize(0.03);
etaH->GetXaxis()->SetTitleOffset(1.4);
etaH->SetYTitle("1/N_{ev} dN/d#eta");
etaH->GetYaxis()->CenterTitle(true);
etaH->GetYaxis()->SetTitleSize(0.04);
etaH->GetYaxis()->SetLabelSize(0.03);
etaH->GetYaxis()->SetTitleOffset(1.2);
//etaH->GetYaxis()->SetRangeUser(0.0,1600);
//pt2H->Draw("sames");
//pt2H->SetLineColor(2);

}
