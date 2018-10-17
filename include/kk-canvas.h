//
//  kk-canvas.h
//  KKCanvas
//
//  Created by hailong11 on 2018/9/28.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#ifndef kk_canvas_h
#define kk_canvas_h

#if defined(KK_PLATFORM_IOS)

#include <KKObject/KKObject.h>

#else

#include "kk-object.h"
#include "kk-script.h"
#include "kk-string.h"
#include "kk-dispatch.h"

#endif

namespace kk {
    
    class Canvas;
    
    typedef void (*CanvasDrawFunc)(Canvas * canvas,kk::Object * CGContext);
    typedef void (*CanvasGetContextFunc)(Canvas * canvas,kk::Object * CGContext);
    typedef void (*CanvasEmitFunc)(Canvas * canvas);
    typedef void (*CanvasUserDataReleaseFunc)(void * userData);
    
    struct CanvasCallback {
        CanvasDrawFunc draw;
        CanvasEmitFunc emit;
        CanvasGetContextFunc getContext;
        CanvasUserDataReleaseFunc userdataRelease;
    };
    
    
    class Canvas : public kk::Object, public kk::script::IObject {
    public:
        
        Canvas(kk::DispatchQueue * queue,
               evdns_base * dns,
               kk::CString basePath,
               const CanvasCallback * cb,
               void * userdata,
               Uint width,
               Uint height);
    
        virtual ~Canvas();
        
        DEF_SCRIPT_CLASS_NOALLOC
        
        DEF_SCRIPT_PROPERTY(width,Width)
        DEF_SCRIPT_PROPERTY(height,Height)
        DEF_SCRIPT_METHOD(getContext)
        
        virtual kk::script::Context * jsContext();
        virtual duk_context * dukContext();
        
        virtual void setSize(Uint width,Uint height);
        virtual void set(kk::CString key, kk::CString value);
        virtual void exec(kk::CString code,kk::CString filename);
        virtual void exec(kk::CString path);
        
        virtual void * userdata();
        
        virtual void clearUserdata();
        
        virtual kk::Strong CGContext();
        
        virtual Uint width();
        virtual Uint height();
        
        virtual void setNeedsDisplay();
        
        virtual void display();
        
        virtual kk::Strong createCanvas(Uint width,Uint height);
        
    protected:

        kk::String _basePath;
        kk::Strong _queue;
        kk::Strong _jsContext;
        kk::Strong _CGContext;
        void * _userdata;
        CanvasUserDataReleaseFunc _userdataRelease;
        CanvasDrawFunc _draw;
        CanvasGetContextFunc _getContext;
        Uint _width;
        Uint _height;
        kk::Boolean _displaying;
    };
    
}

#endif /* kk_canvas_h */
