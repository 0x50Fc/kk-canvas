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

#endif

namespace kk {
    
    class Canvas;
    
    typedef void (*CanvasDrawFunc)(Canvas * canvas,kk::Object * CGContext);
    typedef void (*CanvasEmitFunc)(Canvas * canvas);
    
    struct CanvasCallback {
        CanvasDrawFunc draw;
        CanvasEmitFunc emit;
    };
    
    class Canvas : public kk::Object, public kk::script::IObject {
    public:
        
        Canvas(kk::DispatchQueue * queue,
               evdns_base * dns,
               kk::CString basePath,
               const CanvasCallback * cb,void * userdata);
        
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
        virtual void setUserdata(void *userdata);
        
        virtual kk::Strong popCGContext();
        
    protected:
        kk::String _basePath;
        kk::Strong _queue;
        kk::Strong _jsContext;
        kk::Strong _CGContext;
        void * _userdata;
        Uint _width;
        Uint _height;
    };
    
}

#endif /* kk_canvas_h */
