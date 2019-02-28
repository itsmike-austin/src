package com.example.listviewbasic;

import java.util.Arrays;

import android.os.Build;
import android.os.Bundle;
import android.annotation.TargetApi;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.TextView;

@TargetApi(Build.VERSION_CODES.GINGERBREAD)
public class MainActivity extends Activity {
	
	String[] list = {"Bob","Harry","Marty"};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		String[] joe = Arrays.copyOf(list, list.length+1 );
		joe[list.length] = new String("David");
		
		ArrayAdapter adapter = new ArrayAdapter<String>(
				this,
				android.R.layout.simple_list_item_1,
				joe);
		
		ListView listview = (ListView)findViewById(R.id.listView1);
		listview.setAdapter(adapter);
		listview.setOnItemClickListener(mMessageClickedHandler); 

		// listview.setOnClickListener(new clickItem());

		// adapter.add(new String[] {"David"});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
	private OnItemClickListener mMessageClickedHandler = new OnItemClickListener() {

		@Override
		public void onItemClick(AdapterView parent, View v, int position, long id) {
			TextView tv = (TextView)findViewById(R.id.textview);
			tv.setText( "Position: " + Integer.toString(position) + " Long: " + Long.toString(id) );
	    }
	};
}
