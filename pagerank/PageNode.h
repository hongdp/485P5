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
	void addContributor(const PageNode* contributor_ptr);
	void calculateNextPR();
	double getCurrentPR() const;
	double getContribution() const;
	void updatePR();
	bool updatePR(double converge);
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
