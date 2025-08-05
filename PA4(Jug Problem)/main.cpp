#include "Jug.h"
#include <iostream>
#include <string>

using std::string;
using std::endl;
using std::cout;
using std::ifstream;
using std::istreambuf_iterator;
using std::ofstream;


int main() {
  string solution;  // NOLINT(whitespace/indent)
  Jug head(3, 5, 4, 1, 2, 3, 4, 5, 6);
  if (head.solve(solution) != 1) {
    cout << "Error 3" << endl;
  }
  cout << solution << endl << endl;
  // redeclare solution2 and head2 to prevent redeclare warning
  string solution2;
  Jug head2(3, 5, 4, 1, 1, 1, 1, 1, 2);
  if (head2.solve(solution2) != 1) {
    cout << "Error 3" << endl;
  }
  cout << solution2 << endl;
}
