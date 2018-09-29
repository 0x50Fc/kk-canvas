//
//  CGContextJS.cc
//  KKCanvas
//
//  Created by zhanghailong on 2018/9/27.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//


#include "kk-config.h"
#include "CGContext.h"

namespace kk {
    
    namespace CG {
        
        IMP_SCRIPT_CLASS_BEGIN_NOALLOC(nullptr, Context, CGContext)
        
        static kk::script::Property propertys[] = {
            IMP_SCRIPT_PROPERTY(Context,fillStyle,FillStyle)
            IMP_SCRIPT_PROPERTY(Context,strokeStyle,StrokeStyle)
            IMP_SCRIPT_PROPERTY(Context,shadowColor,ShadowColor)
            IMP_SCRIPT_PROPERTY(Context,shadowBlur,ShadowBlur)
            IMP_SCRIPT_PROPERTY(Context,shadowOffsetX,ShadowOffsetX)
            IMP_SCRIPT_PROPERTY(Context,shadowOffsetY,ShadowOffsetY)
            IMP_SCRIPT_PROPERTY(Context,lineCap,LineCap)
            IMP_SCRIPT_PROPERTY(Context,lineJoin,LineJoin)
            IMP_SCRIPT_PROPERTY(Context,lineWidth,LineWidth)
            IMP_SCRIPT_PROPERTY(Context,miterLimit,MiterLimit)
            IMP_SCRIPT_PROPERTY(Context,font,Font)
            IMP_SCRIPT_PROPERTY(Context,textAlign,TextAlign)
            IMP_SCRIPT_PROPERTY(Context,textBaseline,TextBaseline)
            IMP_SCRIPT_PROPERTY(Context,globalAlpha,GlobalAlpha)
            IMP_SCRIPT_PROPERTY(Context,globalCompositeOperation,GlobalCompositeOperation)
            IMP_SCRIPT_PROPERTY_READONLY(Context,width)
            IMP_SCRIPT_PROPERTY_READONLY(Context,height)
        };
        
        kk::script::SetProperty(ctx, -1, propertys, sizeof(propertys) / sizeof(kk::script::Property));
        
        static kk::script::Method methods[] = {
            IMP_SCRIPT_METHOD(Context,createLinearGradient)
            IMP_SCRIPT_METHOD(Context,createRadialGradient)
            IMP_SCRIPT_METHOD(Context,createPattern)
            IMP_SCRIPT_METHOD(Context,createImageData)
            IMP_SCRIPT_METHOD(Context,getImageData)
            IMP_SCRIPT_METHOD(Context,putImageData)
            IMP_SCRIPT_METHOD(Context,save)
            IMP_SCRIPT_METHOD(Context,restore)
            IMP_SCRIPT_METHOD(Context,rect)
            IMP_SCRIPT_METHOD(Context,fillRect)
            IMP_SCRIPT_METHOD(Context,strokeRect)
            IMP_SCRIPT_METHOD(Context,clearRect)
            IMP_SCRIPT_METHOD(Context,fill)
            IMP_SCRIPT_METHOD(Context,stroke)
            IMP_SCRIPT_METHOD(Context,beginPath)
            IMP_SCRIPT_METHOD(Context,moveTo)
            IMP_SCRIPT_METHOD(Context,closePath)
            IMP_SCRIPT_METHOD(Context,lineTo)
            IMP_SCRIPT_METHOD(Context,clip)
            IMP_SCRIPT_METHOD(Context,quadraticCurveTo)
            IMP_SCRIPT_METHOD(Context,bezierCurveTo)
            IMP_SCRIPT_METHOD(Context,arc)
            IMP_SCRIPT_METHOD(Context,arcTo)
            IMP_SCRIPT_METHOD(Context,isPointInPath)
            IMP_SCRIPT_METHOD(Context,scale)
            IMP_SCRIPT_METHOD(Context,rotate)
            IMP_SCRIPT_METHOD(Context,translate)
            IMP_SCRIPT_METHOD(Context,transform)
            IMP_SCRIPT_METHOD(Context,setTransform)
            IMP_SCRIPT_METHOD(Context,fillText)
            IMP_SCRIPT_METHOD(Context,strokeText)
            IMP_SCRIPT_METHOD(Context,measureText)
            IMP_SCRIPT_METHOD(Context,drawImage)
        };
        
        kk::script::SetMethod(ctx, -1, methods, sizeof(methods) / sizeof(kk::script::Method));
        
        
        IMP_SCRIPT_CLASS_END
        
        
        duk_ret_t Context::duk_fillStyle(duk_context *ctx) {
            
            Style * v = fillStyle();
            
            if(v != nullptr) {
                kk::script::PushObject(ctx, v);
                return 1;
            }
            
            kk::String s = StringFromColor(fillColor());
            
            duk_push_string(ctx, s.c_str());
            
            return 1;
        }
        
        duk_ret_t Context::duk_setFillStyle(duk_context *ctx) {
            
            Style * vStyle = nullptr;
            kk::CString vColor = nullptr;
            
            int top = duk_get_top(ctx);
            
            if(top > 0) {
                if(duk_is_object(ctx, -top)) {
                    vStyle = dynamic_cast<Style *>(kk::script::GetObject(ctx, -top));
                } else if(duk_is_string(ctx, -top)) {
                    vColor = duk_to_string(ctx, -top);
                }
            }
            
            setFillStyle(vStyle);
            setFillColor(ColorFromString(vColor));
            
            return 0;
        }
        
        duk_ret_t Context::duk_strokeStyle(duk_context *ctx) {
            
            Style * v = strokeStyle();
            
            if(v != nullptr) {
                kk::script::PushObject(ctx, v);
                return 1;
            }
            
            kk::String s = StringFromColor(strokeColor());
            
            duk_push_string(ctx, s.c_str());
            
            return 1;
        }
        
        duk_ret_t Context::duk_setStrokeStyle(duk_context *ctx) {
            
            Style * vStyle = nullptr;
            kk::CString vColor = nullptr;
            
            int top = duk_get_top(ctx);
            
            if(top > 0) {
                if(duk_is_object(ctx, -top)) {
                    vStyle = dynamic_cast<Style *>(kk::script::GetObject(ctx, -top));
                } else if(duk_is_string(ctx, -top)) {
                    vColor = duk_to_string(ctx, -top);
                }
            }
            
            setStrokeStyle(vStyle);
            setStrokeColor(ColorFromString(vColor));
            
            return 0;
        }
        
        duk_ret_t Context::duk_shadowColor(duk_context *ctx) {
            duk_push_string(ctx, StringFromColor(shadowColor()).c_str());
            return 1;
        }
        
        duk_ret_t Context::duk_setShadowColor(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0) {
                setShadowColor(ColorFromString(kk::script::toString(ctx, -top).c_str()));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_shadowBlur(duk_context *ctx) {
            duk_push_number(ctx, shadowBlur());
            return 1;
        }
        
        duk_ret_t Context::duk_setShadowBlur(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0) {
                setShadowBlur(kk::script::toDouble(ctx, -top));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_shadowOffsetX(duk_context *ctx) {
            duk_push_number(ctx, shadowOffsetX());
            return 1;
        }
        
        duk_ret_t Context::duk_setShadowOffsetX(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0) {
                setShadowOffsetX(kk::script::toDouble(ctx, -top));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_shadowOffsetY(duk_context *ctx) {
            duk_push_number(ctx, shadowOffsetY());
            return 1;
        }
        
        duk_ret_t Context::duk_setShadowOffsetY(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0) {
                setShadowOffsetY(kk::script::toDouble(ctx, -top));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_lineCap(duk_context *ctx) {
            duk_push_string(ctx, StringFromLineCapType(lineCap()).c_str());
            return 1;
        }
        
        duk_ret_t Context::duk_setLineCap(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0 && duk_is_string(ctx, -top)) {
                setLineCap(LineCapTypeFromString(duk_to_string(ctx, -top)));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_lineJoin(duk_context *ctx) {
            duk_push_string(ctx, StringFromLineJoinType(lineJoin()).c_str());
            return 1;
        }
        
        duk_ret_t Context::duk_setLineJoin(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0 && duk_is_string(ctx, -top)) {
                setLineJoin(LineJoinTypeFromString(duk_to_string(ctx, -top)));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_lineWidth(duk_context *ctx) {
            duk_push_number(ctx, lineWidth());
            return 1;
        }
        
        duk_ret_t Context::duk_setLineWidth(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0) {
                setLineWidth(kk::script::toDouble(ctx, -top));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_miterLimit(duk_context *ctx) {
            duk_push_number(ctx, miterLimit());
            return 1;
        }
        
        duk_ret_t Context::duk_setMiterLimit(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0) {
                setMiterLimit(kk::script::toDouble(ctx, -top));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_font(duk_context *ctx) {
            duk_push_string(ctx, StringFromFont(font()).c_str());
            return 1;
        }
        
        duk_ret_t Context::duk_setFont(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0 && duk_is_string(ctx, -top)) {
                setFont(FontFromString(duk_to_string(ctx, -top)));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_textAlign(duk_context *ctx) {
            duk_push_string(ctx, StringFromTextAlign(textAlign()).c_str());
            return 1;
        }
        
        duk_ret_t Context::duk_setTextAlign(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0 && duk_is_string(ctx, -top)) {
                setTextAlign(TextAlignFromString(duk_to_string(ctx, -top)));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_textBaseline(duk_context *ctx) {
            duk_push_string(ctx, StringFromTextBaseline(textBaseline()).c_str());
            return 1;
        }
        
        duk_ret_t Context::duk_setTextBaseline(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0 && duk_is_string(ctx, -top)) {
                setTextBaseline(TextBaselineFromString(duk_to_string(ctx, -top)));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_globalAlpha(duk_context *ctx) {
            duk_push_number(ctx, globalAlpha());
            return 1;
        }
        
        duk_ret_t Context::duk_setGlobalAlpha(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0 ) {
                setGlobalAlpha(kk::script::toDouble(ctx, -top));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_globalCompositeOperation(duk_context *ctx) {
            duk_push_string(ctx, StringFromGlobalCompositeOperation(globalCompositeOperation()).c_str());
            return 1;
        }
        
        duk_ret_t Context::duk_setGlobalCompositeOperation(duk_context *ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0 && duk_is_string(ctx, -top)) {
                setGlobalCompositeOperation(GlobalCompositeOperationFromString(duk_to_string(ctx, -top)));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_createLinearGradient(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 3) {
                kk::Strong v = createLinearGradient(
                                                    kk::script::toDouble(ctx, -top),
                                                    kk::script::toDouble(ctx, -top + 1),
                                                    kk::script::toDouble(ctx, -top + 2) ,
                                                    kk::script::toDouble(ctx, -top + 3));
                kk::script::PushObject(ctx, v.get());
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_createRadialGradient(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 5) {
                kk::Strong v = createRadialGradient(
                                                    kk::script::toDouble(ctx, -top),
                                                    kk::script::toDouble(ctx, -top + 1),
                                                    kk::script::toDouble(ctx, -top + 2),
                                                    kk::script::toDouble(ctx, -top + 3),
                                                    kk::script::toDouble(ctx, -top + 4),
                                                    kk::script::toDouble(ctx, -top + 5));
                kk::script::PushObject(ctx, v.get());
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_createPattern(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 2 && duk_is_object(ctx, -top)) {
                Image * image = dynamic_cast<Image *>(kk::script::GetObject(ctx, -top));
                if(image) {
                    kk::Strong v = createPattern(image,
                                                 PatternTypeFromString(kk::script::toString(ctx, -top + 1).c_str()));
                    kk::script::PushObject(ctx, v.get());
                    return 1;
                }
                
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_createImageData(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 1) {
                kk::Strong v = createImageData(kk::script::toDouble(ctx, -top),
                                        kk::script::toDouble(ctx, -top + 1));
                kk::script::PushObject(ctx, v.get());
                return 1;
                
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_getImageData(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 3) {
                kk::Strong v = getImageData(kk::script::toDouble(ctx, -top),
                                            kk::script::toDouble(ctx, -top + 1),
                                            kk::script::toDouble(ctx, -top + 2),
                                            kk::script::toDouble(ctx, -top + 3));
                kk::script::PushObject(ctx, v.get());
                return 1;
                
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_putImageData(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 2 && duk_is_object(ctx, -top)) {
                
                ImageData * image = dynamic_cast<ImageData * >(kk::script::GetObject(ctx, -top));
                
                if(image) {
                    
                    Uint x = kk::script::toDouble(ctx, -top + 1);
                    Uint y = kk::script::toDouble(ctx, -top + 2);
                    Uint dirtyX, dirtyY, dirtyWidth, dirtyHeight;
                    
                    if(top > 3) {
                        dirtyX = kk::script::toDouble(ctx, -top + 3);
                    } else {
                        dirtyX = 0;
                    }
                    
                    if(top > 4) {
                        dirtyY = kk::script::toDouble(ctx, -top + 4);
                    } else {
                        dirtyY = 0;
                    }
                    
                    if(top > 5) {
                        dirtyWidth = kk::script::toDouble(ctx, -top + 5);
                    } else {
                        dirtyWidth = 0;
                    }
                    
                    if(top > 6) {
                        dirtyHeight = kk::script::toDouble(ctx, -top + 6);
                    } else {
                        dirtyHeight = 0;
                    }
                    
                    putImageData(image, x, y, dirtyX, dirtyY, dirtyWidth,dirtyHeight);
                   
                    
                }
                
                
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_save(duk_context * ctx) {
            
            save();
            
            return 0;
        }
        
        duk_ret_t Context::duk_restore(duk_context * ctx) {
            
            restore();
            
            return 0;
        }
        
        duk_ret_t Context::duk_rect(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 3) {
                rect(kk::script::toDouble(ctx, -top),
                     kk::script::toDouble(ctx, -top + 1),
                     kk::script::toDouble(ctx, -top + 2),
                     kk::script::toDouble(ctx, -top + 3));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_fillRect(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 3) {
                fillRect(kk::script::toDouble(ctx, -top),
                     kk::script::toDouble(ctx, -top + 1),
                     kk::script::toDouble(ctx, -top + 2),
                         kk::script::toDouble(ctx, -top + 3));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_strokeRect(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 3) {
                strokeRect(kk::script::toDouble(ctx, -top),
                         kk::script::toDouble(ctx, -top + 1),
                         kk::script::toDouble(ctx, -top + 2),
                           kk::script::toDouble(ctx, -top + 3));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_clearRect(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 3) {
                clearRect(kk::script::toDouble(ctx, -top),
                           kk::script::toDouble(ctx, -top + 1),
                           kk::script::toDouble(ctx, -top + 2),
                          kk::script::toDouble(ctx, -top + 3));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_fill(duk_context * ctx) {
            
            fill();
            
            return 0;
        }
        
        duk_ret_t Context::duk_stroke(duk_context * ctx) {
            
            stroke();
            
            return 0;
        }
        
        duk_ret_t Context::duk_beginPath(duk_context * ctx) {
            
            beginPath();
            
            return 0;
        }
        
        duk_ret_t Context::duk_closePath(duk_context * ctx) {
            
            closePath();
            
            return 0;
        }
        
        duk_ret_t Context::duk_moveTo(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 1) {
                moveTo(kk::script::toDouble(ctx, -top),
                          kk::script::toDouble(ctx, -top + 1));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_lineTo(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 1) {
                lineTo(kk::script::toDouble(ctx, -top),
                       kk::script::toDouble(ctx, -top + 1));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_clip(duk_context * ctx) {
            
            clip();
            
            return 0;
        }
        
        duk_ret_t Context::duk_quadraticCurveTo(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 3) {
                quadraticCurveTo(kk::script::toDouble(ctx, -top),
                                 kk::script::toDouble(ctx, -top + 1),
                                 kk::script::toDouble(ctx, -top + 2),
                                 kk::script::toDouble(ctx, -top + 3));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_bezierCurveTo(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 5) {
                bezierCurveTo(kk::script::toDouble(ctx, -top),
                              kk::script::toDouble(ctx, -top + 1),
                              kk::script::toDouble(ctx, -top + 2),
                              kk::script::toDouble(ctx, -top + 3),
                              kk::script::toDouble(ctx, -top + 4),
                              kk::script::toDouble(ctx, -top + 5));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_arc(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 4) {
                kk::Boolean counterclockwise = false;
                
                if(top > 5) {
                    counterclockwise = kk::script::toBoolean(ctx, -top  +5);
                }
                
                arc(kk::script::toDouble(ctx, -top),
                    kk::script::toDouble(ctx, -top + 1),
                    kk::script::toDouble(ctx, -top + 2),
                    kk::script::toDouble(ctx, -top + 3),
                    kk::script::toDouble(ctx, -top + 4),
                    counterclockwise);
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_arcTo(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 4) {
   
                arcTo(kk::script::toDouble(ctx, -top),
                    kk::script::toDouble(ctx, -top + 1),
                    kk::script::toDouble(ctx, -top + 2),
                    kk::script::toDouble(ctx, -top + 3),
                    kk::script::toDouble(ctx, -top + 4));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_isPointInPath(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 1) {
                
                kk::Boolean b = isPointInPath(kk::script::toDouble(ctx, -top),
                      kk::script::toDouble(ctx, -top + 1));
                duk_push_boolean(ctx, b);
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_scale(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 1) {
                scale(kk::script::toDouble(ctx, -top),
                                              kk::script::toDouble(ctx, -top + 1));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_rotate(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0) {
                rotate(kk::script::toDouble(ctx, -top));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_translate(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 1) {
                translate(kk::script::toDouble(ctx, -top),kk::script::toDouble(ctx, -top + 1));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_transform(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 5) {
                transform(kk::script::toDouble(ctx, -top),
                          kk::script::toDouble(ctx, -top + 1),
                          kk::script::toDouble(ctx, -top + 2),
                          kk::script::toDouble(ctx, -top + 3),
                          kk::script::toDouble(ctx, -top + 4),
                          kk::script::toDouble(ctx, -top + 5));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_setTransform(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 5) {
                setTransform(kk::script::toDouble(ctx, -top),
                          kk::script::toDouble(ctx, -top + 1),
                          kk::script::toDouble(ctx, -top + 2),
                          kk::script::toDouble(ctx, -top + 3),
                          kk::script::toDouble(ctx, -top + 4),
                          kk::script::toDouble(ctx, -top + 5));
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_width(duk_context * ctx) {
            duk_push_uint(ctx,width());
            return 1;
        }
                                         
        duk_ret_t Context::duk_height(duk_context * ctx) {
            duk_push_uint(ctx,height());
            return 1;
        }
                                         
        duk_ret_t Context::duk_fillText(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 2) {
                Float maxWidth = 0;
                if(top > 3) {
                    maxWidth = kk::script::toDouble(ctx, -top + 3);
                }
                fillText(kk::script::toString(ctx, -top).c_str(),
                         kk::script::toDouble(ctx, -top + 1),
                         kk::script::toDouble(ctx, -top + 2),
                         maxWidth);
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_strokeText(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 2) {
                Float maxWidth = 0;
                if(top > 3) {
                    maxWidth = kk::script::toDouble(ctx, -top + 3);
                }
                strokeText(kk::script::toString(ctx, -top).c_str(),
                         kk::script::toDouble(ctx, -top + 1),
                         kk::script::toDouble(ctx, -top + 2),
                         maxWidth);
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_measureText(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 0) {

                Float v = measureText(kk::script::toString(ctx, -top).c_str());
                
                duk_push_object(ctx);
                
                duk_push_number(ctx, v);
                duk_put_prop_string(ctx, -2, "width");
                
                return 1;
            }
            
            return 0;
        }
        
        duk_ret_t Context::duk_drawImage(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            Image * image = nullptr;
            
            if(top > 0 && duk_is_object(ctx, -top)) {
                image = dynamic_cast<Image *>(kk::script::GetObject(ctx, -top));
            }
            
            if(image) {
                
                Float sx = 0,sy = 0,swidth = 0,sheight = 0,x = 0,y = 0,width = 0,height = 0;
                
                if(top > 6) {
                    sx = kk::script::toDouble(ctx, -top + 1);
                    sy = kk::script::toDouble(ctx, -top + 2);
                    swidth = kk::script::toDouble(ctx, -top + 3);
                    sheight = kk::script::toDouble(ctx, -top + 4);
                    x = kk::script::toDouble(ctx, -top + 5);
                    y = kk::script::toDouble(ctx, -top + 6);
                    if(top > 7) {
                        width = kk::script::toDouble(ctx, -top + 7);
                    }
                    if(top > 8) {
                        height = kk::script::toDouble(ctx, -top + 8);
                    }
                } else {
                    if(top  >1) {
                        x = kk::script::toDouble(ctx, -top + 1);
                    }
                    if(top > 2) {
                        y = kk::script::toDouble(ctx, -top + 2);
                    }
                    if(top > 3) {
                        width = kk::script::toDouble(ctx, -top + 3);
                    }
                    if(top > 4) {
                        height = kk::script::toDouble(ctx, -top + 4);
                    }
                }
                
                drawImage(image, sx, sy, swidth, sheight, x, y, width, height);
                
            }
            
            return 0;
        }
        
        IMP_SCRIPT_CLASS_BEGIN_NOALLOC(nullptr, Gradient, CGGradient)
        
        static kk::script::Method methods[] = {
            IMP_SCRIPT_METHOD(Gradient,addColorStop)
        };
        
        kk::script::SetMethod(ctx, -1, methods, sizeof(methods) / sizeof(kk::script::Method));
        
        IMP_SCRIPT_CLASS_END
        
        duk_ret_t Gradient::duk_addColorStop(duk_context * ctx) {
            
            int top = duk_get_top(ctx);
            
            if(top > 1){
                addColorStop(kk::script::toDouble(ctx, -top),
                             ColorFromString(kk::script::toString(ctx, -top + 1).c_str()));
            }
            
            return 0;
        }
        
        IMP_SCRIPT_CLASS_BEGIN_NOALLOC(&Gradient::ScriptClass, RadialGradient, CGRadialGradient)
        
        IMP_SCRIPT_CLASS_END
        
        IMP_SCRIPT_CLASS_BEGIN_NOALLOC(&Gradient::ScriptClass, LinearGradient, CGLinearGradient)
        
        IMP_SCRIPT_CLASS_END
        
        IMP_SCRIPT_CLASS_BEGIN_NOALLOC(nullptr, ImageData, CGImageData)

        static kk::script::Property propertys[] = {
            IMP_SCRIPT_PROPERTY_READONLY(ImageData,width)
            IMP_SCRIPT_PROPERTY_READONLY(ImageData,height)
            IMP_SCRIPT_PROPERTY_READONLY(ImageData,data)
        };
        
        kk::script::SetProperty(ctx, -1, propertys, sizeof(propertys) / sizeof(kk::script::Property));
        
        
        IMP_SCRIPT_CLASS_END
        
        duk_ret_t ImageData::duk_width(duk_context * ctx) {
            duk_push_uint(ctx, _width);
            return 1;
        }
        
        duk_ret_t ImageData::duk_height(duk_context * ctx) {
            duk_push_uint(ctx, _width);
            return 1;
        }
        
        duk_ret_t ImageData::duk_data(duk_context *ctx) {
            size_t size = _width * _height * 4;
            duk_push_external_buffer(ctx);
            duk_config_buffer(ctx, -1, _data,size);
            duk_push_buffer_object(ctx, -1, 0, size, DUK_BUFOBJ_UINT8ARRAY);
            duk_remove(ctx, -2);
            return 1;
        }
        
        
        static duk_ret_t OSImageAllocFunc(duk_context * ctx) {
        
            int top = duk_get_top(ctx);
            
            if(top > 0 && duk_is_string(ctx, -top)) {
                
                kk::CString src = duk_to_string(ctx, -top);
                kk::CString basePath = nullptr;
                
                duk_get_global_string(ctx, "__basePath");
                
                if(duk_is_string(ctx, -1)) {
                    basePath = duk_to_string(ctx, -1);
                }
                
                duk_pop(ctx);
                
                OSImage * image = new OSImage(src,basePath);
                
                kk::script::PushObject(ctx, image);
                
                OSImage::load(image);
                
                return 1;
            }
            
            return 0;
        }
        
        IMP_SCRIPT_CLASS_BEGIN_NOALLOC(nullptr, OSImage, CGOSImage)
        
        duk_push_string(ctx, "alloc");
        duk_push_c_function(ctx, OSImageAllocFunc, 1);
        duk_def_prop(ctx, -3, DUK_DEFPROP_HAVE_VALUE | DUK_DEFPROP_CLEAR_WRITABLE | DUK_DEFPROP_CLEAR_CONFIGURABLE);
        
        IMP_SCRIPT_CLASS_END
        
        duk_ret_t OSImage::duk_width(duk_context * ctx) {
            duk_push_uint(ctx, width());
            return 1;
        }
        
        duk_ret_t OSImage::duk_height(duk_context * ctx) {
            duk_push_uint(ctx, height());
            return 1;
        }
        
        duk_ret_t OSImage::duk_src(duk_context * ctx) {
            duk_push_string(ctx, _src.c_str());
            return 1;
        }
        
        void OSImage::done(kk::CString errmsg) {
            
            std::map<duk_context *,void *>::iterator i = _heapptrs.begin();
            
            while(i != _heapptrs.end()) {
                
                duk_context * ctx = i->first;
                void * heapptr = i->second;
                
                duk_push_heapptr(ctx, heapptr);
                
                if(duk_is_object(ctx, -1)) {
                    
                    if(errmsg == nullptr) {
                        
                        duk_get_prop_string(ctx, -1, "onerror");
                        
                        if(duk_is_function(ctx, -1)) {
                            
                            duk_push_string(ctx, errmsg);
                            
                            if(duk_pcall(ctx, 1) != DUK_EXEC_SUCCESS) {
                                kk::script::Error(ctx, -1);
                            }
                            
                        }
                        
                    } else {
                        
                        duk_get_prop_string(ctx, -1, "onload");
                        
                        if(duk_is_function(ctx, -1)) {
                            
                            if(duk_pcall(ctx, 0) != DUK_EXEC_SUCCESS) {
                                kk::script::Error(ctx, -1);
                            }
                            
                        }
                        
                    }
                    
                }
                
                duk_pop_2(ctx);
                
                i ++;
            }
            

        }
    }
    
}


