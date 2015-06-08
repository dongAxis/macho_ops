//
//  service.h
//  Service
//
//  Created by Axis on 6/4/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef Service_service_h
#define Service_service_h

#include "queue.h"

//typedef std::queue<int> RequestQ_t;
typedef com::rhinos::Queue<int, com::rhinos::Mutex> RequestQ_t;

#endif
