//
//  rhinos_errorcode.h
//  Service
//
//  Created by Axis on 6/2/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//
#include <stdlib.h>

#ifndef Service_rhinos_errorcode_h
#define Service_rhinos_errorcode_h

#ifndef RHINOS_ERROR_CODE
#define RHINOS_ERROR_CODE int
#endif

#define RHINOS_IS_ERROR(error_code) ((error_code)<0)?true:false

#define RHINOS_GET_ERROR_DESCRIPTOR(error_code)                     \
        do{                                                         \
            error_descriptor_table[abs((error_code))].descriptor    \
        }while(0);

#define RHINOS_SUCCESS 0
#define RHINOS_FAILURE_BASE                         RHINOS_SUCCESS-1
#define RHINOS_PLUGIN_NOT_EXISTED                   RHINOS_SUCCESS-2
#define RHINOS_CMD_NOT_EXISTED                      RHINOS_SUCCESS-3
#define RHINOS_CMD_ALREADY_EXISTED                  RHINOS_SUCCESS-4
#define RHINOS_IPC_ERROR_INVALID_SOCKET_ADDRESS     RHINOS_SUCCESS-5
#define RHINOS_LOG_ERROR_WRONG_LEVEL                RHINOS_SUCCESS-6
#define RHINOS_CMD_INVALID_COMMAND                  RHINOS_SUCCESS-7
#define RHINOS_INVALID_THREAD_PARAM                 RHINOS_SUCCESS-8
#define RHINOS_GET_THREAD_PRIORITY_FAILED           RHINOS_SUCCESS-9
#define RHINOS_SET_THREAD_PRIORITY_FAILED           RHINOS_SUCCESS-10
#define RHINOS_PLUGIN_HAS_EXISTED                   RHINOS_SUCCESS-11
#define RHINOS_PLUGIN_NOT_EXISTED                   RHINOS_SUCCESS-12

/*struct error_descriptor
{
    int index;
    char descriptor[100];
}   error_descriptor_table[]=
    {
        {abs(RHINOS_PLUGIN_NOT_EXISTED), "plugin in dose not existed!"},
        {abs(RHINOS_CMD_NOT_EXISTED), "command dose not existed"},
    };*/

#endif
