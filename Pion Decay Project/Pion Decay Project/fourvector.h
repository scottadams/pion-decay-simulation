#ifndef FOURVECTOR_H
#define FOURVECTOR_H

#include "threevector.h"
using namespace std;
class fourvector : public threevector
{
private:
	double tcoord;

public:
// Constructors
	fourvector() : threevector()
	{
		tcoord = 0.0;
	}
	fourvector(double t, double x, double y, double z) : threevector(x, y, z)
	{
		tcoord = t;
	}
	fourvector(double t, threevector v) : threevector(v)
	{
		tcoord = t;
	}

// Print fourvector to screen
	void print()
	{
		cout << tcoord << "\t";
		threevector::print();
	}

// Print fourvector to file
	void print (std::ofstream& fout)
	{
		fout << tcoord <<  "\t";
		threevector::print(fout); 
	}

// Square of a fourvector
	double square4()
	{
		return(tcoord*tcoord - threevector::square());
	}

// Access method for fourvector
	double gett()
	{
		return(tcoord);
	}

// Modifier to set t coordinate of fourvector
	void sett(double value)
	{
		tcoord = value;
	}

// Applying the Lorentz transform to fourvector
	void setframe(threevector v_lt)

	{
		double beta = v_lt.getx();
		double gamma = 1.0 /(sqrt(1.0 - beta*beta));	// calculate gamma
		double x_lt = gamma * (getx()- beta*tcoord);	// equation to find transformed x coordinate
		double t_lt = gamma * (tcoord - beta*getx());	// equation to find transformed t coordinate
		setx(x_lt);
		sett(t_lt);	
	}


};

#endif // FOURVECTOR_H