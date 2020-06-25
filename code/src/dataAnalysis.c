#include "TCanvas.h"
#include "TFrame.h"
#include "TBenchmark.h"
#include "TString.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TROOT.h"
#include "TError.h"
#include "TInterpreter.h"
#include "TSystem.h"
#include "TPaveText.h"

#include <cstdlib>

void create() {
  //create a new and empty histogram
  Double_t upper_energy = 200.e-9; // in eV
  Double_t lower_energy = 1.e-11; // in eV

  // Recreate the file
  TFile *file = new TFile("../histogram/beamline_spectrum_cumul.root", "RECREATE");

  TH1F *histogram_inital_ke = new TH1F("initial_ke", "Initial Kinetic Energy Distribution", 100, lower_energy, upper_energy);
  TH1F *histogram_final_ke = new TH1F("final_ke", "Final Kinetic Energy Distribution", 100, lower_energy, upper_energy);

  histogram_inital_ke->Write();
  histogram_final_ke->Write();

  file->Close();
}

//void add(int argc, TFile* argv[]) {
void add() {
  /* Function that read ROOT files which inculde histograms
  This histogram from the source file is added to another histogram on a target file
  */

  // The command line is empty, the user need help
  /*if (argc == 1) {
    std::cout << "Usage: "
              << argv[0]
              << "name_source_file name_target_file"
              << std::endl;
    return EXIT_SUCCESS;
  }

  // The command line contain more than 2 files
  if (argc != 3) {
    std::cerr << "Incorrect number of arguments." << std::endl;
    return EXIT_FAILURE;
  }*/

  // Extract the data from the target file and fill the empty histogram
  TFile f_target("../histogram/beamline_spectrum_cumul.root", "READ");

  TH1F *histogram_inital_ke; // = new TH1F("initial_ke", "Initial Kinetic Energy Distribution", 100, lower_energy, upper_energy);
  TH1F *histogram_final_ke; // = new TH1F("final_ke", "Final Kinetic Energy Distribution", 100, lower_energy, upper_energy);

  // Recover the histogram from the target file
  f_target.GetObject("initial_ke", histogram_inital_ke);
  f_target.GetObject("final_ke", histogram_final_ke);

  // Extract the data from the source file and fill the histogram of the target file
  TFile *f_source = new TFile("../../../output/Beamline/beamline_simulation_P1.root", "READ");
  TTree *t_source = (TTree*)f_source->Get("component_track_world_DATA");
  Double_t initial_ke;
  Double_t final_ke;
  t_source->SetBranchAddress("initial_kinetic_energy", &initial_ke);
  Long64_t n_entries = t_source->GetEntries();
  for (Long64_t i=0; i<n_entries; i++) {
    t_source->GetEntry(i);
    histogram_inital_ke->Fill(initial_ke);
  }
  t_source->SetBranchAddress("final_kinetic_energy", &final_ke);
  n_entries = t_source->GetEntries();
  for (Long64_t i=0; i<n_entries; i++) {
    t_source->GetEntry(i);
    histogram_final_ke->Fill(final_ke);
  }
  f_source->Close();

  // Update the target file
  TFile f_retarget("../histogram/beamline_spectrum_cumul.root", "RECREATE");
  histogram_inital_ke->Write();
  histogram_final_ke->Write();
  f_retarget.Close();
}

void plot() {
  /* Function that extract form a file a histogram and plot if on a canvas
  */

  TFile in_file("../../histogram/beamline_spectrum_cumul.root");
  // Get the Histogram out
  TH1F* histogram;
  in_file.GetObject("initial_ke",histogram);

  // Draw it
  TCanvas *canvas=new TCanvas("canvas_1","Histogram");
  histogram->DrawCopy();
  canvas->Draw();

  in_file.Close();
}

void scale() {
  TFile in_file("../histogram/beamline_spectrum_cumul.root");
  // Get the Histogram out
  TH1F* histogram_o = new TH1F("initial_ke","", 100, 1e-11, 4e-7);
  in_file.GetObject("initial_ke",histogram_o);

  in_file.ReOpen("UPDATE");

  histogram_o->Write();

  in_file.Close();
}
