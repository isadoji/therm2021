{

TH1F *ptH = new TH1F("pt","",100,0,10);
TH1F *pH = new TH1F("p","",200,0,20);
TH1F *eH = new TH1F("e","",200,0,20);
TH1F *etaH = new TH1F("eta","",200,-10,10);
  gROOT->Reset();
  TChain mychain("T");
  mychain.Add("dataUrQMD/prueba.root"); //archivo a leer 500*20
  Int_t nev=10000;
  Int_t nlines = 0;
  struct particula_t
  {
    Float_t time,X,Y,Z,E,Px,Py,Pz,Pt,P,Eta,m,id,isoespin,charge,lastcoll,numbercoll,history,frezetime,frezeX,frezeY,frezeZ,frezeE,frezePx;
    Float_t frezePy,frezePz,frezePt,frezeP,frezeEta;
  } PARTICLE;

  particula_t  particle;
  mychain.SetBranchAddress("particle",&particle);
    Int_t nevent = mychain.GetEntries();
    for (Int_t i=0;i<nevent;i++)
      {
	mychain.GetEvent(i);
  if(particle.numbercoll==0)continue;//protones participantes

	//cout << "pid=" << particle.id << " charge=" << particle.charge << " mass=" << particle.m << endl;
	etaH->Fill(particle.Eta);//protones participantes
  ptH->Fill(particle.Pt);
	pH->Fill(particle.P);
	eH->Fill(particle.E);

	/*if(particle.id==101){
	  etapionsH->Fill(particle.Eta);
	}
	if(particle.id==101 && particle.charge!=0){//piones cargados
	  etapionsCH->Fill(particle.Eta);
	}
	if(particle.id==1 && particle.numbercoll==0){//Protones espectadores
	  etaprotonsH->Fill(particle.Eta);
	}
	if(particle.id==1 && particle.numbercoll!=0){//protones participantes
	  etaprotonsCH->Fill(particle.Eta);
	}*/

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
ptH->Draw();
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
pH->Draw();
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

leg->Draw();
c1->cd(3);
gPad->SetLogy();
eH->Scale(10/Float_t(nev));
eH->Draw();
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
etaH->Draw();
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
etaH->GetYaxis()->SetRangeUser(0.0,1600);
c1->SaveAs("plots/pimaryUrQMD.eps");
c1->SaveAs("plots/pimaryUrQMD.pdf");

}
