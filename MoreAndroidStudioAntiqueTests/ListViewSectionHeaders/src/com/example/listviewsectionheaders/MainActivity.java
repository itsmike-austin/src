package com.example.listviewsectionheaders;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.ExpandableListView;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		// Set up an expandable list
		
		ExpandableListView list = new ExpandableListView(this);
		
		list.setGroupIndicator(null);
		list.setChildIndicator(null);
		
		// Set up simple data and the new adapter
		
		String[] titles  = {"Fruits","Vegetables","Meats"};
		String[] fruits  = {"Apples","Oranges"};
		String[] veggies = {"Carrots","Peas","Broccoli"};
		String[] meats   = {"Pork","Chicken"};
		
		String[][] contents = {fruits,veggies,meats};
		
		SimplerExpandableListAdapter adapter =
				new SimplerExpandableListAdapter(this,titles,contents);
		
		list.setAdapter(adapter);
		
		//* Comment this section for regular expansion
		
		for( int i=0 ; i < adapter.getGroupCount() ; ++i )
		{
			list.expandGroup(i);
		}
		
		// */ End Comment
		
		setContentView(list);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

}
