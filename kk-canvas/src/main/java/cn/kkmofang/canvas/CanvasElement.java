package cn.kkmofang.canvas;

import android.os.Handler;
import android.view.SurfaceView;
import android.view.View;
import java.lang.ref.WeakReference;
import cn.kkmofang.duktape.BasicContext;
import cn.kkmofang.view.Element;
import cn.kkmofang.view.ViewElement;

/**
 * Created by zhanghailong on 2018/10/9.
 */

public class CanvasElement extends ViewElement {

    static {
        System.loadLibrary("duktape");
        System.loadLibrary("event");
        System.loadLibrary("kk-canvas");
    }

    protected GLContext _GLContext;

    protected final Handler _handler;

    public CanvasElement() {
        super();
        _handler = new Handler();
    }

    protected long _canvas = 0;

    @Override
    protected View createView() {
        return new CanvasView(viewContext.getContext());
    }


    protected void installCGContext() {

        if(_canvas != 0) {
            return;
        }

        if(this.view() == null) {
            return;
        }

        String path = get("path");

        String basePath = viewContext.getAbsolutePath(path == null ? "":path);

        _canvas = alloc(basePath,(int) Math.ceil(width()), (int)Math.ceil(height()));

        if(path != null) {
            exec(_canvas,"main.js");
        } else {
            String code = get("#text");
            if(code != null) {
                exec(_canvas, code, "kk-canvas");
            }
        }

    }

    protected void uninstallCGContext() {

        if(_canvas != 0) {
            dealloc(_canvas);
            _canvas = 0;
        }

        if(_GLContext != null) {
            _GLContext.recycle();
            _GLContext = null;
        }

    }

    public void setView(View v) {
        uninstallCGContext();
        super.setView(v);
        if(v != null) {
            installCGContext();
        }
    }

    protected void onLayout(View view) {
        if(_canvas != 0) {
            setSize(_canvas,(int) Math.ceil(width()), (int)Math.ceil(height()));
        }
        super.onLayout(view);
    }

    @Override
    public void recycle() {
        uninstallCGContext();
        super.recycle();
    }

    protected GLContext getGLContext() {

        if(_GLContext == null) {
            SurfaceView view = (SurfaceView) this.view();
            if(view == null) {
                return null;
            }
            _GLContext = new GLContext(view.getHolder(),(int) Math.ceil(width()), (int)Math.ceil(height()));
        }

        return _GLContext;
    }

    public void beginGLContext() {
        GLContext v = getGLContext();
        if(v != null) {
            v.begin();
        }
    }


    public void endGLContext() {
        GLContext v = getGLContext();
        if(v != null) {
            v.end();
        }
    }

    public void displayGLContext() {

        GLContext v = getGLContext();

        if(v != null) {
            v.display();
        }

        endGLContext();
    }

    public void displayCGContext() {

        GLContext v = getGLContext();
        if(v != null) {
            v.display();
        }

    }

    public void resizeGLContext(int width,int height) {

        GLContext v = getGLContext();

        if(v != null) {
            v.resize(width,height);
        }

    }

    public void emitCGContext() {

        if(_canvas == 0) {
            return;
        }

        DukContext dukContext = new DukContext(dukContext(_canvas));

        int top = dukContext.getTop();

        final String name;
        final Object data;

        if(top >0 && dukContext.isString(-top)) {
            name = dukContext.toString(-top);
        } else {
            name = null;
        }

        if(top > 1 ) {
            data = dukContext.toValue(-top +1);
        } else {
            data = null;
        }

        if(name != null) {
            final WeakReference<CanvasElement> element = new WeakReference<CanvasElement>(this);
            _handler.post(new Runnable() {
                @Override
                public void run() {
                    CanvasElement e = element.get();
                    if(e != null) {
                        Element.Event event = new Element.Event(e);
                        event.setData(data);
                        e.emit(name,event);
                    }
                }
            });
        }
    }

    private final native long alloc(String basePath,int width,int height);
    private static final native void dealloc(long ptr);
    private static final native void exec(long ptr,String path);
    private static final native void exec(long ptr,String code,String name);
    private static final native void setSize(long ptr,int width,int height);
    private static final native long dukContext(long ptr);


    private class DukContext extends BasicContext {

        protected DukContext(long ptr) {
            super(ptr);
        }

        @Override
        public void post(Runnable run) {

        }
    }
}
