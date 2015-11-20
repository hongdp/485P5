//
//  PageNode.cpp
//  PageRankProj
//
//  Created by Dapeng Hong on 11/20/15.
//  Copyright © 2015 Hongdp. All rights reserved.
//

#include "PageNode.h"

#include <vector>

using namespace std;

void PageNode::addOutLink(){
	numOutLinks++;
}

void PageNode::calculateNextPR(){
	nextPR = 0;
	for (<#initialization#>; <#condition#>; <#increment#>) {
		<#statements#>
	}
}

int PageNode::getCurrentPR(){
	
}

void PageNode::updatePR(){
	
}

bool PageNode::updatePR(int converge){
	
}