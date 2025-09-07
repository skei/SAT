#pragma once

//#include "base/sat_base.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#if defined SAT_LINUX
    #include "base/global/linux/sat_global_linux_gui.h"
    typedef SAT_LinuxGlobalGui SAT_ImplementedGlobalGui;
#elif defined SAT_WIN32
    #error NOT IMPLEMENTED YET
#elif defined SAT_MAC
    #error NOT IMPLEMENTED YET
#else
    #error NO OS DEFINED
#endif

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

#include "gui/sat_skin.h"
#include "gui/skin/sat_default_skin.h"

class SAT_GlobalGui
: public SAT_ImplementedGlobalGui
{
    public:
        SAT_GlobalGui();
        ~SAT_GlobalGui();
        void activate(SAT_GlobalBase* AGlobal);
        void deactivate(SAT_GlobalBase* AGlobal);
    public:
        void            appendSkin(SAT_Skin* ASkin);
        void            removeSkin(const char* AName, bool ADelete=true);
        void            replaceSkin(SAT_Skin* ASkin, const char* ANAme, bool ADelete=true);
        void            deleteSkins();
        SAT_Skin*       findSkin(const char* AName);
    private:
        SAT_SkinArray   MSkins = {};


};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_GlobalGui::SAT_GlobalGui()
: SAT_ImplementedGlobalGui()
{
}

SAT_GlobalGui::~SAT_GlobalGui()
{
}

void SAT_GlobalGui::activate(SAT_GlobalBase* AGlobal)
{
    SAT_ImplementedGlobalGui::activate(AGlobal);
    appendSkin( new SAT_DefaultSkin() );
    appendSkin( new SAT_DefaultPanelSkin() );
    appendSkin( new SAT_DefaultTextSkin() );
}

void SAT_GlobalGui::deactivate(SAT_GlobalBase* AGlobal)
{
    #ifndef SAT_NO_AUTODELETE
        deleteSkins();
    #endif
    SAT_ImplementedGlobalGui::deactivate(AGlobal);
}

//------------------------------
//
//------------------------------

void SAT_GlobalGui::appendSkin(SAT_Skin* ASkin)
{
    MSkins.append(ASkin);
}

void SAT_GlobalGui::removeSkin(const char* AName, bool ADelete)
{
    SAT_Skin* skin = findSkin(AName);
    if (skin)
    {
        MSkins.remove(skin);
        if (ADelete) delete skin;
    }
}

void SAT_GlobalGui::replaceSkin(SAT_Skin* ASkin, const char* AName, bool ADelete)
{
    removeSkin(AName);
    MSkins.append(ASkin);
}

void SAT_GlobalGui::deleteSkins()
{
    for (uint32_t i=0; i<MSkins.size(); i++)
    {
        delete MSkins[i];
    }
}

SAT_Skin* SAT_GlobalGui::findSkin(const char* AName)
{
    for (uint32_t i=0; i<MSkins.size(); i++)
    {
        SAT_Skin* skin = MSkins[i];
        const char* skin_name = skin->getName();
        if (SAT_IsEqual(AName,skin_name))
        {
            return skin;
        }
    }
    return nullptr;
}
