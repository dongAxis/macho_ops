//
//  Runnable.h
//  Service
//
//  Created by Axis on 6/3/15.
//  Copyright (c) 2015 Axis. All rights reserved.
//

#ifndef Service_Runnable_h
#define Service_Runnable_h

namespace com
{
    namespace rhinos
    {
        class Runnable
        {
        public:
            inline Runnable()
            {
                this->m_stop=0;
            }
            inline virtual ~Runnable(){}
            virtual void run()=0;
            inline virtual void stop()
            {
                this->m_stop=1;
            }
        protected:
            volatile bool m_stop;
        };
    }
}

#endif
