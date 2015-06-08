//
//  command_map.h
//  Service
//
//  Created by Axis on 6/4/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef Service_command_map_h
#define Service_command_map_h

enum PluginType
{
    RHINOS_ALL_PLUGIN           =1,
    RHINOS_NAMINGSERVICE        =RHINOS_ALL_PLUGIN<<1,
    RHINOS_NOTIFICATION         =RHINOS_ALL_PLUGIN<<2,
    RHINOS_DISASSEMBLE_ENGINE   =RHINOS_ALL_PLUGIN<<3,
};

//every command will have 2^8 commands at most
enum CommandMap
{
    //below is the command that need all plugin response
    RHINOS_ALL_START                            =RHINOS_ALL_PLUGIN<<8,
    RHINOS_ALL_STOP,
    RHINOS_ALL_SET_DEBUG_LEVEL,

    RHINOS_NAMINGSERIVCE_REGISTER               =RHINOS_NAMINGSERVICE<<8,
    RHINOS_NAMINGSERIVCE_UNREGISTER,
    RHINOS_NAMINGSERVICE_GETSERVICES,

    RHINOS_ADD_NOTIFICATION                    =RHINOS_NOTIFICATION<<8,
    RHINOS_REMOVE_NOTIFICATION,
    RHINOS_GET_ALL_NOTIFICATION_HANDLE,

    RHINOS_DISASSEMBLE_SET_FILE_PATH           =RHINOS_DISASSEMBLE_ENGINE<<8,
    RHINOS_DISASSEMBLE_START_DISASSEMBLE,
};

#endif
