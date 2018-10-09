//
//  KKCanvasGLContext.m
//  KKCanvas
//
//  Created by hailong11 on 2018/9/29.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#import "KKCanvasGLContext.h"

#if 0
#define KK_GL_ERROR(name) for(GLenum v = glGetError(); v !=0; v = 0) { NSLog(@"[KK] [WebGL] [ERROR] %s(%d) %s: %x",__FILE__,__LINE__,__FUNCTION__,v); } NSLog(@"[KK] [WebGL] %s",#name);
#else
#define KK_GL_ERROR(name)
#endif

@interface KKCanvasGLContext () {
    struct {
        GLuint frame;
        GLuint color;
        GLuint depth;
    } _data;
    CGSize _resize;
}

@end

@implementation KKCanvasGLContext

-(instancetype) initWithAPI:(EAGLRenderingAPI)api {
    if((self = [super initWithAPI:api])) {
        self.multiThreaded = YES;
        
        [EAGLContext setCurrentContext:self];
        
        glGenFramebuffers(1, &_data.frame); KK_GL_ERROR(glGenFramebuffers)
        glGenRenderbuffers(1, &_data.color); KK_GL_ERROR(glGenRenderbuffers)
        glGenRenderbuffers(1, &_data.depth); KK_GL_ERROR(glGenRenderbuffers)
        
        [EAGLContext setCurrentContext:nil];
        
    }
    return self;
}

-(GLuint) framebuffer {
    return _data.frame;
}

-(void) dealloc {
    NSLog(@"[KK] [KKCanvasGLContext] [dealloc]");
}

-(void) recycle {
    
    glDeleteFramebuffers(1,&_data.frame); KK_GL_ERROR(glDeleteFramebuffers)
    glDeleteRenderbuffers(1,&_data.color); KK_GL_ERROR(glDeleteRenderbuffers)
    glDeleteRenderbuffers(1,&_data.depth); KK_GL_ERROR(glDeleteRenderbuffers)
    
}

-(void) begin {
//    NSLog(@"[KK] [WebGL] >>>>>>>>>>");
    glBindFramebuffer(GL_FRAMEBUFFER, _data.frame); KK_GL_ERROR(glBindFramebuffer)
    glBindRenderbuffer(GL_RENDERBUFFER, _data.color); KK_GL_ERROR(glBindRenderbuffer)
}

-(void) resizeLayer:(CAEAGLLayer *) layer {
    
    if(CGSizeEqualToSize(_resize, layer.bounds.size)) {
        return;
    }
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.color); KK_GL_ERROR(glBindRenderbuffer)
    
    [self renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer]; KK_GL_ERROR(renderbufferStorage)
    
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &_width); KK_GL_ERROR(glGetRenderbufferParameteriv)
    glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &_height); KK_GL_ERROR(glGetRenderbufferParameteriv)
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.depth); KK_GL_ERROR(glBindRenderbuffer)
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, _width, _height); KK_GL_ERROR(glRenderbufferStorage)
    
    glBindFramebuffer(GL_FRAMEBUFFER, _data.frame); KK_GL_ERROR(glBindFramebuffer)
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _data.color); KK_GL_ERROR(glFramebufferRenderbuffer)
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _data.depth); KK_GL_ERROR(glFramebufferRenderbuffer)
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _data.depth); KK_GL_ERROR(glFramebufferRenderbuffer)
    
    glBindRenderbuffer(GL_RENDERBUFFER, _data.color); KK_GL_ERROR(glBindRenderbuffer)
    
    glEnable(GL_DEPTH_TEST); KK_GL_ERROR(glEnable GL_DEPTH_TEST)
    glEnable(GL_STENCIL_TEST); KK_GL_ERROR(glEnable GL_STENCIL_TEST)
    glEnable(GL_SCISSOR_TEST); KK_GL_ERROR(glEnable GL_SCISSOR_TEST)
    glEnable(GL_BLEND); KK_GL_ERROR(glEnable GL_BLEND)
    glBlendFunc(GL_ONE , GL_ONE_MINUS_SRC_ALPHA); KK_GL_ERROR(glBlendFunc)
    
//    glEnable(GL_POINT_SMOOTH); KK_GL_ERROR(glEnable GL_POINT_SMOOTH)
//    glEnable(GL_LINE_SMOOTH); KK_GL_ERROR(glEnable GL_LINE_SMOOTH)
//    glHint(GL_POINT_SMOOTH_HINT,GL_NICEST); KK_GL_ERROR(glHint GL_POINT_SMOOTH_HINT)
//    glHint(GL_LINE_SMOOTH_HINT,GL_NICEST); KK_GL_ERROR(glHint GL_LINE_SMOOTH_HINT)
    
    glViewport(0, 0, _width, _height); KK_GL_ERROR(glViewport)
    
}

-(void) display {
    glBindRenderbuffer(GL_RENDERBUFFER, _data.color); KK_GL_ERROR(glBindRenderbuffer)
    [self presentRenderbuffer:GL_RENDERBUFFER]; KK_GL_ERROR(presentRenderbuffer)
//    NSLog(@"[KK] [WebGL] <<<<<<<<<<<");
}

@end
