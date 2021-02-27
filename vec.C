
{
double func( double x){
double sigma = 0.6;
double cte0 = TMath::Power(sigma*TMath::Sqrt(2*TMath::Pi()),-1);
double cte1= TMath::Power(-2*sigma*sigma,-1);
return cte0*TMath::Exp(cte1*TMath::Power(x,1));
}
  auto posxH = new TH1F("posxH","x",100,-10,10);
  auto posyH = new TH1F("posyH","y",100,-10,10);
  auto poszH = new TH1F("poszH","z",100,-10,10);
  auto possmearingxH = new TH1F("possmearingxH","x smearing",100,0,1);
  auto possmearingyH = new TH1F("possmearingyH","y smearing",100,0,1);
  auto possmearingzH = new TH1F("possmearingzH","z smearing",200,-20,20);
  auto velxH = new TH1F("velxH","vx",100,-10,10);
  auto velyH = new TH1F("velyH","vy",100,-10,10);
  auto velzH = new TH1F("velzH","vz",100,-10,10);
  auto velsmearingxH = new TH1F("velsmearingxH","vx smearing",100,0,1);
  auto velsmearingyH = new TH1F("velsmearingyH","vy smearing",100,0,1);
  auto velsmearingzH = new TH1F("velsmearingzH","vz smearing",200,-20,20);

  auto harr = new TH2F("harr","x vs y",20,-2,2,20,-2,2);
  auto harrs = new TH2F("harrs","x smearing vs y smearing ",20,-2,2,20,-2,2);
  auto hvel = new TH2F("hvel"," vx vs vy",20,-2,2,20,-2,2);
  auto hvels = new TH2F("hvels"," vx smering vs vy smearing ",20,-2,2,20,-2,2);

  harr->SetStats(0);
  harrs->SetStats(0);

TChain mychain("particles");
mychain.Add("/media/isadoji/isadoji/github/therm2021/dataSingleFreezeOut/event0.root"); //archivo a leer 500*20
struct particula_t
{
	Float_t px,py,pz,e,x,y,z,t,pid,mass,fatherpid,rootpid,event;
} PARTICLE;

particula_t particle;
mychain.SetBranchAddress("part",&particle);
Int_t nevent = mychain.GetEntries();
float pose, posx, posy, posz,vx, vy, vz,smearingx,smearingy,smearingz,velsmearingx,velsmearingy,velsmearingz;
for (Int_t i=0;i<nevent;i++)
{
//	cout << i << endl;
  	mychain.GetEvent(i);
if(particle.fatherpid !=  particle.pid && particle.pid !=  particle.rootpid ) continue;
pose= particle.e;
posx= particle.x;
posy= particle.y;
posz= particle.z;

vx = posx/pose;
vy = posy/pose;
vz = posz/pose;

smearingx = func(posx*posx+posy*posy);
smearingy = func(posx*posx+posy*posy);
smearingz = func(posz);

velsmearingx = smearingx/pose;
velsmearingy = smearingy/pose;
velsmearingz = smearingz/pose;


cout << posx << " "<<  smearingx << endl;
posxH->Fill(posx);
posyH->Fill(posy);
poszH->Fill(posz);
possmearingxH->Fill(smearingx);
possmearingyH->Fill(smearingy);
possmearingzH->Fill(smearingz);
velxH->Fill(vx);
velyH->Fill(vy);
velzH->Fill(vz);
velsmearingxH->Fill(velsmearingx);
velsmearingyH->Fill(velsmearingy);
velsmearingzH->Fill(velsmearingz);


harr->Fill(posx,posy);
harrs->Fill(smearingx,smearingy);
hvel->Fill(vx,vy);
hvels->Fill(velsmearingx,velsmearingy);
   }
TCanvas* c1 = new TCanvas("c1","Therminator test basic example",0,0,5000,5000);
gStyle->SetOptStat(false);
c1->SetRightMargin(0.05);
c1->SetTopMargin(0.1);
c1->SetFillColor(0);
//c1->SetLogy();
c1->Divide(4,2);
c1->cd(1);
//gPad->SetLogy();
posxH->Draw("");
posyH->Draw("sames");
posyH->SetLineColor(2);
// harr->Draw("ARR COLZ");
c1->cd(2);
harr->Draw("ARR COLZ");
c1->cd(3);
gPad->SetLogy();
possmearingxH->Draw("");
possmearingyH->Draw("sames");
possmearingyH->SetLineColor(2);
c1->cd(4);
harrs->Draw("ARR COLZ");
c1->cd(5);
//gPad->SetLogy();
velxH->Draw("");
velyH->Draw("sames");
velyH->SetLineColor(2);
// harr->Draw("ARR COLZ");
c1->cd(6);

hvel->Draw("ARR COLZ");
c1->cd(7);
gPad->SetLogy();
velsmearingxH->Draw("");
velsmearingyH->Draw("sames");
velsmearingyH->SetLineColor(2);
c1->cd(8);
hvels->Draw("ARR COLZ");

 }
