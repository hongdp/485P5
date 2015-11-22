#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <map>
#include <set>
#include <vector>
#include <sstream>
#include <algorithm>
#include "PageNode.h"

using namespace std;

void ProcessString(string &str) {
  auto c = str.begin();
  while ( c != str.end()) {
    *c = tolower(*c);
    if (isalnum(*c))
      c++;
    else
      str.erase(c);
  }
}

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
    ProcessString(tmp_query);
		queries.push_back(tmp_query);
	}
	// for (auto str : queries) {
	//   cout << str << " ";
	// } cout << endl;

	map<int, PageNode*> Node_map;
	map<string, set<PageNode*, Less_than_ptr<PageNode*> > > invert_index_map;

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
    ProcessString(name);
		invert_index_map[name].insert(tmp_node);
	}
	in_index_stream.close();
	cout << "invert_index_map.size() : " << invert_index_map.size() << endl;

	// construct seed set
	set<PageNode*, Less_than_ptr<PageNode*> > temp_seed_set;
	set<PageNode*, Less_than_ptr<PageNode*> > seed_set;
	for (auto str : queries) {
		auto it_begin = invert_index_map[str].begin();
		auto it_end = invert_index_map[str].end();
		temp_seed_set.insert(it_begin, it_end);
		cout << str << ", set size:" << invert_index_map[str].size() << endl;
		cout << "seed_set size: " << temp_seed_set.size() << endl;
		// cout << "[";
		// for (auto ptr : seed_set) {
		//   cout << ptr->dump_id() << " ";
		// } cout << "]" << endl;
	}
	int counter = 0;
	for (auto it = temp_seed_set.begin(); counter < h && it != temp_seed_set.end(); it++) {
		seed_set.insert(*it);
		counter++;
	}
  cout << "final seed_set size: " << seed_set.size() << endl;

	// construct base set
	set<PageNode*, Less_than_ptr<PageNode*> > base_set(seed_set);
	for (auto it = seed_set.begin(); it != seed_set.end(); it++) {
		auto it_inc = (*it)->getConnectedBegin();
		auto it_end = (*it)->getConnectedEnd();
		int counter = 0;
		while(counter < 50 && it_inc != it_end) {
			PageNode* tmp_node = *it_inc;
			it_inc++;
			if (seed_set.find(tmp_node) != seed_set.end())
				continue;
			else
				base_set.insert(tmp_node);
			counter++;
		}
		// cout << "counter for id " << (*it)->dump_id() << " is: " << counter << endl;
	}
	cout << "base_set size: " << base_set.size() << endl;

	// pre-process PageNode
	for(auto it = base_set.begin(); it != base_set.end(); it++) {
		PageNode* tmp_node = (*it);
		tmp_node->intersectWithBase(base_set);
	}

	// Iterations
	bool use_iter = (converge_type == "-k");
	if (use_iter) {
		for (size_t i = size_t(converge_val); i > 0; i--) {
			// calcualte next auth and hub, accumalate
			double auth_normalizer = 0;
			double hub_normalizer = 0;
			for(auto it = base_set.begin(); it != base_set.end(); it++) {
				PageNode* tmp_node = (*it);
				auth_normalizer += pow(tmp_node->calculateNextAuth(), 2);
				hub_normalizer += pow(tmp_node->calculateNextHub(), 2);
			}
			// normalize auth and hub
			for(auto it = base_set.begin(); it != base_set.end(); it++) {
				PageNode* tmp_node = (*it);
				tmp_node->normalizeNextAuth(sqrt(auth_normalizer));
				tmp_node->normalizeNextHub(sqrt(hub_normalizer));
			}
			// update auth and hub
			for(auto it = base_set.begin(); it != base_set.end(); it++) {
				PageNode* tmp_node = (*it);
				tmp_node->update();
			}
		}
	} else {
		bool break_loop = false;
		while(true) {
			// calcualte next auth and hub, accumalate
			double auth_normalizer = 0;
			double hub_normalizer = 0;
			for(auto it = base_set.begin(); it != base_set.end(); it++) {
				PageNode* tmp_node = (*it);
				auth_normalizer += pow(tmp_node->calculateNextAuth(), 2);
				hub_normalizer += pow(tmp_node->calculateNextHub(), 2);
			}
			// normalize auth and hub
			for(auto it = base_set.begin(); it != base_set.end(); it++) {
				PageNode* tmp_node = (*it);
				tmp_node->normalizeNextAuth(sqrt(auth_normalizer));
				tmp_node->normalizeNextHub(sqrt(hub_normalizer));
			}
			// update auth and hub
			for(auto it = base_set.begin(); it != base_set.end(); it++) {
				PageNode* tmp_node = (*it);
				break_loop &= tmp_node->update(converge_val);
			}
			if (break_loop)
				break;
		}
	}

	// output file
	ofstream outfile_stream(OUT_FILE.c_str());
  double accumalate_hub = 0;
  double accumalate_auth = 0;
	for(auto it = base_set.begin(); it != base_set.end(); it++) {
		PageNode* tmp_node = (*it);
		outfile_stream << tmp_node->dump_id() << "," << tmp_node->getCurrentHub();
    outfile_stream << "," << tmp_node->getCurrentAuth() << endl;
    accumalate_hub += pow(tmp_node->getCurrentHub(), 2);
    accumalate_auth += pow(tmp_node->getCurrentAuth(), 2);
	}
  cout << "accumalate_hub (should be 1) : " << accumalate_hub << endl;
  cout << "accumalate_auth (should be 1) : " << accumalate_auth << endl;
	outfile_stream.close();

	for (auto it = Node_map.begin(); it != Node_map.end(); it++) {
		delete it->second;
	}

	return 0;
}
