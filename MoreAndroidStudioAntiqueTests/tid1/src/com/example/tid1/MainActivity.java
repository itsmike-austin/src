package com.example.tid1;

import java.io.File;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;

import android.os.Bundle;
import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

public class MainActivity extends Activity {
	
	private List<String> item = null;
	private List<String> path = null;
	private String root="/";
	private TextView myPath;

	Context  appContext = null;
	Dialog   dlg        = null;
	ListView listView   = null;
	
	ArrayAdapter<String> fileList = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		appContext = this.getApplicationContext();
		
		Button b = (Button)findViewById(R.id.get_file_button);
		b.setOnClickListener(new OnClickListener() {

			@Override
			public void onClick(View v) {
				dlg = new Dialog(v.getContext());
				dlg.setContentView(R.layout.new_file_dialog);
				dlg.setTitle(R.string.dialog_label);
				
				myPath = (TextView)dlg.findViewById(R.id.current_location);
				
				getDir(root);
				
				listView = (ListView)dlg.findViewById(R.id.listView1);
				
				if ( null == listView ) return;
				
				listView.setAdapter(fileList);
				
				Button dismiss = (Button)dlg.findViewById(R.id.cancel_button);
				dismiss.setOnClickListener(new OnClickListener() {
					@Override
					public void onClick(View v) {
						dlg.dismiss();
					}
				});
				
				dlg.show();
			}
		});
	}

	
    private void getDir(String dirPath)
    {
    	myPath.setText("Location: " + dirPath);

    	item = new ArrayList<String>();
    	path = new ArrayList<String>();

    	File f = new File(dirPath);
    	File[] files = f.listFiles();
    	
    	if(!dirPath.equals(root))
    	{
    		item.add(root);
    		path.add(root);
    		item.add("../");
    		path.add(f.getParent());
    	}
    	
    	Arrays.sort(files,filecomparator);

    	for(int i=0; i < files.length; i++)
    	{
    		File file = files[i];
    		path.add(file.getPath());

    		if(file.isDirectory())
    			item.add(file.getName() + "/");
    		else
    			item.add(file.getName());
    	}

    	fileList = new ArrayAdapter<String>(this, R.layout.file_row, item);
    }

	Comparator<? super File> filecomparator = new Comparator<File>(){

    	public int compare(File file1, File file2) {

    		if(file1.isDirectory()){
    			if (file2.isDirectory()){
    				return String.valueOf(file1.getName().toLowerCase()).compareTo(file2.getName().toLowerCase());
    			}else{
    				return -1;
    			}
    		}else{
    			if (file2.isDirectory()){
    				return 1;
    			}else{
    				return String.valueOf(file1.getName().toLowerCase()).compareTo(file2.getName().toLowerCase());
    			}
    		}
    	}
    };

	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
