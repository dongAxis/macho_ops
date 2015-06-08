//
//  main.cpp
//  disassemble_engine
//
//  Created by Axis on 6/6/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

//
//  main.cpp
//  namingservice
//
//  Created by Axis on 6/4/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "command_map.h"
#include "plugin_interface.h"
#include "const_variable.h"
#include "cmd_interface.h"
#include "macho_ops_interface.h"
#include "disassemble_obj.h"

com::rhinos::DisassembleObj *disassemble_obj=NULL;

int PluginGetId()
{
    return RHINOS_DISASSEMBLE_ENGINE;
}

int PluginInitialize()
{

    return 0;
}

int PluginFinalize()
{
    return 0;
}

void PluginFreeMem(void* ptr)
{
    if(ptr)
    {
        free(ptr);
        ptr=NULL;
    }
}

PluginHandler_t handlers[] =
{
    {RHINOS_DISASSEMBLE_SET_FILE_PATH, "set disassemble path", set_file_path},
    {RHINOS_DISASSEMBLE_START_DISASSEMBLE, "begin to disassemble", start_disassemble}
};

int PluginGetHandlers(PluginHandler_t **handler, int *arrLen)
{
    *handler=handlers;
    *arrLen=DIM(handlers);

    return 0;
}

int PluginSetNotificationCallback(PluginNotificationFun_t cb)
{
    return 0;
}

int PluginSetDebugLevel(int level)
{
    return 0;
}



