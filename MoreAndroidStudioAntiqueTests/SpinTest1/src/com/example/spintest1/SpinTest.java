package com.example.spintest1;

import android.os.Bundle;
import android.app.Activity;
import android.view.Window;
import android.widget.ArrayAdapter;
import android.widget.Spinner;

public class SpinTest extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		requestWindowFeature(Window.FEATURE_RIGHT_ICON);
		setContentView(R.layout.activity_spin_test);
		
		setFeatureDrawableResource(Window.FEATURE_RIGHT_ICON,R.drawable.ic_launcher);
		
		Spinner s1 = (Spinner)findViewById(R.id.spinner);
		ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
				android.R.layout.simple_spinner_item,mStrings);
		adapter.setDropDownViewResource(android.R.layout.simple_dropdown_item_1line);
		s1.setAdapter(adapter);
	}
	
	private static final String[] mStrings = {
		"Mercury", "Venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"
	};
}
