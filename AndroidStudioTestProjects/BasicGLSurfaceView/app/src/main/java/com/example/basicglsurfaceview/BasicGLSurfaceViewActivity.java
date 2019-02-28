package com.example.basicglsurfaceview;

import android.os.Bundle;
import android.app.Activity;

public class BasicGLSurfaceViewActivity extends Activity
{
	private BasicGLSurfaceView mView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		mView = new BasicGLSurfaceView(getApplication());
		setContentView(mView);
	}

	@Override
	protected void onPause()
	{
		super.onPause();
		mView.onPause();
	}
	
	@Override
	protected void onResume()
	{
		super.onResume();
		mView.onResume();
	}

}
