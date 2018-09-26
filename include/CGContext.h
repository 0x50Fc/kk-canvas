//
//  CGContext.h
//  KKCanvas
//
//  Created by zhanghailong on 2018/8/17.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#ifndef CGContext_h
#define CGContext_h

#if defined(KK_PLATFORM_IOS)

#include <CoreGraphics/CoreGraphics.h>
#include <KKObject/KKObject.h>

#else

#include "kk-object.h"

#endif

namespace kk {
    
    namespace CG {
    
        typedef float Float;
        typedef bool Boolean;
        typedef unsigned char Ubyte;
        typedef unsigned int Uint;
        typedef int Int;
        typedef char Byte;
        
        struct Color {
            Float r,g,b,a;
        };
        
        Color ColorFromString(kk::CString string);
        
        class Image : public kk::Object {
        public:
            virtual Uint width() = 0;
            virtual Uint height() = 0;
            
            DEF_SCRIPT_CLASS_NOALLOC
            
            DEF_SCRIPT_METHOD(width)
            DEF_SCRIPT_METHOD(height)
            
        };
        
        class Style : public kk::Object {
            
        };
        
        enum PatternType {
            PatternTypeRepeat,
            PatternTypeRepeatX,
            PatternTypeRepeatY,
            PatternTypeNoRepeat
        };
        
        PatternType PatternTypeFromString(kk::CString string);
        
        class Pattern : public Style {
        public:
            Pattern(Image * image,PatternType type);
            virtual Image * image();
            virtual PatternType type();
        protected:
            kk::Strong _image;
            PatternType _type;
        };
        
        struct ColorStop {
            Float rate;
            Color color;
        };
        
        class Gradient: public Style {
        public:
            virtual std::vector<ColorStop>::iterator begin();
            virtual std::vector<ColorStop>::iterator end();
            virtual void addColorStop(Float rate,Color color);
        protected:
            std::vector<ColorStop> _colorStops;
        };
        
        class RadialGradient: public Gradient {
        public:
            RadialGradient(Float x0,Float y0,Float r0, Float x1, Float y1, Float r1);
        protected:
            Float _x0;
            Float _y0;
            Float _r0;
            Float _x1;
            Float _y1;
            Float _r1;
        };
        
        class LinearGradient: public Gradient {
        public:
            LinearGradient(Float x0,Float y0, Float x1, Float y1);
        protected:
            Float _x0;
            Float _y0;
            Float _x1;
            Float _y1;
        };
        
        enum LineCapType {
            LineCapTypeButt,
            LineCapTypeRound,
            LineCapTypeSquare,
        };
        
        LineCapType LineCapTypeFromString(kk::CString string);
        
        enum LineJoinType {
            LineJoinTypeBevel,
            LineJoinTypeRound,
            LineJoinTypeMiter,
        };
        
        LineJoinType LineJoinTypeFromString(kk::CString string);
        
        enum FontStyle {
            FontStyleNormal,
            FontStyleItalic,
        };
        
        enum FontWeight {
            FontWeightNormal,
            FontWeightBold
        };
        
        struct Font {
            kk::String family;
            Float size;
            FontStyle style;
            FontStyle weight;
        };
        
        Font FontFromString(kk::CString string);
        
        enum TextAlign {
            TextAlignStart,
            TextAlignEnd,
            TextAlignCenter,
            TextAlignLeft,
            TextAlignRight
        };
        
        TextAlign TextAlignFromString(kk::CString string);
        
        enum TextBaseline {
            TextBaselineAlphabetic,
            TextBaselineTop,
            TextBaselineHanging,
            TextBaselineMiddle,
            TextBaselineIdeographic,
            TextBaselineBottom,
        };
        
        class ImageData : public Image {
        public:
            ImageData(Uint width,Uint height);
            virtual ~ImageData();
            virtual Uint width();
            virtual Uint height();
        protected:
            Ubyte * _data;
            Uint _size;
        };
        
        enum GlobalCompositeOperation {
            GlobalCompositeOperationSourceOver,
            GlobalCompositeOperationSourceAtop,
            GlobalCompositeOperationSourceIn,
            GlobalCompositeOperationSourceOut,
            GlobalCompositeOperationSourceDestinationOver,
            GlobalCompositeOperationSourceDestinationAtop,
            GlobalCompositeOperationSourceDestinationIn,
            GlobalCompositeOperationSourceDestinationOut,
            GlobalCompositeOperationSourceDestinationLighter,
            GlobalCompositeOperationSourceDestinationCopy,
            GlobalCompositeOperationSourceDestinationXOR,
        };
        
        GlobalCompositeOperation GlobalCompositeOperationFromString(kk::CString string);
        
        class Context : public kk::Object {
            
#if defined(KK_PLATFORM_IOS)
        public:
            Context(CGContextRef ctx);
            virtual ~Context();
        protected:
            CGContextRef _ctx;
#endif
        
        public:
            
            DEF_SCRIPT_CLASS_NOALLOC
            
            virtual kk::Strong createLinearGradient(Float x0,Float y0, Float x1, Float y1);
            DEF_SCRIPT_METHOD(createLinearGradient)
            
            virtual kk::Strong createRadialGradient(Float x0,Float y0,Float r0, Float x1, Float y1, Float r1);
            DEF_SCRIPT_METHOD(createRadialGradient)
            
            virtual kk::Strong createPattern(Image * image,PatternType type);
            DEF_SCRIPT_METHOD(createPattern)
            
            virtual kk::Strong createImageData(Uint width,Uint height);
            DEF_SCRIPT_METHOD(createImageData)
            
            virtual kk::Strong getImageData(Uint x,Uint y,Uint width,Uint height);
            DEF_SCRIPT_METHOD(getImageData)
            
            virtual void putImageData(ImageData * data,Uint x,Uint y,Uint dirtyX,Uint dirtyWidth,Uint dirtyHeight);
            DEF_SCRIPT_METHOD(putImageData)
            
            virtual void save();
            DEF_SCRIPT_METHOD(save)
            
            virtual void restore();
            DEF_SCRIPT_METHOD(restore)
            
            virtual void rect(Float x, Float y,Float width,Float height);
            DEF_SCRIPT_METHOD(rect)
            
            virtual void fillRect(Float x, Float y,Float width,Float height);
            DEF_SCRIPT_METHOD(fillRect)
            
            virtual void strokeRect(Float x, Float y,Float width,Float height);
            DEF_SCRIPT_METHOD(strokeRect)
            
            virtual void clearRect(Float x, Float y,Float width,Float height);
            DEF_SCRIPT_METHOD(clearRect)
            
            virtual void fill();
            DEF_SCRIPT_METHOD(fill)
            
            virtual void stroke();
            DEF_SCRIPT_METHOD(stroke)
            
            virtual void beginPath();
            DEF_SCRIPT_METHOD(beginPath)
            
            virtual void moveTo(Float x,Float y);
            DEF_SCRIPT_METHOD(moveTo)
            
            virtual void closePath();
            DEF_SCRIPT_METHOD(closePath)
            
            virtual void lineTo(Float x,Float y);
            DEF_SCRIPT_METHOD(lineTo)
            
            virtual void clip();
            DEF_SCRIPT_METHOD(clip)
            
            virtual void quadraticCurveTo(Float cpx,Float cpy,Float x,Float y);
            DEF_SCRIPT_METHOD(quadraticCurveTo)
            
            virtual void bezierCurveTo(Float cp1x,Float cp1y,Float cp2x,Float cp2y,Float x,Float y);
            DEF_SCRIPT_METHOD(bezierCurveTo)
            
            virtual void arc(Float x,Float y,Float r, Float sAngle,Float eAngle,Boolean counterclockwise);
            DEF_SCRIPT_METHOD(arc)
            
            virtual void arcTo(Float x1,Float y1,Float x2,Float y2,Float r);
            DEF_SCRIPT_METHOD(arcTo)
            
            virtual Boolean isPointInPath(Float x,Float y);
            DEF_SCRIPT_METHOD(isPointInPath)
            
            virtual void scale(Float sx,Float sy);
            DEF_SCRIPT_METHOD(scale)
            
            virtual void rotate(Float angle);
            DEF_SCRIPT_METHOD(rotate)
            
            virtual void translate(Float dx,Float dy);
            DEF_SCRIPT_METHOD(translate)
            
            virtual void transform(Float a,Float b,Float c,Float d,Float e,Float f);
            DEF_SCRIPT_METHOD(transform)
            
            virtual void setTransform(Float a,Float b,Float c,Float d,Float e,Float f);
            DEF_SCRIPT_METHOD(setTransform)
            
            virtual void fillText(kk::CString text,Float x,Float y,Float maxWidth);
            DEF_SCRIPT_METHOD(fillText)
            
            virtual void strokeText(kk::CString text,Float x,Float y,Float maxWidth);
            DEF_SCRIPT_METHOD(strokeText)
            
            virtual Float measureText(kk::CString text);
            DEF_SCRIPT_METHOD(measureText)
            
            virtual void drawImage(Image * image,Float sx,Float sy,Float swidth,Float sheight,Float x,Float y,Float width,Float height);
            DEF_SCRIPT_METHOD(drawImage)
            
            
            virtual void setFillStyle(Style * style);
            DEF_SCRIPT_METHOD(setFillStyle)
            
            virtual Style * fillStyle();
            DEF_SCRIPT_METHOD(fillStyle)
            
            virtual void setFillColor(Color color);
            virtual Color fillColor();
            
            virtual void setStrokeStyle(Style * style);
            DEF_SCRIPT_METHOD(setStrokeStyle)
            
            virtual Style * strokeStyle();
            DEF_SCRIPT_METHOD(strokeStyle)
            
            virtual void setStrokeColor(Color color);
            virtual Color strokeColor();
            
            virtual void setShadowBlur(Float v);
            DEF_SCRIPT_METHOD(setShadowBlur)
            virtual Float shadowBlur();
            DEF_SCRIPT_METHOD(shadowBlur)
            
            virtual void setShadowOffsetX(Float v);
            DEF_SCRIPT_METHOD(setShadowOffsetX)
            virtual Float shadowOffsetX();
            DEF_SCRIPT_METHOD(shadowOffsetX)
            
            virtual void setShadowOffsetY(Float v);
            DEF_SCRIPT_METHOD(setShadowOffsetY)
            virtual Float shadowOffsetY();
            DEF_SCRIPT_METHOD(shadowOffsetY)
            
            virtual void setLineCap(LineCapType v);
            DEF_SCRIPT_METHOD(setLineCap)
            virtual LineCapType lineCap();
            DEF_SCRIPT_METHOD(lineCap)
            
            virtual void setLineJoin(LineJoinType v);
            DEF_SCRIPT_METHOD(setLineJoin)
            virtual LineJoinType lineJoin();
            DEF_SCRIPT_METHOD(lineJoin)
            
            virtual void setMiterLimit(Float v);
            DEF_SCRIPT_METHOD(setMiterLimit)
            virtual Float miterLimit();
            DEF_SCRIPT_METHOD(miterLimit)
            
            virtual void setFont(Font v);
            DEF_SCRIPT_METHOD(setFont)
            virtual Font font();
            DEF_SCRIPT_METHOD(font)
            
            virtual void setTextAlign(TextAlign v);
            DEF_SCRIPT_METHOD(setTextAlign)
            virtual TextAlign textAlign();
            DEF_SCRIPT_METHOD(textAlign)
            
            virtual void setTextBaseline(TextBaseline v);
            DEF_SCRIPT_METHOD(setTextBaseline)
            virtual TextBaseline textBaseline();
            DEF_SCRIPT_METHOD(textBaseline)
            
            virtual void setGlobalAlpha(Float v);
            DEF_SCRIPT_METHOD(setGlobalAlpha)
            virtual Float globalAlpha();
            DEF_SCRIPT_METHOD(globalAlpha)
            
            virtual void setGlobalCompositeOperation(GlobalCompositeOperation v);
            DEF_SCRIPT_METHOD(setGlobalCompositeOperation)
            virtual GlobalCompositeOperation globalCompositeOperation();
            DEF_SCRIPT_METHOD(globalCompositeOperation)
            
            
        protected:
            kk::Strong _fillStyle;
            Color _fillColor;
            kk::Strong _strokeStyle;
            Color _strokeColor;
            Float _shadowBlur;
            Float _shadowOffsetX;
            Float _shadowOffsetY;
            LineCapType _lineCap;
            LineJoinType _lineJoin;
            Float _miterLimit;
            Font _font;
            TextAlign _textAlign;
            TextBaseline _textBaseline;
            Float _globalAlpha;
            GlobalCompositeOperation _globalCompositeOperation;
        };
        
        
    }
    
}

#endif /* CGContext_h */
