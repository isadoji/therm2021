{

TFile * ther =new TFile("event0.root");
TFile * ther1 =new TFile("event1.root");
TFile * ther2 =new TFile("event2.root");
TFile * ther3 =new TFile("event3.root");
TTree * arbolT = (TTree *)ther->Get("particles");
TTree * arbolT1 = (TTree *)ther1->Get("particles");
TTree * arbolT2 = (TTree *)ther2->Get("particles");
TTree * arbolT3 = (TTree *)ther3->Get("particles");
TCanvas *c3=new TCanvas();

TH1F * P = new TH1F("P", "P", 100,0,4.4);
TH1F * P1 = new TH1F("P1", "P1", 100,0,4.4);
TH1F * P2 = new TH1F("P2", "P2", 100,0,4.4);
TH1F * P3 = new TH1F("P3", "P3", 100,0,4.4);
TH1F * Pme = new TH1F("Pme", "Pme", 100,0,4.4);
TH1F * Pme1 = new TH1F("Pme1", "Pme1", 100,0,4.4);
TH1F * Pme2 = new TH1F("Pme2", "Pme2", 100,0,4.4);
TH1F * Pme3 = new TH1F("Pme3", "Pme3", 100,0,4.4);
TGraphErrors *grP = new TGraphErrors("proton");
TGraphErrors *grPme = new TGraphErrors("antiproton");
arbolT->Project("P", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==2212&&fatherpid==2212&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT1->Project("P1", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==2212&&fatherpid==2212&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT2->Project("P2", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==2212&&fatherpid==2212&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT3->Project("P3", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==2212&&fatherpid==2212&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");




grP->SetTitle("Transverse momentu spectra for p^{+} |y|<0.5");
grP->Draw();
P->Draw("same");
grP->GetYaxis()->SetTitle("(1/N_{event})dN^{2}/2#pip_{T}dp_{T}dy (GeV^{-2})");
grP->GetYaxis()->CenterTitle();
grP->GetXaxis()->SetTitle("p_{T} (GeV)");
grP->GetXaxis()->CenterTitle();
auto legend5 = new TLegend;
legend5->AddEntry(P, "THERMINATOR data, T=0.1656 GeV, #mu_{B}=0.0285 GeV");
legend5->AddEntry(grP, "STAR experiment, Au+Au #sqrt{s_{NN}}=200 GeV, c=0-12%");
legend5->Draw();
gPad->SetLogy();





}
