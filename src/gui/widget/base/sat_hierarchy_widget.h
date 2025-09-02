#pragma once

#include "base/sat_base.h"
//#include "gui/sat_gui_base.h"
#include "gui/sat_painter.h"
#include "gui/widget/base/sat_base_widget.h"

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

class SAT_HierarchyWidget
: public SAT_BaseWidget
{
    public:
    
        SAT_HierarchyWidget();
        virtual ~SAT_HierarchyWidget();

    public: // hierarchy

        void                    setOwner(SAT_WidgetOwner* AOwner) override;
        void                    setParent(SAT_BaseWidget* AParent) override;
        void                    setIndex(uint32_t AIndex) override;

        SAT_WidgetOwner*        getOwner() override;
        SAT_BaseWidget*         getParent() override;
        uint32_t                getIndex() override;

        SAT_BaseWidget*         appendChild(SAT_BaseWidget* AWidget) override;
        void                    deleteChildren() override;
        void                    removeChild(SAT_BaseWidget* AWidget) override;
        uint32_t                getNumChildren() override;
        SAT_BaseWidget*         getChild(uint32_t AIndex) override;

        SAT_BaseWidget*         findChild(const char* AName) override;

    protected: // hierarchy

        SAT_WidgetOwner*        MOwner      = nullptr;
        SAT_BaseWidget*         MParent     = nullptr;
        SAT_BaseWidgetArray     MChildren   = {};
        const char*             MName       = "";
        uint32_t                MIndex      = 0;

};

//----------------------------------------------------------------------
//
//
//
//----------------------------------------------------------------------

SAT_HierarchyWidget::SAT_HierarchyWidget()
: SAT_BaseWidget()
{
    MWidgetTypeName = "SAT_HierarchyWidget";
}

SAT_HierarchyWidget::~SAT_HierarchyWidget()
{
    #ifndef SAT_NO_AUTODELETE
        deleteChildren();
    #endif
}

//------------------------------
//
//------------------------------

void SAT_HierarchyWidget::setOwner(SAT_WidgetOwner* AOwner)
{
    MOwner = AOwner;
}

void SAT_HierarchyWidget::setParent(SAT_BaseWidget* AParent)
{
    MParent = AParent;
}

void SAT_HierarchyWidget::setIndex(uint32_t AIndex)
{
    MIndex = AIndex;
}

//----------

SAT_WidgetOwner* SAT_HierarchyWidget::getOwner()
{
    return MOwner;
}

SAT_BaseWidget* SAT_HierarchyWidget::getParent()
{
    return MParent;
}

uint32_t SAT_HierarchyWidget::getIndex()
{
    return MIndex;
}

//----------

SAT_BaseWidget* SAT_HierarchyWidget::appendChild(SAT_BaseWidget* AWidget)
{
    AWidget->setParent(this);
    uint32_t index = MChildren.size();
    AWidget->setIndex(index);
    MChildren.append(AWidget);
    return AWidget;
}

void SAT_HierarchyWidget::deleteChildren()
{
    for (uint32_t i=0; i<getNumChildren(); i++)
    {
        SAT_BaseWidget* widget = getChild(i);
        if (widget) delete widget;
    }
}

void SAT_HierarchyWidget::removeChild(SAT_BaseWidget* AWidget)
{
    AWidget->setParent(nullptr);
    MChildren.remove(AWidget);
}

uint32_t SAT_HierarchyWidget::getNumChildren()
{
    return MChildren.size();
}

SAT_BaseWidget* SAT_HierarchyWidget::getChild(uint32_t AIndex)
{
    return MChildren[AIndex];
}

//----------

SAT_BaseWidget* SAT_HierarchyWidget::findChild(const char* AName)
{
    const char* name = getName();
    if (strcmp(AName,name) == 0)
    {
        return this;
    }
    for (uint32_t i=0; i<getNumChildren(); i++)
    {
        SAT_BaseWidget* child = getChild(i);
        name = child->getName();
        if (strcmp(AName,name) == 0) 
        {
            return child;
        }
        else
        {
            SAT_BaseWidget* subchild = child->findChild(AName);
            if (subchild) return subchild;
        }
    }
    return nullptr;
}
