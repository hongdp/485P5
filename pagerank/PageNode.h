//
//  PageNode.hpp
//  PageRankProj
//
//  Created by Dapeng Hong on 11/20/15.
//  Copyright © 2015 Hongdp. All rights reserved.
//

#ifndef PageNode_H
#define PageNode_H

#include <vector>

class PageNode {
public:
	PageNode(double initPR):currentPR(initPR), nextPR(0), numOutLinks(0){};
	void addOutLink();
	void calculateNextPR();
	int getCurrentPR() const;
	void updatePR();
	bool updatePR(int converge);
	static void setGlobalArgs(double d, int N);
private:
	double currentPR;
	double nextPR;
	std::vector<PageNode*> contributors;
	int numOutLinks;
	static double d;
	static int N;
};

#endif /* PageNode_H */
