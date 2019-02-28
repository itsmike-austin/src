package com.example.customdialogtest;

import android.os.Bundle;
import android.app.Activity;
import android.app.Dialog;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {
	
	Button cust;
	Dialog custom;
	EditText Fname;
	EditText Lname;
	TextView txt;
	Button savebtn;
	Button canbtn;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		cust = (Button)  findViewById(R.id.cusdia);
		txt  = (TextView)findViewById(R.id.txt);
		
		cust.setOnClickListener(new View.OnClickListener() {
			String fname,lname;
			
			@Override
			public void onClick(View view)
			{
				// TODO Auto-generated method stub
				custom = new Dialog(MainActivity.this);
				custom.setContentView(R.layout.dialog);
				
				Fname = (EditText)custom.findViewById(R.id.fname);
				Lname = (EditText)custom.findViewById(R.id.lname);
				
				savebtn = (Button)custom.findViewById(R.id.savebtn);
				canbtn  = (Button)custom.findViewById(R.id.canbtn);
				
				custom.setTitle("Custom Dialog");
				
				savebtn.setOnClickListener(new View.OnClickListener() {
					
					@Override
					public void onClick(View view)
					{
						// TODO Auto-generated method stub
						fname = Fname.getText().toString();
						lname = Lname.getText().toString();
						
						txt.setText("Your Name is " + fname + " " + lname);
						
						custom.dismiss();
					}
				});
				
				canbtn.setOnClickListener(new View.OnClickListener() {
					
					@Override
					public void onClick(View view)
					{
						custom.dismiss();
					}
				});
				custom.show();
			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
