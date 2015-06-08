//
//  common_struct.h
//  Service
//
//  Created by Axis on 6/4/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef Service_common_struct_h
#define Service_common_struct_h

#include "rhinos_errorcode.h"

struct RequestHead
{
    int cmd;
};

struct ResponseHead
{
    int cmd;
    RHINOS_ERROR_CODE return_code;
};

#endif
