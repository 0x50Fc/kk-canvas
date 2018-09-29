//
//  WebGLContext.cc
//  KKCanvas
//
//  Created by zhanghailong on 2018/8/17.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#include "kk-config.h"
#include "WebGLContext.h"

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
        
        Context::Context(Uint width,Uint height):_width(width),_height(height) {
            
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
        
    }
    
}
