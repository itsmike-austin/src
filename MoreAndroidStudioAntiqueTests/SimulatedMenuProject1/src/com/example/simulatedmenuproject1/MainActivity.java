package com.example.simulatedmenuproject1;

import android.os.Bundle;
import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.view.Menu;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.example.simulatedmenuproject1.NewFileDialog;

public class MainActivity extends Activity {
	
	int iMajorVersion = 0;
	int iMinorVersion = 1;
	
	int currentZoom = 0; // current zoom factor
	int centerPoint = 0; // current center point
	
	boolean beenChanged;

	Button b1 = null;
	Button b2 = null;
	Button b3 = null;
	Button b4 = null;
	Button b5 = null;
	
	AlertDialog fileOptions = null;
	AlertDialog editOptions = null;
	AlertDialog viewOptions = null;
	AlertDialog optsOptions = null;
	AlertDialog helpOptions = null;
	
	Intent newFileDialog;
	Intent openFileDialog;
	
	Context mainContext;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		ActionBar bar = getActionBar();
		bar.hide();
		
		mainContext = this;
		
		b1 = (Button)findViewById(R.id.button1);
		b1.setOnClickListener(new clickButton1());
		
		b2 = (Button)findViewById(R.id.button2);
		b2.setOnClickListener(new clickButton());
		
		b3 = (Button)findViewById(R.id.button3);
		b3.setOnClickListener(new clickButton3());
		
		b4 = (Button)findViewById(R.id.button4);
		b4.setOnClickListener(new clickButton4());
		
		b5 = (Button)findViewById(R.id.button5);
		b5.setOnClickListener(new clickButton5());
		b5.setOnLongClickListener(new longClickButton5());

		AlertDialog.Builder fileOptsBuilder = new AlertDialog.Builder(this);
		fileOptsBuilder.setTitle("File Options");
		String fileOptionsList[] ={"New","Open...","Save","Save As","Exit"};
		fileOptsBuilder.setItems(fileOptionsList, fileActionListener);
		fileOptsBuilder.setNegativeButton("Cancel",null);
		fileOptions = fileOptsBuilder.create();		

		AlertDialog.Builder editOptsBuilder = new AlertDialog.Builder(this);
		editOptsBuilder.setTitle("Edit Options");
		String editOptionsList[] = {"Cut","Copy","Paste","Delete"};
		editOptsBuilder.setItems(editOptionsList, editActionListener);
		editOptsBuilder.setNegativeButton("Cancel",null);
		editOptions = editOptsBuilder.create();
		
		AlertDialog.Builder viewOptsBuilder = new AlertDialog.Builder(this);
		viewOptsBuilder.setTitle("View Options");
		String viewOptionsList[] = {"Enlarge","Shrink","Zoom+","Zoom-","Normal","Selected"};
		viewOptsBuilder.setItems(viewOptionsList,viewActionListener);
		viewOptsBuilder.setNegativeButton("Cancel",null);
		viewOptions = viewOptsBuilder.create();
		
		AlertDialog.Builder optsOptsBuilder = new AlertDialog.Builder(this);
		optsOptsBuilder.setTitle("Options");
		String optsOptionsList[] = {"One","Two","Three"};
		optsOptsBuilder.setItems(optsOptionsList,optsActionListener);
		optsOptsBuilder.setNegativeButton("Cancel",null);
		optsOptions = optsOptsBuilder.create();
		
		AlertDialog.Builder helpOptsBuilder = new AlertDialog.Builder(this);
		helpOptsBuilder.setTitle("Help");
		String helpOptionsList[] = {"Help","About"};
		helpOptsBuilder.setItems(helpOptionsList, helpActionListener);
		helpOptsBuilder.setNegativeButton("Cancel",null);
		helpOptions = helpOptsBuilder.create();
		
		beenChanged = false;
	}

	// File selection action set here

	DialogInterface.OnClickListener fileActionListener =
			new DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface dialog, int which) {
					switch(which) {
					case 0: // New
						newFileDialog();
						break;
					case 1: // Open
						openFileDialog();
						break;
					case 2: // Save
						saveFile();
						break;
					case 3: // Save As
						newFileDialog();
						break;
					case 4: // Exit
						finish();
						break;
					default:
						break;
					}
				}
	};
	
	public boolean hasBeenChanged()
	{
		return beenChanged;
	}
	
	public void changedImage()
	{
		beenChanged = true;
	}
	
	private void newFileDialog()
	{
		try
		{
			// String newActivity = "com.example.simulatedmenuproject1.NewFileDialog";
			// newFileDialog = new Intent(this,NewFileDialog.class);
			// newFileDialog = new Intent(newActivity);
		    //	startActivity(new Intent(this,NewFileDialog.class));
			newFileDialog = new Intent(mainContext,NewFileDialog.class);
			startActivity(newFileDialog);
		} catch (Exception e) {
			Toast.makeText(getBaseContext(), e.getMessage(),
						Toast.LENGTH_LONG).show();
		}
	}
	
	private void openFileDialog()
	{
		openFileDialog = new Intent(this,OpenFileDialog.class);
		startActivity(openFileDialog);
	}
	
	private void saveFile()
	{
		return;
	}

	// Edit selection action set here

	DialogInterface.OnClickListener editActionListener =
			new DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface dialog, int which) {
					switch(which) {
					case 0: // Cut
						cutSelection();
						break;
					case 1: // Copy
						cutSelection();
						pasteSelection();
						break;
					case 2: // Paste
						pasteSelection();
						break;
					case 3: // Delete
						deleteSelection();
						break;
					default:
						break;
					}
				}
	};
	
	private void cutSelection()
	{
		return;
	}
	
	private void pasteSelection()
	{
		return;
	}
	
	private void deleteSelection()
	{
		return;
	}
	
	// View selection action set here
	
	DialogInterface.OnClickListener viewActionListener =
			new DialogInterface.OnClickListener()
	{
		@Override
		public void onClick(DialogInterface dialog,int which)
		{
			switch(which)
			{
			case 0: // Enlarge
				currentZoom = (currentZoom + 10 < 100 ? currentZoom + 10 : 100);
				zoomAll(currentZoom);
				break;
			case 1: // Shrink
				currentZoom = (currentZoom - 10 > -100 ? currentZoom - 10 : -100);
				zoomAll(currentZoom);
				break;
			case 2: // Zoom+
				currentZoom = (currentZoom + 1 < 100 ? currentZoom + 1 : 100);
				zoomAll(currentZoom);
				break;
			case 3: // Zoom-
				currentZoom = (currentZoom - 1 > -100 ? currentZoom - 1 : -100);
				zoomAll(currentZoom);
				break;
			case 4: // Normal
				currentZoom = 0;
				zoomAll(0);
				break;
			case 5: // Selected (Calculate the zoom area zoom factor)
				break;
			default:
				break;
			}
		}
	};
	
	private void zoomAll(int zoomFactor)
	{
		return;
	}

	// Options selection action set here

	DialogInterface.OnClickListener optsActionListener =
			new DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface dialog, int which) {
					switch(which) {
					case 0: // One
						break;
					case 1: // Two
						break;
					case 2: // Three
						break;
					default:
						break;
					}
				}
	};

	// Help selection action set here

	DialogInterface.OnClickListener helpActionListener =
			new DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface dialog, int which) {
					switch(which) {
					case 0: // One
						break;
					case 1: // Two
						break;
					default:
						break;
					}
				}
	};
	
	private void helpVersion()
	{
		String sVersion = Integer.toString(iMajorVersion) + "." + Integer.toString(iMinorVersion);	
		Toast.makeText(this, sVersion, Toast.LENGTH_SHORT).show();
   	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
	private class clickButton1 implements View.OnClickListener
	{
		@Override
		public void onClick(View v)
		{
			fileOptions.show();
		}
	}
	
	private class clickButton implements View.OnClickListener
	{
		@Override
		public void onClick(View v)
		{
			TextView tv = (TextView)findViewById(R.id.textview);
			if ( v.equals(b1) )
			{
				tv.setText("One");
			}
			else if ( v.equals(b2) )
			{
				editOptions.show();
				tv.setText("Two");
			}
			else
			{
				tv.setText("Try Again");
			}
		}
	}
	
	private class clickButton3 implements View.OnClickListener
	{
		@Override
		public void onClick(View v)
		{
			viewOptions.show();
			TextView tv = (TextView)findViewById(R.id.textview);
			tv.setText("ButtonThree");
		}
	}
	
	private class clickButton4 implements View.OnClickListener
	{
		@Override
		public void onClick(View v)
		{
			optsOptions.show();
			TextView tv = (TextView)findViewById(R.id.textview);
			tv.setText("Button4");
		}
	}
	
	private class clickButton5 implements View.OnClickListener
	{
		@Override
		public void onClick(View v)
		{
			helpOptions.show();
			TextView tv = (TextView)findViewById(R.id.textview);
			tv.setText("Button5");
		}
	}
	
	private class longClickButton5 implements View.OnLongClickListener
	{
		@Override
		public boolean onLongClick(View v) {
			TextView tv = (TextView)findViewById(R.id.textview);
			tv.setText("Long Click");
			return true;
		}
	}
	
}






/*

public class AlertDlg extends Activity {
	
	AlertDialog actions;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setTitle("Activity");
		Button button = new Button(this);
		button.setText("Click for Options");
		button.setOnClickListener(buttonListener);
		
		AlertDialog.Builder builder = new AlertDialog.Builder(this);
		builder.setTitle("Choose an Option");
		String options[] ={"Delete Item","Copy Item","Edit Item"};
		builder.setItems(options, actionListener);
		builder.setNegativeButton("Cancel",null);
		actions = builder.create();

		setContentView(button);
	}
	
	// List selection action set here

	DialogInterface.OnClickListener actionListener =
			new DialogInterface.OnClickListener() {
				@Override
				public void onClick(DialogInterface dialog, int which) {
					switch(which) {
					case 0: // Delete
						break;
					case 1: // Copy
						break;
					case 2: // Edit
						break;
					default:
						break;
					}
				}
	};
			
	// Button action handled here (popup menu)

	View.OnClickListener buttonListener = 
			new View.OnClickListener() {
				@Override
				public void onClick(View v) {
					actions.show();
					
				}
	};
}
*/