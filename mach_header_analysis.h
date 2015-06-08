//
//  mach_header_analysis.h
//  disassemble_engine
//
//  Created by Axis on 6/8/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef disassemble_engine_mach_header_analysis_h
#define disassemble_engine_mach_header_analysis_h

#include <mach-o/loader.h>
#include <vector>

namespace com
{
    namespace rhinos
    {
        template<typename T>
        class MachHeaderAnalysis
        {
        public:
            MachHeaderAnalysis(mach_vm_address_t* start_address);
            virtual ~MachHeaderAnalysis(){this->valid=false;}
            uint32_t getArchitecture();
            cpu_type_t getCpuType();
            cpu_subtype_t getCpuSubType();
            uint32_t getFileType();
            uint32_t getNcmds();
            uint32_t getSizeOfCmds();
            void getflags(std::vector<int> flags_array);
        private:
            void setMachoHeader();
            inline T* getMachoHeader() {return this->header;}
        private:
            T header;
            bool valid;
            mach_vm_address_t* start_address;
        };

        template<typename T>
        MachHeaderAnalysis<T>::MachHeaderAnalysis(mach_vm_address_t* start_address)
        {
            this->start_address=start_address;
            this->valid = true;

            this->setMachoHeader(); //get header
        }

        template<typename T>
        void MachHeaderAnalysis<T>::setMachoHeader()
        {
            this->header = *(T*)(this->start_address);
        }

        template<typename T>
        uint32_t MachHeaderAnalysis<T>::getArchitecture()
        {
            return this->header.magic;
        }

        template<typename T>
        cpu_type_t MachHeaderAnalysis<T>::getCpuType()
        {
            return this->header.cputype;
        }

        template<typename T>
        cpu_subtype_t MachHeaderAnalysis<T>::getCpuSubType()
        {
            return this->header.cpusubtype;
        }

        template<typename T>
        uint32_t MachHeaderAnalysis<T>::getFileType()
        {
            return this->header.filetype;
        }

        template<typename T>
        uint32_t MachHeaderAnalysis<T>::getNcmds()
        {
            return this->header.ncmds;
        }

        template<typename T>
        uint32_t MachHeaderAnalysis<T>::getSizeOfCmds()
        {
            return this->header.sizeofcmds;
        }

        template<typename T>
        void MachHeaderAnalysis<T>::getflags(std::vector<int> flags_array)
        {
            //0x02000000
            uint32_t flags = this->header.flags;
            int cur = 1;

            while (cur<flags && cur < 0x02000000)
            {
                if(cur & flags)
                {
                    flags_array.push_back(cur);
                }
                cur <<= 1;
            }
            return ;
        }
    }
}

#endif
