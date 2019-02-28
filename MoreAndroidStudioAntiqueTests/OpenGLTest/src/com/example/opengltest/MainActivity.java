package com.example.opengltest;

import android.opengl.GLSurfaceView;
import android.opengl.GLSurfaceView.Renderer;
import android.os.Bundle;
import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.view.Menu;
import android.view.Window;
import android.view.WindowManager;

public class MainActivity extends Activity {
	
	private GLSurfaceView mSurfaceView;
	private GLSurfaceView mGLView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);

		if ( hasGLES20() ) {
			mGLView = new GLSurfaceView(this);
			mGLView.setEGLContextClientVersion(2);
			mGLView.setPreserveEGLContextOnPause(true);
			mGLView.setRenderer(new GLES20Renderer());
		} else {
			// Time to get a new phone, OpenGL ES 2.0 not supported
		}
		setContentView(mGLView);
	}
	
	private boolean hasGLES20()
	{
		ActivityManager am = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
		ConfigurationInfo info = am.getDeviceConfigurationInfo();
		return info.reqGlEsVersion >= 0x20000;
	}

	@Override
	protected void onResume()
	{
		super.onResume();
		// The activity must call the GL surface view's onResume() on
		// activity onResume();
		if ( mSurfaceView != null ) {
			mSurfaceView.onResume();
		}
	}
	
	@Override
	protected void onPause() {
		super.onPause();
		// The activity must call the GL surface view's onPause() on
		// activity onPause().
		if ( mSurfaceView != null ) {
			mSurfaceView.onPause();
		}
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
