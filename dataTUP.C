
{
TH1F *ptpiH = new TH1F("ptpi","",100,0,10);
TH1F *ptantipiH = new TH1F("ptantipi","",100,0,10);
TH1F *ptpH = new TH1F("ptp","",100,0,10);
TH1F *ptantipH = new TH1F("ptantip","",100,0,10);
TH1F *ptkH = new TH1F("ptk","",100,0,10);
TH1F *ptantikH = new TH1F("ptantik","",100,0,10);
TH1F *ptlH = new TH1F("ptl","",100,0,10);
TH1F *ptantilH = new TH1F("ptantil","",100,0,10);
TH1F *ptpi2H = new TH1F("ptpi2","",100,0,10);
TH1F *ptantipi2H = new TH1F("ptantipi2","",100,0,10);
TH1F *ptp2H = new TH1F("ptp2","",100,0,10);
TH1F *ptantip2H = new TH1F("ptantip2","",100,0,10);
TH1F *ptk2H = new TH1F("ptk2","",100,0,10);
TH1F *ptantik2H = new TH1F("ptantik2","",100,0,10);
TH1F *ptl2H = new TH1F("ptl2","",100,0,10);
TH1F *ptantil2H = new TH1F("ptantil2","",100,0,10);
TH1F *ptpi3H = new TH1F("ptpi3","",100,0,10);
TH1F *ptantipi3H = new TH1F("ptantipi3","",100,0,10);
TH1F *ptp3H = new TH1F("ptp3","",100,0,10);
TH1F *ptantip3H = new TH1F("ptantip3","",100,0,10);
TH1F *ptk3H = new TH1F("ptk3","",100,0,10);
TH1F *ptantik3H = new TH1F("ptantik3","",100,0,10);
TH1F *ptl3H = new TH1F("ptl3","",100,0,10);
TH1F *ptantil3H = new TH1F("ptantil3","",100,0,10);

TGraphErrors *grPi = new TGraphErrors("dataSTAR/piper");
TGraphErrors *grPime = new TGraphErrors("dataSTAR/antipiper");
TGraphErrors *grP = new TGraphErrors("dataSTAR/protonper");
TGraphErrors *grPme = new TGraphErrors("dataSTAR/antiprotonper");
TGraphErrors *grL = new TGraphErrors("dataSTAR/lambdaper");
TGraphErrors *grLme = new TGraphErrors("dataSTAR/antilambdaper");

gROOT->Reset();
TChain mychain("T");
TChain mychain2("particles");
TChain mychain3("phsd");
mychain.Add("dataUrQMD/7.root"); //10 000
Float_t nev=10000;
mychain2.Add("dataSingleFreezeOut/event*.root"); //archivo a leer 500*20
Int_t nev2=10000;
mychain3.Add("dataPHSD/iglue1/phsd*.root");
Int_t nev3=10000;
Float_t etacut=0.5;
Float_t ptcut=0.5;
Float_t bmi=12;//central0-5 fm, 0-12%, mid= 7-10 fm 20-40%, per= 12-15 fm 60-80%
Float_t bma=15;

struct particula_t
{
	Float_t time,X,Y,Z,E,Px,Py,Pz,Pt,P,Eta,m,id,isoespin,charge,lastcoll,numbercoll,history,frezetime,frezeX,frezeY,frezeZ,frezeE,frezePx;
  Float_t frezePy,frezePz,frezePt,frezeP,frezeEta,b,bmin,bmax,sigma;

} PARTICLE;
struct particula2_t
{

	Float_t px,py,pz,e,x,y,z,t,pid,mass,fatherpid,rootpid,event;

} PARTICLE2;
particula_t  particle;
particula2_t  particle2;


Float_t p,pt ,eta,p2,pt2,eta2= 0;

// Declaration of leaf types
   Int_t           isub; // external loop (run over different values for the impact parameter)
   Int_t           irun; //internal loop (parallel events)
   Float_t         b;
   Float_t         ibw;
   Float_t         psi[4];
   Float_t         epsilon[4];
   Int_t           np;//participants
   Int_t           n;//total particles
   Int_t           id[90000];   //[n]
   Short_t         q[90000];   //[n]
   Float_t         e[90000];   //[n]
   Float_t         px[90000];   //[n]
   Float_t         py[90000];   //[n]
   Float_t         pz[90000];   //[n]
   Int_t           code1[90000];   //[n]
   Int_t           code2[90000];   //[n]
   // List of branches
   TBranch        *b_isub;   //!
   TBranch        *b_irun;   //!
   TBranch        *b_b;   //!
   TBranch        *b_ibw;   //!
   TBranch        *b_psi;   //!
   TBranch        *b_epsilon;   //!
   TBranch        *b_np;   //!
   TBranch        *b_n;   //!
   TBranch        *b_id;   //!
   TBranch        *b_q;   //!
   TBranch        *b_e;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_code1;   //!
   TBranch        *b_code2;   //!


//Setting Branch Adress
   mychain3.SetBranchAddress("isub", &isub, &b_isub);
   mychain3.SetBranchAddress("irun", &irun, &b_irun);
   mychain3.SetBranchAddress("b", &b, &b_b);
   mychain3.SetBranchAddress("ibw", &ibw, &b_ibw);
   mychain3.SetBranchAddress("psi", psi, &b_psi);
   mychain3.SetBranchAddress("epsilon", epsilon, &b_epsilon);
   mychain3.SetBranchAddress("np", &np, &b_np);
   mychain3.SetBranchAddress("n", &n, &b_n);
   mychain3.SetBranchAddress("id", id, &b_id);
   mychain3.SetBranchAddress("q", q, &b_q);
   mychain3.SetBranchAddress("e", e, &b_e);
   mychain3.SetBranchAddress("px", px, &b_px);
   mychain3.SetBranchAddress("py", py, &b_py);
   mychain3.SetBranchAddress("pz", pz, &b_pz);
   mychain3.SetBranchAddress("code1", code1, &b_code1);
   mychain3.SetBranchAddress("code2", code2, &b_code2);

mychain.SetBranchAddress("particle",&particle);
Float_t nevent = mychain.GetEntries();
Int_t nbpart =0;
for (Int_t i=0;i<nevent;i++)
{
	mychain.GetEvent(i);
	//if(particle.b>bcut )continue;//central
		if(particle.b<bmi) continue;
		if(particle.b>bma)continue;
	nbpart++;	//if(particle.charge == 0)
	if(particle.numbercoll==0)continue;//protones participantes
  	pt = particle.Pt;
  eta = particle.Eta;
	if(TMath::Abs(eta) >etacut)continue;
	if(TMath::Abs(pt) <ptcut)continue;
  if(particle.id == 1) ptpH->Fill(pt,Float_t (1/pt));
	if(particle.id == -1) ptantipH->Fill(pt,Float_t (1/pt));
	if(particle.id == 101 && particle.charge ==1) ptpiH->Fill(pt,Float_t (1/pt));
	if(particle.id == 101 && particle.charge ==-1) ptantipiH->Fill(pt,Float_t (1/pt));
	if(particle.id == 106) ptkH->Fill(pt,Float_t (1/pt));
	if(particle.id == -106) ptantikH->Fill(pt,Float_t (1/pt));
	if(particle.id == 27 ) ptlH->Fill(pt,Float_t (1/pt));
	if(particle.id == -27 ) ptantilH->Fill(pt,Float_t (1/pt));
}
Float_t nb = (nbpart*nev)/nevent;

mychain2.SetBranchAddress("part",&particle2);
Int_t nevent2 = mychain2.GetEntries();
for (Int_t i=0;i<nevent2;i++)
	{
		mychain2.GetEvent(i);
		if(particle2.fatherpid !=  particle2.pid && particle2.pid !=  particle2.rootpid) continue;
		p2 = TMath::Sqrt(TMath::Power(particle2.px,2) + TMath::Power(particle2.py,2)+ TMath::Power(particle2.pz,2)); //particle.px + particle.py;
		pt2 = TMath::Sqrt(TMath::Power(particle2.px,2) + TMath::Power(particle2.py,2)); //particle.px + particle.py;
	  eta2 = 0.5*TMath::Log((p2+particle2.pz)/(p2-particle2.pz));
		if(TMath::Abs(eta2) >etacut)continue;
		if(TMath::Abs(pt2) <ptcut)continue;
		if(particle2.pid == 2212) ptp2H->Fill(pt2,Float_t (1/pt2));
		if(particle2.pid == -2212 ) ptantip2H->Fill(pt2,Float_t (1/pt2));
		if(particle2.pid == 211) ptpi2H->Fill(pt2,Float_t (1/pt2));
		if(particle2.pid == -211) ptantipi2H->Fill(pt2,Float_t (1/pt2));
		if(particle2.pid == 321) ptk2H->Fill(pt2,Float_t (1/pt2));
		if(particle2.pid == -321) ptantik2H->Fill(pt2,Float_t (1/pt2));
		if(particle2.pid == 3122) ptl2H->Fill(pt2,Float_t (1/pt2));
		if(particle2.pid == -3122) ptantil2H->Fill(pt2,Float_t (1/pt2));
	}

Int_t nevent3 = mychain3.GetEntries();
Int_t nb3 =0;
for (Int_t jentry=0; jentry < nevent3; jentry++) //Loop over events
    {
mychain3.GetEvent(jentry);
//if (b>bcut)continue;
if(b<bmi) continue;
if(b>bma)continue;
nb3++;
for(Int_t j=0; j < n; j++) {  //Loop over particles
Float_t pt[90000];
Float_t p[90000];
Float_t theta[90000];
Float_t eta[9000];
if (code1[j]<0)continue;
pt[j] = sqrt(px[j]*px[j]+py[j]*py[j]);
p[j] = sqrt(px[j]*px[j]+py[j]*py[j]+pz[j]*pz[j]);
theta[j] = atan2(pt[j],pz[j]);
eta[j] = -log(tan(theta[j]/2));
if(TMath::Abs(eta[j]) >etacut)continue;
if(TMath::Abs(pt[j]) <ptcut)continue;
if(id[j] == 2212) ptp3H->Fill(pt[j],Float_t (1/pt[j]));
if(id[j] == -2212) ptantip3H->Fill(pt[j],Float_t (1/pt[j]));
	if(id[j] == 211) ptpi3H->Fill(pt[j],Float_t (1/pt[j]));
	if(id[j] == -211) ptantipi3H->Fill(pt[j],Float_t (1/pt[j]));
	if(id[j] == 321) ptk3H->Fill(pt[j],Float_t (1/pt[j]));
	if(id[j] == -321) ptantik3H->Fill(pt[j],Float_t (1/pt[j]));
	if(id[j] == 3122) ptl3H->Fill(pt[j],Float_t (1/pt[j]));
	if(id[j]== -3122) ptantil3H->Fill(pt[j],Float_t (1/pt[j]));
   }
  }
  TCanvas* c1 = new TCanvas("c1","Therminator test basic example",800,800);
  gStyle->SetOptStat(false);
  c1->SetRightMargin(0.05);
  c1->SetTopMargin(0.1);
  c1->SetFillColor(0);
  //c1->SetLogy();
  c1->Divide(2,3);
  c1->cd(1);
  gPad->SetLogy();
  ptpH->Scale(10/(Float_t(nb)));
  ptp2H->Scale(10/(Float_t(nev2)));
  ptp3H->Scale(10/(Float_t(nb3)));
  ptpH->Draw();
  ptp2H->Draw("sames");
  ptp2H->SetLineColor(2);
  ptp3H->Draw("sames");
  ptp3H->SetLineColor(6);
  grP->Draw("sames p");
  grP->SetMarkerStyle(21);
  grP->SetMarkerSize(0.5);
  ptpH->SetXTitle("p_{T} [GeV]");
  ptpH->GetXaxis()->CenterTitle(true);
  ptpH->GetXaxis()->SetTitleSize(0.04);
  ptpH->GetXaxis()->SetLabelSize(0.03);
  ptpH->GetXaxis()->SetTitleOffset(1.2);
  ptpH->SetYTitle("1/N_{ev} dN/dp_{T}");
  ptpH->GetYaxis()->CenterTitle(true);
  ptpH->GetYaxis()->SetTitleSize(0.04);
  ptpH->GetYaxis()->SetLabelSize(0.03);
  ptpH->GetYaxis()->SetTitleOffset(1.2);
  ptpH->GetYaxis()->SetRangeUser(0.00001,10000);
  ptpH->GetXaxis()->SetRangeUser(0.5,5);
  TLegend *leg0 = new TLegend(0.75,0.6,0.88,0.88);
  leg0->SetTextFont(62);
  leg0->SetTextSize(0.05);
  leg0->SetLineColor(0);
  leg0->SetLineStyle(0);
  leg0->SetLineWidth(1);
  leg0->SetFillColor(0);
  leg0->SetFillStyle(1001);
  leg0->AddEntry("","p","");
  leg0->Draw();

  c1->cd(2);
  gPad->SetLogy();
  ptantipH->Scale(10/(Float_t(nb)));
  ptantip2H->Scale(10/(Float_t(nev2)));
  ptantip3H->Scale(10/(Float_t(nb3)));
  ptantipH->Draw("");
  ptantip2H->Draw("sames");
  ptantip2H->SetLineColor(2);
  ptantip3H->Draw("sames");
  ptantip3H->SetLineColor(6);
  grPme->Draw("sames p");
  grPme->SetMarkerStyle(21);
  grPme->SetMarkerSize(0.5);
  ptantipH->SetXTitle("p_{T} [GeV]");
  ptantipH->GetXaxis()->CenterTitle(true);
  ptantipH->GetXaxis()->SetTitleSize(0.04);
  ptantipH->GetXaxis()->SetLabelSize(0.03);
  ptantipH->GetXaxis()->SetTitleOffset(1.2);
  ptantipH->SetYTitle("1/N_{ev} dN/dp_{T}");
  ptantipH->GetYaxis()->CenterTitle(true);
  ptantipH->GetYaxis()->SetTitleSize(0.04);
  ptantipH->GetYaxis()->SetLabelSize(0.03);
  ptantipH->GetYaxis()->SetTitleOffset(1.2);
  ptantipH->GetYaxis()->SetRangeUser(0.00001,10000);
  ptantipH->GetXaxis()->SetRangeUser(0.5,5);


	TLegend *leg = new TLegend(0.4,0.65,0.88,0.88);
  leg->SetTextFont(62);
  leg->SetTextSize(0.025);
  leg->SetLineColor(0);
  leg->SetLineStyle(0);
  leg->SetLineWidth(1);
  leg->SetFillColor(0);
  leg->SetFillStyle(1001);
	leg->AddEntry(grPme, "STAR experiment, Au+Au #sqrt{s_{NN}}=200 GeV, c=60-80%","p");
  leg->AddEntry(ptantipH,"UrQMD Au+Au #sqrt{s_{NN}}=200 GeV, b = 12-15 fm","l");
  leg->AddEntry(ptantip3H,"PHSD Au+Au #sqrt{s_{NN}}=200 GeV, b = 12-15 fm","l");
	leg->AddEntry(ptantip2H,"THERMINATOR SingleFreezeOut, T=0.1656 GeV","l");
  leg->Draw();

	TLegend *leg1 = new TLegend(0.75,0.4,0.88,0.6);
  leg1->SetTextFont(62);
  leg1->SetTextSize(0.05);
  leg1->SetLineColor(0);
  leg1->SetLineStyle(0);
  leg1->SetLineWidth(1);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(1001);
  leg1->AddEntry("","#bar{p}","");
  leg1->Draw();
  leg->Draw();

  c1->cd(3);
  gPad->SetLogy();
  ptpiH->Scale(10/(Float_t(nb)));
  ptpi2H->Scale(10/(Float_t(nev2)));
  ptpi3H->Scale(10/(Float_t(nb3)));
  ptpiH->Draw("");
  ptpi2H->Draw("sames");
  ptpi2H->SetLineColor(2);
  ptpi3H->Draw("sames");
  ptpi3H->SetLineColor(6);
  grPi->Draw("sames p");
  grPi->SetMarkerStyle(21);
  grPi->SetMarkerSize(0.5);
  ptpiH->SetXTitle("p_{T} [GeV]");
  ptpiH->GetXaxis()->CenterTitle(true);
  ptpiH->GetXaxis()->SetTitleSize(0.04);
  ptpiH->GetXaxis()->SetLabelSize(0.03);
  ptpiH->GetXaxis()->SetTitleOffset(1.2);
  ptpiH->SetYTitle("1/N_{ev} dN/dp_{T}");
  ptpiH->GetYaxis()->CenterTitle(true);
  ptpiH->GetYaxis()->SetTitleSize(0.04);
  ptpiH->GetYaxis()->SetLabelSize(0.03);
  ptpiH->GetYaxis()->SetTitleOffset(1.2);
  ptpiH->GetYaxis()->SetRangeUser(0.00001,10000);
  ptpiH->GetXaxis()->SetRangeUser(0.5,5);
  TLegend *leg2 = new TLegend(0.75,0.6,0.88,0.88);
  leg2->SetTextFont(62);
  leg2->SetTextSize(0.05);
  leg2->SetLineColor(0);
  leg2->SetLineStyle(0);
  leg2->SetLineWidth(1);
  leg2->SetFillColor(0);
  leg2->SetFillStyle(1001);
  leg2->AddEntry("","#pi","");
  leg2->Draw();

  c1->cd(4);
  gPad->SetLogy();
  ptantipiH->Scale(10/(Float_t(nb)));
  ptantipi2H->Scale(10/(Float_t(nev2)));
  ptantipi3H->Scale(10/(Float_t(nb3)));
  ptantipiH->Draw("");
  ptantipi2H->Draw("sames");
  ptantipi2H->SetLineColor(2);
  ptantipi3H->Draw("sames");
  ptantipi3H->SetLineColor(6);
  grPime->Draw("sames p");
  grPime->SetMarkerStyle(21);
  grPime->SetMarkerSize(0.5);
  ptantipiH->SetXTitle("p_{T} [GeV]");
  ptantipiH->GetXaxis()->CenterTitle(true);
  ptantipiH->GetXaxis()->SetTitleSize(0.04);
  ptantipiH->GetXaxis()->SetLabelSize(0.03);
  ptantipiH->GetXaxis()->SetTitleOffset(1.2);
  ptantipiH->SetYTitle("1/N_{ev} dN/dp_{T}");
  ptantipiH->GetYaxis()->CenterTitle(true);
  ptantipiH->GetYaxis()->SetTitleSize(0.04);
  ptantipiH->GetYaxis()->SetLabelSize(0.03);
  ptantipiH->GetYaxis()->SetTitleOffset(1.2);
  ptantipiH->GetXaxis()->SetRangeUser(0.5,5);
  ptantipiH->GetYaxis()->SetRangeUser(0.00001,10000);
  TLegend *leg3 = new TLegend(0.75,0.6,0.88,0.88);
  leg3->SetTextFont(62);
  leg3->SetTextSize(0.05);
  leg3->SetLineColor(0);
  leg3->SetLineStyle(0);
  leg3->SetLineWidth(1);
  leg3->SetFillColor(0);
  leg3->SetFillStyle(1001);
  leg3->AddEntry("","#bar{#pi}","");
  leg3->Draw();

  c1->cd(5);
  gPad->SetLogy();
  ptlH->Scale(10/(Float_t(nb)));
  ptl2H->Scale(10/(Float_t(nev2)));
  ptl3H->Scale(10/(Float_t(nb3)));
  ptlH->Draw();
  ptl2H->Draw("sames");
  ptl2H->SetLineColor(2);
  ptl3H->Draw("sames");
  ptl3H->SetLineColor(6);
  grL->Draw("sames p");
  grL->SetMarkerStyle(21);
  grL->SetMarkerSize(0.5);
  ptlH->SetXTitle("p_{T} [GeV]");
  ptlH->GetXaxis()->CenterTitle(true);
  ptlH->GetXaxis()->SetTitleSize(0.04);
  ptlH->GetXaxis()->SetLabelSize(0.03);
  ptlH->GetXaxis()->SetTitleOffset(1.2);
  ptlH->SetYTitle("1/N_{ev} dN/dp_{T}");
  ptlH->GetYaxis()->CenterTitle(true);
  ptlH->GetYaxis()->SetTitleSize(0.04);
  ptlH->GetYaxis()->SetLabelSize(0.03);
  ptlH->GetYaxis()->SetTitleOffset(1.2);
  ptlH->GetYaxis()->SetRangeUser(0.00001,1000);
  ptlH->GetXaxis()->SetRangeUser(0.5,5);
  TLegend *leg4 = new TLegend(0.75,0.6,0.88,0.88);
  leg4->SetTextFont(62);
  leg4->SetTextSize(0.05);
  leg4->SetLineColor(0);
  leg4->SetLineStyle(0);
  leg4->SetLineWidth(1);
  leg4->SetFillColor(0);
  leg4->SetFillStyle(1001);
  leg4->AddEntry("","#Lambda","");
  leg4->Draw();

  c1->cd(6);
  gPad->SetLogy();
  ptantilH->Scale(10/(Float_t(nb)));
  ptantil2H->Scale(10/(Float_t(nev2)));
  ptantil3H->Scale(10/(Float_t(nb3)));
  ptantilH->Draw("");
  ptantil2H->Draw("sames");
  ptantil2H->SetLineColor(2);
  ptantil3H->Draw("sames");
  ptantil3H->SetLineColor(6);
  grLme->Draw("sames p");
  grLme->SetMarkerStyle(21);
  grLme->SetMarkerSize(0.5);
  ptantilH->SetXTitle("p_{T} [GeV]");
  ptantilH->GetXaxis()->CenterTitle(true);
  ptantilH->GetXaxis()->SetTitleSize(0.04);
  ptantilH->GetXaxis()->SetLabelSize(0.03);
  ptantilH->GetXaxis()->SetTitleOffset(1.2);
  ptantilH->SetYTitle("1/N_{ev} dN/dp_{T}");
  ptantilH->GetYaxis()->CenterTitle(true);
  ptantilH->GetYaxis()->SetTitleSize(0.04);
  ptantilH->GetYaxis()->SetLabelSize(0.03);
  ptantilH->GetYaxis()->SetTitleOffset(1.2);
  ptantilH->GetYaxis()->SetRangeUser(0.00001,1000);
  ptantilH->GetXaxis()->SetRangeUser(0.5,5);
  TLegend *leg5 = new TLegend(0.75,0.6,0.88,0.88);
  leg5->SetTextFont(62);
  leg5->SetTextSize(0.05);
  leg5->SetLineColor(0);
  leg5->SetLineStyle(0);
  leg5->SetLineWidth(1);
  leg5->SetFillColor(0);
  leg5->SetFillStyle(1001);
  leg5->AddEntry("","#bar{#Lambda}","");

  leg5->Draw();
 c1->SaveAs("plots/piddataTUP60-80.eps");
  c1->SaveAs("plots/piddataTUP60-80.pdf");


}//loop
