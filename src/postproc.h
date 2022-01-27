#pragma once

#include <vector>
#include <string>
#include "mpi.h"

#include <iostream>
#include <new>
#include <cstdlib>
#include "ptrs.h"

using namespace std;

namespace MC_NS
{
  class Postproc: protected Ptrs
  {
  public:
    Postproc(class MC *);
    ~Postproc();

    // Constructor.
    FILE * fh_debug;
    int rank;

    // Functions.
    void initialize();
    void readEmat();
    void readGV(); // Read generalized velocities.
    void calc1();
    void task1();
    void task2();
    void task3();
    double integrate(double*,double*,int);
    
    // Settings
    int task; // 1 - calculate power spectrum overlap.
              // 2 - normalized autocorrelations of anm = xn*vm
              // 3 - thermal conductivity contributions from pairs nm
    string ensemble_dirname;

    /* Booleans */

    /* Arrays */
    double **emat; // eigenvectors


    // Task 1 variables
    int ntimesteps;
    double sampling_interval; // time (in ps typically) between measured data points, or MD output.
    //int ncols; // number of columns, or modes, in the xm.dat and vm.dat files.
    int nind; // number of indices, or number of columns (not including the time column) in xm.dat and vm.dat files.
    int nens; // number of ensembles to average the PS overlap for.
    bool indices_bool; // true if INDICES file exists in current dir
    int *indices;
    int overlap_output_tag; // tag which uniquely names the overlaps.dat file.

    int natoms;
    int nmodes;
    int nfc2;
    int nfc3;
    int nfc4;
    
    // Task 2 variables;
    int npairs; // number of pairs in PAIRS file
    int pairs_bool; // tells whether PAIRS file exists
    int **pairs; // pairs[i][0] and pairs[i][1] give n and m indices of ith pair, respectively.
    int output_tag; // tag for output file name: integral_norm_${output_tag}.dat
    int integral_indx; // indx to take integral to, e.g. if noutput for autocorrelation is 100,000 and timestep is 0.0025 ps, then integral_indx=20,000 gives integration time of 50 ps.
 


  };
}

