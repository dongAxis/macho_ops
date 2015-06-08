//
//  Lock.h
//  tools
//
//  Created by Axis on 6/1/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef tools_Lock_h
#define tools_Lock_h

#include <sys/errno.h>
#include <pthread.h>
#include <unistd.h>
#include <string>

namespace com {
    namespace rhinos
    {
        template<typename L>
        class LockGuard
        {
        public:
            inline LockGuard(L& lock):m_lock(lock)
            {
                if(!m_lock.lock())
                {
                    printf("faile to get lock");
                }
            }

            inline ~LockGuard()
            {
                m_lock.unlock();
            }
        private:
            LockGuard(LockGuard& lock);
            LockGuard& operator=(const LockGuard& rhs);
        private:
            L& m_lock;
        };

        //empty mutex
        class NullMutex
        {
        public:
            inline bool lock() { return true; }
            inline bool unlock() { return true; }
            inline void trylock() {}
        private:
            NullMutex(NullMutex& lock);
            NullMutex& operator=(const NullMutex& rhs);
        };

        class Mutex
        {
        public:
            Mutex();
            ~Mutex();
            bool lock();
            bool unlock();
            bool trylock();
            pthread_mutex_t get();
        private:
            pthread_mutex_t mutex;
        };

        template<typename T>
        class Condition
        {
        public:
            Condition(T &mutex){}
            ~Condition(){}
            int wait(){return 0;}
            int signal() {return 0;}
        private:
            Condition(Condition& rhs);
            Condition& operator=(const Condition& rhs);
        };

        template<>
        class Condition<Mutex>
        {
        public:
            Condition(Mutex &mutex):m_mutex(mutex)
            {
                pthread_cond_init(&this->m_cond, NULL);
            }

            virtual inline ~Condition()
            {
                pthread_cond_destroy(&this->m_cond);
            }

            virtual inline int wait()
            {
                pthread_mutex_t mutex=this->m_mutex.get();
                return pthread_cond_wait(&this->m_cond, &mutex);
            }

            virtual inline int signal()
            {
                return pthread_cond_signal(&this->m_cond);
            }

        private:
        private:
            pthread_cond_t m_cond;
            Mutex& m_mutex;
        };

        inline Mutex::Mutex()
        {
            int error=pthread_mutex_init(&this->mutex, NULL);
            for(;error==EAGAIN;error=pthread_mutex_init(&this->mutex, NULL))
            {
                usleep(200);
            }

            if(error<0)
            {
                throw std::string("error");
            }
        }

        inline Mutex::~Mutex()
        {
            pthread_mutex_destroy(&this->mutex);
        }

        inline bool Mutex::lock()
        {
            return pthread_mutex_lock(&this->mutex)==0;
        }

        inline bool Mutex::unlock()
        {
            return pthread_mutex_unlock(&this->mutex)==0;
        }

        inline bool Mutex::trylock()
        {
            return pthread_mutex_trylock(&this->mutex)==0;
        }

        inline pthread_mutex_t Mutex::get()
        {
            return this->mutex;
        }
    }
}

#endif
