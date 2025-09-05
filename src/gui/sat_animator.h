#pragma once

#include "base/util/sat_easing.h"
#include "gui/sat_widget.h"

// #define SAT_TWEEN_MAX_VALUES        4
// #define SAT_QUEUE_SIZE_TWEEN        32

// delete, end, repeat, ..

//----------

class SAT_AnimNode;
class SAT_AnimChain;

typedef SAT_Array<SAT_AnimNode*> SAT_AnimNodeArray;
typedef SAT_Array<SAT_AnimChain*> SAT_AnimChainArray;
typedef SAT_SPSCQueue<SAT_AnimChain*,SAT_QUEUE_SIZE_TWEEN>  SAT_AnimChainQueue;

//----------------------------------------------------------------------
//
// anim node
//
//----------------------------------------------------------------------

class SAT_AnimNode
{
    public:
        SAT_AnimNode(void* ATarget, uint32_t AId, double ADuration, uint32_t AType, uint32_t ANumValues=0, double* AStartValues=nullptr, double* AEndValues=nullptr, uint32_t AEasing=0);
        ~SAT_AnimNode();
    public:
        uint32_t    MType                               = 0;        // anim, pause, signal ..
        uint32_t    MId                                 = 0;        // id
        double      MDuration                           = 0.0;      // in seconds
        void*       MTarget                             = nullptr;  // target widget
        uint32_t    MEasing                             = 0;        // easing
        uint32_t    MNumValues                          = 0;        // number of coords/vriables
        double      MStartValues[SAT_TWEEN_MAX_VALUES]  = {0};      // start values
        double      MDeltaValues[SAT_TWEEN_MAX_VALUES]  = {0};      // values change to react target in 'duration' time
};

class SAT_AnimChain
{
    public:
        SAT_AnimChain();
        ~SAT_AnimChain();
    public:
        SAT_AnimNode* appendNode(SAT_AnimNode* ANode);
        void deleteNodes();
        uint32_t getNumNodes();
        void start(void);
        void stop(void);
        bool isActive();
    public:
        bool                MActive         = true;
        uint32_t            MCurrentNode    = 0;
        double              MCurrentTime    = 0.0;
        SAT_AnimNodeArray  MNodes          = {};
};

class SAT_Animator
{
    public:
        SAT_Animator();
        ~SAT_Animator();
    public:
        // void appendAnim(SAT_AnimNode* AAnim);
        SAT_AnimChain* appendChain(SAT_AnimChain* AChain);
        void deleteChains();
        virtual void process(double ADelta);
    private:
        SAT_AnimChainArray MChains;    // = {};
        SAT_AnimChainQueue MPending;   // = {};
};

//----------------------------------------------------------------------
//
// implementation
//
//----------------------------------------------------------------------

//------------------------------
// anim node
//------------------------------

SAT_AnimNode::SAT_AnimNode(void* ATarget, uint32_t AId, double ADuration, uint32_t AType, uint32_t ANumValues, double* AStartValues, double* AEndValues, uint32_t AEasing)
{
    //SAT_TRACE;
    MId         = AId;
    MDuration   = ADuration;
    MTarget     = ATarget;
    MEasing     = AEasing;
    MNumValues  = ANumValues;
    for (uint32_t i=0; i<ANumValues; i++)
    {
        MStartValues[i] = AStartValues[i];
        MDeltaValues[i] = AEndValues[i] - AStartValues[i];
    }
}
  
SAT_AnimNode::~SAT_AnimNode()
{
    //SAT_TRACE;
}

//------------------------------
// anim chain
//------------------------------

SAT_AnimChain::SAT_AnimChain()
{
    //SAT_TRACE;
}
  
SAT_AnimChain::~SAT_AnimChain()
{
    //SAT_TRACE;
    #ifndef SAT_NO_AUTODELETE
        deleteNodes();
    #endif
}
  
SAT_AnimNode* SAT_AnimChain::appendNode(SAT_AnimNode* ANode)
{
    MNodes.append(ANode);
    return ANode;
}

void SAT_AnimChain::deleteNodes()
{
    for (uint32_t i=0; i<MNodes.size(); i++) delete MNodes[i];
}

uint32_t SAT_AnimChain::getNumNodes()
{
    return MNodes.size();
}
  
void SAT_AnimChain::start(void)
{
    MActive = true;
    MCurrentNode = 0;
    MCurrentTime = 0.0;
}
  
void SAT_AnimChain::stop(void)
{
    MActive = false;
}
  
bool SAT_AnimChain::isActive()
{
    return MActive;
}

//------------------------------
// animator
//------------------------------

SAT_Animator::SAT_Animator()
{
}

SAT_Animator::~SAT_Animator()
{
    #if !defined (SAT_NO_AUTODELETE)
        deleteChains();
    #endif
}

// void SAT_Animator::appendAnim(SAT_AnimNode* AAnim)
// {
//     // create chain
//     // append node
// }
  
SAT_AnimChain* SAT_Animator::appendChain(SAT_AnimChain* AChain)
{
    MPending.write(AChain);
    return AChain;
}
  
void SAT_Animator::deleteChains()
{
    for (uint32_t i=0; i<MChains.size(); i++) delete MChains[i];
    SAT_AnimChain* chain = nullptr;
    while (MPending.read(&chain)) { delete chain; }
}
  
/*
    'double free or corruption' crash when anim ends..
    (still relevant, or was this from earlier debugging?
*/

void SAT_Animator::process(double ADelta)
{
    // SAT_TRACE;
    SAT_AnimChain* chain;
    while (MPending.read(&chain))
    {
        MChains.append(chain);
    }
    uint32_t num_chains = MChains.size();
    for (uint32_t i=0; i<num_chains; i++)
    {
        if (MChains[i]->MActive)
        {
            uint32_t index = MChains[i]->MCurrentNode;
            SAT_AnimNode* node = MChains[i]->MNodes[index];
            if (node)
            {
                SAT_Widget* target = (SAT_Widget*)node->MTarget;
                double data[16] = {0};
                // double time_left = node->MDuration - (MChains[i]->MCurrentTime + ADelta);
                for (uint32_t j=0; j<node->MNumValues; j++)
                {
                    // if (next_time >= node->MDuration)
                    // {
                    //     data[j] = node->MStartValues[j] + (node->MDeltaValues[j] * node->MDuration);
                    // }
                    // else
                    // {
                    data[j] = SAT_Easing(
                        node->MEasing,
                        MChains[i]->MCurrentTime,
                        node->MStartValues[j],
                        node->MDeltaValues[j],
                        node->MDuration
                    );
                    // }
                }
                target->on_widget_anim(node->MId,node->MType,node->MNumValues,data);
                MChains[i]->MCurrentTime += ADelta;
                if (MChains[i]->MCurrentTime >= node->MDuration)
                {
                    // jump to end point..
                    for (uint32_t j=0; j<node->MNumValues; j++)
                    {
                        data[j] = SAT_Easing(
                            node->MEasing,
                            node->MDuration, // MChains[i]->MCurrentTime,
                            node->MStartValues[j],
                            node->MDeltaValues[j],
                            node->MDuration
                        );
                    }
                    target->on_widget_anim(node->MId,node->MType,node->MNumValues,data);
                    MChains[i]->MCurrentTime = 0.0; // -= node->MDuration;
                    MChains[i]->MCurrentNode += 1;
                    if (MChains[i]->MCurrentNode >= MChains[i]->MNodes.size())
                    {
                        MChains[i]->MActive = false;
                        target->on_widget_anim(node->MId,SAT_ANIM_FINISHED,0,nullptr); // send end anim msg..
                        // // TODO: if looping
                        // MChains[i]->MCurrentNode = 0;
                        // MChains[i]->MCurrentTime = 0.0;
                    }
                } // duration
            } // node active
        } // anim active
    } // for
    // delete finished chains
    uint32_t i = 0;
    while (i < MChains.size())
    {
        SAT_AnimChain* chain = MChains[i];
        if (!chain->MActive)
        {
            MChains.remove(i);
            delete chain;
        }
        i += 1;
    }
}
