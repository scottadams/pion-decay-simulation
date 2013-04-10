#ifndef THREEVECTOR_H  // Prevents the class being re-defined
#define THREEVECTOR_H 

#include <iostream> // Include input/output stream
#include <cmath>

class threevector
{
private:
	double xcoord, ycoord, zcoord; // Private data members

public:
// Default constructor
	threevector() 
	{
		xcoord = 0.0;
		ycoord = 0.0;
		zcoord = 0.0;
 	}

// Cartesian constructor
	threevector(double x, double y, double z)
	{
		xcoord = x;
		ycoord = y;
		zcoord = z;
	}

// Polar constructor
	threevector(double r, double theta, double phi, char ch)
	{
		double pi;
		pi = acos(-1.0);
		if (ch == 'd')
		{
			theta = (pi/180)*theta;
			phi = (pi/180)*phi;
		}
		xcoord = r * sin(theta) * cos(phi);
		ycoord = r * sin(theta) * sin(phi);
		zcoord = r * cos(theta);
	}

// print out contents to screen
	void print()
	{
		std::cout << xcoord << '\t'
 				  << ycoord << '\t'
				  << zcoord << std::endl;
	}

// print out contents to outfile
	void print(std::ofstream& fout)
	{
		fout   	  << xcoord << '\t'
				  << ycoord << '\t'
				  << zcoord << std::endl;
	}

// access method for coordinates
	double getx()
	{
		return xcoord;
	}
	double gety()
	{
		return ycoord;
	}
	double getz()
	{
		return zcoord;
	}


//access method square
	double square()
	{
		return (xcoord*xcoord + ycoord*ycoord + zcoord*zcoord);
	}

	
// access method mag3
	double mag3()
	{
		return (sqrt(square()));
	}

// access method getphi	
	double getphi()
	{
		return (atan2(ycoord, xcoord));
	}

// access method gettheta
	double gettheta()
	{
		return (acos(zcoord/mag3()));
	}

// modifier to change individual coordinates
	void setx(double value) 
	{
		xcoord=value;
	}

	void sety(double value) 
	{
		ycoord=value;
	}

	void setz(double value) 
	{
		zcoord=value;
	}

// overload the + operator
	threevector operator+(threevector v_other)
	{
		threevector v_sum(v_other.getx() + xcoord,
						  v_other.gety() + ycoord,
						  v_other.getz() + zcoord);
		return v_sum;
	}

// overload the += operator
	threevector operator+=(threevector v_other)
	{
		threevector v_inc(xcoord += v_other.getx(),
						  ycoord += v_other.gety(),
						  zcoord += v_other.getz());
		return v_inc;
	}

// overload the - operator
	threevector operator-(threevector v_other)
	{
		threevector v_minus(xcoord - v_other.getx(),
						    ycoord - v_other.gety(),
						    zcoord - v_other.getz());
		return v_minus;
	}
// overload the * operator for scalar products
	threevector operator*(double value)
	{
		threevector v_mult(xcoord*value,
						   ycoord*value,
						   zcoord*value);
		return v_mult;
	}

// overload the / operator for scalar division
	threevector operator/(double value)
	{
		threevector v_div(xcoord/value,
						  ycoord/value,
						  zcoord/value);
		return v_div;
	}

// overload the / operator for dot product
	double operator*(threevector v_other)
	{
		double v_dot = (xcoord*v_other.getx() +
					    ycoord*v_other.gety() +
					    zcoord*v_other.getz());
		return v_dot;
	}

// overload the ^ operator for cross product
	threevector operator^(threevector v_other)
	{
		threevector v_cross (ycoord * v_other.getz() - v_other.gety() * zcoord,
						   -(xcoord * v_other.getz() - v_other.getx() * zcoord),
						     xcoord * v_other.gety() - v_other.getx() * ycoord);
		return v_cross;
	}
}; 

#endif // THREEVECTOR_H