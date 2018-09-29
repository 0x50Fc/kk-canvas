//
//  CGContext.cc
//  KKCanvas
//
//  Created by zhanghailong on 2018/8/17.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "CGContext.h"

namespace kk {
    
    namespace CG {
        
      
        Palette::Palette(kk::CString name, ...) {
            
            va_list va;
            
            va_start(va, name);
            
            kk::CString key = name;
            kk::CString value = nullptr;
            
            while(1) {
                
                if(key == nullptr) {
                    key = va_arg(va, kk::CString);
                    if(key == nullptr) {
                        break;
                    }
                }
                
                if(value == nullptr) {
                    value = va_arg(va, kk::CString);
                    if(value == nullptr) {
                        break;
                    }
                }
                
                _values[key] = ColorFromString(value);
                key = nullptr;
                value = nullptr;
            }
            
            va_end(va);
        }
        
        void Palette::set(kk::CString name,Color v) {
            _values[name] = v;
        }
        
        Color Palette::get(kk::CString name) {
            Color v = {0,0,0,0};
            std::map<kk::String,Color>::iterator i = _values.find(name);
            if(i != _values.end()) {
                return i->second;
            }
            return v;
        }
        
        Palette Palette::Default("black","#000000",
                                 "red","#ff0000",
                                 "white","#ffffff",
                                 "green","#00ff00",
                                 "blue","#0000ff",
                                 "magenta","#ff00ff",
                                 "yellow","#ffff00",
                                 nullptr);
        
        
        
        
        Color ColorFromString(kk::CString string) {
            Color v = {0,0,0,0};
            
            if(string != nullptr) {
                
                if(CStringHasPrefix(string, "rgba(")) {
                    sscanf(string, "rgba(%lf,%lf,%lf,%lf)",&v.r,&v.g,&v.b,&v.a);
                    v.r = v.r / 255.0f;
                    v.g = v.g / 255.0f;
                    v.b = v.b / 255.0f;
                    
                } else if(CStringHasPrefix(string, "rgb(")) {
                    
                    sscanf(string, "rgba(%lf,%lf,%lf)",&v.r,&v.g,&v.b);
                    v.r = v.r / 255.0f;
                    v.g = v.g / 255.0f;
                    v.b = v.b / 255.0f;
                    v.a = 1.0f;
                    
                } else if(CStringHasPrefix(string, "#")) {
                    
                    size_t n = CStringLength(string);
                    
                    if(n == 4) {
                        Uint r = 0,g = 0,b = 0;
                        sscanf(string, "#%1x%1x%1x",&r,&g,&b);
                        v.r = (Float)(r << 8 | r) / 255.0f;
                        v.g = (Float)(g << 8 | r) / 255.0f;
                        v.b = (Float)(b << 8 | r) / 255.0f;
                        v.a = 1.0f;
                    } else if(n == 7) {
                        Uint r = 0,g = 0,b = 0;
                        sscanf(string, "#%2x%2x%2x",&r,&g,&b);
                        v.r = (Float)(r) / 255.0f;
                        v.g = (Float)(g) / 255.0f;
                        v.b = (Float)(b) / 255.0f;
                        v.a = 1.0f;
                    }
                    
                } else {
                    return Palette::Default.get(string);
                }
            }
            
            return v;
        }
        
        kk::String StringFromColor(Color v) {
            
            char fmt[16] = "";
            
            Uint r = v.r * 255.0;
            Uint g = v.g * 255.0;
            Uint b = v.b * 255.0;
            
            if(v.a == 1.0f) {
                snprintf(fmt, sizeof(fmt), "#%2x%2x%2x",r,g,b);
            } else {
                snprintf(fmt, sizeof(fmt), "rgba(%u,%u,%u,%g)",r,g,b,v.a);
            }
            
            return fmt;
            
        }
        
        
        PatternType PatternTypeFromString(kk::CString string) {
            if(CStringEqual(string, "repeat-x")){
                return PatternTypeRepeatX;
            }
            if(CStringEqual(string, "repeat-y")){
                return PatternTypeRepeatY;
            }
            if(CStringEqual(string, "no-repeat")){
                return PatternTypeNoRepeat;
            }
            return PatternTypeRepeat;
        }
        
        kk::String StringFromPatternType(PatternType v) {
            switch (v) {
                case PatternTypeRepeatX:
                    return "repeat-x";
                case PatternTypeRepeatY:
                    return "repeat-y";
                case PatternTypeNoRepeat:
                    return "no-repeat";
                default:
                    return "repeat";
            }
        }
        
        LineCapType LineCapTypeFromString(kk::CString string) {
            if(CStringEqual(string, "round")) {
                return LineCapTypeRound;
            }
            if(CStringEqual(string, "square")) {
                return LineCapTypeSquare;
            }
            return LineCapTypeButt;
        }
        
        kk::String StringFromLineCapType(LineCapType v) {
            switch (v) {
                case LineCapTypeRound:
                    return "round";
                case LineCapTypeSquare:
                    return "square";
                default:
                    return "butt";
            }
        }
        
        LineJoinType LineJoinTypeFromString(kk::CString string) {
            
            if(CStringEqual(string, "round")) {
                return LineJoinTypeRound;
            }
            
            if(CStringEqual(string, "bevel")) {
                return LineJoinTypeBevel;
            }
            
            return LineJoinTypeMiter;
        }
        
        kk::String StringFromLineJoinType(LineJoinType v) {
            switch (v) {
                case LineJoinTypeRound:
                    return "round";
                case LineJoinTypeBevel:
                    return "bevel";
                default:
                    return "miter";
            }
        }
        
        Font FontFromString(kk::CString string) {
            
            Font v = {"",14,FontStyleNormal,FontWeightNormal};
            
            std::vector<kk::String> items;
            
            CStringSplit(string, " ", items);
            
            std::vector<kk::String>::iterator i = items.begin();
            
            while(i != items.end()) {
                
                kk::String & s = * i;
                
                if(s == "bold") {
                    v.weight = FontWeightBold;
                } else if(s == "italic") {
                    v.style = FontStyleItalic;
                } else if(CStringHasSuffix(s.c_str(), "px")) {
                    v.size = atof(s.c_str());
                } else {
                    v.family = s;
                }
                
                i ++;
            }
            
            return v;
        }
        
        kk::String StringFromFont(Font v) {
            
            std::vector<kk::String> items;
            
            if(v.family != "") {
                items.push_back(v.family);
            }
            
            if(v.weight == FontWeightBold) {
                items.push_back("bold");
            }
            
            if(v.style == FontStyleItalic) {
                items.push_back("italic");
            }
            
            char fmt[32];
            
            snprintf(fmt, sizeof(fmt), "%gpx",v.size);
            
            items.push_back(fmt);
            
            return CStringJoin(items, " ");
        }
        
        TextAlign TextAlignFromString(kk::CString string) {
            if(CStringEqual(string, "end")) {
                return TextAlignEnd;
            }
            if(CStringEqual(string, "center")) {
                return TextAlignCenter;
            }
            if(CStringEqual(string, "left")) {
                return TextAlignLeft;
            }
            if(CStringEqual(string, "right")) {
                return TextAlignRight;
            }
            return TextAlignStart;
        }
        
        kk::String StringFromTextAlign(TextAlign v) {
            switch (v) {
                case TextAlignEnd:
                    return "end";
                case TextAlignCenter:
                    return "center";
                case TextAlignLeft:
                    return "left";
                case TextAlignRight:
                    return "right";
                default:
                    return "start";
            }
        }
        
        TextBaseline TextBaselineFromString(kk::CString string) {
            if(CStringEqual(string, "top")) {
                return TextBaselineTop;
            }
            if(CStringEqual(string, "hanging")) {
                return TextBaselineHanging;
            }
            if(CStringEqual(string, "middle")) {
                return TextBaselineMiddle;
            }
            if(CStringEqual(string, "ideographic")) {
                return TextBaselineIdeographic;
            }
            if(CStringEqual(string, "bottom")) {
                return TextBaselineBottom;
            }
            return TextBaselineAlphabetic;
        }
        
        kk::String StringFromTextBaseline(TextBaseline v) {
            
            switch (v) {
                case TextBaselineTop:
                    return "top";
                case TextBaselineHanging:
                    return "hanging";
                case TextBaselineMiddle:
                    return "middle";
                case TextBaselineIdeographic:
                    return "ideographic";
                case TextBaselineBottom:
                    return "bottom";
                default:
                    return "alphabetic";
            }
        }
        
        
        GlobalCompositeOperation GlobalCompositeOperationFromString(kk::CString string) {
            
            if(CStringEqual(string, "source-atop")) {
                return GlobalCompositeOperationSourceAtop;
            }
            
            if(CStringEqual(string, "source-in")) {
                return GlobalCompositeOperationSourceIn;
            }
            
            if(CStringEqual(string, "source-out")) {
                return GlobalCompositeOperationSourceOut;
            }
            
            if(CStringEqual(string, "destination-over")) {
                return GlobalCompositeOperationDestinationOver;
            }
            
            if(CStringEqual(string, "destination-atop")) {
                return GlobalCompositeOperationDestinationAtop;
            }
            
            if(CStringEqual(string, "destination-in")) {
                return GlobalCompositeOperationDestinationIn;
            }
            
            if(CStringEqual(string, "destination-out")) {
                return GlobalCompositeOperationDestinationOut;
            }
            
            if(CStringEqual(string, "destination-lighter")) {
                return GlobalCompositeOperationDestinationLighter;
            }
            
            if(CStringEqual(string, "destination-copy")) {
                return GlobalCompositeOperationDestinationCopy;
            }
            
            if(CStringEqual(string, "destination-xor")) {
                return GlobalCompositeOperationDestinationXOR;
            }
            
            return GlobalCompositeOperationSourceOver;
        }
        
        kk::String StringFromGlobalCompositeOperation(GlobalCompositeOperation v) {
            
            switch (v) {
                case GlobalCompositeOperationSourceAtop:
                    return "source-atop";
                case GlobalCompositeOperationSourceIn:
                    return "source-in";
                case GlobalCompositeOperationSourceOut:
                    return "source-out";
                case GlobalCompositeOperationDestinationOver:
                    return "destination-over";
                case GlobalCompositeOperationDestinationAtop:
                    return "destination-atop";
                case GlobalCompositeOperationDestinationIn:
                    return "destination-in";
                case GlobalCompositeOperationDestinationOut:
                    return "destination-out";
                case GlobalCompositeOperationDestinationLighter:
                    return "destination-lighter";
                case GlobalCompositeOperationDestinationCopy:
                    return "destination-copy";
                case GlobalCompositeOperationDestinationXOR:
                    return "destination-xor";
                default:
                    break;
            }
            return "source-over";
        }
        
        Context::Context(Uint width,Uint height):_width(width),_height(height) {
            _fillColor = {0,0,0,1};
            _strokeColor = {0,0,0,1};
            _shadowColor = {0,0,0,1};
            _shadowBlur = 0;
            _shadowOffsetX = 0;
            _shadowOffsetY = 0;
            _lineCap = LineCapTypeButt;
            _lineJoin = LineJoinTypeBevel;
            _lineWidth = 1;
            _miterLimit = 0;
            _font = {"",14,FontStyleNormal,FontWeightNormal};
            _textAlign = TextAlignStart;
            _textBaseline = TextBaselineAlphabetic;
            _globalAlpha = 1.0f;
            _globalCompositeOperation = GlobalCompositeOperationSourceOver;
        }
        
        kk::Strong Context::getImageData(Uint x,Uint y,Uint width,Uint height) {
            
            if(width == 0 || height == 0) {
                return (kk::Object *) nullptr;
            }
            
            kk::Strong v = createImageData(width, height);
            
            ImageData * image = v.as<ImageData>();
            
            if(image != nullptr) {
                
                Ubyte * p = image->data();
                Ubyte * s = getContextData();
                
                for(Uint r = 0; r < height; r ++) {
                    
                    for(Uint c = 0; c < width; c ++) {
                        
                        if(r + y < _height && c + x < _width) {
                            for(Uint n = 0; n < 4; n ++) {
                                *p = s[((r + y) * _width + (c + x)) * 4 + n];
                                p ++;
                            }
                        } else {
                            p += 4;
                        }
                    }
                }
            }
            
            return image;
        }
        
        void Context::putImageData(ImageData * image,Uint x,Uint y,Uint dirtyX,Uint dirtyY,Uint dirtyWidth,Uint dirtyHeight) {
            
            if(image == nullptr) {
                return;
            }
            
            if(dirtyWidth == 0) {
                dirtyWidth = _width - dirtyX;
            }
            
            if(dirtyHeight == 0) {
                dirtyHeight = _height - dirtyY;
            }
            
            Uint mWidth = image->width();
            Uint width = MIN(mWidth - x,dirtyWidth);
            Uint height = MIN(image->height() - y,dirtyHeight);
            
            Ubyte * p = image->data();
            Ubyte * s = getContextData();
            
            for(Uint r = 0; r < height; r ++) {
                
                for(Uint c = 0; c < width; c ++) {
                    
                    Uint i_p = ((r + y) * mWidth + (c + x)) * 4;
                    Uint i_s = ((r + dirtyY) * _width + (c + dirtyX)) * 4;
                    
                    for(Uint n = 0; n < 4; n ++) {
                        
                        s[i_s + n] = p[i_p + n];
                        
                    }
                    
                }
            }
            
        }
        
        void Context::setFillStyle(Style * style) {
            _fillStyle = style;
        }
        
        Style * Context::fillStyle() {
            return _fillStyle.as<Style>();
        }
        
        void Context::setFillColor(Color color) {
            _fillColor = color;
        }
        
        Color Context::fillColor() {
            return _fillColor;
        }
        
        void Context::setStrokeStyle(Style * style) {
            _strokeStyle = style;
        }
        
        Style * Context::strokeStyle() {
            return _strokeStyle.as<Style>();
        }
        
        
        void Context::setStrokeColor(Color color) {
            _strokeColor = color;
        }
        
        Color Context::strokeColor() {
            return _strokeColor;
        }
        
        void Context::setShadowColor(Color v) {
            _shadowColor = v;
        }
        
        Color Context::shadowColor() {
            return _shadowColor;
        }
        
        void Context::setShadowBlur(Float v) {
            _shadowBlur = v;
        }
        
        Float Context::shadowBlur() {
            return _shadowBlur;
        }
        
        void Context::setShadowOffsetX(Float v) {
            _shadowOffsetX = v;
        }
        
        Float Context::shadowOffsetX() {
            return _shadowOffsetX;
        }
        
        void Context::setShadowOffsetY(Float v) {
            _shadowOffsetY = v;
        }
        
        Float Context::shadowOffsetY() {
            return _shadowOffsetY;
        }
        
        void Context::setLineCap(LineCapType v) {
            _lineCap = v;
        }
        
        LineCapType Context::lineCap() {
            return _lineCap;
        }
        
        void Context::setLineJoin(LineJoinType v) {
            _lineJoin = v;
        }
        
        LineJoinType Context::lineJoin() {
            return _lineJoin;
        }
        
        void Context::setLineWidth(Float v) {
            _lineWidth = v;
        }
        
        Float Context::lineWidth() {
            return _lineWidth;
        }
        
        void Context::setMiterLimit(Float v) {
            _miterLimit = v;
        }
        
        Float Context::miterLimit() {
            return _miterLimit;
        }
        
        void Context::setFont(Font v) {
            _font = v;
        }
        
        Font Context::font() {
            return _font;
        }
        
        void Context::setTextAlign(TextAlign v) {
            _textAlign = v;
        }
        
        TextAlign Context::textAlign() {
            return _textAlign;
        }
        
        void Context::setTextBaseline(TextBaseline v) {
            _textBaseline = v;
        }
        
        TextBaseline Context::textBaseline() {
            return _textBaseline;
        }
        
        void Context::setGlobalAlpha(Float v) {
            _globalAlpha = v;
        }
        
        Float Context::globalAlpha() {
            return _globalAlpha;
        }
        
        void Context::setGlobalCompositeOperation(GlobalCompositeOperation v) {
            _globalCompositeOperation = v;
        }
        
        GlobalCompositeOperation Context::globalCompositeOperation() {
            return _globalCompositeOperation;
        }
        
        Uint Context::width() {
            return _width;
        }
        
        Uint Context::height() {
            return _height;
        }
        
        kk::Strong Context::createLinearGradient(Float x0,Float y0, Float x1, Float y1) {
            return new LinearGradient(x0,y0,x1,y1);
        }
        
        kk::Strong Context::createRadialGradient(Float x0,Float y0,Float r0, Float x1, Float y1, Float r1) {
            return new RadialGradient(x0,y0,r0,x1,y1,r1);
        }
        
        kk::Strong Context::createPattern(Image * image,PatternType type) {
            return new Pattern(image,type);
        }
        
        void Context::fillRect(Float x, Float y,Float width,Float height) {
            rect(x, y, width, height);
            fill();
        }
        
        void Context::strokeRect(Float x, Float y,Float width,Float height) {
            rect(x, y, width, height);
            stroke();
        }
        

        kk::Strong Context::createImageData(Uint width,Uint height) {
            if(width == 0 || height == 0) {
                return (kk::Object *) nullptr;
            }
            return new ImageData(width,height);
        }
        
        Pattern::Pattern(Image * image,PatternType type):_image((kk::Object *) image),_type(type) {
            
        }
        
        Image * Pattern::image() {
            return _image.as<Image>();
        }
        
        PatternType Pattern::type() {
            return _type;
        }
        
        
        void Gradient::addColorStop(Float loc,Color color) {
            _locations.push_back(loc);
            _colors.push_back(color);
        }
        
        
        RadialGradient::RadialGradient(Float x0,Float y0,Float r0, Float x1, Float y1, Float r1)
            :Gradient(),
        _x0(x0),_y0(y0),_r0(r0),
        _x1(x1),_y1(y1),_r1(r1) {
            
        }
        
        LinearGradient::LinearGradient(Float x0,Float y0, Float x1, Float y1)
            :Gradient(),
        _x0(x0),_y0(y0),
        _x1(x1),_y1(y1){
            
        }

        void ImageData::copyPixels(void * data) {
            memcpy(data, _data, _width * _height * 4);
        }
        
        Boolean ImageData::isCopyPixels() {
            return true;
        }
        
        Uint ImageData::width() {
            return _width;
        }
        
        Uint ImageData::height() {
            return _height;
        }
        
        Ubyte * ImageData::data() {
            return _data;
        }
        
        Uint ImageData::size() {
            return _width * _height * 4;
        }

        OSImage::OSImage(kk::CString src,kk::CString basePath):_src(src),_basePath(basePath) {
            
        }
        
        kk::CString OSImage::src() {
            return _src.c_str();
        }
        
        kk::CString OSImage::basePath() {
            return _basePath.c_str();
        }
        
    }
    
}
