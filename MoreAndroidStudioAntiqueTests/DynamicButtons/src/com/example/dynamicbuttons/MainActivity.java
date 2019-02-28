package com.example.dynamicbuttons;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.Button;
import android.widget.LinearLayout;

public class MainActivity extends Activity {
	
	final String[] nameList = new String[]{"Button01","Button02","Button03"};

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		LinearLayout buttonContainer = (LinearLayout)findViewById(R.id.buttonContainer);
		
		for( int i=0 ; i < nameList.length ; ++i )
		{
			Button aButton = new Button(this);
			aButton.setText(nameList[i]);
			buttonContainer.addView(aButton);
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
