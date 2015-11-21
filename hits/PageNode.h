//
//  PageNode.h
//  HITSProj
//
//  Created by Dapeng Hong on 11/20/15.
//  Copyright © 2015 Hongdp. All rights reserved.
//

#ifndef PageNode_H
#define PageNode_H

#include <set>

#include "Utility.h"

class PageNode {
public:
	PageNode(int pageId_): pageId(pageId_), currentHub(1.0),  nextHub(1.0), currentAuth(1.0), nextAuth(1.0){};
	bool operator<(const PageNode& rhs);
	double calculateNextHub();
	double calculateNextAuth();
	void normalizeNextHub(double normalizer);
	void normalizeNextAuth(double normalizer);
	void update();
	bool update(double converge);
	double getCurrentHub();
	double getCurrentAuth();
	void intersectWithBase(const std::set<PageNode*, Less_than_ptr<PageNode*> >& BaseSet);
	void setDest(PageNode* dest_ptr);
	void setSrc(PageNode* src_ptr);
private:
	int pageId;
	double currentHub;
	double nextHub;
	double currentAuth;
	double nextAuth;

	std::set<PageNode*, Less_than_ptr<PageNode*> > outPointers;
	std::set<PageNode*, Less_than_ptr<PageNode*> > inPointers;
	std::set<PageNode*, Less_than_ptr<PageNode*> > connectedPointers;
};

#endif /* PageNode_H */
