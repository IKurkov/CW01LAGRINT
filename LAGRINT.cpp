/* Kurkov Ivan, 22.B05-MM, 15.02.2024 */
#include <cstdlib>
#include <algorithm>

#include "lagrint.h"

void GenNodes( double *nodes, size_t size, double left, double right, DISTR_MODE Mode )
{
  switch (Mode)
  {
  case DISTR_MODE::RANDOM:
    for (size_t i = 0; i < size; i++)
      nodes[i] = ((double)std::rand() / RAND_MAX - 0.5) * (right - left);
    std::sort(nodes, nodes + size);
    break;
  case DISTR_MODE::UNIFORM:
    for (size_t i = 0; i < size; i++)
      nodes[i] = left + (right - left) * i / (size - 1);
    break;
  default:
    break;
  }
}


void GenValues( const double *nodes, double *values, size_t size, double (*f)(double) )
{
  for (size_t i = 0; i < size; i++)
    values[i] = f(nodes[i]);
}

size_t FindNClosest( const double *nodes, size_t size, double target, size_t n )
{
  size_t start = 0, end = size;
  start = 0;

  while (end - start >= n)
    if (fabs(nodes[start] - target) > fabs(nodes[end] - target))
      start++;
    else
      end--;
  return start;
}

double LagrangeInterpolation( const double *nodes, const double *values, size_t deg, double x )
{
  double val = 0, l;

  for (size_t i = 0; i < deg; i++)
  {
    l = 1;
    for (size_t j = 0; j < deg; j++)
      if (i != j)
        l *= (x - nodes[j]) / (nodes[i] - nodes[j]);
    val += l * values[i];
  }

  return val;
}