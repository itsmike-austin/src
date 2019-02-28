package com.example.spinmenutest;

import android.os.Bundle;
import android.annotation.SuppressLint;
import android.app.ActionBar;
import android.app.Activity;
import android.view.Menu;
import android.view.View;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

public class MainActivity extends Activity implements OnItemSelectedListener {

	private final String FileMenu[] = {"New","Open","Save","Save As","Quit" };
	private final String EditMenu[] = {"Select","Cut","Paste","Copy","Delete"};
	private final String DrawMenu[] = {"Properties","Defaults"};
	private final String OptsMenu[] = {"Preferences","Options"};
	private final String HelpMenu[] = {"Help","About"};
	
	Spinner s1 = null;
	Spinner s2 = null;
	Spinner s3 = null;
	Spinner s4 = null;
	Spinner s5 = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_RIGHT_ICON);
		setContentView(R.layout.activity_main);
		
		setFeatureDrawableResource(Window.FEATURE_RIGHT_ICON,R.drawable.ic_launcher);
		
		s1 = (Spinner)findViewById(R.id.file_spinner);
		ArrayAdapter<String> files = new ArrayAdapter<String>(this,
				android.R.layout.simple_spinner_item,FileMenu);
		files.setDropDownViewResource(android.R.layout.simple_dropdown_item_1line);
		s1.setAdapter(files);
		
		s2 = (Spinner)findViewById(R.id.edit_spinner);
		ArrayAdapter<String> edits = new ArrayAdapter<String>(this,
				android.R.layout.simple_spinner_item,EditMenu);
		edits.setDropDownViewResource(android.R.layout.simple_dropdown_item_1line);
		s2.setAdapter(edits);
		
		s3 = (Spinner)findViewById(R.id.draw_spinner);
		ArrayAdapter<String> draws = new ArrayAdapter<String>(this,
				android.R.layout.simple_spinner_item,DrawMenu);
		draws.setDropDownViewResource(android.R.layout.simple_dropdown_item_1line);
		s3.setAdapter(draws);
		
		s4 = (Spinner)findViewById(R.id.options_spinner);
		ArrayAdapter<String> opts = new ArrayAdapter<String>(this,
				android.R.layout.simple_spinner_item,OptsMenu);
		opts.setDropDownViewResource(android.R.layout.simple_dropdown_item_1line);
		s4.setAdapter(opts);
		
		s5 = (Spinner)findViewById(R.id.help_spinner);
		ArrayAdapter<String> hlps = new ArrayAdapter<String>(this,
				android.R.layout.simple_spinner_item,HelpMenu);
		hlps.setDropDownViewResource(android.R.layout.simple_dropdown_item_1line);
		s5.setAdapter(hlps);

		s1.setOnItemSelectedListener(this);
		s2.setOnItemSelectedListener(this);
		s3.setOnItemSelectedListener(this);
		s4.setOnItemSelectedListener(this);
		s5.setOnItemSelectedListener(this);
	}

	@SuppressLint("NewApi")
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		ActionBar bar = getActionBar();
		bar.hide();
		// getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
	@SuppressWarnings("unused")
	@Override
	public void onItemSelected(AdapterView<?> arg0, View arg1, int arg2, long arg3)
	{
		int position;

		if ( arg0 == s1 )
		{
			doFileMethod(arg2);
		}
		else if ( arg0 == s2 )
		{
			position = arg2;
		}
		else if ( arg0 == s3 )
		{
			position = arg2;
		}
		else if ( arg0 == s4 )
		{
			position = arg2;
		}
		else if ( arg0 == s5 )
		{
			position = arg2;
		}
		// TODO Auto-generated method stub
	}
	
	private int doFileMethod(int fileMethod)
	{
		int iRc = (1 == fileMethod ? fileMethod : 0);
		
		return iRc;
	}

	@Override
	public void onNothingSelected(AdapterView<?> arg0) {
		// TODO Auto-generated method stub
		
	}
}
