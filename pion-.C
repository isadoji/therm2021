{
TFile * ther =new TFile("event0.root");
TFile * ther1 =new TFile("event1.root");
TFile * ther2 =new TFile("event2.root");
TFile * ther3 =new TFile("event3.root");
TTree * arbolT0 = (TTree *)ther->Get("particles");
TTree * arbolT1 = (TTree *)ther1->Get("particles");
TTree * arbolT2 = (TTree *)ther2->Get("particles");
TTree * arbolT3 = (TTree *)ther3->Get("particles");
TCanvas *c1=new TCanvas();

TGraphErrors *grPime = new TGraphErrors("pi-");

TH1F * Pime = new TH1F("Pime", "Pime", 100,0,4.4);
TH1F * Pime2 = new TH1F("Pime2", "Pime2", 100,0,4.4);
TH1F * Pime3 = new TH1F("Pime3", "Pime3", 100,0,4.4);
TH1F * Pime4 = new TH1F("Pime4", "Pime4", 100,0,4.4);
arbolT0->Project("Pime", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-211&&fatherpid==-211&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT1->Project("Pime2", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-211&&fatherpid==-211&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT0->Project("Pime3", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-211&&fatherpid==-211&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT1->Project("Pime4", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-211&&fatherpid==-211&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");

Pime->Add(Pime2);Pime->Add(Pime3);Pime->Add(Pime4);


c1->cd(2);
grPime->SetTitle("Transverse momentum distribution for #pi^{-} a |y|<0.5");
grPime->Draw();
Pime->Draw("same");
grPime->GetYaxis()->SetTitle("(1/N_{event})dN^{2}/2#pip_{T}dp_{T}dy (c^{4}/GeV^{2})");
grPime->GetYaxis()->CenterTitle();
grPime->GetXaxis()->SetTitle("p_{T} (GeV/c^{2})");
grPime->GetXaxis()->CenterTitle();
auto legend2 = new TLegend;
legend2->AddEntry(Pime, "THERMINATOR data, T=0.1656 GeV, #mu_{B}=0.0285 GeV");
legend2->AddEntry(grPime, "STAR experiment, Au+Au #sqrt{s_{NN}}=200 GeV, c=0-12%");
legend2->Draw();
gPad->SetLogy();
}
