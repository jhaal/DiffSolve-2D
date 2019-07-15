/**
 * DiffSolve-2D.cpp
 *DESCRIPTION:steady state testbench
 *REQUIREMENTS:DiffSolve-2D.hpp,ccomp,xsec
 *BUGS:
 *AUTHOR: Alok_Jha
 *E-mail: jhaalok1984_at_gmail.com
 *ORGANIZATION:NPCIL
 *VERSION:1.1
 *REVISION:0.0
 *CREATED:Thursday, 17 January 2019. Released on 18-06-2019
 */

#include"DiffSolve-2D.hpp"

int main(void){
  using namespace std;
  ofstream gplot;
  ofstream kfile;
  kfile.open("keff.txt");
  gplot.open("plot.gp");

  cout << string(ss,'*') << endl;
  cout << string(2, '*')  << string(ss-40,' ') << "Author: Alok Jha" << string(ss-40,' ') << string(2,'*') << endl;
  cout << string(2, '*')  << string(ss-47,' ') << "email-Id: jhaalok1984_at_gmail.com" << string(ss-51,' ') << string(2,'*') << endl;
  cout << string(2, '*')  << string(ss-48,' ') << "2-D Neutron Diffusion Equation Solver"  << string(ss-53,' ') << string(2,'*') << endl;
  cout << string(2, '*')  << string(ss-48,' ') << "Steady State Diffusion Equation Solver"  << string(ss-54,' ') << string(2,'*') << endl;
  cout << string(ss,'*') << endl;

  kfile << string(ss,'#') << endl;
  kfile << string(2, '#')  << string(ss-40,' ') << "Author: Alok Jha" << string(ss-40,' ') << string(2,'#') << endl;
  kfile << string(2, '#')  << string(ss-47,' ') << "email-Id: jhaalok1984_at_gmail.com" << string(ss-51,' ') << string(2,'#') << endl;
  kfile << string(2, '#')  << string(ss-48,' ') << "2-D Neutron Diffusion Equation Solver"  << string(ss-53,' ') << string(2,'#') << endl;
  kfile << string(2, '#')  << string(ss-48,' ') << "Steady State Diffusion Equation Solver"  << string(ss-54,' ') << string(2,'#') << endl;
  kfile << string(ss,'#') << endl;
  
  int i,j,z;
  double **A, **B, **C, **Sr, **S, **scat, **phiFast, **phiThermal,**absorption;
  double dx,dy,vcell;

  dx = dy = 1;//changeable mesh size
  vcell = dx*dy;//cell dimensions
  
  A            = new double *[XROW];
  B            = new double *[CROW];
  C            = new double *[XROW]; 
  Sr           = new double *[CROW];
  S            = new double *[CROW];
  scat         = new double *[CROW]; 
  absorption   = new double *[CROW];
  phiFast      = new double *[CROW];
  phiThermal   = new double *[CROW];
  
  for (i = 0; i < XROW; i++){
      C[i] = new double [XCOL];
  
  for (i = 0; i < XROW; i++){
      A[i] = new double [XCOL];
  }
  ifstream InFile1("xsec");
  InFile1.ignore(10000,'\n');
  for (i = 0; i < XROW; i++)
    {    
      for (j = 0; j < XCOL; j++)
	{
	  InFile1 >> A[i][j];
	  // cout << A[i][j] << ' ';
	}
      // cout <<endl;
    }
  // cout << string(ss,'*') << endl;

  for (i = 0; i < CROW; i++){
      B[i] = new double [CCOL];
  }
  ifstream InFile("ccomp");
  InFile.ignore(10000,'\n');
  for (i = 0; i < CROW; i++)
    {    
      for (j = 0; j < CCOL; j++)
	{
	  InFile >> B[i][j];
	  // cout << B[i][j] << ' ';
	}
      // cout <<endl;
    }
  // cout << string(ss,'*') << endl;
  }
  for (i = 0; i < CROW; i++){
      Sr[i] = new double [CCOL];
  }
  for (i = 0; i < CROW; i++){
      S[i] = new double [CCOL];
  }  
  for (i = 0; i < CROW; i++){
      scat[i] = new double [CCOL];
  }
  for (i = 0; i < CROW; i++){
      phiFast[i] = new double [CCOL];
  }
    for (i = 0; i < CROW; i++){
      phiThermal[i] = new double [CCOL];
  }
  for (i = 0; i < CROW; i++){
      absorption[i] = new double [CCOL];
  }
  double kOld,kNew,kTemp;
  double dce[CROW][CCOL],dcw[CROW][CCOL],dcn[CROW][CCOL],dcs[CROW][CCOL],dc[CROW][CCOL];
  double dc0e[CROW][CCOL],dc0w[CROW][CCOL],dc0n[CROW][CCOL],dc0s[CROW][CCOL],total[CROW][CCOL];
  double dce2[CROW][CCOL],dcw2[CROW][CCOL],dcn2[CROW][CCOL],dcs2[CROW][CCOL],dc2[CROW][CCOL];
  double dc0e2[CROW][CCOL],dc0w2[CROW][CCOL],dc0n2[CROW][CCOL],dc0s2[CROW][CCOL],total2[CROW][CCOL];
  //fast parameters
  double t2[CROW][CCOL],t3[CROW][CCOL],t4[CROW][CCOL],t5[CROW][CCOL],t6[CROW][CCOL];
  double t6abs[CROW][CCOL],t6norm[CROW][CCOL];
  //thermal parameters
  double t2t[CROW][CCOL],t3t[CROW][CCOL],t4t[CROW][CCOL],t5t[CROW][CCOL],t6t[CROW][CCOL];
  double t6tabs[CROW][CCOL],t6tnorm[CROW][CCOL];
  // error
  double errorF[CROW][CCOL],errorF1,errorT[CROW][CCOL],errorT1, errorK;
  double k = 1.0;		// initial guess value of k_eff
  double x[CROW][CCOL],y[CROW][CCOL];

  for (int i = 0; i < CROW; i++) {
    for (int j = 0; j < CCOL; j++) {
      phiFast[i][j] = 1;//initial fast flux guess
      phiThermal[i][j] = 1;//initial thermal flux guess
    }
  }
  long  int F_Iteration  = 0 ;	 //iteration counter for flux
  long  int K_Iteration  = 0 ;	 //iteration counter for k_eff

  for (int i = 0; i < CROW; i++){
    for (int j = 0; j < CCOL; j++) {
      z = B[i][j];
      x[i][j]    = A[z-1][1];
      y[i][j]    = A[z-1][2];
      Sr[i][j]   = (A[z-1][3] + A[z-1][5])*vcell;//removal rate calculation
      absorption[i][j]  = A[z-1][4];//thermal absorption
      scat[i][j] = A[z-1][5];//scattering rate
      S[i][j]    = A[z-1][6] * phiThermal[i][j] * vcell / k;// source calculation
      // cout << setprecision(4) << setw(8) << **Sr << ' ';
      // cout << setprecision(4) << setw(8) <<  x[1][1] << ' ';
      // goto iterationF;
    }
    // cout << endl;
  }
 iterationK:     		// iteration for flux and criticality calculation starts here
  for (int i = 1; i < CROW-1; i++){
    for (int j = 1; j < CCOL-1; j++) {
      z = B[i][j];
      x[i][j]    = A[z-1][1];
      y[i][j]    = A[z-1][2];
      Sr[i][j]   = (A[z-1][3] + A[z-1][5])*vcell;//removal rate calculation
      absorption[i][j]  = A[z-1][4];//thermal absorption
      scat[i][j] = A[z-1][5];//scattering rate
      S[i][j]    = A[z-1][6] * phiThermal[i][j] * vcell / k;// source calculation
      goto iterationF;
    }
  }
 iterationF:			// iteration for flux convergence calculation
    for (int i = 1; i < CROW-1; i++) {
    for (int j = 1; j < CCOL-1; j++) {
      
      // fast flux calculations start here
      dce[i][j]   = x[i][j+1];
      dcw[i][j]   = x[i][j-1];
      dcn[i][j]   = x[i+1][j];
      dcs[i][j]   = x[i-1][j];
      dc[i][j]    = x[i][j];
      dc0e[i][j]  = 2*dce[i][j]*dc[i][j]*dy/(dce[i][j]*dx+dc[i][j]*dx);
      dc0w[i][j]  = 2*dc[i][j]*dcw[i][j]*dy/(dc[i][j]*dx+dcw[i][j]*dx);
      dc0n[i][j]  = 2*dc[i][j]*dcn[i][j]*dx/(dc[i][j]*dy+dcn[i][j]*dy);
      dc0s[i][j]  = 2*dc[i][j]*dcs[i][j]*dx/(dc[i][j]*dy+dcs[i][j]*dy);
      total[i][j] = dc0e[i][j]-dc0w[i][j]+dc0n[i][j]-dc0s[i][j]; // considering isotropic leakage

      // thermal flux calculations start here
      dce2[i][j]   = y[i][j+1];
      dcw2[i][j]   = y[i][j-1];
      dcn2[i][j]   = y[i+1][j];
      dcs2[i][j]   = y[i-1][j];
      dc2[i][j]    = y[i][j];
      dc0e2[i][j]  = 2*dc2[i][j]*dce2[i][j]*dy/(dc2[i][j]*dx+dce2[i][j]*dx);
      dc0w2[i][j]  = 2*dc2[i][j]*dcw2[i][j]*dy/(dc2[i][j]*dx+dcw2[i][j]*dx);
      dc0n2[i][j]  = 2*dc2[i][j]*dcn2[i][j]*dx/(dc2[i][j]*dy+dc2[i][j]*dy);
      dc0s2[i][j]  = 2*dc2[i][j]*dcs2[i][j]*dx/(dc2[i][j]*dy+dcs2[i][j]*dy);
      total2[i][j] = dc0e2[i][j]-dc0w2[i][j]+dc0n2[i][j]-dc0s2[i][j]; // considering isotropic leakage

      // component calculation fast
      t2[i][j] = total2[i][j]*phiThermal[i][j]; // total diffusion with thermal flux
      t3[i][j] = absorption[i][j]*phiThermal[i][j]*vcell; // removal by thermal neutron absorption
      t4[i][j] = dce[i][j]*phiThermal[i][j+1]+dcw[i][j]*phiThermal[i][j-1]+dcn[i][j]*phiThermal[i+1][j]+dcs[i][j]*phiThermal[i-1][j];
      t5[i][j] = t4[i][j]-t2[i][j]-t3[i][j];
      t6[i][j] = t5[i][j]/(vcell*scat[i][j]);
      t6abs[i][j]  = abs(t6[i][j]); //absolute value 
      t6norm[i][j] = t6abs[i][j]/findMax(t6abs); //normalized fast flux
      errorF[i][j]  = phiFast[i][j] - t6norm[i][j];
      errorF1 = findMax(errorF);

      // component calculation thermal
      t2t[i][j] = total[i][j]*phiFast[i][j];
      t3t[i][j] = Sr[i][j]*phiFast[i][j]*vcell;
      t4t[i][j] = dce2[i][j]*phiFast[i][j+1]+dcw2[i][j]*phiFast[i][j-1]+dcn2[i][j]*phiFast[i+1][j]+dcs2[i][j]*phiFast[i-1][j];
      t5t[i][j] = t4t[i][j]-t2t[i][j]-t3t[i][j];
      t6t[i][j] = t5t[i][j] / S[i][j];
      t6tabs[i][j]  = abs(t6t[i][j]); // absolute value
      t6tnorm[i][j] = t6tabs[i][j]/findMax(t6tabs);//normalized thermal flux
      errorT[i][j]  = phiThermal[i][j] - t6tnorm[i][j];
      errorT1 = findMax(errorT);
    }
    }
// k error correction and re-evaluation starts here
    for (int i = 1; i < CROW-1; i++) {
      for (int j = 1; j < CCOL-1; j++) {
	
	kOld = kOld + phiThermal[i][j] + phiFast[i][j];
	kNew = kNew + t6norm[i][j] + t6tnorm[i][j];
	// k = k/kOld;
	// cout << kOld << endl;
      }
    }
    // error in k calculation(outer iteration)
    kTemp = k;
    k = kTemp*(kNew/kOld);
    errorK = abs(kTemp - k);
    
    if (errorK > Kepsilon && K_Iteration < K_max){  
      if (errorF1 > epsilon && F_Iteration < F_max) {
	if (errorT1 > epsilon && F_Iteration < F_max) {	  	
	  for (int i = 1; i < CROW-1; i++) {
	    for (int j = 1; j < CCOL-1; j++) {
	      phiFast[i][j] = t6norm[i][j];
	      phiThermal[i][j] = t6tnorm[i][j];
	      // cout << setprecision(6) << setw(12) << phiThermal[i][j] << ' ';
	      // cout << setprecision(6) << setw(12) << phiFast[i][j] << ' ';
	    }
	    // cout << endl;
	  }
	  F_Iteration = F_Iteration+1;
	  cout << "#flux iteration number:\t" << F_Iteration << "\tin progress" << endl;
	  goto iterationF;
	}
      }
      K_Iteration = K_Iteration+1;
      // writing k_eff in output file kfile.txt
      kfile <<  K_Iteration << setprecision(5) << setw(12) << k << endl;
      cout << "#k iteration number:\t" << K_Iteration << "\tin progress, intermediate k value is:" << k << endl;
      goto iterationK;
    }
    else {
      cout << "\n#flux and k iteration completed \n #Normalized Thermal Flux:\n" << endl;
      for (int i = 1; i < CROW-1; i++) {
	for (int j   = 1; j < CCOL-1; j++) {
	  cout << setprecision(6) << setw(12) << phiThermal[i][j] << ' ';
	}
	cout << endl;
      }
      cout << "\n#Normalized Fast Flux:\n" << endl;
      for (int i = 1; i < CROW-1; i++) {
	for (int j   = 1; j < CCOL-1; j++) {
	  cout << setprecision(6) << setw(12) << phiFast[i][j] << ' ';
	}
	cout << endl;
      }
    // }
    cout << "\n#k_eff->\t" << k << endl;
// }
//
// open output files to write thermal and fast flux in the files for processing
//
    ofstream Thermalfile;
    ofstream Fastfile;
    // writing thermal flux in output file thermal.txt
    Thermalfile.open ("thermal.txt");
    // header
    Thermalfile << string(ss,'#') << endl;
    Thermalfile << string(2, '#')  << string(ss-40,' ') << "Author: Alok Jha" << string(ss-40,' ') << string(2,'#') << endl;
    Thermalfile << string(2, '#')  << string(ss-47,' ') << "email-Id: jhaalok1984_at_gmail.com" << string(ss-51,' ') << string(2,'#') << endl;
    Thermalfile << string(2, '#')  << string(ss-48,' ') << "2-D Neutron Diffusion Equation Solver"  << string(ss-53,' ') << string(2,'#') << endl;
    Thermalfile << string(2, '#')  << string(ss-48,' ') << "Steady State Diffusion Equation Solver"  << string(ss-54,' ') << string(2,'#') << endl;
    Thermalfile << string(ss,'#') << endl;
    for (int i = 1; i < CROW-1; i++) {
      for (int j = 1; j < CCOL-1; j++) {
	// cout << setprecision(6) << setw(12) << phiThermal[i][j] << ' ';
	Thermalfile << setprecision(6) << setw(12) << phiThermal[i][j] << ' ';
      }
      // cout << endl;
      Thermalfile << endl;
    }
    // writing fast flux in output file fast.txt    
    Fastfile.open ("fast.txt");
    // header 
    Fastfile << string(ss,'#') << endl;
    Fastfile << string(2, '#')  << string(ss-40,' ') << "Author: Alok Jha" << string(ss-40,' ') << string(2,'#') << endl;
    Fastfile << string(2, '#')  << string(ss-47,' ') << "email-Id: jhaalok1984_at_gmail.com" << string(ss-51,' ') << string(2,'#') << endl;
    Fastfile << string(2, '#')  << string(ss-48,' ') << "2-D Neutron Diffusion Equation Solver"  << string(ss-53,' ') << string(2,'#') << endl;
    Fastfile << string(2, '#')  << string(ss-48,' ') << "Steady State Diffusion Equation Solver"  << string(ss-54,' ') << string(2,'#') << endl;
    Fastfile << string(ss,'#') << endl;
    for (int i = 1; i < CROW-1; i++) {
      for (int j = 1; j < CCOL-1; j++) {
	// cout << setprecision(6) << setw(12) << phiFast[i][j] << ' ';
	Fastfile << setprecision(6) << setw(12) << phiFast[i][j] << ' ';
      }
      // cout << endl;
      Fastfile << endl;
    }
    Thermalfile.close();
    Fastfile.close();
    //
    // close output files to write thermal and fast flux in the files for processing
    //
    }
    kfile.close();

    cout << "\n#Number of rows in core matrix:\t\t\t"        << out1(0) << '\n';
    cout << "#Number of columns in core matrix:\t\t"         << out2(0) << '\n';
    cout << "#Number of rows in cross-section matrix:\t"     << out3(0) << '\n';
    cout << "#Number of columns in cross-section matrix:\t"  << out4(0) << '\n';
    cout << endl;
    cout << "Plot script named " << "\"plot.gp\"" << " created. Use command \"gnuplot < plot.gp\" to obtain plots" << '\n';
    
    // plot script file starts here - it is for gnuplot *.gp file generation
    gplot << "reset" << '\n';
    gplot << "set term eps enhanced" << '\n';
    gplot << "set output"<< " \"fast\"" << '\n';
    gplot << "set title  " << "\"3D surface from a grid (matrix) of fast flux values\"" << '\n';
    gplot << "set xrange [0:" << out1(0)-2 << "]" << '\n' ;
    gplot << "set yrange [0:" << out2(0)-2 << "]" << '\n' ;				
    gplot << "set zrange [0.95:1.0]" << '\n';
    gplot << "set dgrid3d 95,95" << '\n' ; 
    gplot << "set hidden3d" << '\n' ;
    gplot << "set xlabel  " << "\"Core Dimension Along x-axis\"" << " offset 0,-1,0 rotate parallel" << '\n' ; 
    gplot << "set ylabel  " << "\"Core Dimension Along y-axis\"" << " offset 0,-1,0 rotate parallel" << '\n' ;
    gplot << "set zlabel  " << "\"Fast Flux\"" << " offset -1,0,0 rotate parallel" << '\n' ;
    gplot << "splot " << "\"fast.txt\"" << " matrix with lines title " << "\"Normalized Fast Flux\"" << '\n' ;
    gplot << "set output" << '\n';
    gplot << endl;
    gplot << endl;
    gplot << "reset" << '\n';
    gplot << "set term eps enhanced" << '\n';
    gplot << "set output"<< " \"thermal\"" << '\n';
    gplot << "set title  " << "\"3D surface from a grid (matrix) of thermal flux values\"" << '\n';
    gplot << "set xrange [0:" << out1(0)-2 << "]" << '\n' ;
    gplot << "set yrange [0:" << out2(0)-2 << "]" << '\n' ;				
    gplot << "set zrange [0.95:1.0]" << '\n';
    gplot << "set dgrid3d 95,95" << '\n' ; 
    gplot << "set hidden3d" << '\n' ;
    gplot << "set xlabel  " << "\"Core Dimension Along x-axis\"" << " offset 0,-1,0 rotate parallel" << '\n' ; 
    gplot << "set ylabel  " << "\"Core Dimension Along y-axis\"" << " offset 0,-1,0 rotate parallel" << '\n' ;
    gplot << "set zlabel  " << "\"Thermal Flux\"" << " offset -1,0,0 rotate parallel" << '\n' ;
    gplot << "splot " << "\"thermal.txt\"" << " matrix with lines title " << "\"Normalized Thermal Flux\"" << '\n' ;
    gplot << "set output" << '\n';
    gplot << endl;
    gplot << endl;
    gplot << "reset" << '\n';
    gplot << "set term eps enhanced" << '\n';
    gplot << "set output"<< " \"k_eff\"" << '\n';
    gplot << "set title  " << "\"Plot of k_{effective} with number of iterations\"" << '\n';
    gplot << "set xlabel  " << "\"Number of iterations\"" << '\n' ; 
    gplot << "set ylabel  " << "\"k_{effective}\"" << '\n' ;
    gplot << "set xrange[0:200]" << '\n';
    gplot << "set yrange[0.9:1.1]" << '\n';
    // gplot << "plot " << "\"keff.txt\"" << " u 1:2  with lines lw 2 title " << "\"k_eff=1\"" << '\n' ;
    gplot << "plot \"keff.txt\" u 1:2 with lines lw 1 lc \'red\' title \"k_{eff}\", 1  lc \'black\' title \"k_{eff} = 1\"" << '\n';
    gplot << "set output" << '\n';
    gplot << endl;
    gplot << endl;
    gplot << "reset" << '\n';
    gplot << "set terminal qt persist size 700,700" << '\n';
    gplot << "set size 1,1" << '\n';
    gplot << "set multiplot" << '\n';
    gplot << endl;
    // fast
    gplot << "set size 0.5" << '\n';
    gplot << "set origin 0.05,0.5" << '\n';
    gplot << "set title \"Fast Flux Values \"" << '\n';
    gplot << "set xrange [0:10]" << '\n';
    gplot << "set yrange [0:10]" << '\n';
    gplot << "set zrange [0.95:1.0]" << '\n';
    gplot << "set dgrid3d 95,95" << '\n';
    gplot << "set hidden3d" << '\n';
    gplot << "set xlabel \"x-axis\"" << '\n';
    gplot << "set ylabel \"y-axis\"" << '\n';
    gplot << "set zlabel \"z-axis\" offset 0.05" << '\n';
    gplot << "splot \"fast.txt\" matrix with lines title \"Normalized Fast Flux\"" << '\n';
    gplot << endl;
    // thermal
    gplot << "set size 0.5" << '\n';
    gplot << "set origin 0.5,0.5" << '\n';
    gplot << "set title \"Thermal Flux Values\"" << '\n';
    gplot << "set xrange [0:10]" << '\n';
    gplot << "set yrange [0:10]" << '\n';
    gplot << "set zrange [0.98:1.0]" << '\n';
    gplot << "set dgrid3d 95,95" << '\n';
    gplot << "set hidden3d" << '\n';
    gplot << "set xlabel \"x-axis\"" << '\n';
    gplot << "set ylabel \"y-axis\"" << '\n';
    gplot << "set zlabel \"z-axis\" offset 0.05 " << '\n';
    gplot << "splot  \"thermal.txt\" matrix with lines title \"Normalized Thermal Flux\"" << '\n';
    gplot << endl;
    // k_eff
    gplot << "set size 1,0.5" << '\n';
    gplot << "set origin 0,0" << '\n';
    gplot << "set title \"k_{effective}\"" << '\n';
    gplot << "set xlabel \"Number of iterations\"" << '\n';
    gplot << "set ylabel \"k_{effective}\"" << '\n';
    gplot << "set xrange[0:120]" << '\n';
    gplot << "set yrange[0.9:1.1]" << '\n';
    gplot << "plot \"keff.txt\" u 1:2 with lines lw 1 lc \'red\' title \"k_{eff}\", 1  lc \'black\' title \"k_{eff} = 1\"" << '\n';
    gplot << "unset multiplot" << '\n';
    gplot.close();    
    return 0;
}
