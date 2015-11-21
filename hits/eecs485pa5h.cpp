#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>
#include "PageNode.h"

using namespace std;

int main(int argc, char const *argv[]) {
  // cout << "num " << argc << endl;
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
  // printf("h = %d, converge_type = %s, converge_val = %f, query = %s, net file = %s, index file = %s, out file = %s\n", h, converge_type.c_str(), converge_val, query.c_str(), IN_NET_FILE.c_str(), IN_INDEX_FILE.c_str(), OUT_FILE.c_str());
  stringstream squeries;
  squeries << query;
  string tmp_query;
  vector<string> queries;
  while(squeries >> tmp_query) {
    queries.push_back(tmp_query);
  }
  // for (auto str : queries) {
  //   cout << str << " ";
  // } cout << endl;

  map<int, PageNode*> Node_map;
  map<string, set<PageNode*> > invert_index_map;

  // read net file
  string ver_title;
  int num_ver;
  ifstream in_net_stream(IN_NET_FILE.c_str());
  if (!in_net_stream.is_open()) {
    cout << "Failed to open the net file" << endl;
    exit(1);
  }
  // read Vertices
  in_net_stream >> ver_title >> num_ver;
  if (ver_title != "*Vertices") {
    cout << "Wrong file format! No *Vertices" << endl;
    exit(1);
  }
  for (size_t i = 0; i < size_t(num_ver); i++) {
    int id;
    string name;
    in_net_stream >> id >> name;
    PageNode* tmp_node = new PageNode(id);
    Node_map[id] = tmp_node;
  }
  // read edges
  string edge_title;
  int num_edge;
  in_net_stream >> edge_title >> num_edge;
  if (edge_title != "*Arcs") {
    cout << "Wrong file format! No *Arcs" << endl;
    exit(1);
  }
  for (size_t i = 0; i < size_t(num_edge); i++) {
    int src, dest;
    in_net_stream >> src >> dest;
	  if (src == dest) {
		  continue;
	  }
    PageNode* src_ptr = Node_map[src];
    PageNode* dest_ptr = Node_map[dest];
    dest_ptr->setSrc(src_ptr);
    src_ptr->setDest(dest_ptr);
  }
  in_net_stream.close();
  cout << "Node_map.size() : " << Node_map.size() << endl;

  // read inverted index file
  ifstream in_index_stream(IN_INDEX_FILE.c_str());
  if (!in_index_stream.is_open()) {
    cout << "Failed to open the index file" << endl;
    exit(1);
  }
  string name;
  int id;
  while(in_index_stream >> name >> id) {
    PageNode* tmp_node = Node_map[id];
    invert_index_map[name].insert(tmp_node);
  }
  in_index_stream.close();
  cout << "invert_index_map.size() : " << invert_index_map.size() << endl;

  // construct seed set
  set<PageNode*> seed_set;
  for (auto str : queries) {
    auto it_begin = invert_index_map[str].begin();
    auto it_end = invert_index_map[str].end();
    seed_set.insert(it_begin, it_end);
    cout << str << ", set size:" << invert_index_map[str].size() << endl;
    cout << "seed_set size: " << seed_set.size() << endl;
    // cout << "[";
    // for (auto ptr : seed_set) {
    //   cout << ptr->dump_id() << " ";
    // } cout << "]" << endl;
  }
  // construct base set
  for (auto it = seed_set.begin(); it != seed_set.end(); it++) {
    PageNode* tmp_node = *it;
  }







  return 0;
}
