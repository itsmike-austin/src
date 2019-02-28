package com.example.testoptionsmenu2;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;

public class MainActivity extends Activity {
	
	Menu myMenu = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		
		this.myMenu = menu;
		
		addRegularMenuItems(menu);
		addSecondaryMenuItems(menu);
		
		// Inflate the menu; this adds items to the action bar if it is present.
		//getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
	private void addRegularMenuItems(Menu menu)
	{
		int base = Menu.FIRST;
		
		menu.add(base,base,base,"append");
		menu.add(base,base+1,base+1,"item 2");
		menu.add(base,base+2,base+2,"clear");
		
		menu.add(base,base+3,base+3,"hide secondary");
		menu.add(base,base+4,base+4,"show secondary");
		
		menu.add(base,base+5,base+5,"enable secondary");
		menu.add(base,base+6,base+6,"disable secondary");
		
		menu.add(base,base+7,base+7,"check secondary");
		menu.add(base,base+8,base+8,"uncheck secondary");
	}
	
	private void addSecondaryMenuItems(Menu menu)
	{
		int base = Menu.CATEGORY_SECONDARY;
		
		menu.add(base,base+1,base+1,"sec. item 1");
		menu.add(base,base+2,base+2,"sec. item 2");
		menu.add(base,base+3,base+3,"sec. item 3");
		menu.add(base,base+3,base+3,"sec. item 4");
		menu.add(base,base+4,base+4,"sec. item 5");
			
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item)
	{
		int iid = item.getItemId();
		
		if ( iid == 1 ) {
			appendText("\nhello");
		} else if ( iid == 2 ) {
			appendText("\nitem2");
		} else if ( iid == 3 ) {
			emptyText();
		} else if ( iid ==4 ) {
			this.appendMenuItemText(item);
			this.myMenu.setGroupVisible(Menu.CATEGORY_SECONDARY,false);
		} else if ( iid == 5 ) {
			this.appendMenuItemText(item);
			this.myMenu.setGroupVisible(Menu.CATEGORY_SECONDARY,true);
		} else if ( iid == 6 ) {
			this.appendMenuItemText(item);
			this.myMenu.setGroupEnabled(Menu.CATEGORY_SECONDARY,true);
		} else if ( iid == 7 ) {
			this.appendMenuItemText(item);
			this.myMenu.setGroupEnabled(Menu.CATEGORY_SECONDARY,false);
		} else if ( iid == 8 ) {
			this.appendMenuItemText(item);
			this.myMenu.setGroupCheckable(Menu.CATEGORY_SECONDARY,true,false);
		} else if ( iid == 9 ) {
			this.appendMenuItemText(item);
			this.myMenu.setGroupCheckable(Menu.CATEGORY_SECONDARY,false,false);
		} else {
			this.appendMenuItemText(item);
		}
		return true;
	}
	
	private void appendText(String text )
	{
		TextView tv = (TextView)this.findViewById(R.id.textViewId);
		tv.setText(tv.getText() + text);
	}
	
	private void appendMenuItemText(MenuItem menuItem)
	{
		String title = menuItem.getTitle().toString();
		TextView tv = (TextView)this.findViewById(R.id.textViewId);
		tv.setText(tv.getText() + "\n" + title);
	}
	
	private void emptyText()
	{
		TextView tv = (TextView)this.findViewById(R.id.textViewId);
		tv.setText("");
	}
}
