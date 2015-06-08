//
//  macho_ops.h
//  disassemble_engine
//
//  Created by Axis on 6/6/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef disassemble_engine_macho_ops_h
#define disassemble_engine_macho_ops_h

#include <mach-o/loader.h>

#include "mach_header_analysis.h"

namespace com
{
    namespace rhinos
    {
        class MachoOpsInterface
        {
        public:
            inline MachoOpsInterface(mach_vm_address_t *addr)
            {
                this->start_addr=addr;
                this->valid=true;
            }
            virtual inline ~MachoOpsInterface()
            {

            }
            static bool is_64bit(mach_vm_address_t* addr)
            {
                //if(addr) return FALSE;

//                uint32_t tmp = *((uint32_t*)addr);
//                addr+=sizeof(uint32_t);
//                tmp = *((uint32_t*)addr);
                return (*(uint32_t*)addr)==MH_MAGIC_64?TRUE:FALSE;
            }
            virtual void* get_macho_header()=0;
            virtual mach_vm_address_t* get_text_seg()=0;
        protected:
            mach_vm_address_t *start_addr;
            bool valid;
        };
    }
}

#endif
