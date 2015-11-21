//
//  PageNode.cpp
//  HITSProj
//
//  Created by Dapeng Hong on 11/20/15.
//  Copyright © 2015 Hongdp. All rights reserved.
//

#include "PageNode.h"

#include <set>
#include <cmath>

using namespace std;

bool PageNode::operator<(const PageNode& rhs){
	return pageId < rhs.pageId;
}

double PageNode::calculateNextHub(){
	nextHub = 0;
	for (auto it = outPointers.begin(); it != outPointers.end(); it++) {
		nextHub += (*it)->getCurrentAuth();
	}
	return nextHub;
}

double PageNode::calculateNextAuth(){
	nextAuth = 0;
	for (auto it = inPointers.begin(); it != inPointers.end(); it++) {
		nextAuth += (*it)->getCurrentHub();
	}
	return nextAuth;
}

void PageNode::normalizeNextHub(double normalizer){
	nextHub /= normalizer;
}

void PageNode::normalizeNextAuth(double normalizer){
	nextAuth /= normalizer;
}

void PageNode::update(){
	currentAuth = nextAuth;
	currentHub = nextHub;
}

bool PageNode::update(double converge){
	bool returnVal = false;
	if (abs(nextHub - currentHub)/currentHub <= converge && abs(nextAuth - currentAuth)/currentAuth <= converge) {
		returnVal = true;
	}
	currentAuth = nextAuth;
	currentHub = nextHub;
	return returnVal
}

double PageNode::getCurrentHub(){
	return currentHub;
}

double PageNode::getCurrentAuth(){
	return currentAuth;
}

void PageNode::intersectWithBase(const set<PageNode*, Less_than_ptr<PageNode*> >& BaseSet){
	set<PageNode*, Less_than_ptr<PageNode*> > newInSet;
	set<PageNode*, Less_than_ptr<PageNode*> > newOutSet;
	set_intersection(BaseSet.begin(), BaseSet.end(), inPointers.begin(), inPointers.end(), inserter(newInSet, newInSet.begin()));
	set_intersection(BaseSet.begin(), BaseSet.end(), outPointers.begin(), outPointers.end(), inserter(newOutSet, newOutSet.begin()));
	inPointers = move(newInSet);
	outPointers = move(newOutSet);
}

void PageNode::setDest(PageNode* dest_ptr){
	outPointers.insert(dest_ptr);
}

void PageNode::setSrc(PageNode* src_ptr){
	inPointers.insert(src_ptr);
}

std::set<PageNode*, Less_than_ptr<PageNode*> >::iterator PageNode::getConnectedBegin(){
	return connectedPointers.begin();
}

std::set<PageNode*, Less_than_ptr<PageNode*> >::iterator PageNode::getConnectedEnd(){
	return connectedPointers.end();
}



