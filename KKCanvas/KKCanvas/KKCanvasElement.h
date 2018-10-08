//
//  KKCanvasElement.h
//  KKCanvas
//
//  Created by hailong11 on 2018/9/27.
//  Copyright © 2018年 kkmofang.cn. All rights reserved.
//

#import <KKView/KKView.h>
#import <KKDuktape/KKDuktape.h>
#import <KKEvent/KKEvent.h>

#ifdef __cplusplus
kk::DispatchQueue * KKCanvasDispatchQueue(void);
evdns_base * KKCanvasEventDNS(void);
#endif

#ifdef __cplusplus
extern "C" {
#endif
    
    dispatch_queue_t KKCanvasQueue(void);

#ifdef __cplusplus
}
#endif

@interface KKCanvasElement : KKViewElement

-(void) installCGContext;

-(void) uninstallCGContext;

@end
