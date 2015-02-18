int main(){

#include "../../sdl2base/GLWindow.h"

class ExampleWindow : public GLWindow
{
    public:
       using GLWindow::checkEvents;
       ExampleWindow(const char *ititle, size_t width, size_t height, Uint32 windowflags);
       ~ExampleWindow();
       int checkEvents(Leap::Controller &controller);
 };
 
 #endif }
