//
//  ConfigureOps.h
//  tools
//
//  Created by Axis on 6/1/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef __tools__ConfigureOps__
#define __tools__ConfigureOps__

#include <fstream>
#include <CoreFoundation/CoreFoundation.h>

#include "Lock.h"
#include "common.h"

namespace com {
    namespace rhinos
    {
        template <typename L=NullMutex>
        class ConfigureOps
        {
        public:
            ConfigureOps(char *filename);
            ConfigureOps();
            int save_result();
            bool is_valid();
            bool set_value();
            const void* get_group_data(const char* key);
        private:
            L lock;         //lock
            bool m_valid;   //whether the file that we read is true
            CFDictionaryRef dict_ref;
            char *m_file_name;
            int m_fd;
        };

        template<typename L>
        inline ConfigureOps<L>::ConfigureOps(char *file_name)
                               :m_file_name(file_name), dict_ref(NULL), m_valid(false), m_fd(-1)
        {
            if(file_name==NULL) return ;

            std::fstream file_stream(this->m_file_name);

            //check the file length
            long long file_length = file_stream.seekg(0, std::ios::end).tellg();
            if(file_length<=0) return ;

            //read file
            std::string file_content(file_length, '\0');
            if(!file_stream.seekg(std::ios::beg).read(&file_content[0], file_length))
                return ;
            CFDataRef data = CFDataCreateWithBytesNoCopy(NULL, (const UInt8*)file_content.c_str(),
                                                         file_length, kCFAllocatorNull);
            if(data==NULL) return ;

            CFPropertyListFormat format=kCFPropertyListXMLFormat_v1_0;
            CFPropertyListRef plist_data = CFPropertyListCreateWithData(kCFAllocatorDefault, data,
                                                                        kCFPropertyListMutableContainers,
                                                                        &format, NULL);
            CFRelease(data);

            Boolean t = CFPropertyListIsValid(plist_data, kCFPropertyListXMLFormat_v1_0);
            printf("%d", t);

            if(plist_data==NULL ||
               CFGetTypeID(plist_data)!=CFDictionaryGetTypeID() ||
               !CFPropertyListIsValid(plist_data, kCFPropertyListXMLFormat_v1_0))
            {
                SAFE_RELEASE(plist_data);
                return ;
            }

            this->m_valid=true;
            this->dict_ref=(CFMutableDictionaryRef)plist_data;
            printf("%d", t);
        }

        template<typename L>
        inline ConfigureOps<L>::ConfigureOps()
        {
            if(m_fd!=-1)
            {
                close(m_fd);
            }
            if(this->dict_ref!=NULL)
                SAFE_RELEASE(this->dict_ref);
        }

        template<typename L>
        inline int ConfigureOps<L>::save_result()
        {
            if(!this->is_valid()) return false;

            LockGuard<L> guard(this->m_lock);   //add lock

            if((this->m_fd=open(this->m_file_name, O_WRONLY))<0) return false;

            CFPropertyListFormat format=kCFPropertyListXMLFormat_v1_0;
            CFDataRef data = CFPropertyListCreateData(kCFAllocatorDefault, this->dict_ref,
                                                      kCFPropertyListMutableContainers, &format, NULL);
            if(data==NULL) return false;

            CFIndex length = CFDataGetLength(data);
            if(lseek(this->m_fd, 0, SEEK_SET)==-1) return false;
            if(write(this->m_fd, CFDataGetBytePtr(data), length)==-1) return false;

            SAFE_RELEASE(data);
            ftruncate(this->m_fd, length);
            fsync(this->m_fd);
            return true;
        }

        template<typename L>
        inline bool ConfigureOps<L>::is_valid()
        {
            return this->m_valid;
        }

        template<typename L>
        inline const void* ConfigureOps<L>::get_group_data(const char* key)
        {
            LockGuard<L> guard(this->lock);

            CFDictionaryRef dict = CFDictionaryCreate(NULL, NULL, NULL, 0, &kCFTypeDictionaryKeyCallBacks, NULL);
            CFDictionaryContainsKey(dict, "");

            CFStringRef keyRef=CFStringCreateWithCString(NULL, key, kCFStringEncodingUTF8);
            if(keyRef==NULL)
                return NULL;
            if(CFDictionaryContainsKey(this->dict_ref, keyRef))
                return CFDictionaryGetValue(this->dict_ref, keyRef);
            else
                return NULL;
        }
        /*template<typename L>
        template<typename Pb>
        bool ConfigureOps<L>::set_value(const Pb& pb, )
        {

        }*/
    }
}


#endif /* defined(__tools__ConfigureOps__) */
