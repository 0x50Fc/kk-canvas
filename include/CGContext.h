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
#include <CoreText/CoreText.h>
#include <KKObject/KKObject.h>

#else

#include "kk-object.h"

#endif

namespace kk {
    
    namespace CG {
    
#if defined(KK_PLATFORM_IOS)
        typedef CGFloat Float;
#else
        typedef float Float;
#endif
        typedef bool Boolean;
        typedef unsigned char Ubyte;
        typedef unsigned int Uint;
        typedef int Int;
        typedef char Byte;
        
        struct Color {
            Float r,g,b,a;
        };
        
        Color ColorFromString(kk::CString string);
        kk::String StringFromColor(Color v);
        
        class Palette {
        public:
            Palette(kk::CString name, ...);
            virtual void set(kk::CString name,Color v);
            virtual Color get(kk::CString name);
            static Palette Default;
        protected:
            std::map<kk::String,Color> _values;
        };
        
        class Image : public kk::Object, public kk::script::IObject {
        public:
            virtual Uint width() = 0;
            virtual Uint height() = 0;
            
            DEF_SCRIPT_CLASS_NOALLOC
            
            DEF_SCRIPT_PROPERTY_READONLY(width)
            DEF_SCRIPT_PROPERTY_READONLY(height)
            
#if defined(KK_PLATFORM_IOS)
        public:
            virtual CGImageRef CGImage() = 0;
#endif
            
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
        kk::String StringFromPatternType(PatternType v);
        
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
        
        class Gradient: public Style, public kk::script::IObject  {
        public:

            virtual void addColorStop(Float loc,Color color);
            
            DEF_SCRIPT_CLASS_NOALLOC
            
            DEF_SCRIPT_METHOD(addColorStop)
            
#if defined(KK_PLATFORM_IOS)
        public:
            virtual CGGradientRef createCGGradient();
#endif
            
        protected:
            std::vector<Float> _locations;
            std::vector<Color> _colors;
        };
        
        class RadialGradient: public Gradient {
        public:
            RadialGradient(Float x0,Float y0,Float r0, Float x1, Float y1, Float r1);
            
            DEF_SCRIPT_CLASS_NOALLOC
            
#if defined(KK_PLATFORM_IOS)
        public:
            virtual CGPoint startCenter();
            virtual CGFloat startRadius();
            virtual CGPoint endCenter();
            virtual CGFloat endRadius();
#endif
            
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
            
            DEF_SCRIPT_CLASS_NOALLOC
            
#if defined(KK_PLATFORM_IOS)
        public:
            virtual CGPoint startPoint();
            virtual CGPoint endPoint();
#endif
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
        kk::String StringFromLineCapType(LineCapType v);
        
        enum LineJoinType {
            LineJoinTypeMiter,
            LineJoinTypeRound,
            LineJoinTypeBevel,
        };
        
        LineJoinType LineJoinTypeFromString(kk::CString string);
        kk::String StringFromLineJoinType(LineJoinType v);
        
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
            FontWeight weight;
        };
        
        Font FontFromString(kk::CString string);
        kk::String StringFromFont(Font v);
        
        enum TextAlign {
            TextAlignStart,
            TextAlignEnd,
            TextAlignCenter,
            TextAlignLeft,
            TextAlignRight
        };
        
        TextAlign TextAlignFromString(kk::CString string);
        kk::String StringFromTextAlign(TextAlign v);
        
        enum TextBaseline {
            TextBaselineAlphabetic,
            TextBaselineTop,
            TextBaselineHanging,
            TextBaselineMiddle,
            TextBaselineIdeographic,
            TextBaselineBottom,
        };
        
        TextBaseline TextBaselineFromString(kk::CString string);
        kk::String StringFromTextBaseline(TextBaseline v);
        
        class ImageData : public Image {
        public:
            ImageData(Uint width,Uint height);
            virtual ~ImageData();
            virtual Uint width();
            virtual Uint height();
            virtual Ubyte * data();
            virtual Uint size();
            
            DEF_SCRIPT_CLASS_NOALLOC
            
            DEF_SCRIPT_PROPERTY_READONLY(data)
            
#if defined(KK_PLATFORM_IOS)
        public:
            virtual CGImageRef CGImage();
        protected:
            CGImageRef _CGImage;
#endif
        protected:
            Ubyte * _data;
            Uint _width;
            Uint _height;
        };
        
        enum GlobalCompositeOperation {
            GlobalCompositeOperationSourceOver,
            GlobalCompositeOperationSourceAtop,
            GlobalCompositeOperationSourceIn,
            GlobalCompositeOperationSourceOut,
            GlobalCompositeOperationDestinationOver,
            GlobalCompositeOperationDestinationAtop,
            GlobalCompositeOperationDestinationIn,
            GlobalCompositeOperationDestinationOut,
            GlobalCompositeOperationDestinationLighter,
            GlobalCompositeOperationDestinationCopy,
            GlobalCompositeOperationDestinationXOR,
        };
        
        GlobalCompositeOperation GlobalCompositeOperationFromString(kk::CString string);
        kk::String StringFromGlobalCompositeOperation(GlobalCompositeOperation v);
        
        class Context : public kk::Object , public kk::script::IObject{
            
        protected:
            Context(Uint width,Uint height);
        
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
            
            virtual void putImageData(ImageData * data,Uint x,Uint y,Uint dirtyX,Uint dirtyY,Uint dirtyWidth,Uint dirtyHeight);
            DEF_SCRIPT_METHOD(putImageData)
            
            virtual void save() = 0;
            DEF_SCRIPT_METHOD(save)
            
            virtual void restore() = 0;
            DEF_SCRIPT_METHOD(restore)
            
            virtual void rect(Float x, Float y,Float width,Float height) = 0;
            DEF_SCRIPT_METHOD(rect)
            
            virtual void fillRect(Float x, Float y,Float width,Float height) = 0;
            DEF_SCRIPT_METHOD(fillRect)
            
            virtual void strokeRect(Float x, Float y,Float width,Float height) = 0;
            DEF_SCRIPT_METHOD(strokeRect)
            
            virtual void clearRect(Float x, Float y,Float width,Float height) = 0;
            DEF_SCRIPT_METHOD(clearRect)
            
            virtual void fill() = 0;
            DEF_SCRIPT_METHOD(fill)
            
            virtual void stroke() = 0;
            DEF_SCRIPT_METHOD(stroke)
            
            virtual void beginPath() = 0;
            DEF_SCRIPT_METHOD(beginPath)
            
            virtual void moveTo(Float x,Float y) = 0;
            DEF_SCRIPT_METHOD(moveTo)
            
            virtual void closePath() = 0;
            DEF_SCRIPT_METHOD(closePath)
            
            virtual void lineTo(Float x,Float y) = 0;
            DEF_SCRIPT_METHOD(lineTo)
            
            virtual void clip() = 0;
            DEF_SCRIPT_METHOD(clip)
            
            virtual void quadraticCurveTo(Float cpx,Float cpy,Float x,Float y) = 0;
            DEF_SCRIPT_METHOD(quadraticCurveTo)
            
            virtual void bezierCurveTo(Float cp1x,Float cp1y,Float cp2x,Float cp2y,Float x,Float y) = 0;
            DEF_SCRIPT_METHOD(bezierCurveTo)
            
            virtual void arc(Float x,Float y,Float r, Float sAngle,Float eAngle,Boolean counterclockwise) = 0;
            DEF_SCRIPT_METHOD(arc)
            
            virtual void arcTo(Float x1,Float y1,Float x2,Float y2,Float r) = 0;
            DEF_SCRIPT_METHOD(arcTo)
            
            virtual Boolean isPointInPath(Float x,Float y) = 0;
            DEF_SCRIPT_METHOD(isPointInPath)
            
            virtual void scale(Float sx,Float sy) = 0;
            DEF_SCRIPT_METHOD(scale)
            
            virtual void rotate(Float angle) = 0;
            DEF_SCRIPT_METHOD(rotate)
            
            virtual void translate(Float dx,Float dy) = 0;
            DEF_SCRIPT_METHOD(translate)
            
            virtual void transform(Float a,Float b,Float c,Float d,Float e,Float f) = 0;
            DEF_SCRIPT_METHOD(transform)
            
            virtual void setTransform(Float a,Float b,Float c,Float d,Float e,Float f) = 0;
            DEF_SCRIPT_METHOD(setTransform)
            
            virtual void fillText(kk::CString text,Float x,Float y,Float maxWidth) = 0;
            DEF_SCRIPT_METHOD(fillText)
            
            virtual void strokeText(kk::CString text,Float x,Float y,Float maxWidth) = 0;
            DEF_SCRIPT_METHOD(strokeText)
            
            virtual Float measureText(kk::CString text) = 0;
            DEF_SCRIPT_METHOD(measureText)
            
            virtual void drawImage(Image * image,Float sx,Float sy,Float swidth,Float sheight,Float x,Float y,Float width,Float height) = 0;
            DEF_SCRIPT_METHOD(drawImage)
            
            
            virtual void setFillStyle(Style * style);
            virtual Style * fillStyle();
            DEF_SCRIPT_PROPERTY(fillStyle,FillStyle)
            
            virtual void setFillColor(Color color);
            virtual Color fillColor();
            
            virtual void setStrokeStyle(Style * style);
            virtual Style * strokeStyle();
            DEF_SCRIPT_PROPERTY(strokeStyle,StrokeStyle)
            
            virtual void setStrokeColor(Color color);
            virtual Color strokeColor();
            
            virtual void setShadowColor(Color v);
            virtual Color shadowColor();
            DEF_SCRIPT_PROPERTY(shadowColor,ShadowColor)
            
            virtual void setShadowBlur(Float v);
            virtual Float shadowBlur();
            DEF_SCRIPT_PROPERTY(shadowBlur,ShadowBlur)
            
            virtual void setShadowOffsetX(Float v);
            virtual Float shadowOffsetX();
            DEF_SCRIPT_PROPERTY(shadowOffsetX,ShadowOffsetX)
            
            virtual void setShadowOffsetY(Float v);
            virtual Float shadowOffsetY();
            DEF_SCRIPT_PROPERTY(shadowOffsetY,ShadowOffsetY)
            
            virtual void setLineCap(LineCapType v);
            virtual LineCapType lineCap();
            DEF_SCRIPT_PROPERTY(lineCap,LineCap)
            
            virtual void setLineJoin(LineJoinType v);
            virtual LineJoinType lineJoin();
            DEF_SCRIPT_PROPERTY(lineJoin,LineJoin)
            
            virtual void setLineWidth(Float v);
            virtual Float lineWidth();
            DEF_SCRIPT_PROPERTY(lineWidth,LineWidth)
            
            virtual void setMiterLimit(Float v);
            virtual Float miterLimit();
            DEF_SCRIPT_PROPERTY(miterLimit,MiterLimit)
            
            virtual void setFont(Font v);
            virtual Font font();
            DEF_SCRIPT_PROPERTY(font,Font)
            
            virtual void setTextAlign(TextAlign v);
            virtual TextAlign textAlign();
            DEF_SCRIPT_PROPERTY(textAlign,TextAlign)
            
            virtual void setTextBaseline(TextBaseline v);
            virtual TextBaseline textBaseline();
            DEF_SCRIPT_PROPERTY(textBaseline,TextBaseline)
            
            virtual void setGlobalAlpha(Float v);
            virtual Float globalAlpha();
            DEF_SCRIPT_PROPERTY(globalAlpha,GlobalAlpha)
            
            virtual void setGlobalCompositeOperation(GlobalCompositeOperation v);
            virtual GlobalCompositeOperation globalCompositeOperation();
            DEF_SCRIPT_PROPERTY(globalCompositeOperation,GlobalCompositeOperation)
            
            virtual Uint width();
            DEF_SCRIPT_PROPERTY_READONLY(width);
            
            virtual Uint height();
            DEF_SCRIPT_PROPERTY_READONLY(height);
            
        protected:
            
            virtual Ubyte * getContextData() = 0;
            
        protected:
            
            Uint _width;
            Uint _height;
            
            kk::Strong _fillStyle;
            Color _fillColor;
            kk::Strong _strokeStyle;
            Color _strokeColor;
            Color _shadowColor;
            Float _shadowBlur;
            Float _shadowOffsetX;
            Float _shadowOffsetY;
            LineCapType _lineCap;
            LineJoinType _lineJoin;
            Float _lineWidth;
            Float _miterLimit;
            Font _font;
            TextAlign _textAlign;
            TextBaseline _textBaseline;
            Float _globalAlpha;
            GlobalCompositeOperation _globalCompositeOperation;
        };
        
        class OSContext : public Context {
        public:
            OSContext(Uint width,Uint height);
            virtual ~OSContext();
            
#if defined(KK_PLATFORM_IOS)
            virtual CGImageRef createCGImage();
#endif
            
            DEF_SCRIPT_CLASS_NOALLOC
            
            virtual void save();
            virtual void restore();
            virtual void rect(Float x, Float y,Float width,Float height);
            virtual void fillRect(Float x, Float y,Float width,Float height);
            virtual void strokeRect(Float x, Float y,Float width,Float height);
            virtual void clearRect(Float x, Float y,Float width,Float height);
            virtual void fill();
            virtual void stroke();
            virtual void beginPath();
            virtual void moveTo(Float x,Float y);
            virtual void closePath();
            virtual void lineTo(Float x,Float y);
            virtual void clip();
            virtual void quadraticCurveTo(Float cpx,Float cpy,Float x,Float y);
            virtual void bezierCurveTo(Float cp1x,Float cp1y,Float cp2x,Float cp2y,Float x,Float y);
            virtual void arc(Float x,Float y,Float r, Float sAngle,Float eAngle,Boolean counterclockwise);
            virtual void arcTo(Float x1,Float y1,Float x2,Float y2,Float r);
            virtual Boolean isPointInPath(Float x,Float y);
            virtual void scale(Float sx,Float sy);
            virtual void rotate(Float angle);
            virtual void translate(Float dx,Float dy);
            virtual void transform(Float a,Float b,Float c,Float d,Float e,Float f);
            virtual void setTransform(Float a,Float b,Float c,Float d,Float e,Float f);
            virtual void fillText(kk::CString text,Float x,Float y,Float maxWidth);
            virtual void strokeText(kk::CString text,Float x,Float y,Float maxWidth);
            virtual Float measureText(kk::CString text);
            virtual void drawImage(Image * image,Float sx,Float sy,Float swidth,Float sheight,Float x,Float y,Float width,Float height);
            

            virtual void setFillStyle(Style * style);
            virtual void setFillColor(Color color);
            virtual void setStrokeStyle(Style * style);
            virtual void setStrokeColor(Color color);
            virtual void setShadowColor(Color v);
            virtual void setShadowBlur(Float v);
            virtual void setShadowOffsetX(Float v);
            virtual void setShadowOffsetY(Float v);
            virtual void setLineCap(LineCapType v);
            virtual void setLineJoin(LineJoinType v);
            virtual void setLineWidth(Float v);
            virtual void setMiterLimit(Float v);
            virtual void setFont(Font v);
            virtual void setTextAlign(TextAlign v);
            virtual void setTextBaseline(TextBaseline v);
            virtual void setGlobalAlpha(Float v);
            virtual void setGlobalCompositeOperation(GlobalCompositeOperation v);
            
        protected:
            virtual Ubyte * getContextData();
        protected:
#if defined(KK_PLATFORM_IOS)
            CGContextRef _ctx;
#endif
        };

        
    }
    
}

#endif /* CGContext_h */
