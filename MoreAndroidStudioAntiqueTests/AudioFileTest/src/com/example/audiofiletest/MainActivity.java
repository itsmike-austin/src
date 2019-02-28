package com.example.audiofiletest;

import android.os.Bundle;

import android.app.Activity;
import android.content.res.Configuration;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity {
	
	private Button DlgButton = null;

	private static AudioFileDialog dlg           = null;
	private static String          finalFileName = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		DlgButton = (Button)findViewById(R.id.button1);
		DlgButton.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View arg0) {
				dlg = new AudioFileDialog(arg0.getContext(),MainActivity.this);
				dlg.show();
				/*
				 * Programatic method for changing the screen orientation.
				 *
				 *				display = ((WindowManager)getSystemService(WINDOW_SERVICE)).getDefaultDisplay();
				 *				int orientation = display.getRotation();
				 *				switch( orientation )
				 *				{
				 *				case Surface.ROTATION_0:
				 *				case Surface.ROTATION_180:
				 *					setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
				 *					break;
				 *				case Surface.ROTATION_90:
				 *				case Surface.ROTATION_270:
				 *					setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
				 *				default:
				 *					break;
				 *				}
				 **/
			}
		});
	}
	
	@Override
	public void onConfigurationChanged(Configuration newConfig)
	{
		super.onConfigurationChanged(newConfig);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	public void clearDialog() {
		dlg = null;
	}
	
	public void addFileToList(String filename)
	{
		finalFileName = filename;
		Log.d("Got this filename: ",finalFileName);
	}

}
