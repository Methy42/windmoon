#ifndef WINDOW_SYSTEM_MAC_WINDOW_H
#define WINDOW_SYSTEM_MAC_WINDOW_H

#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>

class MacWindow {
public:
    MacWindow();
    ~MacWindow();
    
    void render();
    
    void run();
    
private:
    static const int kMaxDisplays = 16;
    static const int kWindowWidth = 640;
    static const int kWindowHeight = 480;
    static constexpr double kRunLoopInterval = 1.0 / 60.0; // 60帧每秒
    
    CGRect _windowRect;
    CFArrayRef _windowRef;
    CGContextRef _contextRef;
};

#endif  // WINDOW_SYSTEM_MAC_WINDOW_H