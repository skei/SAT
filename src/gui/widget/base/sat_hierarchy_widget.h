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

        SAT_WidgetOwner*        getOwner() override;
        SAT_BaseWidget*         getParent() override;
        uint32_t                getNumChildren() override;
        SAT_BaseWidget*         getChild(uint32_t AIndex) override;
        uint32_t                getIndex() override;

        void                    setOwner(SAT_WidgetOwner* AOwner) override;
        void                    setParent(SAT_BaseWidget* AParent) override;
        void                    setIndex(uint32_t AIndex) override;

        SAT_BaseWidget*         appendChild(SAT_BaseWidget* AWidget) override;
        void                    removeChild(SAT_BaseWidget* AWidget) override;
        void                    deleteChildren() override;
        SAT_BaseWidget*         findWidget(const char* AName, bool ARecursive=true) override;

    public: // on_

        void                    on_widget_show(SAT_WidgetOwner* AOwner) override;
        void                    on_widget_hide(SAT_WidgetOwner* AOwner) override;

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
    MWidgetType     = 0;
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

SAT_WidgetOwner* SAT_HierarchyWidget::getOwner()
{
    return MOwner;
}

SAT_BaseWidget* SAT_HierarchyWidget::getParent()
{
    return MParent;
}

uint32_t SAT_HierarchyWidget::getNumChildren()
{
    return MChildren.size();
}

SAT_BaseWidget* SAT_HierarchyWidget::getChild(uint32_t AIndex)
{
    return MChildren[AIndex];
}

uint32_t SAT_HierarchyWidget::getIndex()
{
    return MIndex;
}

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

SAT_BaseWidget* SAT_HierarchyWidget::appendChild(SAT_BaseWidget* AWidget)
{
    AWidget->setParent(this);
    uint32_t index = MChildren.size();
    AWidget->setIndex(index);
    MChildren.append(AWidget);
    return AWidget;
}

void SAT_HierarchyWidget::removeChild(SAT_BaseWidget* AWidget)
{
    AWidget->setParent(nullptr);
    MChildren.remove(AWidget);
}

void SAT_HierarchyWidget::deleteChildren()
{
    for (uint32_t i=0; i<getNumChildren(); i++)
    {
        SAT_BaseWidget* widget = getChild(i);
        if (widget) delete widget;
    }
}

SAT_BaseWidget* SAT_HierarchyWidget::findWidget(const char* AName, bool ARecursive)
{
    for (uint32_t i=0; i<getNumChildren(); i++)
    {
        SAT_BaseWidget* child = getChild(i);
        const char* name = child->getName();
        if (strcmp(AName,name) == 0)
        {
            return child;
        }
        else
        {
            if (ARecursive)
            {
                SAT_BaseWidget* subchild = child->findWidget(AName,ARecursive);
                if (subchild) return subchild;
            }
        }
    }
    return nullptr;
}

//------------------------------
// on_
//------------------------------

void SAT_HierarchyWidget::on_widget_show(SAT_WidgetOwner* AOwner)
{
    setOwner(AOwner);
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_BaseWidget* widget = getChild(i);
        widget->on_widget_show(AOwner);
    }
}

void SAT_HierarchyWidget::on_widget_hide(SAT_WidgetOwner* AOwner)
{
    setOwner(nullptr);
    uint32_t num = getNumChildren();
    for (uint32_t i=0; i<num; i++)
    {
        SAT_BaseWidget* widget = getChild(i);
        widget->on_widget_hide(AOwner);
    }
}
