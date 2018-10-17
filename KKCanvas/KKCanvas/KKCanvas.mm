//
//  KKCanvas.m
//  KKCanvas
//
//  Created by hailong11 on 2018/10/11.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#import <Foundation/Foundation.h>


#import <UIKit/UIKit.h>
#import <KKHttp/KKHttp.h>

#include "kk-config.h"
#include "kk-canvas.h"
#include "WebGLContext.h"

#import "KKCanvasGLContext.h"

@interface KKCanvas : NSObject

@property(nonatomic,strong) KKCanvasGLContext * GLContext;

-(KKCanvasGLContext *) GLContext:(CGSize) size;

@end

@implementation KKCanvas

-(void) dealloc {
    
    if(_GLContext) {
        [EAGLContext setCurrentContext:_GLContext];
        [_GLContext recycle];
        [EAGLContext setCurrentContext:nil];
        _GLContext = nil;
    }
    
}

-(KKCanvasGLContext *) GLContext:(CGSize) size {
    if(_GLContext == nil) {
        _GLContext = [[KKCanvasGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
        [EAGLContext setCurrentContext:_GLContext];
        [_GLContext resize:size];
        [EAGLContext setCurrentContext:nil];
    }
    return _GLContext;
}


@end

namespace kk {
    
    static void Canvas_createCanvas_CanvasDrawFunc(Canvas * canvas,kk::Object * CGContext) {
        
        kk::WebGL::Context * v = dynamic_cast<kk::WebGL::Context *>(CGContext);
        
        if(v) {
            v->end();
            [EAGLContext setCurrentContext:nil];
        }
        
    }
    
    static void Canvas_createCanvas_CanvasGetContextFunc(Canvas * canvas,kk::Object * CGContext) {
        
        __weak KKCanvas * e = (__bridge KKCanvas *) canvas->userdata();
        
        if(e != nullptr) {
            
            kk::WebGL::Context * v = dynamic_cast<kk::WebGL::Context *>(CGContext);
            
            if(v) {
                
                @autoreleasepool {
                    
                    CGSize size = CGSizeMake(canvas->width(), canvas->height());
                    
                    KKCanvasGLContext * GLContext = [e GLContext:size];
                    
                    [EAGLContext setCurrentContext:GLContext];
                    
                    if(v->width() != canvas->width() || v->height() != canvas->height()) {
                        [GLContext resize:size];
                        v->setSize(canvas->width(), canvas->height());
                    }
                    
                    v->setFramebuffer([GLContext framebuffer]);
                    v->begin();
                    
                    [GLContext begin];
                    
                }
            }
            
            
        }
        
    }
    
    static void Canvas_createCanvas_CanvasEmitFunc(Canvas * canvas) {
        
    }
    
    
    static kk::CanvasCallback Canvas_createCanvas_cb = {
        Canvas_createCanvas_CanvasDrawFunc,
        Canvas_createCanvas_CanvasEmitFunc,
        Canvas_createCanvas_CanvasGetContextFunc,
        (CanvasUserDataReleaseFunc) CFRelease,
    };
    
    kk::Strong Canvas::createCanvas(Uint width,Uint height) {
        
        duk_context * ctx = dukContext();
        
        CFTypeRef u = nil;
        
        @autoreleasepool {
            u = CFBridgingRetain([[KKCanvas alloc] init]);
        }
        
        kk::Strong v = new kk::Canvas(_queue.as<kk::DispatchQueue>(),
                                      ev_dns(ctx),
                                      _basePath.c_str(),
                                      &Canvas_createCanvas_cb,
                                      (void *) u,
                                      width,
                                      height);
        
        return v;
    }
    
}


