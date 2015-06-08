//
//  Plugin.h
//  Service
//
//  Created by Axis on 6/2/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef Service_Plugin_h
#define Service_Plugin_h

#include "const_variable.h"

#ifdef __cplusplus
extern "C"{
#endif

    typedef int (*PluginProcessFun_t)(int cmd, void *in, int inLen, void **out, int *outLen);
    typedef void (*PluginNotificationFun_t)(int cmd, const void* in, int inLen);
    typedef struct
    {
        int cmd;
        char name[64];
        PluginProcessFun_t handler;
    }PluginHandler_t;

    typedef int (*PluginGetId_t)();
    typedef int (*PluginInitlize_t)();
    typedef int (*PluginFinalize_t)();
    typedef int (*PluginGetHandlers_t)(PluginHandler_t **arr, int *arrLen);
    typedef void (*PluginSetNotificationCallback_t)(PluginNotificationFun_t cb);
    typedef void (*PluginFreeMem_t)(void* ptr);


    EXPORT_FUNCTION int PluginGetId();
    EXPORT_FUNCTION int PluginInitialize();
    EXPORT_FUNCTION int PluginFinalize();
    EXPORT_FUNCTION int PluginGetHandlers(PluginHandler_t **handler, int *arrLen);
    EXPORT_FUNCTION int PluginSetNotificationCallback(PluginNotificationFun_t cb);
    EXPORT_FUNCTION int PluginSetDebugLevel(int level);
    EXPORT_FUNCTION void PluginFreeMem(void* ptr);

#ifdef __cplusplus
}
#endif

#endif
