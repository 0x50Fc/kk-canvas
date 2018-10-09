//
//  WebGLContext.cc
//  KKCanvas
//
//  Created by zhanghailong on 2018/8/17.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "WebGLContext.h"

#if defined(__ANDROID_API__)

typedef GLvoid (*glBindVertexArrayOESFunc)(GLuint array);
typedef GLvoid (*glDeleteVertexArraysOESFunc)(GLsizei n, const GLuint *arrays);
typedef GLvoid (*glGenVertexArraysOESFunc)(GLsizei n, GLuint *arrays);

static glBindVertexArrayOESFunc v_glBindVertexArrayOESFunc = nullptr;
static glDeleteVertexArraysOESFunc v_glDeleteVertexArraysOESFunc = nullptr;
static glGenVertexArraysOESFunc v_glGenVertexArraysOESFunc = nullptr;

static bool kk_glOES_is = 0;

static void kk_glOES(void) {
    if(kk_glOES_is == false) {
        v_glBindVertexArrayOESFunc = (glBindVertexArrayOESFunc)eglGetProcAddress ( "glGenVertexArraysOES" );
        v_glBindVertexArrayOESFunc = (glBindVertexArrayOESFunc)eglGetProcAddress ( "glBindVertexArrayOES" );
        v_glDeleteVertexArraysOESFunc = (glDeleteVertexArraysOESFunc)eglGetProcAddress ( "glDeleteVertexArraysOES" );
        kk_glOES_is = true;
    }
}

GLvoid glBindVertexArrayOES(GLuint array) {
    if(v_glBindVertexArrayOESFunc) {
        return v_glBindVertexArrayOESFunc(array);
    }
}
GLvoid glDeleteVertexArraysOES(GLsizei n, const GLuint *arrays) {
    if(v_glDeleteVertexArraysOESFunc) {
        v_glDeleteVertexArraysOESFunc(n,arrays);
    }
}

GLvoid glGenVertexArraysOES(GLsizei n, GLuint *arrays) {
    if(v_glGenVertexArraysOESFunc) {
        v_glGenVertexArraysOESFunc(n,arrays);
    }
}


#endif

namespace kk {
    
    
    namespace WebGL {
        
        GLObject::GLObject(GLuint value):_value(value) {
            
        }
        
        Buffer::Buffer(GLuint value):GLObject(value){}
        
        Texture::Texture(GLuint value):GLObject(value){}
        
        Program::Program(GLuint value):GLObject(value){}
        
        Shader::Shader(GLuint value):GLObject(value){}
        
        Framebuffer::Framebuffer(GLuint value):GLObject(value){}
        
        Renderbuffer::Renderbuffer(GLuint value):GLObject(value){}
        
        GLuint GLObject::value() {
            return _value;
        }
        
        Context::Context(Uint width,Uint height):_width(width),_height(height),_framebuffer(0),_vao(0) {
            
#if defined(__ANDROID_API__)
            kk_glOES();
#endif
            glGenVertexArraysOES(1, &_vao);
        }
        
        Context::~Context() {
            glDeleteVertexArraysOES(1, &_vao);
        }
        
        void Context::setSize(Uint width,Uint height) {
            _width = width;
            _height = height;
        }
        
        Uint Context::width() {
            return _width;
        }
        
        Uint Context::height() {
            return _height;
        }
        
        Uint Context::framebuffer() {
            return _framebuffer;
        }
        
        void Context::setFramebuffer(Uint v) {
            _framebuffer = v;
        }
        
        void Context::begin() {
            glBindVertexArrayOES(_vao);
        }
        
        void Context::end() {
            glBindVertexArrayOES(0);
        }
        
    }
    
}
