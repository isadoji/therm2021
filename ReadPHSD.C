
{
  TChain mychain("phsd");
  mychain.Add("dataPHSD/phsd.root");
  Int_t nev=1000;

// Declaration of leaf types
   Int_t           isub; // external loop (run over different values for the impact parameter)
   Int_t           irun; //internal loop (parallel events)
   Float_t         b;
   Float_t         ibw;
   Float_t         psi[4];
   Float_t         epsilon[4];
   Int_t           np;//participants
   Int_t           n;//total particles
   Int_t           id[9000];   //[n]
   Short_t         q[90000];   //[n]
   Float_t         e[9000];   //[n]
   Float_t         px[9000];   //[n]
   Float_t         py[9000];   //[n]
   Float_t         pz[9000];   //[n]
   Int_t           code1[9000];   //[n]
   Int_t           code2[9000];   //[n]
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
////////////All particles, protons, neutrons, and all charged particles////////////////////////////
TH1F *ptH = new TH1F("pt","",100,0,10);
TH1F *pH = new TH1F("p","",200,0,20);
TH1F *eH = new TH1F("e","",200,0,20);
TH1F *etaH = new TH1F("eta","",200,-10,10);

//Setting Branch Adress
   mychain.SetBranchAddress("isub", &isub, &b_isub);
   mychain.SetBranchAddress("irun", &irun, &b_irun);
   mychain.SetBranchAddress("b", &b, &b_b);
   mychain.SetBranchAddress("ibw", &ibw, &b_ibw);
   mychain.SetBranchAddress("psi", psi, &b_psi);
   mychain.SetBranchAddress("epsilon", epsilon, &b_epsilon);
   mychain.SetBranchAddress("np", &np, &b_np);
   mychain.SetBranchAddress("n", &n, &b_n);
   mychain.SetBranchAddress("id", id, &b_id);
   mychain.SetBranchAddress("q", q, &b_q);
   mychain.SetBranchAddress("e", e, &b_e);
   mychain.SetBranchAddress("px", px, &b_px);
   mychain.SetBranchAddress("py", py, &b_py);
   mychain.SetBranchAddress("pz", pz, &b_pz);
   mychain.SetBranchAddress("code1", code1, &b_code1);
   mychain.SetBranchAddress("code2", code2, &b_code2);
Int_t nevent = mychain.GetEntries();
for (Int_t jentry=0; jentry < nevent; jentry++) //Loop over events
    {
mychain.GetEvent(jentry);
cout << n << endl;

for(Int_t j=0; j < n; j++) {  //Loop over particles
Float_t pt[9000];
Float_t p[9000];
Float_t theta[9000];
Float_t eta[9000];
if (code1[j]<0)continue;
if(id[j]==3122) {
pt[j] = sqrt(px[j]*px[j]+py[j]*py[j]);
p[j] = sqrt(px[j]*px[j]+py[j]*py[j]+pz[j]*pz[j]);
theta[j] = atan2(pt[j],pz[j]);
eta[j] = -log(tan(theta[j]/2));
///Filling histograms/////////////////////////////////////////////////////////////////////////////////
ptH->Fill(pt[j]);
pH->Fill(p[j]);
eH->Fill(e[j]);
etaH->Fill(eta[j]);
}//for j
   }//for i
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
   ptH->Scale(10/(Float_t(nev)));
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
  // pH->GetYaxis()->SetRangeUser(7,1000);

   TLegend *leg = new TLegend(0.4,0.7,0.88,0.88);
   leg->SetTextFont(62);
   leg->SetTextSize(0.022);
   leg->SetLineColor(0);
   leg->SetLineStyle(0);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->AddEntry("","PHSD Au-Au #sqrt{s_{NN}} = 200 GeV","");
  // leg->AddEntry(pH,"SingleFreezeOut","l");

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
//   eH->GetYaxis()->SetRangeUser(7,1000);
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
//   etaH->GetYaxis()->SetRangeUser(0.0,1600);
   //c1->SaveAs("pimaryPHSD.eps");


}//loop
