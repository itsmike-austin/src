package com.example.testservice;

import android.os.Bundle;
import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends Activity {
	
	ComponentName thisService;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}
	
	public void startNewService(View view)
	{
		try {
			thisService = startService(new Intent(this,MyService.class));
		}catch(SecurityException s){
			Toast.makeText(this, "SecurityExecption", Toast.LENGTH_LONG).show();
			return;
		}catch(Exception e){
			Toast.makeText(this, e.getLocalizedMessage(), Toast.LENGTH_LONG).show();
			return;
		}
		if ( null == thisService ) Toast.makeText(this,"Start Failed",Toast.LENGTH_SHORT).show();
	}
	
	public void stopNewService(View view)
	{
		stopService(new Intent(this,MyService.class));
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
