// This script reads the gain results written to a text file and plots one dimensional histogram of gain for that
{ 
  TH1F *Gain_hist = new TH1F("Gain at point 16","Charge_distribution of 354  pulses at point 16 on the PMT",100,0,6254);
 
  // Opening the text file and checking the data; then putting them into the vector and array 
  ifstream myfile("Gain16.txt");
  vector<double> numbers;
  double number;
  if ( myfile.is_open()){
    while(myfile >>number ){
      numbers.push_back(number);
    }
  }
  
  int n=numbers.size();
  double a[numbers.size()];
  
  for (int i=0; i<numbers.size();i++){
    a[i]=numbers.at(i);
    double  maximum=0;
    for(int i=0;i<n;i++)
      {
        if(a[i]>maximum)
	  maximum=a[i];
      }
     
    cout<< "The maximum number is"<< maximum<<endl;
    
    // Setting the histogram and filling it with the array of data of calculated gain
    Gain_hist->GetXaxis()->SetTitle("Charge distribution(ADC unit)");
    Gain_hist->GetYaxis()->SetTitle("The number of events");
    Gain_hist->GetXaxis()->CenterTitle();
    Gain_hist->GetYaxis()->CenterTitle();
    Gain_hist->Fill(a[i]);
    Gain_hist->Draw("HIST");
    cout<<a[i]<<endl;
  }
} 
