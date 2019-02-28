package com.example.menutest10;

import android.annotation.TargetApi;
import android.app.ActionBar;
import android.app.Fragment;
import android.os.Build;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

@TargetApi(Build.VERSION_CODES.ICE_CREAM_SANDWICH)
public class MainActivity extends FragmentActivity  implements ActionBar.OnNavigationListener {

	private static final String STATE_SELECTED_NAVIGATION_ITEM = "selected_navigation_item";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		// Setup the action bar to show a dropdown list.
		
		final ActionBar actionBar = getActionBar();
		actionBar.setDisplayShowTitleEnabled(false);
		actionBar.setNavigationMode(ActionBar.NAVIGATION_MODE_LIST);
		
		final String[] dropdownValues = getResources().getStringArray(R.array.dropdown);
		
		// Specify a SpinnerAdapter to populate the dropdown list
		
		ArrayAdapter<String> adapter = new ArrayAdapter<String>(actionBar.getThemedContext(),
				android.R.layout.simple_spinner_item,
				android.R.id.text1,
				dropdownValues);
		
		adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
		
		// Setup the dropdown list navigation in the action bar
		
		actionBar.setListNavigationCallbacks(adapter,this);
		
		// Use getActionBar().getThemedContext() to ensure
		// that the text color is always appropriate for the action bar
		// background rather than the activity background.
	}
	
	@Override
	public void onRestoreInstanceState(Bundle savedInstanceState)
	{
		// Restore the previously serialized current dropdown position.
		if ( savedInstanceState.containsKey(STATE_SELECTED_NAVIGATION_ITEM) )
		{
			getActionBar().setSelectedNavigationItem(savedInstanceState.getInt(STATE_SELECTED_NAVIGATION_ITEM));
		}
	}
	
	@Override
	public void onSaveInstanceState(Bundle outState)
	{
		// Serialize the current dropdown position
		outState.putInt(STATE_SELECTED_NAVIGATION_ITEM,getActionBar().getSelectedNavigationIndex());
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	@Override
	public boolean onNavigationItemSelected(int position,long id)
	{
		// When the given dropdown item is selected, show its contents
		// in the container view.
		
		Fragment fragment = new DummySectionFragment();
		Bundle args = new Bundle();
		args.putInt(DummySectionFragment.ARG_SECTION_NUMBER,position+1);
		getFragmentManager().beginTransaction().replace(R.id.text,fragment).commit();
//		getFragmentManager().beginTransaction().replace(R.id.container,fragment).commit();
		return true;
	}
	
	// Dummy Fragment
	
	public static class DummySectionFragment extends Fragment
	{
		public static final String ARG_SECTION_NUMBER = "placeholder_text";
		
		@Override
		public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState)
		{
			TextView textView = new TextView(getActivity());
			textView.setGravity(Gravity.CENTER);
			textView.setText(Integer.toString(getArguments().getInt(ARG_SECTION_NUMBER)));
			return textView;
		}
	}
}
