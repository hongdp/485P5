#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <PageNode.h>

using namespace std;

int main(int argc, char const *argv[]) {
  if (argc != 6) {
    cout << "Usage: eecs485pa5p <dvalue> (-k <numiterations> |";
    cout <<" -converge <maxchange>) inputnetfile outputfile" << endl;
    exit(1);
  }
  assert(argv);

  // init with input arguement
  double d = atof(argv[1]);
  string converge_type(argv[2]);
  double converge_val = atof(argv[3]);
  string IN_FILE(argv[4]);
  string OUT_FILE(argv[5]);

  // Read file
  map<int, PageNode*> Node_map;
  ifstream infile_stream(IN_FILE.c_str());
  string ver_title;
  int num_ver;
  infile_stream.open();
  if (!infile_stream.is_open()) {
    cout << "Failed to open input file" << endl;
    exit(1);
  }
  infile_stream >> ver_title >> num_ver;
  if (ver_title != "*Vertices") {
    cout << "Wrong file formate no *Vertices" << endl;
  }
  PageNode::setGlobalArgs(d, num_ver);
  for (size_t i = 0; i < num_ver; i++) {
    PageNode* tmp_node = new PageNode()
  }







  PageNode::setGlobalArgs(d, );



  return 0;
}
