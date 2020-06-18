#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"

#include <iostream>

using namespace std;

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

  TH1F *histogram;
  char* histogram_id = new char[15];
  char* tree_name = new char[50];
  char* branch_name = new char[50];

  cout << "Histogram's id in the target file: ";
  cin >> histogram_id;

  // Recover the histogram from the target file
  f_target.GetObject(histogram_id, histogram);

  cout << "Tree name in the source file (component_track_world_DATA , component_step_world_DATA , ...): ";
  cin >> tree_name;

  // Extract the data from the source file and fill the histogram of the target file
  TFile *f_source = new TFile(argv[1], "READ");
  TTree *t_source = (TTree*)f_source->Get(tree_name);

  // Check if there is data in the file
  if (!t_source) {
    std::cerr << "There is no data in the file " << argv[1]
              << std::endl;
    std::cerr << "Make sure that the name of the file or his content are correct."
              << std::endl;
    return(EXIT_SUCCESS);
  }

  cout << "Branch_name in the tree (ex: initial_kinetic_energy): ";
  cin >> branch_name;

  Double_t data;
  t_source->SetBranchAddress(branch_name, &data);
  Long64_t n_entries = t_source->GetEntries();
  for (Long64_t i=0; i<n_entries; i++) {
    t_source->GetEntry(i);
    histogram->Fill(data);
  }
  f_source->Close();

  // Update the target file
  TFile f_retarget(argv[2], "UPDATE");
  histogram->Write(histogram_id, TObject::kOverwrite);
  f_retarget.Close();

  std::cout << n_entries << " entries have been added from " << argv[1] << " to "
            << argv[2] << std::endl;

  return(EXIT_SUCCESS);
}
