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

TGraphErrors *grPi = new TGraphErrors("pi+");
TGraphErrors *grPime = new TGraphErrors("pi-");
TH1F * Pi = new TH1F("Pi", "Pi", 100,0,4.4);
TH1F * Pi2 = new TH1F("Pi2", "Pi2", 100,0,4.4);
TH1F * Pi3 = new TH1F("Pi3", "Pi2", 100,0,4.4);
TH1F * Pi4 = new TH1F("Pi4", "Pi2", 100,0,4.4);

arbolT0->Project("Pi", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==211&&fatherpid==211&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT1->Project("Pi2", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==211&&fatherpid==211&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT2->Project("Pi3", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==211&&fatherpid==211&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT3->Project("Pi4", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==211&&fatherpid==211&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");

Pi->Add(Pi2);Pi->Add(Pi3);Pi->Add(Pi4);

grPi->SetTitle("Transverse momentum distribution for #pi^{+} |y|<0.5");
grPi->Draw();
Pi->Draw("same");
grPi->GetYaxis()->SetTitle("(1/N_{event})dN^{2}/2#pip_{T}dp_{T}dy (c^{4}/GeV^{2})");
grPi->GetYaxis()->CenterTitle();
grPi->GetXaxis()->SetTitle("p_{T} (GeV/c^{2})");
grPi->GetXaxis()->CenterTitle();
auto legend = new TLegend;
legend->AddEntry(Pi, "THERMINATOR data, T=0.1656 GeV, #mu_{B}=0.0285 GeV");
legend->AddEntry(grPi, "STAR experiment, Au+Au #sqrt{s_{NN}}=200 GeV, c=0-12%");
legend->Draw();
gPad->SetLogy();

}
