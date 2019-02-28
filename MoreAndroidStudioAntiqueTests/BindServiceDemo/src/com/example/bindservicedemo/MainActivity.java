package com.example.bindservicedemo;

import java.util.ArrayList;
import java.util.List;

import android.os.Bundle;
import android.os.IBinder;
import android.app.ListActivity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.view.Menu;
import android.view.View;
import android.widget.ArrayAdapter;
import android.widget.Toast;

public class MainActivity extends ListActivity {
	
	private LocalWordService     s;
	private ArrayAdapter<String> adapter;
	private List<String>         wordList;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		wordList = new ArrayList<String>();
		
		adapter = new ArrayAdapter<String>(this,android.R.layout.simple_list_item_1,android.R.id.text1,wordList);
		
		setListAdapter(adapter);
	}
	
	@Override
	protected void onResume()
	{
		super.onResume();
		Intent intent = new Intent(this,LocalWordService.class);
		bindService(intent,mConnection,Context.BIND_AUTO_CREATE);
	}
	
	@Override
	protected void onPause()
	{
		super.onPause();
		unbindService(mConnection);
	}
	
	private ServiceConnection mConnection = new ServiceConnection()
	{
		@Override
		public void onServiceConnected(ComponentName className,IBinder binder)
		{
			LocalWordService.MyBinder b = (LocalWordService.MyBinder)binder;
			s = b.getService();
			Toast.makeText(MainActivity.this, "Connected", Toast.LENGTH_LONG).show();
		}
		
		@Override
		public void onServiceDisconnected(ComponentName className)
		{
			s = null;
		}
	};
	
	public void onClick(View v)
	{
		if ( s != null )
		{
			Toast.makeText(this, "Number of elements" + s.getWordList().size(), Toast.LENGTH_SHORT).show();
			wordList.clear();
			wordList.addAll(s.getWordList());
			adapter.notifyDataSetChanged();
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
