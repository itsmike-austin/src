package com.example.testdialoglistview;

import java.util.ArrayList;

import android.app.Dialog;
import android.content.Context;
import android.widget.ListView;

public class DisplayDataDialog extends Dialog
{
	private final String[] aList = {"a","b","c","d","e"};
	private final int[]    nList = { R.drawable.ic_launcher,
									 R.drawable.ic_launcher,
									 R.drawable.ic_launcher,
									 R.drawable.ic_launcher,
									 R.drawable.ic_launcher };
	
	private ArrayList<ListDisplayData> ddata = new ArrayList<ListDisplayData>();
	
	public DisplayDataDialog(Context context) {
		super(context);
		
		setContentView(R.layout.activity_main);
		
		for( int i=0 ; i < aList.length ; ++i ) ddata.add(new ListDisplayData(nList[i],aList[i]));
		
		ListDisplayArrayAdapter adapter = new ListDisplayArrayAdapter(context,R.layout.item_layout,ddata);
		
		ListView l = (ListView)findViewById(R.id.listView1);
		
		l.setAdapter(adapter);
		
	}
}
	
	

