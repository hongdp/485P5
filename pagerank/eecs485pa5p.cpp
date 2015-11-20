#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 6) {
    cout << "Usage: eecs485pa5p <dvalue> (-k <numiterations> |";
    cout <<" -converge <maxchange>) inputnetfile outputfile\n";
    exit(1);
  }
  assert(argv);
  return 0;
}
