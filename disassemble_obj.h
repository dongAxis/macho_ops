//
//  DisassembleObj.h
//  disassemble_engine
//
//  Created by Axis on 6/6/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef __disassemble_engine__DisassembleObj__
#define __disassemble_engine__DisassembleObj__

#include <stdlib.h>
#include <string>
#include <mach-o/loader.h>

#include "udis86.h"
#include "lock.h"
#include "macho_ops_interface.h"
#include "mach_header_analysis.h"
#include "const_variable.h"
#include "rhinos_disassemble_engine_msg.pb.h"

namespace com
{
    namespace rhinos
    {
        class DisassembleObj
        {
        public:
            static DisassembleObj* get_instace();
            virtual ~DisassembleObj()
            {
                this->finalize_disassemble_obj();
            }

            void set_file_path(std::string path);
            std::string get_file_path() {return this->file_path;}
            inline bool is_valid() {return this->valid;}

            void analysis_macho();
            void* get_header();
            bool file_existed();
            mach_vm_address_t* get_text_seg();
            //mach_vm_address_t* get_data_seg();

            int start_disassemble();
        private:
            inline DisassembleObj():disassemble_array(NULL)
            {
                this->valid=false;
                this->mach_ops=NULL;
            }

            inline void finalize_disassemble_obj()
            {
                if(this->mach_ops)
                {
                    free(this->mach_ops);
                    this->mach_ops=NULL;
                }

                if(this->disassemble_array)
                {
                    free(this->disassemble_array);
                    this->disassemble_array=NULL;
                }
            }
            bool init_macho_file(IN mach_vm_address_t* addr);
        private:
            std::string file_path;
            bool is_64;
            Mutex lock;
            bool valid;
            com::rhinos::MachoOpsInterface *mach_ops;
            com::rhinos::disassenble_data_array *disassemble_array;

        private:
            static DisassembleObj *disassemble_obj;
            static Mutex instance_lock;
            static uint8_t current_offset;
        };

    }
}

#endif /* defined(__disassemble_engine__DisassembleObj__) */
