package com.example.styledattributedemo;

import android.R.color;
import android.support.v7.app.ActionBarActivity;
import android.content.res.TypedArray;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

public class MainActivity extends ActionBarActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		int attrs[] = {android.R.attr.textColor,android.R.attr.background,android.R.attr.text};
		
		// Parse the attribute attray from the custom styles
		
		TypedArray ta = obtainStyledAttributes(R.style.MyCustomStyle,attrs);
		
		String text = ta.getString(2);
		
		int textColor = ta.getColor(0, Color.BLACK);
		int bgColor   = ta.getColor(1, Color.BLACK);
		
		TextView tv = (TextView)findViewById(R.id.textView1);
		tv.setText(text);
		tv.setBackgroundColor(bgColor);
		tv.setTextColor(textColor);
		
		ta.recycle();
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
}
