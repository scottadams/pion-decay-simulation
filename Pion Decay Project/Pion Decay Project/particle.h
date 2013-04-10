#ifndef PARTICLE_H
#define PARTICLE_H

#include "fourvector.h"
#include "threevector.h"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;
class particle : public fourvector
{
public:
// Constructors
	particle () : fourvector ()
	{
	}

	particle (double m, double px, double py, double pz) : fourvector (m, px, py, pz)
// tcoord is replaced by m, and particle has a momentum threevector
	{
		double psquared = threevector::square(); // calculates momentum
		sett(sqrt(psquared + m*m));
	}

	particle(double m, threevector p) : fourvector (m, p)
	{
		double psquared = threevector::square(); 
		sett(sqrt(psquared + m*m));
		setx(p.getx());	
		sety(p.gety());
		setz(p.getz());
	}

// Access method for mass
	double getm()
	{
		return sqrt(fourvector::square4());
	}
// Access method for energy
	double gete()
	{
		return fourvector::gett(); 
	}	
// Access method for kinetic energy
	double getT()
	{
		return (gett() - getm());
	}
// Access method for components of momentum
	double getpx()
	{
		return fourvector::getx(); 
	}	
	double getpy()
	{
		return fourvector::gety(); 
	}	
	double getpz()
	{
		return fourvector::getz();
	}	
	// inherits x, y, z from fourvector

// Access method for momentum threevector
	threevector getp()
	{
		return threevector(getx(), gety(), getz());
	}

// Access method for velocity components
	double getvx()
	{ 
		return (getpx() / gett()); 
	}
	double getvy()
	{
		return (getpy() / gett());
	}
	double getvz()
	{
		return (getpz() / gett());
	}
	// calculated using v = p/m

// Access method for total velocity
	threevector getv()
	{
		return threevector((getx()/gett()), (gety()/gett()), (getz()/gett()));
	}
};

#endif //PARTICLE_H
