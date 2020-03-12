// Include useful libraries
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <Firmament.h>
#include <ParseCommandLine.h>

// Get namespaces
using namespace sky;
using namespace std;

// Define main function
// argc no. cmdline params
// argv actual param vals
int main(int argc, char* argv[])
{
    // Firmament sub-model
    Firmament f;

    // Command line input
    string azimuth;
    ParseCommandLine(argc, argv, "-a", azimuth);
    string inclination;
    ParseCommandLine(argc, argv, "-i", inclination);
    string radiation;
    ParseCommandLine(argc, argv, "-r", radiation);
    string filename;
    ParseCommandLine(argc, argv, "-fn", filename);

    // Convert strings to numbers
    int a = atoi(azimuth.c_str());
    int i = atoi(inclination.c_str());
    double r = atol(radiation.c_str());

    // Open file to write data to
    fstream s;
    s.open(filename,std::ios::out);

    // Resize the sky
    f.resize(i,a,r);

    // Get number of sectors in the sky
    int regions = f.numberOfRegions();

    /* Loop through sectors to get data for:
    1. Sector number
    2. Direction xyz co-ords
    3. Radiation intensity */
    for (int i = 0; i < regions; i++){

        // Create a vector of length 3 for xyz coords
        vector<double> direction(3);

        // Return val (radiation intensity)
        double ri;
        ri = f.diffuseRegionRadiationSum(i, direction);

        // Write data to file (s)
        s << i << "," << direction[0] << "," << direction[1]
        << "," << direction[2] << "," << ri << endl;
    }

    // Close file
    s.close();

}
