//
//  PageNode.cpp
//  PageRankProj
//
//  Created by Dapeng Hong on 11/20/15.
//  Copyright © 2015 Hongdp. All rights reserved.
//

#include "PageNode.h"

#include <vector>
#include <cmath>

using namespace std;

double PageNode::d;
int PageNode::N;
vector<const PageNode*> PageNode::nodesWithNoOut;

void PageNode::addOutLink(){
	numOutLinks++;
}

void PageNode::calculateNextPR(){
	nextPR = (1 - d)/N;
	for (const PageNode* nodePtr : contributors) {
		nextPR += d*nodePtr->getContribution();
	}
	for (const PageNode* nodePtr : nodesWithNoOut) {
		if (nodePtr != this) {
			nextPR += d*nodePtr->getContribution();
		}
	}
}

double PageNode::getCurrentPR() const {
	return currentPR;
}

void PageNode::updatePR(){
	currentPR = nextPR;
	nextPR = 0;
}

bool PageNode::updatePR(double converge){
	bool returnVal = false;
	if (abs(currentPR - nextPR)/currentPR <= converge ) {
		returnVal = true;
	}
	currentPR = nextPR;
	nextPR = 0;
	return returnVal;
}

double PageNode::getContribution() const{
	return currentPR/numOutLinks;
}

void PageNode::setGlobalArgs(double d_, int N_){
	d = d_;
	N = N_;
}

void PageNode::addContributor(const PageNode* contributor_ptr){
	contributors.push_back(contributor_ptr);
}

bool PageNode::hasNoOutGoing(){
	return !numOutLinks;
}

void PageNode::setNumOutLink(int numOutLinks_){
	numOutLinks = numOutLinks_;
}

void PageNode::addNodeToNoOut(const PageNode* node_ptr){
	nodesWithNoOut.push_back(node_ptr);
}
