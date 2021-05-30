{

  f = new TF2("f", "sin(x)*sin(y)/(x*y)",0,10,0,10);
  f->SetTitle("Example of three dimentional graph;x axis;y axis; z axis");
  
  f->Draw("surf1");

}
