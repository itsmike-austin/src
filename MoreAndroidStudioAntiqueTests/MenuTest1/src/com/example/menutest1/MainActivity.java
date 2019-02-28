package com.example.menutest1;

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
		// Inflate the menu; this adds items to the action bar if it is present.
		// getMenuInflater().inflate(R.menu.main, menu);
		super.onCreateOptionsMenu(menu);
		
		this.myMenu = menu;
		
		addRegularMenuItems(menu);
		addSecondaryMenuItems(menu);

		return true;
	}
	
	private void addRegularMenuItems(Menu menu)
	{
		int Base = Menu.FIRST;
		
		menu.add(Base,Base,Base,"append");
		menu.add(Base,Base+1,Base+1,"item2");
		menu.add(Base,Base+2,Base+2,"clear");
		menu.add(Base,Base+3,Base+3,"hide secondary");
		menu.add(Base,Base+4,Base+4,"show secondary");
		menu.add(Base,Base+5,Base+5,"enable secondary");
		menu.add(Base,Base+6,Base+6,"check secondary");
		menu.add(Base,Base+7,Base+7,"uncheck secondary");
	}
	
	private void addSecondaryMenuItems(Menu menu)
	{
		int Base = Menu.CATEGORY_SECONDARY;
		menu.add(Base,Base+1,Base+1,"sec. item 1");
		menu.add(Base,Base+2,Base+2,"sec. item 2");
		menu.add(Base,Base+3,Base+3,"sec. item 3");
		menu.add(Base,Base+4,Base+4,"sec. item 4");
		menu.add(Base,Base+5,Base+5,"sec. item 5");
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item)
	{
		switch( item.getItemId() )
		{
		case 1:
			appendText("\nhello");
			break;
		case 2:
			appendText("\nitem2");
			break;
		case 3:
			emptyText();
			break;
		case 4:
			// hide secondary
			this.appendMenuItemText(item);
			this.myMenu.setGroupVisible(Menu.CATEGORY_SECONDARY,false);
			break;
		case 5:
			// show secondary
			this.appendMenuItemText(item);
			this.myMenu.setGroupVisible(Menu.CATEGORY_SECONDARY,true);
			break;
		case 6:
			// enable secondary
			this.appendMenuItemText(item);
			this.myMenu.setGroupEnabled(Menu.CATEGORY_SECONDARY,true);
			break;
		case 7:
			// disable secondary
			this.appendMenuItemText(item);
			this.myMenu.setGroupEnabled(Menu.CATEGORY_SECONDARY,false);
			break;
		case 8:
			// check secondary
			this.appendMenuItemText(item);
			myMenu.setGroupCheckable(Menu.CATEGORY_SECONDARY, true, false);
			break;
		case 9:
			// uncheck secondary
			this.appendMenuItemText(item);
			myMenu.setGroupCheckable(Menu.CATEGORY_SECONDARY,false,false);
			break;
		default:
			this.appendMenuItemText(item);
			break;
		}
		return true;
	}
	
	// Given a string fo text append it to the text view
	
	private void appendText(String text)
	{
		TextView tv = (TextView)this.findViewById(R.id.textViewId);
		tv.setText(tv.getText() + text);
	}
	
	// Given a menu item append its title to the TextView
	
	private void appendMenuItemText(MenuItem menuItem)
	{
		String title = menuItem.getTitle().toString();
		TextView tv = (TextView)this.findViewById(R.id.textViewId);
		tv.setText(tv.getText() + "\n" + title);
	}
	
	// Empty the text view text
	
	private void emptyText()
	{
		TextView tv = (TextView)this.findViewById(R.id.textViewId);
		tv.setText("");
	}

}
