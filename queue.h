//
//  Queue.h
//  Service
//
//  Created by Axis on 6/3/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef Service_Queue_h
#define Service_Queue_h

#include <queue>
#include "Lock.h"

namespace com
{
    namespace rhinos
    {
        /*
         * for: this is the thread-safe queue.
         */
        template<typename T, typename L>
        class Queue
        {
        public:
            Queue():m_cond(m_lock){};
            T pop();
            void push(T& data);
            T peek();
            bool empty();
        private:
            std::queue<T> m_queue;
            Condition<L> m_cond;
            L m_lock;
        };

        template<typename T, typename L>
        T Queue<T, L>::pop()
        {
            LockGuard<L> guard(m_lock);
            if(this->m_queue.empty())
            {
                m_cond.wait();
            }

            if(this->m_queue.empty())
            {
                return NULL;
            }

            T data = this->m_queue.front();
            this->m_queue.pop();
            return data;
        }

        template<typename T, typename L>
        void Queue<T, L>::push(T& data)
        {
            {
                LockGuard<L> guard(m_lock);
                this->m_queue.push(data);
            }
            this->m_cond.signal();
        }

        template<typename T, typename L>
        T Queue<T, L>::peek()
        {
            LockGuard<L> guard(this->m_lock);
            if(this->m_queue.empty())
            {
                return NULL;
            }
            return this->m_queue.front();
        }

        template<typename T, typename L>
        bool Queue<T, L>::empty()
        {
            return this->m_queue.empty();
        }
    }
}

#endif
