/* Kurkov Ivan, 22.B05-MM, 15.02.2024 */
#include <cstdlib>
#include <algorithm>

#include "lagrint.h"

Lagrange::Lagrange( void ) : Cnt(0), Left(0), Right(0), Nodes(nullptr), Values(nullptr) {}

Lagrange::Lagrange( size_t m, double a, double b, DISTR_MODE mode, double (*f)(double) )
  : Cnt(m), Nodes(new double[Cnt]), Values(new double[Cnt]), NodesDistr(mode), IntF(f)
{
  if (a < b)
  {
    Left = a;
    Right = b;
  }
  else
  {
    Left = b;
    Right = a;
  }
  GenNodes();
  GenValues();
}

Lagrange::~Lagrange(void)
{
  delete[] Nodes;
  delete[] Values;
}

void Lagrange::swap( Lagrange &Other )
{
  std::swap(Cnt, Other.Cnt);
  std::swap(Left, Other.Left);
  std::swap(Right, Other.Right);
  std::swap(Nodes, Other.Nodes);
  std::swap(Values, Other.Values);
  std::swap(NodesDistr, Other.NodesDistr);
  std::swap(IntF, Other.IntF);
}

Lagrange & Lagrange::operator=( Lagrange &&Other )
{
  swap(Other);
  return *this;
}

void Lagrange::GenNodes( void )
{
  switch (NodesDistr)
  {
  case DISTR_MODE::RANDOM:
    for (size_t i = 0; i < Cnt; i++)
      Nodes[i] = ((double)std::rand() / RAND_MAX - 0.5) * (Right - Left);
    std::sort(Nodes, Nodes + Cnt);
    break;
  case DISTR_MODE::UNIFORM:
    for (size_t i = 0; i < Cnt; i++)
      Nodes[i] = Left + (Right - Left) * i / (Cnt - 1);
    break;
  default:
    break;
  }
}


void Lagrange::GenValues( void )
{
  for (size_t i = 0; i < Cnt; i++)
    Values[i] = IntF(Nodes[i]);
}

size_t Lagrange::FindNClosest( double target, size_t n )
{
  size_t start = 0, end = Cnt;
  start = 0;

  while (end - start >= n)
    if (fabs(Nodes[start] - target) > fabs(Nodes[end] - target))
      start++;
    else
      end--;
  return start;
}

double Lagrange::Interpolate( size_t n, double x, double &error )
{
  size_t start = FindNClosest(x, n + 1);
  double val = 0, l;

  for (size_t i = 0; i < n; i++)
  {
    l = 1;
    for (size_t j = 0; j < n; j++)
      if (i != j)
        l *= (x - Nodes[j]) / (Nodes[i] - Nodes[j]);
    val += l * Values[i];
  }

  error = fabs(IntF(x) - val);
  return val;
}