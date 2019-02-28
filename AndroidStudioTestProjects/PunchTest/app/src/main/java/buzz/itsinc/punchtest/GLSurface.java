package buzz.itsinc.punchtest;

import android.content.Context;
import android.opengl.GLSurfaceView;

/**
 * Created by artwork on 1/11/2016.
 */

class GLSurface extends GLSurfaceView
{
    public GLSurface(Context context)
    {
        super(context);
        setEGLContextClientVersion(2);
        setRenderer(new TestCube(context));
    }
}

