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

TH1F * lambdame = new TH1F("lambdame", "lambdame", 100,0,4.4);
TH1F * lambdame1 = new TH1F("lambdame1", "lambdame1", 100,0,4.4);
TH1F * lambdame2 = new TH1F("lambdame2", "lambdame2", 100,0,4.4);
TH1F * lambdame3 = new TH1F("lambdame3", "lambdame3", 100,0,4.4);

TGraphErrors *grlambdame = new TGraphErrors("antilambda");

arbolT->Project("lambdame", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-3122&&fatherpid==-3122&&abs(0.5*log((e+pz)/(e-pz)))<1)");
arbolT1->Project("lambdame1", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-3122&&fatherpid==-3122&&abs(0.5*log((e+pz)/(e-pz)))<1)");
arbolT2->Project("lambdame2", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-3122&&fatherpid==-3122&&abs(0.5*log((e+pz)/(e-pz)))<1)");
arbolT3->Project("lambdame3", "sqrt(px*px+py*py)", "(1/sqrt(px*px+py*py))*(1/event)*(pid==-3122&&fatherpid==-3122&&abs(0.5*log((e+pz)/(e-pz)))<1)");

lambdame->Add(lambdame1);lambdame->Add(lambdame2);lambdame->Add(lambdame3);

grlambdame->SetTitle("Transverse momentum distribution for #bar{#Lambda^{-}} |y|<1");
grlambdame->Draw();
lambdame->Draw("same");
grlambdame->GetYaxis()->SetTitle("(1/N_{event})dN^{2}/2#pip_{T}dp_{T}dy (c^{4}/GeV^{2})");
grlambdame->GetYaxis()->CenterTitle();
grlambdame->GetXaxis()->SetTitle("p_{T} (GeV/c^{2})");
grlambdame->GetXaxis()->CenterTitle();
auto legend2 = new TLegend;
legend2->AddEntry(lambdame, "THERMINATOR data, T=0.1656 GeV, #mu_{B}=0.0285 GeV");
legend2->AddEntry(grlambdame, "STAR experiment, Au+Au #sqrt{s_{NN}}=200 GeV, c=0-5%");
legend2->Draw();
gPad->SetLogy();


}
