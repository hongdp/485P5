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

void PageNode::addOutLink(){
	numOutLinks++;
}

void PageNode::calculateNextPR(){
	nextPR = (1 - d)/N;
	for (PageNode* nodePtr : contributors) {
		nextPR += nodePtr->getContribution();
	}
}

int PageNode::getCurrentPR(){
	return currentPR;
}

void PageNode::updatePR(){
	currentPR = nextPR;
	nextPR = 0;
}

bool PageNode::updatePR(double converge){
	bool returnVal;
	if (abs(currentPR - nextPR)/currentPR <= converge ) {
		<#statements#>
	}
}