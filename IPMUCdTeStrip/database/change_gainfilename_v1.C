

void change_gainfilename_v1(){
  gROOT->Reset();
  TFile *fin = new TFile("parameter0927.root");
  TFile *fout = new TFile("parameter0927_namechanged.root","recreate");
  
  int numsection=8;
  int numchannel=32;
  
  int readoutblock = 0;
  int section = 0;
  int channel = 0;

  char orgname[256];
  char newname[256];

  for(int i=0;i<numsection;i++){
    for(int j=0;j<numchannel;j++){
      sprintf(orgname,"spl%d",numchannel*i+j);
      sprintf(newname,"gain_func_r%03d_%03d_%03d",readoutblock,i,j);
      TSpline *s = (TSpline *)fin->Get(orgname);
      int Np = s->GetNp();
      double xmin = s->GetXmin();
      double xmax = s->GetXmax();      
      double *x = new double[Np];
      double *y = new double[Np];

      for(int k=0;k<Np;k++){
	s->GetKnot(k,x[k],y[k]);      
	std::cout << orgname << " " << xmin << " " << xmax << " " << Np << " " << x[k] << " " << y[k] << " " << std::endl;
      }
	
      //      TSpline *ss = new TSpline3(newname,xmin,xmax,&x,&y,Np);
      
      for(int k=0;k<Np;k++){
	//	y[k] = 1000.*y[k];
	y[k] = y[k];
      }
      TSpline *ss = new TSpline3(newname,x,y,Np);
      
      ss->SetName(newname);
      ss->SetTitle(newname);

      fout->cd();
      ss->Write();
      delete x;
      delete y;
      
    }
  }
  


  fout->Close();

}
