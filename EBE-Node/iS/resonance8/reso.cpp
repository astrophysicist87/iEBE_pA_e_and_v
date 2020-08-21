/*    reso.c   */
/* 
********************************************************************************
This is the public version of the resonance decay calculation using the output 
generated by the hydrodynamical code azhydro0p2.  The majority of the code was 
developed by Josef Sollfrank and Peter Kolb.  Additional work and comments 
were added by Evan Frodermann, September 2005.
Please refer to the papers 
J. Sollfrank, P. Koch, and U. Heinz, Phys. Lett B 252 (1990) and 
J. Sollfrank, P. Koch, and U. Heinz, Z. Phys. C 52 (1991) 
for a description of the formalism utilized in this program.
********************************************************************************
*/

#include <iostream>
#include <string.h>
#include <fstream>
#include <stdio.h>
#include <math.h>

#include "reso.h"
#include "functions.h"
#include "decay.h"

//*****************************************************
//This is the main program that calls all the needed subroutines.

int main() 
{

   //FILE *datin;
    
   char outdir[FILEDIM];
   char specfile[FILEDIM];
   //char dummy[200];
   
   int max, maxdecay, bound;
   
   printf("START of resonance decays !\n");
   //Read in the data from "reso.inp, including the results folder and the spectra data      
   //datin = fopen("reso.inp", "r");

   // Chris's input reading process
   std::string path="results";
   std::ifstream pathfile("pathToWorkingDirectory.txt");
   if (pathfile.good())
   {
      path = "";
      pathfile >> path;
   }
   pathfile.close();

   std::cout << "Using path = " << path << std::endl;
std::string test = "";
std::cout << "test string length = " << test.length() << std::endl;

   //fscanf(datin, "%s%s", specfile, dummy);
   //std::cout << specfile << std::endl;
   //fscanf(datin, "%s%s", outdir, dummy);
   //fscanf(datin, "%i%s", &bound, dummy);
   //fclose(datin);

   std::string tmp = "", dummy = "";
   std::ifstream datin("reso.inp");
   datin >> tmp >> dummy;
   std::string tmp2 = path + "/" + tmp;
   strcpy(specfile, tmp2.c_str());
   //std::getline(datin, dummy);	//skip reading in out directory; use "path" above instead
   datin >> dummy >> dummy;
   strcpy(outdir, path.c_str());
   datin >> bound;
   datin.close();
   std::cout << specfile << "   " << outdir << "   " << dummy << "   " << bound << std::endl;

//if (1) return(1);

   //Read in the spectra and decays using "resoweak.dat" as a database of particles
   readspec(specfile, &max, &maxdecay);
   //The main module that calculates the resonance decay feeddown
   cal_reso_decays(max, maxdecay, bound); 
   //Writes the spectra to specified data files.
   writespec(max,outdir);
   
   printf("END of reso decays ! \n");
   
   return 0;	/* ok */
}





