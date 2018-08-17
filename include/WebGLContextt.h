//
//  WebGLContextt.h
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

namespace kk {
    
    namespace WebGL {
        
        
        class Context : public kk::Object {
            
            
        };
        
    }
    
}

#endif /* WebGLContextt_h */
