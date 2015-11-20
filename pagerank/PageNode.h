//
//  PageNode.hpp
//  PageRankProj
//
//  Created by Dapeng Hong on 11/20/15.
//  Copyright © 2015 Hongdp. All rights reserved.
//

#ifndef PageNode_H
#define PageNode_H

class PageNode {
public:
	PageNode(double initPR):currentPR(initPR), nextPR(0), numOutLinks(0);
	void addOutLink();
	void calculateNextPR();
	int getCurrentPR();
	void updatePR();
	bool updatePR(int converge);
private:
	double currentPR;
	double nextPR;
	vector<PageNode*> contributors;
	int numOutLinks;
};

#endif /* PageNode_H */
