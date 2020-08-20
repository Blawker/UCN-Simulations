/*
Created the 03. July 2020
Author: Thomas Guilbaud
Conversion of ROOT histogram into CSV table
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "TFile.h"
#include "TROOT.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"

using namespace std;

int main(int argc, char* argv[]) {
  /* Extraction of data in a CSV file into a TGraph chart in a ROOT file.
  */
  // The command line is empty, the user need help
  if (argc == 1) {
    cout << "Usage: "
         << argv[0]
         << " path/file_in.root path/file_out.csv"
         << endl;
    return(EXIT_SUCCESS);
  }

  // The command line contain more than 1 argument
  if (argc != 3) {
    cerr << "Incorrect number of arguments." << endl;
    return(EXIT_FAILURE);
  }

  // Open the output CSV file
  std::ofstream file_out(argv[2]);

  // Check if the CSV file exist
  if (!file_out) {
    cerr << "The file " << argv[2] << " doesn't exit." << endl;
    return(EXIT_FAILURE);
  }

  auto file_in = TFile::Open(argv[1]);
  if (!file_in || file_in->IsZombie()) {
     return(EXIT_FAILURE);
  }

  char* tree_name = new char[50];
  char* leaf_name = new char[50];

  // Ask the tree's name
  cout << "Tree Name : ";
  cin >> tree_name;

  // Ask the leaf's name (histogram)
  cout << "Leaf Name : ";
  cin >> leaf_name;

  // Create a TTreeReader for the tree, for instance by passing the
  // TTree's name and the TDirectory / TFile it is in.
  TTreeReader tTreeReader(tree_name, file_in);

  // The branch "final_kinetic_energy" contains double; access them as valueReader.
  TTreeReaderValue<Double_t> valueReader(tTreeReader, leaf_name);

  // Loop over all entries of the TTree or TChain.
  while (tTreeReader.Next()) {
     // Just access the data as if valueReader and valueReader were iterators (note the '*'
     // in front of them):
     file_out << *valueReader;
     file_out << endl;
  }

  std::cout << "Correct conversion from " << argv[1] << " to " << argv[2] << std::endl;

  return(EXIT_SUCCESS);
}
