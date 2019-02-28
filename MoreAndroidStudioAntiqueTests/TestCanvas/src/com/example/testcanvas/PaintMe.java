package com.example.testcanvas;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

public class PaintMe extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_paint_me);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_paint_me, menu);
		return true;
	}

}
