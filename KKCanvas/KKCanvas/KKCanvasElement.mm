//
//  KKCanvasElement.m
//  KKCanvas
//
//  Created by hailong11 on 2018/9/27.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#import <KKObject/KKObject.h>
#import "KKCanvasElement.h"
#include "CGContext.h"
#include "WebGLContext.h"
#include "kk-canvas.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/EAGL.h>
#import "KKCanvasGLContext.h"

@interface KKCanvasView : UIView
@end

@interface KKCanvasElement() {
    kk::Canvas * _canvas;
}

@property(nonatomic,strong,readonly) KKCanvasGLContext * GLContext;

-(void) displayCGContext:(kk::CG::OSContext *) CGContext;

-(void) displayGLContext:(kk::WebGL::Context *) CGContext;

-(void) resizeGLContext;

@end

evdns_base * KKCanvasEventDNS() {
    static evdns_base * v = nullptr;
    if(v == nullptr) {
        evdns_base_new(KKCanvasDispatchQueue()->base(), 0);
    }
    return v;
}

kk::DispatchQueue * KKCanvasDispatchQueue() {
    static kk::DispatchQueue * v = nullptr;
    if(v == nullptr) {
        v = new kk::DispatchQueue("KKCanvasDispatchQueue");
        v->retain();
    }
    return v;
}

static void KKCanvasElement_Recycle(kk::DispatchQueue * queue,BK_DEF_ARG) {
    
    BK_GET(canvas, kk::Object)
    BK_GET_VAR(GLContext, CFTypeRef)
    
    if(GLContext != nil) {
        [EAGLContext setCurrentContext:(__bridge EAGLContext *) GLContext];
    }
    
    canvas->release();
    
    if(GLContext != nil) {
        [(__bridge KKCanvasGLContext *) GLContext recycle];
        [EAGLContext setCurrentContext:nil];
    }
    
}

@implementation KKCanvasElement

@synthesize GLContext = _GLContext;

+(void) initialize {
    [KKViewContext setDefaultElementClass:[KKCanvasElement class] name:@"canvas"];
}

-(void) dealloc {

    if(_canvas != nil) {
        
        _canvas->setUserdata(nil);
        
        BK_CTX
        
        BK_RETAIN(canvas, _canvas)
        
        if(_GLContext != nil) {
            BK_PTR(GLContext, CFBridgingRetain(_GLContext), CFRelease);
        }
        
        KKCanvasDispatchQueue()->async(KKCanvasElement_Recycle, BK_ARG);
        
        _canvas = nullptr;
        
    }
    
}

static void KKCanvasElement_CanvasDrawFunc(kk::Canvas * canvas,kk::Object * CGContext) {
    
    __weak KKCanvasElement * e = (__bridge KKCanvasElement *) canvas->userdata();
    
    if(e != nil) {
        
        {
            kk::CG::OSContext * v = dynamic_cast<kk::CG::OSContext *>(CGContext);
            
            if(v) {
                v->retain();
                dispatch_async(dispatch_get_main_queue(), ^{
                    [e displayCGContext:v];
                    v->release();
                });
                return;
            }
        }
        
        {
            kk::WebGL::Context * v = dynamic_cast<kk::WebGL::Context *>(CGContext);
            
            if(v) {
                @autoreleasepool {
                     [e displayGLContext:v];
                }
                return;
            }
        }
        
    }
    
}

static void KKCanvasElement_CanvasEmitFunc(kk::Canvas * canvas) {
    
    duk_context * ctx = canvas->dukContext();
    
    __weak KKCanvasElement * e = (__bridge KKCanvasElement *) canvas->userdata();
    
    if(e != nil && ctx != nullptr) {
        
        @autoreleasepool {
            
            NSString * name = nil;
            id data = nil;
            
            int top = duk_get_top(ctx);
            
            if(top > 0 && duk_is_string(ctx, -top)) {
                name = [NSString stringWithCString:duk_to_string(ctx, -top) encoding:NSUTF8StringEncoding];
            }
            
            if(top > 1 && duk_is_object(ctx, -top  +1)) {
                data = duk_to_NSObject(ctx,-top + 1);
            }
            
            if(name) {
                
                dispatch_async(dispatch_get_main_queue(), ^{
                    
                    KKCanvasElement * element = e;
                    
                    if(element) {
                        KKElementEvent * event = [[KKElementEvent alloc] initWithElement:element];
                        event.data = data;
                        [element emit:name event:event];
                    }
                    
                });
                
            }
            
            
        }
        
        
    }
    
}

static void KKCanvasElement_CanvasGetContextFunc(kk::Canvas * canvas,kk::Object * CGContext) {
    
    __weak KKCanvasElement * e = (__bridge KKCanvasElement *) canvas->userdata();
    
    if(e != nullptr) {
        
        kk::WebGL::Context * v = dynamic_cast<kk::WebGL::Context *>(CGContext);
        
        if(v) {
            
            @autoreleasepool {
                
                if(v->width() != canvas->width() || v->height() != canvas->height()) {
                    dispatch_sync(dispatch_get_main_queue(), ^{
                        [e resizeGLContext];
                    });
                    v->setSize(canvas->width(), canvas->height());
                }
                
                [EAGLContext setCurrentContext:[e GLContext]];

                [[e GLContext] begin];
                
            }
        }
        
        
    }
    
}

-(void) installCGContext {
    
    if(_canvas != nil) {
        return;
    }
    
    UIView * view = self.view;
    
    if(view == nil) {
        return;
    }
    
    NSString * basePath = self.viewContext.basePath;
    
    NSString * path = [self get:@"path"];
    
    if(path) {
        basePath = [basePath stringByAppendingPathComponent:path];
    }
    
    kk::CanvasCallback cb = {
        KKCanvasElement_CanvasDrawFunc,
        KKCanvasElement_CanvasEmitFunc,
        KKCanvasElement_CanvasGetContextFunc,
    };
    
    CGFloat v = view.window.screen.scale;
    
    if(v ==0.0f) {
        v = [UIScreen mainScreen].scale;
    }
    
    _canvas = new kk::Canvas(KKCanvasDispatchQueue(),
                             KKCanvasEventDNS(),
                             [basePath UTF8String],
                             &cb,
                             (__bridge void *) self,
                             ceil(self.frame.size.width * v),
                             ceil(self.frame.size.height * v));

    _canvas->retain();
    
//    kk::script::Debugger * debugger = new kk::script::Debugger(9091);
//    
//    debugger->debug(_canvas->jsContext()->jsContext());
//    
    if(path) {
        _canvas->exec("main.js");
    } else {
        _canvas->exec([[self get:@"#text"] UTF8String], "kk-canvas");
    }
    
}

-(void) uninstallCGContext {
    
    if(_canvas != nil) {
        
        _canvas->setUserdata(nil);
        
        BK_CTX
        
        BK_RETAIN(canvas, _canvas)
        
        if(_GLContext != nil) {
            BK_PTR(GLContext, CFBridgingRetain(_GLContext), CFRelease);
            _GLContext = nil;
        }
        
        KKCanvasDispatchQueue()->async(KKCanvasElement_Recycle, BK_ARG);
        
        _canvas = nullptr;
    }
    
}

-(Class) viewClass{
    return [KKCanvasView class];
}

-(void) setView:(UIView *) view {
    [self uninstallCGContext];
    [super setView:view];
    if(view) {
        [self installCGContext];
    }
}

-(void) recycle {
    [self uninstallCGContext];
    [super recycle];
}

-(void) changedKey:(NSString *)key {
    [super changedKey:key];
}

-(void) displayGLContext:(kk::WebGL::Context *) CGContext {
    
    if(_GLContext != nil) {
        
 
        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE , GL_ONE_MINUS_SRC_ALPHA);
        
        GLfloat vs[] = {-0.5, 0.5, -0.5, -0.5, 0.0, -0.5};
        
        GLuint vsh = glCreateShader(GL_VERTEX_SHADER);
        
        kk::CString vshCode = "attribute vec2 coordinates; void main(void) { gl_Position = vec4(coordinates,0.0, 1.0); }";
        
        glShaderSource(vsh, 1, & vshCode, NULL);
        
        glCompileShader(vsh);
        
        GLint status = GL_FALSE;
        
        glGetShaderiv(vsh, GL_COMPILE_STATUS, &status);
        
        if (status != GL_TRUE ){
            
            char data[2048] = "";
            GLint n = 0;
            
            glGetShaderInfoLog(vsh, sizeof(data), &n, data);
            
            kk::Log("[WebGL] [VSH] [ERROR] %s",data);
        }
        
        GLuint fsh = glCreateShader(GL_FRAGMENT_SHADER);
        
        kk::CString fshCode = "void main(void) { gl_FragColor = vec4(1.0, 1.0, 0.0, 1.0); }";
        
        glShaderSource(fsh, 1, & fshCode, NULL);
        
        glCompileShader(fsh);
        
        glGetShaderiv(fsh, GL_COMPILE_STATUS, &status);
        
        if (status != GL_TRUE ){
            
            char data[2048] = "";
            GLint n = 0;
            
            glGetShaderInfoLog(fsh, sizeof(data), &n, data);
            
            kk::Log("[WebGL] [FSH] [ERROR] %s",data);
        }
        
        GLuint program = glCreateProgram();
        
        glAttachShader(program, vsh);
        glAttachShader(program, fsh);
        
        glLinkProgram(program);
        
        glGetProgramiv(program, GL_LINK_STATUS, &status);
        
        if (status != GL_TRUE ){
            
            char data[2048] = "";
            
            glGetProgramInfoLog(program, sizeof(data), NULL, data);
            
            kk::Log("[WebGL] [PROGRAM] [ERROR] %s",data);
        }
        
        glUseProgram(program);
        
        GLint loc = glGetAttribLocation(program, "coordinates");
        
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, vs);
        
        glEnableVertexAttribArray(loc);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glDeleteShader(vsh);
        
        glDeleteShader(vsh);
        
        glDeleteProgram(program);
        
        [_GLContext display];
        
        [EAGLContext setCurrentContext:nil];
        
    }
    
}

-(void) displayCGContext:(kk::CG::OSContext *) CGContext{
    
    UIView * view = self.view;
    
    if(view == nil) {
        return ;
    }
    
    if(_canvas == nullptr) {
        return;
    }
    
    CGImageRef image = CGContext->createCGImage();
    view.layer.contents = (__bridge id) image;
    CGImageRelease(image);
    
}

-(void) didLayouted {
    [super didLayouted];
    
    UIView * view = self.view;
    
    if(view == nil) {
        return ;
    }
    
    if(_canvas != nullptr) {
        
        CGFloat v = view.window.screen.scale;
        
        if(v ==0.0f) {
            v = [UIScreen mainScreen].scale;
        }
        
        _canvas->setSize(ceil(self.frame.size.width * v), ceil(self.frame.size.height * v));
    }
}

-(void) resizeGLContext {
    
    UIView * view = self.view;
    
    if(view == nil) {
        return;
    }
    
    if(_GLContext == nil) {
        return;
    }
    
    CAEAGLLayer * layer = (CAEAGLLayer *) view.layer;
    
    CGFloat scale = view.window.screen.scale;
    
    if(scale == 0.0f) {
        scale = [UIScreen mainScreen].scale;
    }
    
    layer.contentsScale = scale;
    layer.opaque = NO;
    
    [EAGLContext setCurrentContext:_GLContext];
    [_GLContext resizeLayer:layer];
    [EAGLContext setCurrentContext:nil];
    
}

-(EAGLContext *) GLContext {
    
    if(_GLContext == nil) {
        
        _GLContext = [[KKCanvasGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        
        __weak KKCanvasElement * e = self;
        
        dispatch_sync(dispatch_get_main_queue(), ^{
            [e resizeGLContext];
        });
        
    }
    
    return _GLContext;
}

@end

@implementation KKCanvasView

+(Class) layerClass {
    return [CAEAGLLayer class];
}

-(void) KKViewElementDidLayouted:(KKViewElement *)element {
    [super KKViewElementDidLayouted:element];
}

@end

