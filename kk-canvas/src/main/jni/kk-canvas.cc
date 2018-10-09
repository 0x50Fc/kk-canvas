//
// Created by hailong11 on 2018/10/9.
//

#include <jni.h>
#include "kk.h"
#include "kk-config.h"
#include "kk-script.h"
#include "kk-canvas.h"
#include "CGContext.h"
#include "WebGLContext.h"

static kk::DispatchQueue * KKCanvasDispatchQueue() {

    static kk::DispatchQueue * v = nullptr;

    if(v == nullptr) {
        v = new kk::DispatchQueue("KKCanvasDispatchQueue");
        v->retain();
    }

    return v;
}

static evdns_base * KKCanvasEventDNS() {
    static evdns_base * v = nullptr;
    if(v == nullptr) {
        evdns_base_new(KKCanvasDispatchQueue()->base(), EVDNS_BASE_INITIALIZE_NAMESERVERS);
    }
    return v;
}

static void KKCanvasElement_CanvasDrawFunc(kk::Canvas * canvas,kk::Object * CGContext) {

    jboolean isAttach = false;
    JNIEnv * env = kk_env(&isAttach);

    jweak object = (jweak) canvas->userdata();
    jclass clazz = env->GetObjectClass(object);

    {
        kk::CG::OSContext * v = dynamic_cast<kk::CG::OSContext *>(CGContext);

        if(v) {
            jmethodID method = env->GetMethodID(clazz,"displayCGContext","()V");
            env->CallVoidMethod(object,method);
            return;
        }
    }

    {
        kk::WebGL::Context * v = dynamic_cast<kk::WebGL::Context *>(CGContext);

        if(v) {
            jmethodID method = env->GetMethodID(clazz,"displayGLContext","()V");
            env->CallVoidMethod(object,method);
            v->end();
            return;
        }
    }

    if(isAttach) {
        gJavaVm->DetachCurrentThread();
    }

}

static void KKCanvasElement_CanvasEmitFunc(kk::Canvas * canvas) {

    jboolean isAttach = false;
    JNIEnv * env = kk_env(&isAttach);

    jweak object = (jweak) canvas->userdata();
    jclass clazz = env->GetObjectClass(object);

    jmethodID method = env->GetMethodID(clazz,"emitCGContext","()V");
    env->CallVoidMethod(object,method);

    if(isAttach) {
        gJavaVm->DetachCurrentThread();
    }

}

static void KKCanvasElement_CanvasGetContextFunc(kk::Canvas * canvas,kk::Object * CGContext) {

    kk::WebGL::Context * v = dynamic_cast<kk::WebGL::Context *>(CGContext);

    if(v) {

        jboolean isAttach = false;
        JNIEnv * env = kk_env(&isAttach);

        jweak object = (jweak) canvas->userdata();
        jclass clazz = env->GetObjectClass(object);

        {
            jmethodID method = env->GetMethodID(clazz,"beginGLContext","()V");
            env->CallVoidMethod(object,method,(jint)canvas->width(),(jint)canvas->height());
        }

        if(v->width() != canvas->width() || v->height() != canvas->height()) {
            {
                jmethodID method = env->GetMethodID(clazz,"resizeGLContext","(II)V");
                env->CallVoidMethod(object,method,(jint)canvas->width(),(jint)canvas->height());
            }
            v->setSize(canvas->width(), canvas->height());
        }

        v->setFramebuffer(0);
        v->begin();

        if(isAttach) {
            gJavaVm->DetachCurrentThread();
        }
    }



}

extern "C"
JNIEXPORT jlong JNICALL
Java_cn_kkmofang_canvas_CanvasElement_alloc(JNIEnv *env, jobject instance, jstring basePath_,
                                            jint width, jint height) {
    const char *basePath = env->GetStringUTFChars(basePath_, 0);

    kk::CanvasCallback cb = {
            KKCanvasElement_CanvasDrawFunc,
            KKCanvasElement_CanvasEmitFunc,
            KKCanvasElement_CanvasGetContextFunc,
    };

    kk::Canvas * v = new kk::Canvas(KKCanvasDispatchQueue(),
                                    KKCanvasEventDNS(),
                                    basePath,
                                    &cb,
                                    env->NewWeakGlobalRef(instance),
                                    width,
                                    height);

    v->retain();

    env->ReleaseStringUTFChars(basePath_, basePath);

    return (jlong)(long) v;
}

static void KKCanvasElement_Recycle(kk::DispatchQueue * queue,BK_DEF_ARG) {

    BK_GET(canvas, kk::Canvas)

    if(canvas == nullptr) {
        return;
    }

    jboolean isAttach = false;
    JNIEnv * env = kk_env(&isAttach);

    jweak object = (jweak) canvas->userdata();
    jclass clazz = env->GetObjectClass(object);

    {

        jmethodID method = env->GetMethodID(clazz,"beginGLContext","()V");
        env->CallVoidMethod(object,method);
    }


    canvas->release();


    {
        jmethodID method = env->GetMethodID(clazz,"endGLContext","()V");
        env->CallVoidMethod(object,method);
    }

    env->DeleteWeakGlobalRef(object);

    if(isAttach) {
        gJavaVm->DetachCurrentThread();
    }

}

extern "C"
JNIEXPORT void JNICALL
Java_cn_kkmofang_canvas_CanvasElement_dealloc(JNIEnv *env, jclass type, jlong ptr) {

    kk::Canvas * v = (kk::Canvas *) ptr;

    BK_CTX

    BK_WEAK(canvas, v)

    KKCanvasDispatchQueue()->async(KKCanvasElement_Recycle, BK_ARG);

}

extern "C"
JNIEXPORT void JNICALL
Java_cn_kkmofang_canvas_CanvasElement_exec__JLjava_lang_String_2(JNIEnv *env, jclass type,
                                                                 jlong ptr, jstring path_) {
    const char *path = env->GetStringUTFChars(path_, 0);


    kk::Canvas * v = (kk::Canvas *) ptr;

    v->exec(path);

    env->ReleaseStringUTFChars(path_, path);
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_kkmofang_canvas_CanvasElement_exec__JLjava_lang_String_2Ljava_lang_String_2(JNIEnv *env,
                                                                                    jclass type,
                                                                                    jlong ptr,
                                                                                    jstring code_,
                                                                                    jstring name_) {
    const char *code = env->GetStringUTFChars( code_, 0);
    const char *name = env->GetStringUTFChars( name_, 0);

    kk::Canvas * v = (kk::Canvas *) ptr;

    v->exec(code,name);

    env->ReleaseStringUTFChars( code_, code);
    env->ReleaseStringUTFChars( name_, name);
}

extern "C"
JNIEXPORT void JNICALL
Java_cn_kkmofang_canvas_CanvasElement_setSize(JNIEnv *env, jclass type, jlong ptr, jint width,
                                              jint height) {

    kk::Canvas * v = (kk::Canvas *) ptr;

    v->setSize((kk::Uint) width,(kk::Uint) height);

}

extern "C"
JNIEXPORT jlong JNICALL
Java_cn_kkmofang_canvas_CanvasElement_dukContext(JNIEnv *env, jclass type, jlong ptr) {
    kk::Canvas * v = (kk::Canvas *) ptr;
    return (jlong)(long) v->jsContext()->jsContext();
}
