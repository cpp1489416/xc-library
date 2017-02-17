#pragma once

namespace XC
{
    namespace GUI 
    {
        class IApplication
        {
        public:
            virtual void Execute() = 0;
        };
    }
}