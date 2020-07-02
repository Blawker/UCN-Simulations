/*
Created the 22. June 2020
Author: Thomas Guilbaud
Conversion of CSV file into ROOT histogram
The data in the CSV file must be like for example:
123.456,0.123456
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "TCanvas.h"
#include "TFrame.h"
#include "TBenchmark.h"
#include "TString.h"
#include "TF1.h"
#include "TH1.h"
#include "TGraph.h"
#include "TFile.h"
#include "TROOT.h"
#include "TError.h"
#include "TInterpreter.h"
#include "TSystem.h"
#include "TPaveText.h"
#include "TFitResult.h"

using namespace std;

TF1* fit1, *fit2;

long count_line(std::string file_path) {
  long number_of_lines = 0;
  std::string line;
  std::ifstream file(file_path);

  while (std::getline(file, line))
      ++number_of_lines;
  //std::cout << "Number of lines in csv file: " << number_of_lines;
  file.close();
  return(number_of_lines);
}

Double_t fit_Boltzmann(Double_t *x, Double_t *par) {
  // Fit with a Maxwell-Boltzmann distribution; Parameters[0: temperature T, 1: Normalized Constant]
  Double_t k = 1.38e-23; // Boltzmann constant
  Double_t e = 1.602e-19; // Coulomb charge in J
  Double_t fitval = par[1]*2*TMath::Sqrt(x[0]*e/TMath::Pi())*TMath::Power(1/(k*par[0]), 3/2) * exp(-x[0]*e/(k*par[0]));
  return(fitval);
}

Double_t fit_Landau(Double_t* x, Double_t* par) {
  // Fit with a Landau distribution; Parameters[0: const, 1: mpv, 2: sigma]
  Double_t fitval = par[0]*TMath::Landau(x[0], par[1], par[2]);
  return(fitval);
}

Double_t sum(Double_t* x, Double_t* par){
  if (x[0] <= 255e-9) {
    return(fit1->EvalPar(x,par));
  }
  return(fit2->EvalPar(x,par));
}

void fit() {
  // https://root.cern.ch/root/html/tutorials/tree/tree1.C.html

  Double_t upper_energy = 5000e-9; // in eV
  Double_t lower_energy = 0; // in eV
  Double_t mid_energy = 255e-9;

  TCanvas *canvas_1 = new TCanvas("c1", "TRIGA Spectrum Fit");
  //gStyle->SetOptFit(111); // Show the fit parameters on the canvas

  TFile *f = new TFile("../config/Spectrum/triga_neutron_spectrum_gr.root", "UPDATE");

  //create one histogram
  //TH1F *hke = new TH1F("hke_P1", "Kinetic Energy Distribution", 100, lower_energy, upper_energy);
  TGraph* graph;

  f->GetObject("Graph", graph);

  // Fit
  /*TF1 *func = new TF1("fit", fit_Boltzmann, lower_energy, upper_energy, 2);
  func->SetParameters(1.e-3, 8.e-13);
  func->SetParNames("Temperature", "Normalized Const");
  graph->Fit(func, "R");
  graph->Draw();
  func->DrawClone("Same");
  canvas_1->Draw();*/

  Double_t par[6];
  fit1 = new TF1("fit1", fit_Landau, lower_energy, mid_energy, 3);
  fit2 = new TF1("fit2", fit_Landau, mid_energy, upper_energy, 3);
  fit1->SetParameters(1, 2e-7, 8e-8);
  fit2->SetParameters(1, 2e-7, 8e-8);
  fit1->SetParNames("Constant1", "MPV1", "Sigma1");
  fit2->SetParNames("Constant2", "MPV2", "Sigma2");
  std::cout << std::endl
            << "****************************************" << std::endl
            << "        Landau Distribution Fit         ";
  graph->Fit(fit1, "R");
  graph->Fit(fit2, "R+");
  fit1->GetParameters(&par[0]);
  fit2->GetParameters(&par[3]);


  TF1 *fit_tot = new TF1("fit1+fit2", sum, lower_energy, upper_energy, 0);

  TH1* histogram_fit = new TH1F("hke_triga", "TRIGA Distribution", 1000, lower_energy, upper_energy);

  for (double i=0; i<1e7; i++) {
    histogram_fit->Fill(fit_tot->GetRandom());
  }
  histogram_fit->GetXaxis()->SetTitle("Energy (eV)");
  histogram_fit->GetYaxis()->SetTitle("Rate");
  histogram_fit->Write();

  graph->Draw();
  fit1->DrawClone("Same");
  fit2->DrawClone("Same");
  canvas_1->Draw();

  f->Close();
  return;
}

int main(int argc, char* argv[]) {
  /* Extraction of data in a CSV file into a TGraph chart in a ROOT file.
  */
  // The command line is empty, the user need help
  if (argc == 1) {
    cout << "Usage: "
         << argv[0]
         << " path/file_in.csv path/file_out.root"
         << endl;
    return(EXIT_SUCCESS);
  }

  // The command line contain more than 1 argument
  if (argc != 3) {
    cerr << "Incorrect number of arguments." << endl;
    return(EXIT_FAILURE);
  }

  // Open the input CSV file
  std::ifstream file_in(argv[1]);

  // Check if the CSV file exist
  if (!file_in) {
    cerr << "The file " << argv[1] << " doesn't exit." << endl;
    return(EXIT_FAILURE);
  }

  // Create the output ROOT file
  TFile *file_out = new TFile(argv[2], "RECREATE");

  // Check if the ROOT file exist
  if (!file_out) {
    cerr << "The file " << argv[2] << " doesn't exit." << endl;
    return(EXIT_FAILURE);
  }

  // Boundary of the graph on x-axis
  double upper_energy = 5000e-9;
  double lower_energy = 0e-9;

  // Variables for the extraction
  std::string line, word;
  vector<double> row;
  double num;

  // Variables for the graph
  const long n = count_line(argv[1]); // number of lines
  Double_t x[n], y[n];
  long i = 0;

  // Extraction by reading by lines
  while (getline(file_in, line, '\n')) {
    row.clear();
    stringstream s(line);
    // Read by word
    while (getline(s, word, ',')) {
      num = atof(word.c_str());
      row.push_back(num);
    }
    x[i] = row[0];
    y[i] = row[1];
    i++;
  }

  // Create the Graph
  TGraph *gr = new TGraph(n,x,y);
  gr->SetTitle("TRIGA Spectrum");
  gr->GetXaxis()->SetTitle("Energy (eV)");
  gr->GetYaxis()->SetTitle("Rate");
  gr->Write();

  // Close the files
  file_in.close();
  file_out->Close();

  // Output comment success of the program
  cout << n << " values have been extract from " << argv[1] << endl;
  cout << "The histogram has been successfully writen in " << argv[2] << endl;

  return(EXIT_SUCCESS);
}
