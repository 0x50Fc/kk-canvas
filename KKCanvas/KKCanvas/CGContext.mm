//
//  CGContext.m
//  KKCanvas
//
//  Created by hailong11 on 2018/9/27.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#import <UIKit/UIKit.h>

#include "kk-config.h"
#include "CGContext.h"

namespace kk {
    
    namespace CG {
        
        IMP_SCRIPT_CLASS_BEGIN_NOALLOC(&Context::ScriptClass, OSContext, CGOSContext)
        
        IMP_SCRIPT_CLASS_END
        
        OSContext::OSContext(Uint width,Uint height):Context(width,height){
            CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
            _ctx = CGBitmapContextCreate(NULL, width, height, 8, width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
            CGContextTranslateCTM(_ctx, 0, height);
            CGContextScaleCTM(_ctx, 1, -1);
            CGColorSpaceRelease(rgbSpace);
        }
        
        OSContext::~OSContext() {
            CGContextRelease(_ctx);
        }
        
        Ubyte * OSContext::getContextData() {
            return (Ubyte *) CGBitmapContextGetData(_ctx);
        }
        
        void OSContext::save() {
            CGContextSaveGState(_ctx);
        }
        
        void OSContext::restore() {
            CGContextRestoreGState(_ctx);
        }
        
        void OSContext::rect(Float x, Float y,Float width,Float height) {
            CGContextAddRect(_ctx, CGRectMake(x, y, width, height));
        }
        
        void OSContext::fillRect(Float x, Float y,Float width,Float height) {
            Context::fillRect(x, y, width, height);
        }
        
        void OSContext::strokeRect(Float x, Float y,Float width,Float height) {
            Context::strokeRect(x, y, width, height);
        }
        
        void OSContext::clearRect(Float x, Float y,Float width,Float height) {
            CGContextClearRect(_ctx, CGRectMake(x, y, width, height));
        }
        
        void OSContext::fill() {
            
            {
                LinearGradient * v = _fillStyle.as<LinearGradient>();
                
                if(v) {
                    
                    CGGradientRef gradient = v->createCGGradient();
                    
                    CGContextClip(_ctx);
                    
                    CGContextDrawLinearGradient(_ctx, gradient, v->startPoint(), v->endPoint(), kCGGradientDrawsBeforeStartLocation);
                    
                    
                    CGGradientRelease(gradient);
                    
                    return;
                }
            }
            
            {
                RadialGradient * v = _fillStyle.as<RadialGradient>();
                
                if(v) {
                    
                    CGGradientRef gradient = v->createCGGradient();
                    
                    CGContextClip(_ctx);
                    
                    CGContextDrawRadialGradient(_ctx, gradient, v->startCenter(), v->startRadius(), v->endCenter(), v->endRadius(), kCGGradientDrawsBeforeStartLocation);
                    
                    CGGradientRelease(gradient);
                    
                    return;
                }
            }
            
            CGContextDrawPath(_ctx, kCGPathFill);
        }
        
        void OSContext::stroke() {
            
            {
                LinearGradient * v = _strokeStyle.as<LinearGradient>();

                if(v) {

                    CGGradientRef gradient = v->createCGGradient();

                    CGPathRef path = CGContextCopyPath(_ctx);
                    
                    CGRect r = CGPathGetBoundingBox(path);
                    
                    size_t width = (size_t) ceil(r.size.width);
                    size_t height = (size_t) ceil(r.size.height);
                    
                    CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
                    
                    CGContextRef c = CGBitmapContextCreate(NULL, width, height, 8, width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
                    CGContextTranslateCTM(c, 0, height);
                    CGContextScaleCTM(c, 1, -1);
                    CGColorSpaceRelease(rgbSpace);
                    
                    CGContextTranslateCTM(c, - r.origin.x, - r.origin.y);
                    
                    CGContextAddPath(c, path);
                    
                    CGContextSetLineWidth(c, _lineWidth);
                    CGContextSetRGBStrokeColor(c, 0, 0, 0, 1);
                    CGContextDrawPath(c, kCGPathStroke);
                    
                    CGImageRef image = CGBitmapContextCreateImage(c);
                    
                    CGContextRelease(c);
                    CGPathRelease(path);
                
                
                    CGContextClipToMask(_ctx, r, image);
                    
                    CGContextDrawLinearGradient(_ctx, gradient, v->startPoint(), v->endPoint(), kCGGradientDrawsBeforeStartLocation);

                    CGGradientRelease(gradient);
                    
                    CGImageRelease(image);
                    
                    return;
                }
            }

            {
                RadialGradient * v = _strokeStyle.as<RadialGradient>();

                if(v) {

                    CGGradientRef gradient = v->createCGGradient();

                    CGPathRef path = CGContextCopyPath(_ctx);
                    
                    CGRect r = CGPathGetBoundingBox(path);
                    
                    size_t width = (size_t) ceil(r.size.width);
                    size_t height = (size_t) ceil(r.size.height);
                    
                    CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
                    
                    CGContextRef c = CGBitmapContextCreate(NULL, width, height, 8, width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
                    CGContextTranslateCTM(c, 0, height);
                    CGContextScaleCTM(c, 1, -1);
                    CGColorSpaceRelease(rgbSpace);
                    
                    CGContextTranslateCTM(c, - r.origin.x, - r.origin.y);
                    
                    CGContextAddPath(c, path);
                    
                    CGContextSetLineWidth(c, _lineWidth);
                    CGContextSetRGBStrokeColor(c, 0, 0, 0, 1);
                    CGContextDrawPath(c, kCGPathStroke);
                    
                    CGImageRef image = CGBitmapContextCreateImage(c);
                    
                    CGContextRelease(c);
                    CGPathRelease(path);
                    
                    CGContextClipToMask(_ctx, r, image);

                    CGContextDrawRadialGradient(_ctx, gradient, v->startCenter(), v->startRadius(), v->endCenter(), v->endRadius(), kCGGradientDrawsBeforeStartLocation);

                    CGGradientRelease(gradient);

                    CGImageRelease(image);
                    
                    return;
                }
            }

            CGContextDrawPath(_ctx, kCGPathStroke);
        }
        
        void OSContext::beginPath() {
            CGContextBeginPath(_ctx);
        }
        
        void OSContext::closePath() {
            CGContextClosePath(_ctx);
        }
        
        void OSContext::moveTo(Float x,Float y) {
            CGContextMoveToPoint(_ctx, x, y);
        }
        
        void OSContext::lineTo(Float x,Float y) {
            CGContextAddLineToPoint(_ctx,x, y);
        }
        
        void OSContext::clip() {
            CGContextClip(_ctx);
        }
        
        void OSContext::quadraticCurveTo(Float cpx,Float cpy,Float x,Float y) {
            CGContextAddQuadCurveToPoint(_ctx, cpx, cpy, x, y);
        }
        
        void OSContext::bezierCurveTo(Float cp1x,Float cp1y,Float cp2x,Float cp2y,Float x,Float y) {
            CGContextAddCurveToPoint(_ctx, cp1x, cp1y, cp2x, cp2y, x, y);
        }
        
        void OSContext::arc(Float x,Float y,Float r, Float sAngle,Float eAngle,Boolean counterclockwise) {
            CGContextAddArc(_ctx, x, y, r, sAngle, eAngle, counterclockwise ? 1 : 0);
        }
        
        void OSContext::arcTo(Float x1,Float y1,Float x2,Float y2,Float r) {
            CGContextAddArcToPoint(_ctx, x1, y1, x2, y2, r);
        }
        
        Boolean OSContext::isPointInPath(Float x,Float y) {
            return CGContextPathContainsPoint(_ctx, CGPointMake(x, y), kCGPathFillStroke);
        }
        
        void OSContext::scale(Float sx,Float sy) {
            CGContextScaleCTM(_ctx, sx, sy);
        }
        
        void OSContext::rotate(Float angle) {
            CGContextRotateCTM(_ctx, angle);
        }
        
        void OSContext::translate(Float dx,Float dy) {
            CGContextTranslateCTM(_ctx, dx, dy);
        }
        
        void OSContext::transform(Float a,Float b,Float c,Float d,Float e,Float f) {
            CGContextConcatCTM(_ctx, CGAffineTransformMake(a, b, c, d, e, f));
        }
        
        void OSContext::setTransform(Float a,Float b,Float c,Float d,Float e,Float f) {
            CGAffineTransform v = CGContextGetCTM(_ctx);
            v = CGAffineTransformInvert(v);
            v = CGAffineTransformConcat(v, CGAffineTransformMake(a, b, c, d, e, f));
            CGContextConcatCTM(_ctx, v);
        }
        
        Float GetAttributeStringBaseline(NSDictionary * attributes,Context * ctx) {
            
            UIFont * font = [attributes valueForKey:NSFontAttributeName];
            
            if(font) {
                switch (ctx->textBaseline()) {
                    case TextBaselineAlphabetic:
                        return -font.ascender;
                        break;
                    case TextBaselineBottom:
                        return -font.lineHeight;
                        break;
                    case TextBaselineMiddle:
                        return -font.lineHeight * 0.5;
                        break;
                    case TextBaselineHanging:
                        return font.descender;
                        break;
                    case TextBaselineIdeographic:
                        return - font.ascender - font.leading;
                    default:
                        break;
                }
            }
            
            return 0;
        };
        
        NSMutableDictionary *CreateAttributeStringAttributes(Context * ctx) {
            
            NSMutableDictionary * attributes = [NSMutableDictionary dictionaryWithCapacity: 4];
            
            {
                UIFont * v = nil;
                Font font = ctx->font();
                
                if(font.family != "") {
                    
                    NSString * name = nil;
                    NSArray * fontNames = [UIFont fontNamesForFamilyName:[NSString stringWithCString:font.family.c_str() encoding:NSUTF8StringEncoding]];
                    
                    for(NSString * fontName in fontNames) {
                        
                        if(font.style == FontStyleItalic) {
                            if([fontName hasSuffix:@"Italic"]) {
                                name = fontName;
                                break;
                            }
                        } else if(font.weight == FontWeightBold) {
                            if([fontName hasSuffix:@"Bold"]) {
                                name = fontName;
                                break;
                            }
                        } else {
                            name = fontName;
                            break;
                        }
                    }
                    
                    if(name == nil && [fontNames count] > 0) {
                        name = [fontNames objectAtIndex:0];
                    }
                    
                    if(name) {
                        v = [UIFont fontWithName:name size:font.size];
                    }
                }
                
                if(v == nil) {
                    if(font.style == FontStyleItalic) {
                        v = [UIFont italicSystemFontOfSize:font.size];
                    } else if(font.weight == FontWeightBold) {
                        v = [UIFont boldSystemFontOfSize:font.size];
                    } else {
                        v = [UIFont systemFontOfSize:font.size];
                    }
                }
                
                attributes[NSFontAttributeName] = v;
                
            }
            
            
            return attributes;
        }

        
        void OSContext::fillText(kk::CString text,Float x,Float y,Float maxWidth) {
            
            if(text == nullptr) {
                return ;
            }
            
            {
                LinearGradient * v = _fillStyle.as<LinearGradient>();
                
                if(v) {
                    
                    @autoreleasepool {
                        
                        CGGradientRef gradient = v->createCGGradient();
                        
                        NSMutableDictionary * attributes = CreateAttributeStringAttributes(this);
                        
                        NSAttributedString * string = [[NSAttributedString alloc] initWithString:[NSString stringWithCString:text encoding:NSUTF8StringEncoding] attributes:attributes];
                        
                        CGRect r = [string boundingRectWithSize:CGSizeMake(maxWidth > 0 ?maxWidth: MAXFLOAT, MAXFLOAT)
                                                        options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                        
                        size_t width = (size_t) ceil(r.size.width);
                        size_t height = (size_t) ceil(r.size.height);
                        
                        CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
                        CGContextRef c = CGBitmapContextCreate(NULL, width, height, 8, width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
                        CGColorSpaceRelease(rgbSpace);
                        
                        UIGraphicsPushContext(c);
                        
                        [string drawWithRect:r options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                        
                        UIGraphicsPopContext();
                        
                        CGImageRef image = CGBitmapContextCreateImage(c);
                        
                        CGContextRelease(c);
                        
                        r.origin.x = x;
                        r.origin.y = y;
                        
                        switch (_textAlign) {
                            case TextAlignEnd:
                            case TextAlignRight:
                                r.origin.x = x - r.size.width;
                                break;
                            case TextAlignCenter:
                                r.origin.x = x - r.size.width * 0.5f;
                                break;
                            default:
                                break;
                        }
                        
                        r.origin.y += GetAttributeStringBaseline(attributes,this);
                        
                        CGContextClipToMask(_ctx, r, image);
                        
                        CGContextDrawLinearGradient(_ctx, gradient, v->startPoint(), v->endPoint(), kCGGradientDrawsBeforeStartLocation);
                        
                        CGGradientRelease(gradient);
                        
                        CGImageRelease(image);
                        
                    }
                    
                    return;
                }
            }
            
            {
                RadialGradient * v = _strokeStyle.as<RadialGradient>();
                
                if(v) {
                    
                    @autoreleasepool {
                        
                        CGGradientRef gradient = v->createCGGradient();
                        
                        NSMutableDictionary * attributes = CreateAttributeStringAttributes(this);
                        
                        NSAttributedString * string = [[NSAttributedString alloc] initWithString:[NSString stringWithCString:text encoding:NSUTF8StringEncoding] attributes:attributes];
                        
                        CGRect r = [string boundingRectWithSize:CGSizeMake(maxWidth > 0 ?maxWidth: MAXFLOAT, MAXFLOAT)
                                                        options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                        
                        size_t width = (size_t) ceil(r.size.width);
                        size_t height = (size_t) ceil(r.size.height);
                        
                        CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
                        CGContextRef c = CGBitmapContextCreate(NULL, width, height, 8, width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
                        CGColorSpaceRelease(rgbSpace);
                        
                        UIGraphicsPushContext(c);
                        
                        [string drawWithRect:r options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                        
                        UIGraphicsPopContext();
                        
                        CGImageRef image = CGBitmapContextCreateImage(c);
                        
                        CGContextRelease(c);
                        
                        r.origin.x = x;
                        r.origin.y = y;
                        
                        switch (_textAlign) {
                            case TextAlignEnd:
                            case TextAlignRight:
                                r.origin.x = x - r.size.width;
                                break;
                            case TextAlignCenter:
                                r.origin.x = x - r.size.width * 0.5f;
                                break;
                            default:
                                break;
                        }
                        
                        r.origin.y += GetAttributeStringBaseline(attributes,this);
                        
                        CGContextClipToMask(_ctx, r, image);
                        
                        CGContextDrawRadialGradient(_ctx, gradient, v->startCenter(), v->startRadius(), v->endCenter(), v->endRadius(), kCGGradientDrawsBeforeStartLocation);
                        
                        CGGradientRelease(gradient);
                        
                        CGImageRelease(image);
                        
                    }
                    
                    return;
                }
            }
            
            @autoreleasepool {
                
                NSMutableDictionary * attributes = CreateAttributeStringAttributes(this);
                
                attributes[NSForegroundColorAttributeName] = [UIColor colorWithRed:_fillColor.r green:_fillColor.g blue:_fillColor.b alpha:_fillColor.a];
                
                NSAttributedString * string = [[NSAttributedString alloc] initWithString:[NSString stringWithCString:text encoding:NSUTF8StringEncoding] attributes:attributes];
                
                CGRect r = [string boundingRectWithSize:CGSizeMake(MAXFLOAT, MAXFLOAT) options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                
                r.origin.x = x;
                r.origin.y = y;
                
                switch (_textAlign) {
                    case TextAlignEnd:
                    case TextAlignRight:
                        r.origin.x = x - r.size.width;
                        break;
                    case TextAlignCenter:
                        r.origin.x = x - r.size.width * 0.5f;
                        break;
                    default:
                        break;
                }
                
                r.origin.y += GetAttributeStringBaseline(attributes,this);
                
                UIGraphicsPushContext(_ctx);
                
                [string drawWithRect:r options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                
                UIGraphicsPopContext();
                
            }
            
        }
        
        void OSContext::strokeText(kk::CString text,Float x,Float y,Float maxWidth) {
            
            if(text == nullptr) {
                return ;
            }
            
            {
                LinearGradient * v = _strokeStyle.as<LinearGradient>();
                
                if(v) {
                    
                    @autoreleasepool {
                        
                        CGGradientRef gradient = v->createCGGradient();
                        
                        NSMutableDictionary * attributes = CreateAttributeStringAttributes(this);
                        
                        attributes[NSStrokeColorAttributeName] = [UIColor blackColor];
                        attributes[NSStrokeWidthAttributeName] = @(_lineWidth);
                        
                        NSAttributedString * string = [[NSAttributedString alloc] initWithString:[NSString stringWithCString:text encoding:NSUTF8StringEncoding] attributes:attributes];
                        
                        CGRect r = [string boundingRectWithSize:CGSizeMake(maxWidth > 0 ?maxWidth: MAXFLOAT, MAXFLOAT)
                                                        options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                        
                        size_t width = (size_t) ceil(r.size.width);
                        size_t height = (size_t) ceil(r.size.height);
                        
                        CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
                        CGContextRef c = CGBitmapContextCreate(NULL, width, height, 8, width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
                        CGColorSpaceRelease(rgbSpace);
                        
                        UIGraphicsPushContext(c);
                        
                        [string drawWithRect:r options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                        
                        UIGraphicsPopContext();
                        
                        CGImageRef image = CGBitmapContextCreateImage(c);
                        
                        CGContextRelease(c);
                        
                        r.origin.x = x;
                        r.origin.y = y;
                        
                        switch (_textAlign) {
                            case TextAlignEnd:
                            case TextAlignRight:
                                r.origin.x = x - r.size.width;
                                break;
                            case TextAlignCenter:
                                r.origin.x = x - r.size.width * 0.5f;
                                break;
                            default:
                                break;
                        }
                        
                        r.origin.y += GetAttributeStringBaseline(attributes,this);
                        
                        CGContextClipToMask(_ctx, r, image);
                        
                        CGContextDrawLinearGradient(_ctx, gradient, v->startPoint(), v->endPoint(), kCGGradientDrawsBeforeStartLocation);
                        
                        CGGradientRelease(gradient);
                        
                        CGImageRelease(image);
                        
                    }
                    
                    return;
                }
            }
            
            {
                RadialGradient * v = _strokeStyle.as<RadialGradient>();
                
                if(v) {
                    
                    @autoreleasepool {
                        
                        CGGradientRef gradient = v->createCGGradient();
                        
                        NSMutableDictionary * attributes = CreateAttributeStringAttributes(this);
                        
                        attributes[NSStrokeColorAttributeName] = [UIColor blackColor];
                        attributes[NSStrokeWidthAttributeName] = @(_lineWidth);
                        
                        NSAttributedString * string = [[NSAttributedString alloc] initWithString:[NSString stringWithCString:text encoding:NSUTF8StringEncoding] attributes:attributes];
                        
                        CGRect r = [string boundingRectWithSize:CGSizeMake(maxWidth > 0 ?maxWidth: MAXFLOAT, MAXFLOAT)
                                                        options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                        
                        size_t width = (size_t) ceil(r.size.width);
                        size_t height = (size_t) ceil(r.size.height);
                        
                        CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
                        CGContextRef c = CGBitmapContextCreate(NULL, width, height, 8, width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
                        CGColorSpaceRelease(rgbSpace);
                        
                        UIGraphicsPushContext(c);
                        
                        [string drawWithRect:r options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                        
                        UIGraphicsPopContext();
                        
                        CGImageRef image = CGBitmapContextCreateImage(c);
                        
                        CGContextRelease(c);
                        
                        r.origin.x = x;
                        r.origin.y = y;
                        
                        switch (_textAlign) {
                            case TextAlignEnd:
                            case TextAlignRight:
                                r.origin.x = x - r.size.width;
                                break;
                            case TextAlignCenter:
                                r.origin.x = x - r.size.width * 0.5f;
                                break;
                            default:
                                break;
                        }
                        
                        r.origin.y += GetAttributeStringBaseline(attributes,this);
                        
                        CGContextClipToMask(_ctx, r, image);
                        
                        CGContextDrawRadialGradient(_ctx, gradient, v->startCenter(), v->startRadius(), v->endCenter(), v->endRadius(), kCGGradientDrawsBeforeStartLocation);
                        
                        CGGradientRelease(gradient);
                        
                        CGImageRelease(image);
                        
                    }
                    
                    return;
                }
            }
            
            @autoreleasepool {
                
                NSMutableDictionary * attributes = CreateAttributeStringAttributes(this);
                
                attributes[NSStrokeColorAttributeName] = [UIColor colorWithRed:_strokeColor.r green:_strokeColor.g blue:_strokeColor.b alpha:_strokeColor.a];
                
                attributes[NSStrokeWidthAttributeName] = @(_lineWidth);
                
                NSAttributedString * string = [[NSAttributedString alloc] initWithString:[NSString stringWithCString:text encoding:NSUTF8StringEncoding] attributes:attributes];
                
                CGRect r = [string boundingRectWithSize:CGSizeMake(maxWidth > 0 ?maxWidth: MAXFLOAT, MAXFLOAT)
                                                options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                
                r.origin.x = x;
                r.origin.y = y;
                
                switch (_textAlign) {
                    case TextAlignEnd:
                    case TextAlignRight:
                        r.origin.x = x - r.size.width;
                        break;
                    case TextAlignCenter:
                        r.origin.x = x - r.size.width * 0.5f;
                        break;
                    default:
                        break;
                }
                
                r.origin.y += GetAttributeStringBaseline(attributes,this);
                
                UIGraphicsPushContext(_ctx);
                
                [string drawWithRect:r options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                
                UIGraphicsPopContext();
                
            }
            
        }
        
        Float OSContext::measureText(kk::CString text) {
            
            if(text == nullptr) {
                return 0.0f;
            }
            
            CGRect r = CGRectZero;
            
            @autoreleasepool {
                
                NSMutableDictionary * attributes = CreateAttributeStringAttributes(this);
                
                NSAttributedString * string = [[NSAttributedString alloc] initWithString:[NSString stringWithCString:text encoding:NSUTF8StringEncoding] attributes:attributes];
                
                r = [string boundingRectWithSize:CGSizeMake(MAXFLOAT, MAXFLOAT) options:NSStringDrawingUsesLineFragmentOrigin context:nil];
                
            }
            
            return r.size.width;
        }
        
        void OSContext::drawImage(Image * image,Float sx,Float sy,Float swidth,Float sheight,Float x,Float y,Float width,Float height) {
            
            if(image == nullptr) {
                return;
            }
            
            CGImageRef CGImage = image->CGImage();
            
            if(CGImage == nil) {
                return;
            }
            
            CGContextSaveGState(_ctx);
            
            if(swidth >0 && sheight > 0) {
                
                if(width <= 0) {
                    width = swidth;
                }
                
                if(height <= 0) {
                    height = sheight;
                }
                
                CGContextClipToRect(_ctx, CGRectMake(x, y, width, height));
                
                CGContextDrawImage(_ctx, CGRectMake(-sx, -sy, CGImageGetWidth(CGImage), CGImageGetHeight(CGImage)), CGImage);
                
            } else {
                
                if(width <= 0) {
                    width = CGImageGetWidth(CGImage);
                }
                
                if(height <= 0) {
                    height = CGImageGetHeight(CGImage);
                }
                
                CGContextDrawImage(_ctx, CGRectMake(x, y, width, height), CGImage);
            }
            
            CGContextRestoreGState(_ctx);
            
        }
        
        static void OSContext_CGPatternDrawPatternCallback(void * info,
                                                           CGContextRef ctx) {
            Pattern * p = (Pattern *) info;
            
            Image * image = p->image();
            
            if(image) {
                
                CGImageRef CGImage = image->CGImage();
                
                if(CGImage) {
                    CGContextDrawImage(ctx, CGRectMake(0, 0, image->width(), image->height()), CGImage);
                }
            }
        }
        
        static void OSContext_CGPatternReleaseInfoCallback(void * info) {
            Pattern * p = (Pattern *) info;
            p->release();
        }

        void OSContext::setFillStyle(Style * v) {
            Context::setFillStyle(v);
            
            Pattern * p = dynamic_cast<Pattern *>(v);
            
            if(p) {
                
                Image * image = p->image();
                
                CGPatternCallbacks cb = {0,OSContext_CGPatternDrawPatternCallback,OSContext_CGPatternReleaseInfoCallback};
                
                CGPatternRef vv = CGPatternCreate(p, CGRectMake(0, 0, image->width(), image->height()), CGAffineTransformIdentity, image->width(), image->height(), kCGPatternTilingNoDistortion, false, &cb);
                
                p->retain();
                
                CGContextSetFillPattern(_ctx, vv, nil);
                
                CGPatternRelease(vv);
            }
        
        }
        
        void OSContext::setFillColor(Color v) {
            Context::setFillColor(v);
            CGContextSetRGBFillColor(_ctx, v.r, v.g, v.b, v.a);
        }
        
        void OSContext::setStrokeStyle(Style * v) {
            Context::setStrokeStyle(v);
            
            Pattern * p = dynamic_cast<Pattern *>(v);
            
            if(p) {
                Image * image = p->image();
                
                CGPatternCallbacks cb = {0,OSContext_CGPatternDrawPatternCallback,OSContext_CGPatternReleaseInfoCallback};
                
                CGPatternRef vv = CGPatternCreate(p, CGRectMake(0, 0, image->width(), image->height()), CGAffineTransformIdentity, image->width(), image->height(), kCGPatternTilingNoDistortion, false, &cb);
                
                p->retain();
                
                CGContextSetStrokePattern(_ctx, vv, nil);
                
                CGPatternRelease(vv);
            }
        }
        
        void OSContext::setStrokeColor(Color v) {
            Context::setStrokeColor(v);
            CGContextSetRGBStrokeColor(_ctx, v.r, v.g, v.b, v.a);
        }
        
        void OSContext::setShadowColor(Color v) {
            Context::setShadowColor(v);
            @autoreleasepool {
                UIColor * vv = [UIColor colorWithRed:_shadowColor.r green:_shadowColor.g blue:_shadowColor.b alpha:_shadowColor.a];
                CGContextSetShadowWithColor(_ctx, CGSizeMake(_shadowOffsetX, _shadowOffsetY), _shadowBlur, vv.CGColor);
            }
            
        }
        
        void OSContext::setShadowBlur(Float v) {
            Context::setShadowBlur(v);
            @autoreleasepool {
                UIColor * vv = [UIColor colorWithRed:_shadowColor.r green:_shadowColor.g blue:_shadowColor.b alpha:_shadowColor.a];
                CGContextSetShadowWithColor(_ctx, CGSizeMake(_shadowOffsetX, _shadowOffsetY), _shadowBlur, vv.CGColor);
            }
        }
        
        void OSContext::setShadowOffsetX(Float v) {
            Context::setShadowOffsetX(v);
            @autoreleasepool {
                UIColor * vv = [UIColor colorWithRed:_shadowColor.r green:_shadowColor.g blue:_shadowColor.b alpha:_shadowColor.a];
                CGContextSetShadowWithColor(_ctx, CGSizeMake(_shadowOffsetX, _shadowOffsetY), _shadowBlur, vv.CGColor);
            }
        }
        
        void OSContext::setShadowOffsetY(Float v) {
            Context::setShadowOffsetY(v);
            @autoreleasepool {
                UIColor * vv = [UIColor colorWithRed:_shadowColor.r green:_shadowColor.g blue:_shadowColor.b alpha:_shadowColor.a];
                CGContextSetShadowWithColor(_ctx, CGSizeMake(_shadowOffsetX, _shadowOffsetY), _shadowBlur, vv.CGColor);
            }
        }
        
        void OSContext::setLineCap(LineCapType v) {
            Context::setLineCap(v);
            CGContextSetLineCap(_ctx, (CGLineCap) v);
        }
        
        void OSContext::setLineJoin(LineJoinType v) {
            Context::setLineJoin(v);
            CGContextSetLineJoin(_ctx, (CGLineJoin)v);
        }
        
        void OSContext::setLineWidth(Float v) {
            Context::setLineWidth(v);
            CGContextSetLineWidth(_ctx, v);
        }
        
        void OSContext::setMiterLimit(Float v) {
            Context::setMiterLimit(v);
            CGContextSetMiterLimit(_ctx, v);
        }
        
        void OSContext::setFont(Font v) {
            Context::setFont(v);
        }
        
        void OSContext::setTextAlign(TextAlign v) {
            Context::setTextAlign(v);
        }
        
        void OSContext::setTextBaseline(TextBaseline v) {
            Context::setTextBaseline(v);
        }
        
        void OSContext::setGlobalAlpha(Float v) {
            Context::setGlobalAlpha(v);
            CGContextSetAlpha(_ctx, v);
        }
        
        void OSContext::setGlobalCompositeOperation(GlobalCompositeOperation v) {
            Context::setGlobalCompositeOperation(v);
        }
        
        
        CGImageRef OSContext::createCGImage() {
            return CGBitmapContextCreateImage(_ctx);
        }
        
        ImageData::ImageData(Uint width,Uint height):_CGImage(nil),_width(width),_height(height) {
            Uint size = width * height * 4;
            _data = (Ubyte *) malloc(size);
            memset(_data, 0, size);
        }
        
        ImageData::~ImageData() {
            free(_data);
            if(_CGImage != nil) {
                CGImageRelease(_CGImage);
            }
        }
        
        CGImageRef ImageData::CGImage() {
            if(_CGImage == nil) {
                CGColorSpaceRef rgbSpace = CGColorSpaceCreateDeviceRGB();
                CGContextRef ctx = CGBitmapContextCreate(_data, _width, _height, 8, _width * 4, rgbSpace, kCGImageAlphaPremultipliedLast);
                _CGImage = CGBitmapContextCreateImage(ctx);
                CGColorSpaceRelease(rgbSpace);
                CGContextRelease(ctx);
            }
            return _CGImage;
        }
        
        CGGradientRef Gradient::createCGGradient() {
            
            CGColorSpaceRef space = CGColorSpaceCreateDeviceRGB();
            
            CGGradientRef v= CGGradientCreateWithColorComponents(space, (CGFloat *) _colors.data(), (CGFloat *) _locations.data(), _colors.size());
            
            CGColorSpaceRelease(space);
            
            return v;
            
        }
        
        CGPoint LinearGradient::startPoint() {
            return CGPointMake(_x0, _y0);
        }
        
        CGPoint LinearGradient::endPoint() {
            return CGPointMake(_x1, _y1);
        }
        
        CGPoint RadialGradient::startCenter() {
            return CGPointMake(_x0, _y0);
        }
        
        CGFloat RadialGradient::startRadius() {
            return _r0;
        }
        
        CGPoint RadialGradient::endCenter() {
            return CGPointMake(_x1, _y1);
        }
        
        CGFloat RadialGradient::endRadius() {
            return _r1;
        }
        
    }
    
}


