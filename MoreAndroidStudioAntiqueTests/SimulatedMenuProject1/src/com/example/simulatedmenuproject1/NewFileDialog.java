package com.example.simulatedmenuproject1;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RelativeLayout;
import android.widget.TableLayout;

public class NewFileDialog extends Activity
{
	int           dlgid   = 0;
	NewFileDialog thebase = null;
	EditText      filename = null;
	TableLayout   dirlist  = null;
	Button        savebtn  = null;
	Button        canclbtn = null;
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.new_file_dialog);
		
		thebase = this;

		dirlist  = (TableLayout)findViewById(R.id.new_file_dialog_directory_list);
		filename = (EditText)   findViewById(R.id.new_file_dialog_filename);
		savebtn  = (Button)     findViewById(R.id.new_file_dialog_ok_button);
		canclbtn = (Button)     findViewById(R.id.new_file_dialog_cancel_button);

		savebtn.setOnClickListener(new saveButtonCallback());
		canclbtn.setOnClickListener(new cancelButtonCallback());
	}
	
	private class saveButtonCallback implements View.OnClickListener
	{
		@Override
		public void onClick(View v)
		{
			return;
		}
	}
	
	private class cancelButtonCallback implements View.OnClickListener
	{
		@Override
		public void onClick(View v)
		{
			thebase.finish();
		}
	}
}