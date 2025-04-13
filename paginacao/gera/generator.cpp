
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time() to seed the random number generator
#include <fstream>
#include <iostream>

using namespace std;

void generateInstance(int numFrames, int numJobs, const string &filename) {
  // Open the output file
  ofstream outFile(filename);
  if (!outFile) {
    cerr << "Error: Could not open file " << filename << " for writing!"
         << endl;
    return;
  }

  // Write the number of frames as the first line
  outFile << numFrames << endl;

  // Generate and write the job sequence
  for (int i = 0; i < numJobs; i++) {
    int jobValue = (rand() % (numFrames * 3)) + 1; // Random number between 1 and 10
    outFile << jobValue << endl;
  }

  outFile.close();
  cout << "Instance generated and saved to " << filename << endl;
}

int main(int argc, char *argv[]) {
  // Seed the random number generator with the current time
  srand(static_cast<unsigned>(time(0)));

  // Parameters
  int numFrames = atoi(argv[1]);    // Number of frames (adjustable)
  int numJobs = atoi(argv[2]);      // Number of jobs
  string filename = "../instance.txt"; // Output file name

  // Generate the instance
  generateInstance(numFrames, numJobs, filename);

  return 0;
}
