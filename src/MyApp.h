#pragma once

#include <wx/wx.h>
#include "DrawingView.h"
#include "StrokeSettings.h"

class MyFrame;

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();

    static void SetupCanvasForView(DrawingView *view);
    static StrokeSettings &GetStrokeSettings();

private:
    MyFrame *m_frame{};

    std::unique_ptr<wxDocManager> m_docManager{};

    StrokeSettings m_strokeSettings;
};