package com.example.testoptionsmenu1;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MenuItem.OnMenuItemClickListener;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity implements OnMenuItemClickListener {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		menu.add(0,        // Group
				 1,        // item id
				 0,        // order
				"append"); // title
		
		menu.add(0,2,1,"item2");
		menu.add(0,3,2,"clear");
		
		int group1 = 1;
		menu.add(group1,4,1,"g1.item1");
		menu.add(group1,5,2,"g1.item2");
		
		int group2 = 2;
		menu.add(group2,6,1,"g2.item1");
		menu.add(group2,7,2,"g2.item2");
		
		menu.setGroupCheckable(0,true,true);
		menu.setGroupCheckable(1,true,false);
		
		// Inflate the menu; this adds items to the action bar if it is present.
		// getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item)
	{
		TextView txt = (TextView)findViewById(R.id.text1);
		txt.setText("inside onOptionsItemSelected: " + item.getItemId());
		
		return super.onOptionsItemSelected(item);
	}

	@Override
	public boolean onMenuItemClick(MenuItem item)
	{
		TextView txt = (TextView)findViewById(R.id.text1);
		txt.setText("inside onMenuItemClick: " + item.getItemId() );
		return false;
	}
}
