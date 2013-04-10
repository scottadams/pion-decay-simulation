#include <iostream>
#include <fstream>
#include <cmath>
#include "particle.h"

using namespace std;

double pi = acos(-1.0);

// Gaussian random distribution function
double gaussian()
{
	double x, y;
	do
	{
		x = 10.0*(1.0*rand()/RAND_MAX-0.5);
		y = exp(-x*x/2.0);
	} while (1.0*rand()/RAND_MAX > y);
	return x;
}

class detector
{
private:
double maxtheta, mintheta, sigma1, sigma2;
// private data members

public:
// default constructor
	detector()
	{
		maxtheta = 0.0;
		mintheta = 0.0;
		sigma1 = 0.0;
		sigma2 = 0.0;
	}

// constructor (converts degrees to radians)
	detector(double min, double max, double sig1, double sig2)
	{
		mintheta = min*pi/180;
		maxtheta = max*pi/180;
		sigma1 = sig1;
		sigma2 = sig2;
	}

// access methods for max and min theta
	double getmaxtheta()
	{
		return maxtheta;
	}
	double getmintheta()
	{
		return mintheta;
	}


// modifiers to set max and min theta
	double setmaxtheta(double value)
	{
		maxtheta = value;
	}
	double setmintheta(double value)
	{
		mintheta = value;
	}

// access methods for sigma1 and sigma2
	double getsigma1()
	{
		return sigma1;
	}
	double getsigma2()
	{
		return sigma2;
	}

// access method for total resolution sigmaT - equation in lab script
	double getsigmaT(particle pos)
	{
		return sqrt(sigma1*sigma1 + sigma2*sigma2*(pos.getT()));
	}
	
// return kinetic energy of positron in range of accepted theta for perfect detector
	double perfT(particle pos)
	{
	if
		((mintheta < pos.gettheta())&& (pos.gettheta() < maxtheta))
		return pos.getT();
	else
		return 0;
	}

// return kinetic energy of positron in accepted range for realistic detector
	double realT(particle pos)
	{
	if
		((mintheta < pos.gettheta())&& (pos.gettheta() < maxtheta))
		return pos.getT() + getsigmaT(pos)*gaussian();
	else
		return sigma1*gaussian();
	}

};