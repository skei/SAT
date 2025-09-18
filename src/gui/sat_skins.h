#pragma once

#include "base/sat_base.h"
#include "gui/sat_skin.h"
#include "gui/skin/sat_default_skin.h"

class SAT_Skin;
typedef SAT_Array<SAT_Skin*> SAT_SkinArray;



//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_Skins
{
    public:
        SAT_Skins();
        ~SAT_Skins();
    public:
        void            initialize();
        void            cleanup();
        void            append(SAT_Skin* ASkin);
        void            remove(const char* AName, bool ADelete=true);
        void            replace(SAT_Skin* ASkin, const char* ANAme, bool ADelete=true);
        void            deleteAll();
        SAT_Skin*       find(const char* AName);
    private:
        SAT_SkinArray   MSkins = {};
};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_Skins::SAT_Skins()
{
}

SAT_Skins::~SAT_Skins()
{
}

//------------------------------
//
//------------------------------

void SAT_Skins::initialize()
{
    append( new SAT_DefaultSkin() );
    append( new SAT_DefaultBackgroundSkin() );
    append( new SAT_DefaultOverlaySkin() );
    append( new SAT_DefaultPanelSkin() );
    append( new SAT_DefaultTextSkin() );
}

void SAT_Skins::cleanup()
{
    #ifndef SAT_NO_AUTODELETE
        deleteAll();
    #endif
}

void SAT_Skins::append(SAT_Skin* ASkin)
{
    MSkins.append(ASkin);
}

void SAT_Skins::remove(const char* AName, bool ADelete)
{
    SAT_Skin* skin = find(AName);
    if (skin)
    {
        MSkins.remove(skin);
        if (ADelete) delete skin;
    }
}

void SAT_Skins::replace(SAT_Skin* ASkin, const char* AName, bool ADelete)
{
    remove(AName);
    MSkins.append(ASkin);
}

void SAT_Skins::deleteAll()
{
    for (uint32_t i=0; i<MSkins.size(); i++)
    {
        delete MSkins[i];
    }
}

SAT_Skin* SAT_Skins::find(const char* AName)
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
