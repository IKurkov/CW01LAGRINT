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
  double x, a, b, e = 0;
  size_t n, m;
  int key;
  bool run = true;
  DISTR_MODE mode;
  Lagrange L;
  
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
      std::cout << "Input [a, b]: ";
      std::cin >> a >> b;
      do
      {
        std::cout << "Choose nodes distribution: r - random/u - uniform\n";
        key = _getch();
        if (key == 'r')
          mode = DISTR_MODE::RANDOM;
        if (key == 'u')
          mode = DISTR_MODE::UNIFORM;
      } while (key != 'r' && key != 'u');

      std::cout << "Input interpolation point: ";
      std::cin >> x;
      do
      {
        std::cout << "Input degree of Lagrange polynomial < " << m << ": ";
        std::cin >> n;
      } while (n >= m);
      L = Lagrange(m, a, b, mode, Variant7);

      std::cout << "f(x) = " << L.Interpolate(n, x, e) << " +- " << e << '\n';
      break;
    case '0':
      run = false;
      break;
    default:
      std::cout << "Incorrect choice!\n";
    }
  }

  return 0;
}