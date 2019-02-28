package com.example.scrollingtextviewticker;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.LinearLayout;
import android.widget.TextView;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);		
		setContentView(R.layout.activity_main);
		
		TextView ticker = (TextView)findViewById(R.id.ticker);
		ticker.setSelected(true);
		ticker.setText("THIS IS A REALLY LONG TEXT LINE THAT SHOULD GO PAST THE END OF STUFF AND REPEAT FOREVER");
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

}
