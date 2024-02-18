/* Kurkov Ivan, 22.B05-MM, 15.02.2024 */
#include <iostream>
#include <cmath>
#include <conio.h>

#include "lagrint.h"

double Variant7( double x )
{
  return exp(-x) - x * x / 2;
}

int main()
{
  bool run = true;
  int key;
  size_t n, m, start;
  double x, a, b, L, e = 0, *nodes = nullptr, *values = nullptr;
  DISTR_MODE mode;
  
  while (run)
  {
    std::cout << "Algebraic interpolation utility menu:\n"
              << "1 - Create new interpolation task\n"
              << "2 - Change point\n"
              << "3 - Change degree of Lagrange polynomial\n"
              << "0 - exit\n";
    switch (_getch())
    {
    case '1':
      std::cout << "Input number of arguments: ";
      std::cin >> m;
      do
      {
        std::cout << "Input [a, b]: ";
        std::cin >> a >> b;
      } while (a >= b);
      do
      {
        std::cout << "Choose nodes distribution: r - random/u - uniform\n";
        key = _getch();
        if (key == 'r')
          mode = DISTR_MODE::RANDOM;
        if (key == 'u')
          mode = DISTR_MODE::UNIFORM;
      } while (key != 'r' && key != 'u');

      if (nodes != nullptr)
        delete[] nodes;
      nodes = new double[m];
      if (values != nullptr)
        delete[] values;
      values = new double[m];
      GenNodes(nodes, m, a, b, mode);
      GenValues(nodes, values, m, Variant7);

      std::cout << "Input interpolation point: ";
      std::cin >> x;
      do
      {
        std::cout << "Input degree of Lagrange polynomial < " << m << ": ";
        std::cin >> n;
      } while (n >= m);

      start = FindNClosest(nodes, m, x, n);
      L = LagrangeInterpolation(nodes + start, values + start, n, x);

      std::cout << "f(" << x << ") = " << L << " +- " << fabs(L - Variant7(x)) << '\n';
      break;
    case '0':
      run = false;
      delete[] nodes;
      delete[] values;
      break;
    default:
      std::cout << "Incorrect choice!\n";
    }
  }
  return 0;
}