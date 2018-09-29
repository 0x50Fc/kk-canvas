//
//  CGImage.m
//  KKCanvas
//
//  Created by hailong11 on 2018/9/29.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <KKHttp/KKHttp.h>

#include "kk-config.h"
#include "CGContext.h"

namespace kk {

    namespace CG {
        
        OSImage::OSImage(kk::CString src,kk::CString basePath):_src(src),_basePath(basePath),_image(nullptr) {
            
        }
        
        OSImage::~OSImage() {
            if(_image) {
                CGImageRelease(_image);
            }
        }
        
        Uint OSImage::width() {
            if(_image != nil) {
                return (Uint) CGImageGetWidth(_image);
            }
            return 0;
        }
        
        Uint OSImage::height() {
            if(_image != nil) {
                return (Uint) CGImageGetHeight(_image);
            }
            return 0;
        }
        
        CGImageRef OSImage::CGImage() {
            return _image;
        }
        
        void OSImage::setCGImage(CGImageRef image) {
            if(_image != image) {
                if(image != nil) {
                    CGImageRetain(image);
                }
                if(_image != nil) {
                    CGImageRelease(_image);
                }
                _image = image;
            }
        }
        
        Boolean OSImage::isCopyPixels() {
            return _image != nullptr;
        }
        
        void OSImage::copyPixels(void * data) {
            
            if(_image != nullptr) {
                
                size_t width = CGImageGetWidth(_image);
                size_t height = CGImageGetHeight(_image);
                
                CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
                CGContextRef ctx = CGBitmapContextCreate(data, width, height, 8, width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
                CGContextTranslateCTM(ctx, 0, height);
                CGContextScaleCTM(ctx, 1, -1);
                CGColorSpaceRelease(rgbSpace);
                
                CGContextDrawImage(ctx, CGRectMake(0, 0, width, height), _image);
                
                CGContextRelease(ctx);
                
            }
        }
        
        static void OSImage_loadDispatchFunc(DispatchQueue * queue,BK_DEF_ARG) {
            
            BK_GET_STRONG(image)
            BK_GET_VAR(CGImage, CGImageRef)
            
            OSImage * v = image.as<OSImage>();
            
            if(v != nullptr) {
            
                if(CGImage == nullptr) {
                    v->done("图片加载错误" );
                } else {
                    v->setCGImage(CGImage);
                    v->done(nullptr);
                }
                
            }
        }
        
        void OSImage::load(OSImage * image) {
            
            if(kk::CStringHasPrefix(image->src(), "http://")
               || kk::CStringHasPrefix(image->src(), "https://")) {
                
                kk::DispatchQueue * queue = kk::DispatchQueue::current();
                
                @autoreleasepool {
                    
                    OSImage ** v = (OSImage **) malloc(sizeof(OSImage *));
                    
                    image->weak((kk::Object **) v);
                    
                    *v = image;
                    
                    NSString * url = [NSString stringWithCString:image->src() encoding:NSUTF8StringEncoding];
                    
                    KKHttpImageCallback cb = ^(UIImage *m) {
                        
                        CGImageRef im = m.CGImage;
                        
                        kk::Strong s = * v;
                        
                        BK_CTX
                        BK_WEAK(image, s.get())
                        
                        if(im) {
                            CGImageRetain(im);
                            BK_PTR(CGImage, im, CGImageRelease)
                        }
                        
                        queue->async(OSImage_loadDispatchFunc, BK_ARG);
                        
                        if(s.get() != nullptr) {
                            s.get()->unWeak((kk::Object **) v);
                        }
                        
                        free(v);
                        
                    };
                    
                    if(![KKHttp imageWithURL:url callback:cb]) {
                        
                        KKHttpOptions * options = [[KKHttpOptions alloc] initWithURL:url];
                        
                        options.method = @"GET";
                        options.type = KKHttpOptionsTypeImage;
                        
                        options.onload = ^(id data, NSError *error, id weakObject) {
                            if(error != nil) {
                                NSLog(@"[KK] [CG] [IMAGE] [ERROR] %@",error);
                            }
                            cb((UIImage *) data);
                        };
                        
                        options.onfail = ^(NSError *error, id weakObject) {
                            NSLog(@"[KK] [CG] [IMAGE] [ERROR] %@",error);
                            cb(nil);
                        };
                        
                        [[KKHttp main] send:options weakObject:nil];
                        
                    }
                    
                }
                
            } else {
                
                kk::String b = image->basePath();
                
                if(b == "") {
                    b = "./";
                } else if(!kk::CStringHasSuffix(b.c_str(), "/")) {
                    b.append("/");
                }
                
                b.append(image->src());
                
                kk::DispatchQueue * queue = kk::DispatchQueue::current();
                
                @autoreleasepool {
                    
                    OSImage ** v = (OSImage **) malloc(sizeof(OSImage *));
                    
                    image->weak((kk::Object **) v);
                    
                    *v = image;
                    
                    NSString * path = [NSString stringWithCString:b.c_str() encoding:NSUTF8StringEncoding];
                    
                    dispatch_async(KKHttpIODispatchQueue(), ^{
                        
                        UIImage * m = [UIImage kk_imageWithPath:path];
                        
                        CGImageRef im = m.CGImage;
                        
                        kk::Strong s = * v;
                        
                        BK_CTX
                        BK_RETAIN(image, s.get())
                        
                        if(im) {
                            CGImageRetain(im);
                            BK_PTR(CGImage, im, CGImageRelease)
                        }
                        
                        queue->async(OSImage_loadDispatchFunc, BK_ARG);
                        
                        if(s.get() != nullptr) {
                            s.get()->unWeak((kk::Object **) v);
                        }
                        
                        free(v);
                        
                    });
                    
                    
                }
                
            }
            
        }
        
    }
    
}

