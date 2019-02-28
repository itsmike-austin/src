package com.example.voicerecorder;

import java.io.IOException;

import com.example.voicerecorder.DefaultAttributes.DefaultDirectoryDialog;
import com.example.voicerecorder.DefaultAttributes.OutputTypeSelectionDialog;

import android.os.Build;
import android.os.Bundle;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.Configuration;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.ImageButton;
import android.widget.Toast;

public class MainActivity extends Activity {
	
	private static DefaultAttributes      defaultAttrs   = null;
	private static FileListDialog         fileListDialog = null;
	private static DefaultDirectoryDialog defDirDialog   = null;
	private static ImageButton            pauseButton    = null;
	private static ImageButton            recordButton   = null;
	
	private Recording currentRecording = null;

	/* ***********************************************************************
	 * Default method called when the intent activity is instantiated
	 * *********************************************************************** */

	@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		initialize(this);
		Intent thisGuy = this.getIntent();
		thisGuy.addFlags(Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS);
		/*
		int flags = thisGuy.getFlags();
		flags |= Intent.FLAG_ACTIVITY_EXCLUDE_FROM_RECENTS;
		thisGuy.setFlags(flags);
		*/
	}
	
	/* ***********************************************************************
	 * Default method called when the options menu is about to be created.
	 * *********************************************************************** */

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
	
		// Inflate the menu; this adds items to the action bar if it is present.

		getMenuInflater().inflate(R.menu.main, menu);
		
		return true;
	}
	
	/* ***********************************************************************
	 * Options menu callback method (ActionBar callbacks)
	 * *********************************************************************** */

	@Override
	public boolean onOptionsItemSelected(MenuItem item)
	{
		switch( item.getItemId() )
		{
		case R.id.default_directory_menu:
			defDirDialog = defaultAttrs.getDefaultDirectoryDialog(this);
			defDirDialog.show();
			return true;

		case R.id.file_dialog_menu1:
			
			// Construct and display the file management dialog.
			
			fileListDialog = new FileListDialog(this,defaultAttrs.getDefaultDir());
			fileListDialog.show();
			return true;

		case R.id.output_type_dialog_button:
			
			OutputTypeSelectionDialog d1 = defaultAttrs.getOutputTypeDialog(this);
			d1.show();
			return true;
//			return super.onOptionsItemSelected(item);
/*		case R.id.action_settings:
			return super.onOptionsItemSelected(item);
	*/
		
		case R.id.menu_exit_button1:
			/* XXX: This area should be uncommented. */
			this.moveTaskToBack(true);
			android.os.Process.killProcess(android.os.Process.myPid());
			System.exit(1);
			/* */
			finish();
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	/* ***********************************************************************
	 * Callback method for the record button.
	 * *********************************************************************** */

	class RecordButtonListener implements ImageButton.OnClickListener {
		@Override
		public void onClick(View v) {
			
			// Flip flop the buttons to signal the system is recording.
			
			recordButton.setVisibility(View.INVISIBLE);
			pauseButton.setVisibility(View.VISIBLE);
			
			// Start recording
			
			currentRecording = new Recording(defaultAttrs);
		}
	}
	
	/* ***********************************************************************
	 * Callback method for the pause button.
	 * *********************************************************************** */
	
	class PauseButtonListener implements ImageButton.OnClickListener {
		@Override
		public void onClick(View v) {
			
			// Flip flop the buttons to signal that recording has stopped.
			
			pauseButton.setVisibility(View.INVISIBLE);
			recordButton.setVisibility(View.VISIBLE);
			
			// Stop the recording
			
			currentRecording.stopRecording();
		}
	}
	
	/* ***********************************************************************
	 * Setup the app default attributes
	 * *********************************************************************** */

	private void initialize(Context context)
	{
		recordButton = (ImageButton)findViewById(R.id.start_recording1);
		pauseButton  = (ImageButton)findViewById(R.id.pause_button1);
		
		recordButton.setOnClickListener(new RecordButtonListener());
		pauseButton.setOnClickListener(new PauseButtonListener());
		
		defaultAttrs = new DefaultAttributes(context);
		
		try {
			defaultAttrs.getDefaults();
		}catch( IOException e ){
			(Toast.makeText(context, e.getLocalizedMessage(), Toast.LENGTH_LONG)).show();
			finish();
		}
	}
	
	/* ***********************************************************************
	 * Callback method for the pause button. Method to eliminate restarts for
	 * changes in app orientation. This is combined with updates to
	 * the activity definition in the manifest to route calls for
	 * configuration changes here.
	 * *********************************************************************** */
	
	@Override
	public void onConfigurationChanged(Configuration newConfig)
	{
		super.onConfigurationChanged(newConfig);
	}
}
