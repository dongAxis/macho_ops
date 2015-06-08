//
//  macho_ops_64.cpp
//  disassemble_engine
//
//  Created by Axis on 6/8/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//
#include <stdlib.h>

#include "macho_ops_64.h"

using namespace com::rhinos;

Macho_ops_64::Macho_ops_64(mach_vm_address_t *addr):MachoOpsInterface(addr)//, header(NULL)
{
    this->header = new MachHeaderAnalysis<struct mach_header_64>(addr);
}

Macho_ops_64::~Macho_ops_64()
{
    free(this->header);
    this->header=NULL;
}

void* Macho_ops_64::get_macho_header()
{
    return (void*)(this->header);
}

mach_vm_address_t* Macho_ops_64::get_seg_address(char segname[])
{
    if(!this->valid) return NULL;

    int ncmds = this->header->getNcmds();
    mach_vm_address_t *addr =
    (mach_vm_address_t*)((uint8_t*)this->start_addr + sizeof(struct mach_header_64));

    for(int i=0; i<ncmds; i++)
    {
        struct segment_command_64 *seg = (struct segment_command_64*)addr;
        if(strcmp(seg->segname, segname)==0)
        {
            return addr;
        }
        addr = (mach_vm_address_t*)((uint8_t*)addr + seg->cmdsize);
    }
    return NULL;

}

mach_vm_address_t* Macho_ops_64::get_data_seg()
{
    char seg_name[] = SEG_DATA;
    return this->get_seg_address(seg_name);
}

mach_vm_address_t* Macho_ops_64::get_text_seg()
{
    return this->get_seg_address(SEG_TEXT);
}