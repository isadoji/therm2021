{
TFile * ther =new TFile("event0.root");
TFile * ther1 =new TFile("event1.root");
TFile * ther2 =new TFile("event2.root");
TFile * ther3 =new TFile("event3.root");
TTree * arbolT = (TTree *)ther->Get("particles");
TTree * arbolT1 = (TTree *)ther1->Get("particles");
TTree * arbolT2 = (TTree *)ther2->Get("particles");
TTree * arbolT3 = (TTree *)ther3->Get("particles");
TCanvas *c1=new TCanvas();

TH1F * lambda = new TH1F("lambda", "lambda", 100,0,4.4);
TH1F * lambda1 = new TH1F("lambda1", "lambda1", 100,0,4.4);
TH1F * lambda2 = new TH1F("lambda2", "lambda2", 100,0,4.4);
TH1F * lambda3 = new TH1F("lambda3", "lambda3", 100,0,4.4);

TGraphErrors *grlambda = new TGraphErrors("lambda");

arbolT->Project("lambda", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==3122&&fatherpid==3122&&abs(0.5*log((e+pz)/(e-pz)))<1)");
arbolT1->Project("lambda1", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==3122&&fatherpid==3122&&abs(0.5*log((e+pz)/(e-pz)))<1)");
arbolT2->Project("lambda2", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==3122&&fatherpid==3122&&abs(0.5*log((e+pz)/(e-pz)))<1)");
arbolT3->Project("lambda3", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==3122&&fatherpid==3122&&abs(0.5*log((e+pz)/(e-pz)))<1)");

lambda->Add(lambda1);lambda->Add(lambda2);lambda->Add(lambda3);



grlambda->SetTitle("Transverse momentum distribution for #Lambda |y|<1");
grlambda->Draw();
lambda->Draw("same");
grlambda->GetYaxis()->SetTitle("(1/N_{event})dN^{2}/2#pip_{T}dp_{T}dy (c^{4}/GeV^{2})");
grlambda->GetYaxis()->CenterTitle();
grlambda->GetXaxis()->SetTitle("p_{T} (GeV/c^{2})");
grlambda->GetXaxis()->CenterTitle();
auto legend = new TLegend;
legend->AddEntry(lambda, "THERMINATOR data, T=0.1656 GeV, #mu_{B}=0.0285 GeV");
legend->AddEntry(grlambda, "STAR experiment, Au+Au #sqrt{s_{NN}}=200 GeV, c=0-5%");
legend->Draw();
gPad->SetLogy();


}
