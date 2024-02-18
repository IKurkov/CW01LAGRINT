#ifndef LAGRINT_H
#define LAGRINT_H

enum class DISTR_MODE
{
  RANDOM,
  UNIFORM
};

void GenNodes( double *nodes, size_t size, double left, double right, DISTR_MODE Mode );
void GenValues( const double *nodes, double *values, size_t size, double (*f)(double) );
size_t FindNClosest( const double *nodes, size_t size, double target, size_t n );
double LagrangeInterpolation( const double *nodes, const double *values, size_t deg, double x );

#endif // !LAGRINT_H