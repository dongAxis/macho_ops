//
//  DisassembleObj.cpp
//  disassemble_engine
//
//  Created by Axis on 6/6/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/ioccom.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "disassemble_obj.h"
#include "macho_ops_64.h"
#include "udis86.h"

com::rhinos::DisassembleObj* com::rhinos::DisassembleObj::disassemble_obj=NULL;
com::rhinos::Mutex com::rhinos::DisassembleObj::instance_lock;

com::rhinos::DisassembleObj* com::rhinos::DisassembleObj::get_instace()
{
    LockGuard<com::rhinos::Mutex> guard(com::rhinos::DisassembleObj::instance_lock);

    if(com::rhinos::DisassembleObj::disassemble_obj==NULL)
    {
        com::rhinos::DisassembleObj::disassemble_obj =
                new com::rhinos::DisassembleObj();
    }
    return com::rhinos::DisassembleObj::disassemble_obj;
}

void com::rhinos::DisassembleObj::set_file_path(std::string path)
{
    LockGuard<com::rhinos::Mutex> guard(this->lock);
    this->file_path = path;
    this->valid=true;
}

bool com::rhinos::DisassembleObj::file_existed()
{
    //LockGuard<com::rhinos::Mutex> guard(this->lock);
    if(!this->valid)
        return false;

    if(::access(this->file_path.c_str(), F_OK)!=0)
    {
        printf("file %s dose not existed", this->file_path.c_str());
        return false;
    }
    return true;
}

void* com::rhinos::DisassembleObj::get_header()
{
    LockGuard<com::rhinos::Mutex> guard(this->lock);

    //header will release when the object mach_ops release
    return mach_ops->get_macho_header();
}

mach_vm_address_t* com::rhinos::DisassembleObj::get_text_seg()
{
    LockGuard<com::rhinos::Mutex> guard(this->lock);
    return this->mach_ops->get_text_seg();
}

bool com::rhinos::DisassembleObj::init_macho_file(IN mach_vm_address_t* addr)
{
    //LockGuard<com::rhinos::Mutex> guard(this->lock);
    if(addr==0)
    {
        return NULL;
    }

    finalize_disassemble_obj(); //release the mmeory resource

    bool is_64 = com::rhinos::MachoOpsInterface::is_64bit(addr);
    if(is_64)
    {
        mach_ops = new Macho_ops_64(addr);
    }
    else
    {
        //for 32 bit
    }
    this->is_64 = is_64;

    return true;
}

int input_hook_callback(ud_t* u)
{
    unsigned int c, i;

    //i = fscanf(fptr, "%x", &c);

    if (i == EOF)
        return UD_EOI;
    if (i == 0) {
        fprintf(stderr, "Error: Invalid input, should be in hexadecimal form (8-bit).\n");
        return UD_EOI;
    }
    if (c > 0xFF)
        fprintf(stderr, "Warning: Casting non-8-bit input (%x), to %x.\n", c, c & 0xFF);
    return (int) (c & 0xFF);
}

int com::rhinos::DisassembleObj::start_disassemble()
{
    ud_t ud_obj;
    ud_init(&ud_obj);
    //ud_set_input_hook(&ud_obj, input_hook_callback);

    return 0;
}

void com::rhinos::DisassembleObj::analysis_macho()
{
    LockGuard<com::rhinos::Mutex> guard(this->lock);

    if(!this->file_existed())
    {
        return;
    }

    int fd;
    struct stat file_property;
    uint64_t file_length;

    fd = open(this->file_path.c_str(), O_RDWR,777);
    if(fd<0) return;

    fstat(fd, &file_property);
    file_length = file_property.st_size;

    mach_vm_address_t *addr;

    addr = (mach_vm_address_t*)mmap(NULL, file_length, PROT_READ, MAP_SHARED, fd, 0);
    if(addr<0)
    {
        printf("mmap failed");
        return ;
    }

    this->init_macho_file(addr);    //begin to analysis this mach-o file
}