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

#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"

using namespace std;

int main(int argc, char* argv[]) {
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

  double upper_energy = 350e-9;
  double lower_energy = 100e-9;
  /*double n_mass = 1.6749e-27;
  double e = 1.602e-19;
  double E;*/

  // Create the histogram
  TH1F *histogram = new TH1F("hke_triga", "TRIGA Distribution", 25, lower_energy, upper_energy);

  // Usefull variables
  std::string line, word, x_csv, y_csv;
  vector<double> row;
  double num;
  long count = 0; // count the number of lines
  double i;

  // Read by line
  while (getline(file_in, line, '\n')) {
    row.clear();
    stringstream s(line);
    // Read by word
    while (getline(s, word, ',')) {
      num = atof(word.c_str());
      row.push_back(num);
    }
    //E = 0.5*n_mass*row[0]*row[0]/e;

    cout << row[0] << "; " << row[1] << endl;

    // Fill the histogram by using the rate with a large factor
    if (lower_energy <= row[0] && row[0] <= upper_energy) {
      for (i=0.0; i<=row[1]*1e6+1; i++) {
        histogram->Fill(row[0]);
      }
      count++;
    }
  }

  // Store the histogram in the ROOT file
  histogram->Write();

  // Close the files
  file_in.close();
  file_out->Close();

  // Output comment success of the program
  cout << count << " values have been extract from " << argv[1] << endl;
  cout << "The histogram has been successfully writen in " << argv[2] << endl;

  return(EXIT_SUCCESS);
}
