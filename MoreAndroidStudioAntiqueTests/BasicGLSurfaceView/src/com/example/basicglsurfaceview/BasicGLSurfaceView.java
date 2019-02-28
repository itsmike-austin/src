package com.example.basicglsurfaceview;

import android.content.Context;
import android.opengl.GLSurfaceView;

class BasicGLSurfaceView extends GLSurfaceView
{
	public BasicGLSurfaceView(Context context)
	{
		super(context);
		setEGLContextClientVersion(2);
		setRenderer(new GLES20TriangleRenderer(context));
	}
}