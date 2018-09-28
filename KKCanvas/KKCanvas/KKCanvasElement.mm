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
#include "kk-canvas.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/EAGL.h>

@interface KKCanvasView : UIView
@end

@interface KKCanvasElement() {
    kk::Canvas * _canvas;
}

-(void) display:(kk::Object *) CGContext;

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
    
    canvas->release();
}


@implementation KKCanvasElement

+(void) initialize {
    [KKViewContext setDefaultElementClass:[KKCanvasElement class] name:@"canvas"];
}

-(void) dealloc {

    if(_canvas != nil) {
        
        _canvas->setUserdata(nil);
        
        BK_CTX
        
        BK_RETAIN(canvas, _canvas)
        
        KKCanvasDispatchQueue()->async(KKCanvasElement_Recycle, BK_ARG);
        
        _canvas = nullptr;
        
    }
    
}

static void KKCanvasElement_CanvasDrawFunc(kk::Canvas * canvas,kk::Object * CGContext) {
    
    __weak KKCanvasElement * e = (__bridge KKCanvasElement *) canvas->userdata();
    
    if(e != nil) {
        CGContext->retain();
        dispatch_async(dispatch_get_main_queue(), ^{
            [e display:CGContext];
            CGContext->release();
        });
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
    };
    
    _canvas = new kk::Canvas(KKCanvasDispatchQueue(),KKCanvasEventDNS(),[basePath UTF8String],&cb,(__bridge void *) self);
    
    _canvas->retain();
    
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

-(void) display : (kk::Object *) CGContext {
    
    UIView * view = self.view;
    
    if(view == nil) {
        return ;
    }
    
    if(_canvas == nullptr) {
        return;
    }
    
    {
        kk::CG::OSContext * v = dynamic_cast<kk::CG::OSContext *>(CGContext);
        
        if(v != nullptr) {
            CGImageRef image = v->createCGImage();
            view.layer.contents = (__bridge id) image;
            CGImageRelease(image);
            return ;
        }
    }
    
    view.layer.contents = nil;
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

@end

@implementation KKCanvasView

+(Class) layerClass {
    return [CAEAGLLayer class];
}

-(void) KKViewElementDidLayouted:(KKViewElement *)element {
    [super KKViewElementDidLayouted:element];
}

@end

