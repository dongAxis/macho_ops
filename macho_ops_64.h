//
//  macho_ops_64.h
//  disassemble_engine
//
//  Created by Axis on 6/8/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef __disassemble_engine__macho_ops_64__
#define __disassemble_engine__macho_ops_64__

#include <mach-o/loader.h>

#include "macho_ops_interface.h"
#include "macho_mappping.h"

namespace com
{
    namespace rhinos
    {
        class Macho_ops_64 : public MachoOpsInterface
        {
        public:
            Macho_ops_64(mach_vm_address_t* addr);
            virtual ~Macho_ops_64();
            mach_vm_address_t* get_text_seg();
            mach_vm_address_t* get_data_seg();
            void* get_macho_header();
        private:
            mach_vm_address_t* get_seg_address(char *segname);
        private:
//            mach_header_64 *header;
            MachHeaderAnalysis<struct mach_header_64> *header;
        };
    }
}

#endif /* defined(__disassemble_engine__macho_ops_64__) */
