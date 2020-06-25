/*
Created the 18. June 2020
Author: Thomas Guilbaud
*/

#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  /* Function that read ROOT files which inculde histograms of interest
  This histogram from the source file is added to another histogram in a target file
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

  /*if (!f_target) {
    cerr << "The target file " << argv[2] << " doesn't exit." << endl;
    return(EXIT_FAILURE);
  }*/

  TH1F *histogram;
  char* histogram_id = new char[15];
  char* tree_name = new char[50];
  char* branch_name = new char[50];

  // Ask the histogram's id
  cout << "Histogram's id in the target file: ";
  cin >> histogram_id;

  // Recover the histogram from the target file
  f_target.GetObject(histogram_id, histogram);

  // Check if the histogram have the correct id
  if (!histogram) {
    cerr << "There is no histogram with this id." << endl;
    return(EXIT_FAILURE);
  }

  // Ask the tree's name
  cout << "Tree name in the source file (component_track_world_DATA , component_step_world_DATA , ...): ";
  cin >> tree_name;

  // Open the source file
  TFile *f_source = new TFile(argv[1], "READ");

  // Check if the source file exist
  if (!f_source) {
    cerr << "The source file " << argv[1] << " doesn't exit." << endl;
    return(EXIT_FAILURE);
  }

  // Get the tree in the source file
  TTree *t_source = (TTree*)f_source->Get(tree_name);

  // Check if there is data in the file
  if (!t_source) {
    cout << "There is no data in the file " << argv[1]
         << endl;
    cout << "Make sure that the name of the file or his content are correct."
         << endl;
    return(EXIT_SUCCESS);
  }

  // Ask the data of interest
  cout << "Branch_name in the tree (ex: initial_kinetic_energy): ";
  cin >> branch_name;

  // Extract the data from the source file and fill the histogram of the target file
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

  // Success message of the program
  cout << n_entries << " entries have been added from " << argv[1] << " to "
       << argv[2] << endl;

  return(EXIT_SUCCESS);
}
