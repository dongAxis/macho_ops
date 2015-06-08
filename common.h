//
//  common.h
//  tools
//
//  Created by Axis on 6/1/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef tools_common_h
#define tools_common_h

#ifndef SAFE_RELEASE        
#define SAFE_RELEASE(ptr)   \
    do {                    \
        CFRelease(ptr);     \
        ptr=NULL;           \
    }while(0);
#endif

#endif
