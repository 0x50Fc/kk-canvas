//
//  KKCanvasGLContext.m
//  KKCanvas
//
//  Created by hailong11 on 2018/9/29.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#import "KKCanvasGLContext.h"

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
        
        glGenFramebuffers(1, &_data.frame);
        glGenRenderbuffers(1, &_data.color);
        glGenRenderbuffers(1, &_data.depth);
        
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_STENCIL_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE , GL_ONE_MINUS_SRC_ALPHA);
        
        [EAGLContext setCurrentContext:nil];
        
    }
    return self;
}

-(void) recycle {
    
    [EAGLContext setCurrentContext:self];
    
    if(_data.frame) {
        glDeleteFramebuffers(1,&_data.frame);
        _data.frame = 0;
    }
    
    if(_data.color) {
        glDeleteFramebuffers(1,&_data.color);
        _data.color = 0;
    }
    
    if(_data.depth) {
        glDeleteFramebuffers(1,&_data.depth);
        _data.depth = 0;
    }
    
    [EAGLContext setCurrentContext:nil];
    
}

-(void) begin {
    
    glBindFramebuffer(GL_FRAMEBUFFER, _data.frame);
}

-(void) resizeLayer:(CAEAGLLayer *) layer {
    
    if(CGSizeEqualToSize(_resize, layer.bounds.size)) {
        return;
    }
    
    @synchronized (self) {
        
        _resize = layer.bounds.size;
        
        glBindRenderbuffer(GL_RENDERBUFFER, _data.color);
        
        [self renderbufferStorage:GL_RENDERBUFFER fromDrawable:layer];
        
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &_width);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &_height);
        
        glBindRenderbuffer(GL_RENDERBUFFER, _data.depth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8_OES, _width, _height);

        glBindFramebuffer(GL_FRAMEBUFFER, _data.frame);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _data.color);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _data.depth);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, _data.depth);
        
    }
    
    
}

-(void) display {
    glBindRenderbuffer(GL_RENDERBUFFER, _data.color);
    [self presentRenderbuffer:GL_RENDERBUFFER];
}

@end
