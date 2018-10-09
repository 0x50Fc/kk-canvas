package cn.kkmofang.canvas;

import android.graphics.PixelFormat;
import android.view.SurfaceHolder;
import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by zhanghailong on 2018/10/9.
 */

public class GLContext implements SurfaceHolder.Callback{

    private final EGLSurface _surface;
    private final EGLDisplay _dpy;
    private final EGL10 _egl;
    private final EGLConfig _config;
    private final EGLContext _context;
    private final SurfaceHolder _holder;
    protected int _width;
    protected int _height;

    public GLContext(SurfaceHolder holder,int width,int height) {

        holder.setFormat(PixelFormat.TRANSLUCENT);
        holder.addCallback(this);
        _holder = holder;
        _egl = (EGL10) EGLContext.getEGL();
        _dpy = _egl.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY);
        int[] version = new int[2];
        _egl.eglInitialize(_dpy, version);
        int[] configSpec = {
                EGL10.EGL_LEVEL, 0,
                EGL10.EGL_RED_SIZE,8,
                EGL10.EGL_GREEN_SIZE,8,
                EGL10.EGL_BLUE_SIZE,8,
                EGL10.EGL_ALPHA_SIZE,8,
                EGL10.EGL_DEPTH_SIZE,16,
                EGL10.EGL_STENCIL_SIZE,0,
                EGL10.EGL_RENDERABLE_TYPE, 4,
                EGL10.EGL_SAMPLE_BUFFERS, 1,
                EGL10.EGL_SAMPLES,4,
                EGL10.EGL_SURFACE_TYPE,EGL10.EGL_WINDOW_BIT,
                EGL10.EGL_TRANSPARENT_TYPE,1,
                EGL10.EGL_NONE};

        EGLConfig[] configs = new EGLConfig[1];

        int[] num_config = new int[1];

        _egl.eglChooseConfig(_dpy, configSpec, configs, 1, num_config);
        _config = configs[0];

        int attrs[] = {
//                EGL14.EGL_CONTEXT_CLIENT_VERSION, 2,
                12440, 2,
                EGL10.EGL_NONE, };

        _context = _egl.eglCreateContext(_dpy, _config, EGL10.EGL_NO_CONTEXT, attrs);
        _surface = _egl.eglCreateWindowSurface(_dpy, _config, _holder, null);

        _width = width;
        _height = height;

        onInit((GL10) _context.getGL(),_width,_height);
    }

    protected void onInit(GL10 gl,int width,int height) {
        _egl.eglMakeCurrent(_dpy, _surface, _surface, _context);
        onResize(gl,width,height);
    }

    protected void onResize(GL10 gl,int width,int height) {

        gl.glEnable(GL10.GL_DEPTH_TEST);
        gl.glEnable(GL10.GL_STENCIL_TEST);
        gl.glEnable(GL10.GL_SCISSOR_TEST);
        gl.glEnable(GL10.GL_CULL_FACE);
        gl.glEnable(GL10.GL_BLEND);
        gl.glBlendFunc(GL10.GL_ONE,GL10.GL_ONE_MINUS_SRC_ALPHA);
        gl.glViewport(0,0,width,height);

    }

    public void resize(int width,int height) {
        if(_width != width || _height != height) {
            _width = width;
            _height = height;
            onResize((GL10) _context.getGL(),_width,_height);
        }
    }

    public void begin() {
        _egl.eglMakeCurrent(_dpy, _surface, _surface, _context);
    }

    public void end() {
        _egl.eglMakeCurrent(_dpy, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_CONTEXT);
    }

    public void recycle() {
        _egl.eglMakeCurrent(_dpy, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_CONTEXT);
        _egl.eglDestroySurface(_dpy, _surface);
        _egl.eglDestroyContext(_dpy, _context);
        _egl.eglTerminate(_dpy);
        _holder.removeCallback(this);
    }

    public void display() {
        _egl.eglSwapBuffers(_dpy, _surface);
    }


    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int width, int height) {

    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {

    }
}
