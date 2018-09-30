//
//  WebGLContext.h
//  KKCanvas
//
//  Created by zhanghailong on 2018/8/17.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#ifndef WebGLContextt_h
#define WebGLContextt_h


#if defined(KK_PLATFORM_IOS)

#include <KKObject/KKObject.h>

#else

#include "kk-object.h"

#endif


#if defined(__APPLE__)

#if TARGET_OS_OSX
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#else
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#endif

#elif defined(__ANDROID_API__)

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#endif


namespace kk {
    
    namespace WebGL {
        
        class GLObject : public kk::Object {
        public:
            GLObject(GLuint value);
            virtual GLuint value();
        protected:
            GLuint _value;
        };
        
        class Buffer : public GLObject {
        public:
            Buffer(GLuint value);
        };
        
        class Texture : public GLObject {
        public:
            Texture(GLuint value);
        };
        
        class Program : public GLObject {
        public:
            Program(GLuint value);
        };
        
        class Shader : public GLObject{
        public:
            Shader(GLuint value);
        };
        
        class Framebuffer : public GLObject{
        public:
            Framebuffer(GLuint value);
        };
        
        class Renderbuffer : public GLObject{
        public:
            Renderbuffer(GLuint value);
        };
    
        class Context : public kk::Object , public kk::script::IObject {
            
        public:
            
            Context(Uint width,Uint height);
            
            DEF_SCRIPT_CLASS_NOALLOC
            
            DEF_SCRIPT_PROPERTY_READONLY(drawingBufferWidth)
            DEF_SCRIPT_PROPERTY_READONLY(drawingBufferHeight)
  
            DEF_SCRIPT_METHOD(activeTexture)
            DEF_SCRIPT_METHOD(attachShader)
            DEF_SCRIPT_METHOD(bindAttribLocation)
            DEF_SCRIPT_METHOD(bindBuffer)
            DEF_SCRIPT_METHOD(bindFramebuffer)
            DEF_SCRIPT_METHOD(bindRenderbuffer)
            DEF_SCRIPT_METHOD(bindTexture)
            DEF_SCRIPT_METHOD(blendColor)
            DEF_SCRIPT_METHOD(blendEquation)
            DEF_SCRIPT_METHOD(blendEquationSeparate)
            DEF_SCRIPT_METHOD(blendFunc)
            DEF_SCRIPT_METHOD(blendFuncSeparate)
            DEF_SCRIPT_METHOD(bufferData)
            DEF_SCRIPT_METHOD(bufferSubData)
            DEF_SCRIPT_METHOD(checkFramebufferStatus)
            DEF_SCRIPT_METHOD(clear)
            DEF_SCRIPT_METHOD(clearColor)
            DEF_SCRIPT_METHOD(clearDepth)
            DEF_SCRIPT_METHOD(clearStencil)
            DEF_SCRIPT_METHOD(colorMask)
            DEF_SCRIPT_METHOD(compileShader)
            DEF_SCRIPT_METHOD(compressedTexImage2D)
            DEF_SCRIPT_METHOD(compressedTexSubImage2D)
            DEF_SCRIPT_METHOD(copyTexImage2D)
            DEF_SCRIPT_METHOD(copyTexSubImage2D)
            
            DEF_SCRIPT_METHOD(createBuffer)
            DEF_SCRIPT_METHOD(createFramebuffer)
            DEF_SCRIPT_METHOD(createProgram)
            DEF_SCRIPT_METHOD(createRenderbuffer)
            DEF_SCRIPT_METHOD(createShader)
            DEF_SCRIPT_METHOD(createTexture)
            
            DEF_SCRIPT_METHOD(cullFace)
            
            DEF_SCRIPT_METHOD(deleteBuffer)
            DEF_SCRIPT_METHOD(deleteFramebuffer)
            DEF_SCRIPT_METHOD(deleteProgram)
            DEF_SCRIPT_METHOD(deleteRenderbuffer)
            DEF_SCRIPT_METHOD(deleteShader)
            DEF_SCRIPT_METHOD(deleteTexture)
            
            DEF_SCRIPT_METHOD(depthFunc)
            DEF_SCRIPT_METHOD(depthMask)
            DEF_SCRIPT_METHOD(depthRange)
            DEF_SCRIPT_METHOD(detachShader)
            DEF_SCRIPT_METHOD(disable)
            DEF_SCRIPT_METHOD(disableVertexAttribArray)
            DEF_SCRIPT_METHOD(drawArrays)
            DEF_SCRIPT_METHOD(drawElements)
            
            DEF_SCRIPT_METHOD(enable)
            DEF_SCRIPT_METHOD(enableVertexAttribArray)
            DEF_SCRIPT_METHOD(finish)
            DEF_SCRIPT_METHOD(flush)
            DEF_SCRIPT_METHOD(framebufferRenderbuffer)
            DEF_SCRIPT_METHOD(framebufferTexture2D)
            DEF_SCRIPT_METHOD(frontFace)
            
            DEF_SCRIPT_METHOD(generateMipmap)
            
            DEF_SCRIPT_METHOD(getActiveAttrib)
            DEF_SCRIPT_METHOD(getActiveUniform)
            DEF_SCRIPT_METHOD(getAttachedShaders)
            
            DEF_SCRIPT_METHOD(getAttribLocation)
            
            DEF_SCRIPT_METHOD(getBufferParameter)
            DEF_SCRIPT_METHOD(getParameter)
            
            DEF_SCRIPT_METHOD(getError)
            
            DEF_SCRIPT_METHOD(getFramebufferAttachmentParameter)
            DEF_SCRIPT_METHOD(getProgramParameter)
            DEF_SCRIPT_METHOD(getProgramInfoLog)
            DEF_SCRIPT_METHOD(getRenderbufferParameter)
            DEF_SCRIPT_METHOD(getShaderParameter)
            DEF_SCRIPT_METHOD(getShaderPrecisionFormat)
            DEF_SCRIPT_METHOD(getShaderInfoLog)
            
            DEF_SCRIPT_METHOD(getShaderSource)
            
            DEF_SCRIPT_METHOD(getTexParameter)
            
            DEF_SCRIPT_METHOD(getUniform)
            
            DEF_SCRIPT_METHOD(getUniformLocation)
            
            DEF_SCRIPT_METHOD(getVertexAttrib)
            
            DEF_SCRIPT_METHOD(getVertexAttribOffset)
            
            DEF_SCRIPT_METHOD(hint)
            DEF_SCRIPT_METHOD(isBuffer)
            DEF_SCRIPT_METHOD(isEnabled)
            DEF_SCRIPT_METHOD(isFramebuffer)
            DEF_SCRIPT_METHOD(isProgram)
            DEF_SCRIPT_METHOD(isRenderbuffer)
            DEF_SCRIPT_METHOD(isShader)
            DEF_SCRIPT_METHOD(isTexture)
            DEF_SCRIPT_METHOD(lineWidth)
            DEF_SCRIPT_METHOD(linkProgram)
            DEF_SCRIPT_METHOD(pixelStorei)
            DEF_SCRIPT_METHOD(polygonOffset)
            
            DEF_SCRIPT_METHOD(readPixels)
            
            void extracted(duk_context *ctx);
            
            DEF_SCRIPT_METHOD(renderbufferStorage)
            DEF_SCRIPT_METHOD(sampleCoverage)
            DEF_SCRIPT_METHOD(scissor)
            
            DEF_SCRIPT_METHOD(shaderSource)
            
            DEF_SCRIPT_METHOD(stencilFunc)
            DEF_SCRIPT_METHOD(stencilFuncSeparate)
            DEF_SCRIPT_METHOD(stencilMask)
            DEF_SCRIPT_METHOD(stencilMaskSeparate)
            DEF_SCRIPT_METHOD(stencilOp)
            DEF_SCRIPT_METHOD(stencilOpSeparate)
            
            DEF_SCRIPT_METHOD(texImage2D)
            
            DEF_SCRIPT_METHOD(texParameterf)
            DEF_SCRIPT_METHOD(texParameteri)
            
            DEF_SCRIPT_METHOD(texSubImage2D)
            
            DEF_SCRIPT_METHOD(uniform1f)
            DEF_SCRIPT_METHOD(uniform1fv)
            DEF_SCRIPT_METHOD(uniform1i)
            DEF_SCRIPT_METHOD(uniform1iv)
            DEF_SCRIPT_METHOD(uniform2f)
            DEF_SCRIPT_METHOD(uniform2fv)
            DEF_SCRIPT_METHOD(uniform2i)
            DEF_SCRIPT_METHOD(uniform2iv)
            DEF_SCRIPT_METHOD(uniform3f)
            DEF_SCRIPT_METHOD(uniform3fv)
            DEF_SCRIPT_METHOD(uniform3i)
            DEF_SCRIPT_METHOD(uniform3iv)
            DEF_SCRIPT_METHOD(uniform4f)
            DEF_SCRIPT_METHOD(uniform4fv)
            DEF_SCRIPT_METHOD(uniform4i)
            DEF_SCRIPT_METHOD(uniform4iv)
            
            DEF_SCRIPT_METHOD(uniformMatrix2fv)
            DEF_SCRIPT_METHOD(uniformMatrix3fv)
            DEF_SCRIPT_METHOD(uniformMatrix4fv)
            
            DEF_SCRIPT_METHOD(useProgram)
            DEF_SCRIPT_METHOD(validateProgram)
            
            DEF_SCRIPT_METHOD(vertexAttrib1f)
            DEF_SCRIPT_METHOD(vertexAttrib1fv)
            DEF_SCRIPT_METHOD(vertexAttrib2f)
            DEF_SCRIPT_METHOD(vertexAttrib2fv)
            DEF_SCRIPT_METHOD(vertexAttrib3f)
            DEF_SCRIPT_METHOD(vertexAttrib3fv)
            DEF_SCRIPT_METHOD(vertexAttrib4f)
            DEF_SCRIPT_METHOD(vertexAttrib4fv)
            DEF_SCRIPT_METHOD(vertexAttribPointer)
            
            DEF_SCRIPT_METHOD(viewport)
            
            DEF_SCRIPT_METHOD(getSupportedExtensions)
            DEF_SCRIPT_METHOD(getExtension)

            virtual void setSize(Uint width,Uint height);
            
            virtual Uint width();
            virtual Uint height();
            
        protected:
            Uint _width;
            Uint _height;
            
        };
        
    }
    
}

#endif /* WebGLContextt_h */
