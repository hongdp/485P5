//
//  Utility.h
//  HITSProj
//
//  Created by Dapeng Hong on 11/20/15.
//  Copyright © 2015 Hongdp. All rights reserved.
//

#ifndef Utility_H
#define Utility_H

template<typename T>
struct Less_than_ptr {
	bool operator()(const T p1, const T p2) const {return *p1 < *p2;}
};

#endif /* Utility_H */
