
{
  TChain mychain("phsd");
  mychain.Add("dataPHSD/iglue0/phsd*.root");
  Int_t nev=10000;
  TChain mychain2("phsd");
   mychain2.Add("dataPHSD/iglue1/phsd*.root");
   Int_t nev2=10000;


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



    Int_t           isub2; // external loop (run over different values for the impact parameter)
   Int_t           irun2; //internal loop (parallel events)
   Float_t         b2;
   Float_t         ibw2;
   Float_t         psi2[4];
   Float_t         epsilon2[4];
   Int_t           np2;//participants
   Int_t           n2;//total particles
   Int_t           id2[90000];   //[n]
   Short_t         q2[90000];   //[n]
   Float_t         e2[90000];   //[n]
   Float_t         px2[90000];   //[n]
   Float_t         py2[90000];   //[n]
   Float_t         pz2[90000];   //[n]
   Int_t           code12[90000];   //[n]
   Int_t           code22[90000];   //[n]
   /////////All particles, protons, neutrons, and all charged particles////////////////////////////
TH1F *ptH = new TH1F("pt","",100,0,10);
TH1F *pH = new TH1F("p","",200,0,20);
TH1F *eH = new TH1F("e","",200,0,20);
TH1F *etaH = new TH1F("eta","",200,-10,10);
TH1F *pt2H = new TH1F("pt2","",100,0,10);
TH1F *p2H = new TH1F("p2","",200,0,20);
TH1F *e2H = new TH1F("e2","",200,0,20);
TH1F *eta2H = new TH1F("eta2","",200,-10,10);
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

   //Setting Branch Adress
      mychain2.SetBranchAddress("isub", &isub2, &b_isub);
      mychain2.SetBranchAddress("irun", &irun2, &b_irun);
      mychain2.SetBranchAddress("b", &b2, &b_b);
      mychain2.SetBranchAddress("ibw", &ibw2, &b_ibw);
      mychain2.SetBranchAddress("psi", psi2, &b_psi);
      mychain2.SetBranchAddress("epsilon", epsilon2, &b_epsilon);
      mychain2.SetBranchAddress("np", &np2, &b_np);
      mychain2.SetBranchAddress("n", &n2, &b_n);
      mychain2.SetBranchAddress("id", id2, &b_id);
      mychain2.SetBranchAddress("q", q2, &b_q);
      mychain2.SetBranchAddress("e", e2, &b_e);
      mychain2.SetBranchAddress("px", px2, &b_px);
      mychain2.SetBranchAddress("py", py2, &b_py);
      mychain2.SetBranchAddress("pz", pz2, &b_pz);
      mychain2.SetBranchAddress("code1", code12, &b_code1);
      mychain2.SetBranchAddress("code2", code22, &b_code2);

Int_t nevent = mychain.GetEntries();
cout << nevent << endl;
Int_t nb =0;
Int_t nb2 =0;

for (Int_t jentry=0; jentry < nevent; jentry++) //Loop over events
    {
mychain.GetEvent(jentry);
if (b>5)continue;
nb++;
for(Int_t j=0; j < n; j++) {  //Loop over particles
Float_t pt[90000];
Float_t p[90000];
Float_t theta[90000];
Float_t eta[90000];
if (code1[j]<0)continue;
//if(id[j]==3122) {

pt[j] = sqrt(px[j]*px[j]+py[j]*py[j]);
p[j] = sqrt(px[j]*px[j]+py[j]*py[j]+pz[j]*pz[j]);
theta[j] = atan2(pt[j],pz[j]);
eta[j] = -log(tan(theta[j]/2));
///Filling histograms/////////////////////////////////////////////////////////////////////////////////
ptH->Fill(pt[j]);
pH->Fill(p[j]);
eH->Fill(e[j]);
etaH->Fill(eta[j]);
//}//for j
   }//for i
 }
 Int_t nevent2 = mychain2.GetEntries();
 cout << nevent2 << endl;

 for (Int_t jentry2=0; jentry2 < nevent2; jentry2++) //Loop over events
     {
 mychain2.GetEvent(jentry2);
if (b2>5)continue;
nb2++;
 for(Int_t j=0; j < n2; j++) {  //Loop over particles
 Float_t pt2[90000];
 Float_t p2[90000];
 Float_t theta2[90000];
 Float_t eta2[90000];
 if (code12[j]<0)continue;
 //if(id[j]==3122) {
 pt2[j] = sqrt(px2[j]*px2[j]+py2[j]*py2[j]);
 p2[j] = sqrt(px2[j]*px2[j]+py2[j]*py2[j]+pz2[j]*pz2[j]);
 theta2[j] = atan2(pt2[j],pz2[j]);
 eta2[j] = -log(tan(theta2[j]/2));
 ///Filling histograms/////////////////////////////////////////////////////////////////////////////////
 pt2H->Fill(pt2[j]);
 p2H->Fill(p2[j]);
 e2H->Fill(e2[j]);
 eta2H->Fill(eta2[j]);
 //}//for j
    }//for i
  }
  cout << nb << " " << nb2 << endl;


   TCanvas* c1 = new TCanvas("c1","Therminator test basic example",800,800);
   gStyle->SetOptStat(false);
   c1->SetRightMargin(0.05);
   c1->SetTopMargin(0.1);
   c1->SetFillColor(0);
   //c1->SetLogy();
   c1->Divide(2,2);
   c1->cd(1);
   gPad->SetLogy();
   ptH->Scale(10/(Float_t(nb)));
   pt2H->Scale(10/(Float_t(nb2)));
   ptH->Draw();
   pt2H->Draw("sames");
   pt2H->SetLineColor(2);
   ptH->SetXTitle("p_{T} [GeV]");
   ptH->GetXaxis()->CenterTitle(true);
   ptH->GetXaxis()->SetTitleSize(0.04);
   ptH->GetXaxis()->SetLabelSize(0.03);
   ptH->GetXaxis()->SetTitleOffset(1.2);
   ptH->SetYTitle("1/N_{ev} dN/dp_{T}");
   ptH->GetYaxis()->CenterTitle(true);
   ptH->GetYaxis()->SetTitleSize(0.04);
   ptH->GetYaxis()->SetLabelSize(0.03);
   ptH->GetYaxis()->SetTitleOffset(1.2);

   c1->cd(2);
   gPad->SetLogy();
   pH->Scale(10/Float_t(nb));
   p2H->Scale(10/Float_t(nb2));
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
   //pH->GetYaxis()->SetRangeUser(5,1e3);

   TLegend *leg = new TLegend(0.4,0.7,0.88,0.88);
   leg->SetTextFont(62);
   leg->SetTextSize(0.022);
   leg->SetLineColor(0);
   leg->SetLineStyle(0);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   leg->AddEntry("","PHSD Au-Au #sqrt{s_{NN}} = 200 GeV 0-5%","l");
   leg->AddEntry(pH,"iglue=0","l");
   leg->AddEntry(p2H,"iglue=1","l");

  // leg->AddEntry(pH,"SingleFreezeOut","l");

   leg->Draw();
   c1->cd(3);
   gPad->SetLogy();
   eH->Scale(10/Float_t(nb));
   e2H->Scale(10/Float_t(nb2));
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
   eH->GetYaxis()->SetRangeUser(10,1e4);
   c1->cd(4);
   //gPad->SetLogy();
   etaH->Scale(10/Float_t(nb));
   eta2H->Scale(10/Float_t(nb2));
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
   etaH->GetYaxis()->SetRangeUser(0,1000);
   c1->SaveAs("pimaryPHSD0-5.eps");


}//loop
