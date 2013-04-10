#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

#include "particle.h"
#include "detector.h"

//Function to return momentum from (fake) Michel Distribution
double michel()
{
	double x, y;
	do
	{
		x = 53.0*rand()/RAND_MAX;
		y = x/53.0;
	} while (1.0*rand()/RAND_MAX > y);
	return x;
}

int main(void)
{
	ofstream outfile1 ("Positron.txt");
	ofstream outfile2 ("Muon.txt");
	ofstream outfile3 ("Michel.txt");
	ofstream outfile4 ("detectPos.txt");
	ofstream outfile5 ("detectMuon.txt");
	ofstream outfile6 ("acceptance.txt");
    
	outfile4 << "Exact" << "\t" << "Measured" << endl;
	outfile5 << "Exact" << "\t" << "Measured" << endl;
	// provides headings for the columns of energies outputted to outfiles 4 and 5
    
	detector d(40, 140, 3.5, 0.9);
    
	double pi = acos(-1.0);
    
	double Mpion = 139.6,
    Mpos = 0.511,
    Mmuon = 105.7,
    Mneu = 0.0;		// setting masses to values from lab script. units are MeV
    
	double countP1perf = 0, // declare perfect acceptance counter for muon and pion decay
    countP2perf = 0,
    countP1real = 0, // declare realistic acceptance counter for muon and pion decay
    countP2real = 0,
    effP1count = 0,	// declare efficiency counter for muon and pion decay
    effP2count = 0,
    impP1count = 0,	// declare impurity counter for muon and pion decay
    impP2count = 0; 
    
    
    // Pion decay at rest
    // energies of positron and muon from masses
	double Epos = ((Mpion*Mpion) +(Mpos*Mpos)-(Mneu*Mneu))/(2*Mpion);
	double Emuon = ((Mpion*Mpion)+(Mmuon*Mmuon)-(Mneu*Mneu))/(2*Mpion);
    
    // magnitudes of momenta of positron and muon
	double Ppos = sqrt((Epos*Epos)-(Mpos*Mpos));
	double Pmuon = sqrt((Emuon*Emuon)-(Mmuon*Mmuon));
    
    // define positron and muon objects
	particle positron(Mpos, 0.0, 0.0, Ppos),
    muon(Mmuon, 0.0, 0.0, Pmuon);		// particle momentum constrained to z axis
    
    // declare arrays
	particle pos1[1000];
	particle muon1[1000];
	particle pos2[1000];
    
    // Pion to positron decay
	for (int i=0; i<1000; i++)
	{
		double theta = acos(2.0*rand()/RAND_MAX - 1);
		double phi = 2.0*pi*rand()/RAND_MAX - pi;	
		// sets theta and phi randomly
        
		threevector v1(Ppos, theta, phi, 'r');
		particle p1(Mpos, v1);
		pos1[i] = p1;
        
		outfile1 << pos1[i].getT() << "\t"
        << pos1[i].gettheta() << "\t"
        << pos1[i].getphi() << "\t" << endl;
		outfile4 << d.perfT(pos1[i]) << "\t" 	// perfectly detect kinetic energy of positron
        << d.realT(pos1[i]) << endl;	// realistically detect kinetic energy of positron
        
		if (d.perfT(pos1[i]) > 0)
		{
			countP1perf++;
		}						
		// increase positron from pion acceptance count for perfect detector
		if (d.realT(pos1[i]) > 0)
		{
			countP1real++;
		}						
		// increase positron from pion acceptance count for realistic detector
		if (d.realT(pos1[i]) > 56)
		{
			effP1count++;
		}						
		// count number of positrons from pions in assumed range for pion-positron decay
		if (d.realT(pos1[i]) > 10 && d.realT(pos1[i]) < 56)
		{
			impP2count++;
		}						
		// count number of impurities in assumed range of particles for muon-positron decay
        
	}
    
    // Muon to positron decay
	for (int i=0; i<1000; i++)
	{
		double theta = acos(2.0*rand()/RAND_MAX - 1);
		double phi = 2.0*pi*rand()/RAND_MAX - pi;	
        
		threevector v2(Pmuon, theta, phi, 'r');
		particle m(Mmuon, v2);
		muon1[i] = m;
        
		outfile2 << muon1[i].getT() << "\t"
        << muon1[i].gettheta() << "\t"
        << muon1[i].getphi() << "\t" << endl;
	}
    
    // Muon to positron decay - uses Michel distribution
	for (int i = 0; i < 1000; i++)
	{
		double theta = acos(2.0*rand()/RAND_MAX - 1);
		double phi = 2.0*pi*rand()/RAND_MAX - pi;
        
		threevector v3(michel(), theta, phi, 'r');
		particle p2(Mpos, v3);
		pos2[i] = p2;
		outfile3 << pos2[i].getT() << "\t"
        << pos2[i].gettheta() << "\t"
        << pos2[i].getphi() << "\t" << endl;
		outfile5 << d.perfT(pos2[i]) << "\t"	// perfectly detect kinetic energy of positron
        << d.realT(pos2[i]) << "\t" << endl;	// realistically detect kinetic energy of positron
        
		if (d.perfT(pos2[i]) > 0)
		{
			countP2perf++;
		}
		// increase positron from pion acceptance count for perfect detector
		if (d.realT(pos2[i]) > 0)
		{
			countP2real++;
		}						
		// increase positron from pion acceptance count for realistic detector
		if (d.realT(pos2[i]) > 10 && d.realT(pos2[i]) < 56)
		{
			effP2count++;
		}
		// count number of positrons from muons in assumed range for muon-positron decay
		if (d.realT(pos2[i]) > 56)
		{
			impP1count++;
		}
		// count number of impurities in assumed range for pion-positron decay
	}
    
	outfile6 << "From Pion:" << endl
    << "\t Acceptance = " << 100.0*countP1perf/1000.0 << "%" << endl
    << "\t Efficiency = " << 100.0*effP1count/1000.0 << "%" << endl
    << "\t Impurity = " << 100.0*impP1count/countP1real << "%" << endl
    << "From Muon:" << endl
    << "\t Acceptance = " << 100.0*countP2perf/1000.0 << "%" << endl
    << "\t Efficiency = " << 100.0*effP2count/1000.0 << "%" << endl
    << "\t Impurity = " << 100.0*impP2count/countP2real  << "%" << endl;
    
    
    
	return 0;
    
}