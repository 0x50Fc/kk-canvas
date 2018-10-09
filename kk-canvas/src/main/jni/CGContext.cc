//
// Created by zhanghailong on 2018/10/8.
//


#include "kk-config.h"
#include "CGContext.h"
#include "kk-script.h"

namespace kk {

    namespace CG {

        IMP_SCRIPT_CLASS_BEGIN_NOALLOC(&Context::ScriptClass, OSContext, CGOSContext)

        IMP_SCRIPT_CLASS_END

        OSContext::OSContext(Uint width,Uint height):Context(width,height){

        }

        OSContext::~OSContext() {

        }

        Ubyte * OSContext::getContextData() {
            return (Ubyte *) nullptr;
        }

        void OSContext::save() {

        }

        void OSContext::restore() {

        }

        void OSContext::rect(Float x, Float y,Float width,Float height) {

        }

        void OSContext::fillRect(Float x, Float y,Float width,Float height) {
            Context::fillRect(x, y, width, height);
        }

        void OSContext::strokeRect(Float x, Float y,Float width,Float height) {
            Context::strokeRect(x, y, width, height);
        }

        void OSContext::clearRect(Float x, Float y,Float width,Float height) {

        }

        void OSContext::fill() {

        }

        void OSContext::stroke() {

        }

        void OSContext::beginPath() {

        }

        void OSContext::closePath() {

        }

        void OSContext::moveTo(Float x,Float y) {

        }

        void OSContext::lineTo(Float x,Float y) {

        }

        void OSContext::clip() {

        }

        void OSContext::quadraticCurveTo(Float cpx,Float cpy,Float x,Float y) {

        }

        void OSContext::bezierCurveTo(Float cp1x,Float cp1y,Float cp2x,Float cp2y,Float x,Float y) {

        }

        void OSContext::arc(Float x,Float y,Float r, Float sAngle,Float eAngle,Boolean counterclockwise) {

        }

        void OSContext::arcTo(Float x1,Float y1,Float x2,Float y2,Float r) {

        }

        Boolean OSContext::isPointInPath(Float x,Float y) {
            return false;
        }

        void OSContext::scale(Float sx,Float sy) {

        }

        void OSContext::rotate(Float angle) {

        }

        void OSContext::translate(Float dx,Float dy) {

        }

        void OSContext::transform(Float a,Float b,Float c,Float d,Float e,Float f) {

        }

        void OSContext::setTransform(Float a,Float b,Float c,Float d,Float e,Float f) {

        }


        void OSContext::fillText(kk::CString text,Float x,Float y,Float maxWidth) {

        }

        void OSContext::strokeText(kk::CString text,Float x,Float y,Float maxWidth) {

        }

        Float OSContext::measureText(kk::CString text) {
            return 0;
        }

        void OSContext::drawImage(Image * image,Float sx,Float sy,Float swidth,Float sheight,Float x,Float y,Float width,Float height) {

        }


        void OSContext::setFillStyle(Style * v) {
            Context::setFillStyle(v);


        }

        void OSContext::setFillColor(Color v) {
            Context::setFillColor(v);

        }

        void OSContext::setStrokeStyle(Style * v) {
            Context::setStrokeStyle(v);

        }

        void OSContext::setStrokeColor(Color v) {
            Context::setStrokeColor(v);

        }

        void OSContext::setShadowColor(Color v) {
            Context::setShadowColor(v);
        }

        void OSContext::setShadowBlur(Float v) {
            Context::setShadowBlur(v);
        }

        void OSContext::setShadowOffsetX(Float v) {
            Context::setShadowOffsetX(v);
        }

        void OSContext::setShadowOffsetY(Float v) {
            Context::setShadowOffsetY(v);
        }

        void OSContext::setLineCap(LineCapType v) {
            Context::setLineCap(v);
        }

        void OSContext::setLineJoin(LineJoinType v) {
            Context::setLineJoin(v);
        }

        void OSContext::setLineWidth(Float v) {
            Context::setLineWidth(v);
        }

        void OSContext::setMiterLimit(Float v) {
            Context::setMiterLimit(v);
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
        }

        void OSContext::setGlobalCompositeOperation(GlobalCompositeOperation v) {
            Context::setGlobalCompositeOperation(v);
        }


        ImageData::ImageData(Uint width,Uint height):_width(width),_height(height) {
            Uint size = width * height * 4;
            _data = (Ubyte *) malloc(size);
            memset(_data, 0, size);
        }

        ImageData::~ImageData() {
            free(_data);
        }

    }

}


