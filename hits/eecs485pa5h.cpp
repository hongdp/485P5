#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include "PageNode.h"

using namespace std;

int main(int argc, char const *argv[]) {
  cout << "num " << argc << endl;
  if (argc != 8) {
    cout << "Usage: eecs485pa5h <h value> (-k <numiterations> | -converge";
    cout << "<maxchange>) “queries” <input-net-file> ";
    cout << "<input-inverted-index-file> <output-file>" << endl;
    exit(1);
  }
  assert(argv);

  int h = atoi(argv[1]);
  string converge_type(argv[2]);
  double converge_val = atof(argv[3]);
  string query(argv[4]);
  string IN_NET_FILE(argv[5]);
  string IN_INDEX_FILE(argv[6]);
  string OUT_FILE(argv[7]);
  printf("h = %d, converge_type = %s, converge_val = %f, query = %s, net file = %s, index file = %s, out file = %s\n", h, converge_type.c_str(), converge_val, query.c_str(), IN_NET_FILE.c_str(), IN_INDEX_FILE.c_str(), OUT_FILE.c_str());
  stringstream squeries;
  squeries << query;
  string tmp_query;
  vector<string> queries;
  while(squeries >> tmp_query) {
    queries.push_back(tmp_query);
  }
  for (auto str : queries) {
    cout << str << " ";
  } cout << endl;

  map<int, PageNode*> id_to_pagenode_map;
  map<string, set<PageNode*> > invert_index_map;
  ifstream in_net_stream(IN_NET_FILE.c_str());
  if (!in_net_stream.is_open()) {
    cout << "Failed to open the net file" << endl;
    exit(1);
  }
  




  return 0;
}
