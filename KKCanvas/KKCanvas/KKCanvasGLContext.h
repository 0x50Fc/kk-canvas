//
//  KKCanvasGLContext.h
//  KKCanvas
//
//  Created by hailong11 on 2018/9/29.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#include <UIKit/UIKit.h>
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/EAGL.h>

@interface KKCanvasGLContext : EAGLContext

@property(nonatomic,assign,readonly) GLsizei width;
@property(nonatomic,assign,readonly) GLsizei height;

-(void) begin;

-(void) resizeLayer:(CAEAGLLayer *) layer;

-(void) recycle;

-(void) display;

@end

