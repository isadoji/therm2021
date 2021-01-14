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
TH1F * Pme = new TH1F("Pme", "Pme", 100,0,4.4);
TH1F * Pme1 = new TH1F("Pme1", "Pme1", 100,0,4.4);
TH1F * Pme2 = new TH1F("Pme2", "Pme2", 100,0,4.4);
TH1F * Pme3 = new TH1F("Pme3", "Pme3", 100,0,4.4);
TGraphErrors *grPme = new TGraphErrors("antiproton");
arbolT->Project("Pme", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-2212&&fatherpid==-2212&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT1->Project("Pme1", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-2212&&fatherpid==-2212&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT2->Project("Pme2", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-2212&&fatherpid==-2212&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");
arbolT3->Project("Pme3", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-2212&&fatherpid==-2212&&abs(0.5*log((e+pz)/(e-pz)))<0.5)");

Pme->Add(Pme1);Pme->Add(Pme2);Pme->Add(Pme3);

grPme->SetTitle("Transverse momentu distribution #bar{p} |y|<0.5");
grPme->Draw();
Pme->Draw("same");
grPme->GetYaxis()->SetTitle("(1/N_{event})dN^{2}/2#pip_{T}dp_{T}dy (c^{4}/GeV^{2})");
grPme->GetYaxis()->CenterTitle();
grPme->GetXaxis()->SetTitle("p_{T} (GeV/c^{2})");
grPme->GetXaxis()->CenterTitle();
auto legend6 = new TLegend;
legend6->AddEntry(Pme, "THERMINATOR data, T=0.1656 GeV, #mu_{B}=0.0285 GeV");
legend6->AddEntry(grPme, "STAR experiment, Au+Au #sqrt{s_{NN}}=200 GeV, c=0-12%");
legend6->Draw();
gPad->SetLogy();
gStyle->SetLabelFont(36);
}
