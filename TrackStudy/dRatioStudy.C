#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "iostream"
#include "dumpMap.C"
void dRatioStudy(){
  using namespace std;
  //Macro to study dRatio(x(zRef) , y(zRef) );
  TFile *file = new TFile("Analysed_Track.root");
  TTree* t1 = (TTree*)file->Get("treee");
  cout<<"Loaded"<<endl;
  //Iterate on tree, get the ax, ay and dRatio value;
  //Fill the histogram with the average in the bin
  //Load the branches

  //
  //
  Double_t P;
  Double_t ax;
  Double_t ay;
  Double_t dRatio;
  Double_t dx;
  Double_t cx;
  t1->SetBranchAddress("Track_P",&P);
  t1->SetBranchAddress("ax_parXZ",&ax);
  t1->SetBranchAddress("ay_line",&ay);
  t1->SetBranchAddress("cx_cubXZ",&cx);
  t1->SetBranchAddress("dx_cubXZ",&dx);
  const Int_t nBinX = 39;
  Double_t BinningX[nBinX] = {0.,20.,30.,40.,50.,60.,70.,80.,90.,100.,120.,140.,160.,180.,200.,220.,240.,260.,280.,300.,340.,380.,420.,480.,520.,560.,600.,640.,700.,800.,1000.,1100.,1300.,1500.,1700.,2000.,2300.,3000.,4000.};
  const Int_t nBinY = 38;
  Int_t NBINS=100;
  TH2D *histogramOld = new TH2D("dRatio","dRatio",NBINS,-3000,3000,NBINS,-2400,2400);
  TH2D *histogramCount = new TH2D("dRatioCount","dRatioCount",100,-3000,3000,100,-2400,2400);


  Double_t BinningY[nBinY] = {0.,20.,30.,40.,50.,60.,70.,80.,90.,100.,120.,140.,160.,180.,200.,220.,240.,260.,280.,300.,340.,380.,420.,480.,520.,560.,600.,640.,700.,800.,1000.,1100.,1300.,1500.,1700.,2000.,2400.,3000.};
  TH2D *histogram = new TH2D("dRatio","dRatio",39,BinningX,38,BinningY);
  cout<<"Histogram Generated"<<endl;
  Int_t nSelected= (Int_t)t1->GetEntries("dx_cubXZ/cx_cubXZ>-0.001 && dx_cubXZ/cx_cubXZ<-0.000001 && Track_P>2000");
  std::cout<<"Selected = "<<nSelected<<std::endl;
  Int_t nEntries = (Int_t)t1->GetEntries();
  Double_t AvgDratio[37*38];
  typedef std::pair<Double_t, Double_t> xyPair;
  typedef std::pair<Int_t , Int_t> xyBinPair;

  typedef std::map<xyBinPair,std::vector<Double_t>> XYBinToValue;
  TH1D *dRatioH = new TH1D("dRatio_1D","dRatio_1D",500,-0.001,0.000010001);
  Int_t j=0;
  double data[nSelected*2];
  for (Int_t i= 0; i<nEntries; i++) {
    t1->GetEntry(i);
    dRatio = (Double_t)dx/cx;
      // std::cout<<"ax \t"<<ax<<std::endl;
      // std::cout<<"ay \t"<<ay<<std::endl;
      // std::cout<<"dRatio \t"<<dRatio<<std::endl;
    //Int_t x_=histogramOld->GetXAxis()->GetBinCenter( histogramOld->GetXaxis()->FindBin(ax)));
    //Int_t y_=histogramOld->GetYAxis()->GetBinCenter( histogramOld->GetYaxis()->FindBin(ay)));
    //SetBinContent(Int_t binx, Int_t biny, Double_t content)
    //if(x_==0) std::cout<<"Binning has also 0"<<std::endl;
    //i have the dRatio Value the ax value and the ay value;
    //for (j=0;j<38;j++)
    if(dRatio>-0.001 && dRatio<-0.000001 && P>2000){
    j++;
    dRatioH->Fill(dRatio);
    data[nSelected+j]=ay;
    data[j]=ax;
    histogramOld->Fill(ax,ay,-dRatio);
    histogramCount->Fill(ax,ay);
    }
    //if(dRatio<0.0000 && dRatio>-0.0005){
    //histogramOld->Fill(ax,ay,dRatio);
    //nt has been filled at this point
 }
 std::cout<<"Selected  "<<j<<std::endl;

 TCanvas *c1 = new TCanvas("c1","c1", 400, 400);
 //c1->Divide(1,2);
 //c1->cd(1);
 histogramOld->Divide(histogramOld,histogramCount,1,1);
 histogramOld->Draw("colz");
 //dumpMap(histogramOld);

 //DATASZ = nEntries in the histogram
 TKDTreeBinning* kdBins = new TKDTreeBinning(nSelected, 2, data, NBINS);
 UInt_t nbins = kdBins->GetNBins();
 UInt_t dim   = kdBins->GetDim();
 const Double_t* binsMinEdges = kdBins->GetBinsMinEdges();
 const Double_t* binsMaxEdges = kdBins->GetBinsMaxEdges();

 TH2Poly* h2pol = new TH2Poly("h2PolyBinTest", "KDTree binning", kdBins->GetDataMin(0), kdBins->GetDataMax(0), kdBins->GetDataMin(1), kdBins->GetDataMax(1));

 for (UInt_t i = 0; i < nbins; ++i) {
    UInt_t edgeDim = i * dim;
    h2pol->AddBin(binsMinEdges[edgeDim], binsMinEdges[edgeDim + 1], binsMaxEdges[edgeDim], binsMaxEdges[edgeDim + 1]);
 }
 Double_t Integral = 0;
 for (UInt_t i = 1; i <= kdBins->GetNBins(); ++i){
    h2pol->SetBinContent(i, kdBins->GetBinDensity(i - 1));
    Integral+=nSelected*kdBins->GetBinDensity(i - 1);
  }
  std::cout<<" Integral "<<Integral<<endl;
 std::cout << "Bin with minimum density: " << kdBins->GetBinMinDensity() << std::endl;
 std::cout << "Bin with maximum density: " << kdBins->GetBinMaxDensity() << std::endl;
 h2pol->Draw("COLZ L");
 //AdaptiveBinning
 /*TKDTreeBinning(UInt_t dataSize, UInt_t dataDim, Double_t* data, UInt_t nBins = 100, bool adjustBinEdges = false)
  Class's constructor taking the size of the data points, dimension, a data array and the number
  of bins (default = 100). It is reccomended to have the number of bins as an exact divider of
  the data size.
  The data array must be organized with a stride=1 for the points and = N (the dataSize) for the dimension.

  Thus data[] = x1,x2,x3,......xN, y1,y2,y3......yN, z1,z2,...........zN,....
  ax_1;ax_2;ax_3,.......ax_N, ay_1;ay_2;......
  Note that the passed dataSize is not the size of the array but is the number of points (N)
  The size of the array must be at least  dataDim*dataSize
*/
 //c1->cd(2);
 //dRatioH->Draw();

}