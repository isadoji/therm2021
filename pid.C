{
Float_t p,pt ,eta,p2,pt2,eta2= 0;
TH1F *ptpiH = new TH1F("ptpi","",100,0,10);
TH1F *ptantipiH = new TH1F("ptantipi","",100,0,10);
TH1F *ptpH = new TH1F("ptp","",100,0,10);
TH1F *ptantipH = new TH1F("ptantip","",100,0,10);
TH1F *ptkH = new TH1F("ptk","",100,0,10);
TH1F *ptantikH = new TH1F("ptantik","",100,0,10);
TH1F *ptlH = new TH1F("ptl","",100,0,10);
TH1F *ptantilH = new TH1F("ptantil","",100,0,10);

gROOT->Reset();
TChain mychain("particles");
mychain.Add("dataBlastWaveVT/event*.root"); //archivo a leer 500*20
Int_t nev=10000;
struct particula_t
{
	Float_t px,py,pz,e,x,y,z,t,pid,mass,fatherpid,rootpid,event;
} PARTICLE;

particula_t particle;
mychain.SetBranchAddress("part",&particle);
Int_t nevent = mychain.GetEntries();
for (Int_t i=0;i<nevent;i++)
{
	/*1. primordial particle has “pid” = “fatherpid” = “rootpid”
	2. the particle coming from the decay of primordial particle has “rootpid” =“fatherpid” and its own, different “pid”
	3. the particle coming from a cascade decay has its own “pid”, a PID of its immediate parent th “fatherpid”, and the
	PID of the original primordial resonance – “rootpid”.*/
	mychain.GetEvent(i);
//	if(particle.fatherpid !=  particle.pid && particle.pid !=  particle.rootpid ) continue;

	p = TMath::Sqrt(TMath::Power(particle.px,2) + TMath::Power(particle.py,2)+ TMath::Power(particle.pz,2)); //particle.px + particle.py;
	pt = TMath::Sqrt(TMath::Power(particle.px,2) + TMath::Power(particle.py,2)); //particle.px + particle.py;
  eta = 0.5*TMath::Log((p+particle.pz)/(p-particle.pz));
	if(TMath::Abs(eta) >0.5)continue;
	if(particle.pid == 2212) ptpH->Fill(pt);
	if(particle.pid == -2212) ptantipH->Fill(pt);
	if(particle.pid == 211) ptpiH->Fill(pt);
	if(particle.pid == -211) ptantipiH->Fill(pt);
	if(particle.pid == 321) ptkH->Fill(pt);
	if(particle.pid == -321) ptantikH->Fill(pt);
	if(particle.pid == 3122) ptlH->Fill(pt);
	if(particle.pid == -3122) ptantilH->Fill(pt);

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
ptpH->Scale(10/(2*3.14*Float_t(nev)));
ptantipH->Scale(10/(2*3.14*Float_t(nev)));
ptpH->Draw();
ptantipH->Draw("sames");
ptantipH->SetLineColor(2);
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
TLegend *leg = new TLegend(0.4,0.7,0.88,0.88);
leg->SetTextFont(62);
leg->SetTextSize(0.022);
leg->SetLineColor(0);
leg->SetLineStyle(0);
leg->SetLineWidth(1);
leg->SetFillColor(0);
leg->SetFillStyle(1001);
leg->AddEntry("","Therminator Au-Au #sqrt{s_{NN}} = 200 GeV","");
leg->AddEntry("","BlastWaveVT","");
leg->AddEntry(ptpH,"proton","l");
leg->AddEntry(ptantipH,"anti proton","l");
leg->Draw();

c1->cd(2);
gPad->SetLogy();
ptpiH->Scale(10/(2*3.14*Float_t(nev)));
ptantipiH->Scale(10/(2*3.14*Float_t(nev)));
ptpiH->Draw();
ptantipiH->Draw("sames");
ptantipiH->SetLineColor(2);
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
TLegend *legpi = new TLegend(0.4,0.7,0.88,0.88);
legpi->SetTextFont(62);
legpi->SetTextSize(0.022);
legpi->SetLineColor(0);
legpi->SetLineStyle(0);
legpi->SetLineWidth(1);
legpi->SetFillColor(0);
legpi->SetFillStyle(1001);
legpi->AddEntry("","Therminator Au-Au #sqrt{s_{NN}} = 200 GeV","");
legpi->AddEntry("","BlastWaveVT","");
legpi->AddEntry(ptpH,"pion","l");
legpi->AddEntry(ptantipH,"anti pion","l");
legpi->Draw();

c1->cd(3);
gPad->SetLogy();
ptkH->Scale(10/(2*3.14*Float_t(nev)));
ptantikH->Scale(10/(2*3.14*Float_t(nev)));
ptkH->Draw();
ptantikH->Draw("sames");
ptantikH->SetLineColor(2);
ptkH->SetXTitle("p_{T} [GeV]");
ptkH->GetXaxis()->CenterTitle(true);
ptkH->GetXaxis()->SetTitleSize(0.04);
ptkH->GetXaxis()->SetLabelSize(0.03);
ptkH->GetXaxis()->SetTitleOffset(1.2);
ptkH->SetYTitle("1/N_{ev} dN/dp_{T}");
ptkH->GetYaxis()->CenterTitle(true);
ptkH->GetYaxis()->SetTitleSize(0.04);
ptkH->GetYaxis()->SetLabelSize(0.03);
ptkH->GetYaxis()->SetTitleOffset(1.2);
TLegend *legk = new TLegend(0.4,0.7,0.88,0.88);
legk->SetTextFont(62);
legk->SetTextSize(0.022);
legk->SetLineColor(0);
legk->SetLineStyle(0);
legk->SetLineWidth(1);
legk->SetFillColor(0);
legk->SetFillStyle(1001);
legk->AddEntry("","Therminator Au-Au #sqrt{s_{NN}} = 200 GeV","");
legk->AddEntry("","BlastWaveVT","");
legk->AddEntry(ptpH,"kaon","l");
legk->AddEntry(ptantipH,"anti kaon","l");
legk->Draw();
c1->cd(4);
gPad->SetLogy();
ptlH->Scale(10/(2*3.14*Float_t(nev)));
ptantilH->Scale(10/(2*3.14*Float_t(nev)));
ptlH->Draw();
ptantilH->Draw("sames");
ptantilH->SetLineColor(2);
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
TLegend *legl = new TLegend(0.4,0.7,0.88,0.88);
legl->SetTextFont(62);
legl->SetTextSize(0.022);
legl->SetLineColor(0);
legl->SetLineStyle(0);
legl->SetLineWidth(1);
legl->SetFillColor(0);
legl->SetFillStyle(1001);
legl->AddEntry("","Therminator Au-Au #sqrt{s_{NN}} = 200 GeV","");
legl->AddEntry("","BlastWaveVT","");
legl->AddEntry(ptpH,"lambda","l");
legl->AddEntry(ptantipH,"anti lambda","l");
legl->Draw();
c1->SaveAs("pidBW.eps");

}
