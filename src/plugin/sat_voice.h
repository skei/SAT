#pragma once

#include "base/sat_base.h"

template <class VOICE>
class SAT_Voice
{
    public:
        SAT_Voice();
        ~SAT_Voice();
    private:
        VOICE   MVoice;
};
