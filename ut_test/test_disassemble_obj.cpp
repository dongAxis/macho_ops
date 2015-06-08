//
//  test_disassemble_obj.h
//  disassemble_engine
//
//  Created by Axis on 6/8/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef __disassemble_engine__test_disassemble_obj__
#define __disassemble_engine__test_disassemble_obj__

#include <gtest/gtest.h>
#include <mach-o/loader.h>

#include "disassemble_obj.h"

TEST(TestDisassembleObj, test_get_text_seg)
{
    com::rhinos::DisassembleObj *dis = com::rhinos::DisassembleObj::get_instace();

    dis->set_file_path("/Users/Axis/Desktop/asm/cpuid");
    dis->analysis_macho();

    mach_vm_address_t *addr = dis->get_text_seg();
    struct segment_command_64 *seg = (struct segment_command_64*)addr;

    ASSERT_STREQ(SEG_TEXT, seg->segname);
}

#endif /* defined(__disassemble_engine__test_disassemble_obj__) */
