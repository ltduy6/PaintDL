#pragma once

#include <wx/wx.h>

class Myframe;

class MyApp : public wxApp
{
public:
    virtual bool OnInit();

private:
    Myframe *frame{};
};