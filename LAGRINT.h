#ifndef LAGRINT_H
#define LAGRINT_H

enum class DISTR_MODE
{
  RANDOM,
  UNIFORM
};

struct Lagrange
{
  size_t Cnt;
  double Left, Right, *Nodes, *Values;
  DISTR_MODE NodesDistr;

  double (*IntF)(double);

  Lagrange( void );
  Lagrange( size_t m, double a, double b, DISTR_MODE mode, double (*f)(double) );
  ~Lagrange( void );

  void swap( Lagrange &Other );
  Lagrange & operator=( Lagrange &&Other );

  void GenNodes( void );
  void GenValues( void );
  size_t FindNClosest( double target, size_t n );
  double Interpolate( size_t n, double x, double &error );
};

#endif // !LAGRINT_H

