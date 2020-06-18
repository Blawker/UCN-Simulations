#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"

#include <iostream>

int main(int argc, char* argv[]) {
  /* Function that read ROOT files which inculde histograms
  This histogram from the source file is added to another histogram on a target file
  */

  // The command line is empty, the user need help
  if (argc == 1) {
    std::cout << "Usage: "
              << argv[0]
              << " name_source_file name_target_file"
              << std::endl;
    return EXIT_SUCCESS;
  }

  // The command line contain more than 2 files
  if (argc != 3) {
    std::cerr << "Incorrect number of arguments." << std::endl;
    return EXIT_FAILURE;
  }

  // Extract the data from the target file and fill the empty histogram
  TFile f_target(argv[2], "READ");

  TH1F *histogram_inital_ke; // = new TH1F("initial_ke", "Initial Kinetic Energy Distribution", 100, lower_energy, upper_energy);
  TH1F *histogram_final_ke; // = new TH1F("final_ke", "Final Kinetic Energy Distribution", 100, lower_energy, upper_energy);

  // Recover the histogram from the target file
  f_target.GetObject("initial_ke", histogram_inital_ke);
  f_target.GetObject("final_ke", histogram_final_ke);

  // Extract the data from the source file and fill the histogram of the target file
  TFile *f_source = new TFile(argv[1], "READ");
  TTree *t_source = (TTree*)f_source->Get("component_track_world_DATA");

  // Check if there is data in the file
  if (!t_source) {
    std::cerr << "There is no data in the file " << argv[1]
              << std::endl;
    std::cerr << "Make sure that the name of the file or his content are correct."
              << std::endl;
    return(EXIT_SUCCESS);
  }

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
  TFile f_retarget(argv[2], "RECREATE");
  histogram_inital_ke->Write();
  histogram_final_ke->Write();
  f_retarget.Close();

  std::cout << n_entries << " entries have been added from " << argv[1] << " to "
            << argv[2] << std::endl;

  return(EXIT_SUCCESS);
}
