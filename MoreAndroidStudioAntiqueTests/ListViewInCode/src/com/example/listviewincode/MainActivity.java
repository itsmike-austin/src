package com.example.listviewincode;

import android.os.Bundle;
import android.app.Activity;
import android.view.Gravity;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {
	
	String[]  wordList = new String[]{"a","b","c","d"};

	Integer[] imageId  = {
			R.drawable.ic_launcher,
			R.drawable.ic_launcher,
			R.drawable.ic_launcher,
			R.drawable.ic_launcher };

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		ListView list = new ListView(this);
		list.setAdapter(new MyAdapter(this,wordList,imageId));
        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
        	@Override
        	public void onItemClick(AdapterView<?> parent, View view,int position, long id) {
        		Toast.makeText(MainActivity.this, "You Clicked at " +wordList[+ position], Toast.LENGTH_SHORT).show();
        	}
        });
		
		setContentView(list);
	}
	
	public class TextOnClickListener implements View.OnClickListener
	{
		public void MyOnClickListener(){}
		
		@SuppressWarnings("unused")
		@Override public void onClick(View v)
		{
			TextView tv = (TextView)v;
			String value = tv.getText().toString();
			String k = value;
			int    whoareyou = tv.getId();
			int    l = whoareyou;
			// can get the text value here for more data.
		}
	}
	
	private class MyAdapter extends ArrayAdapter<String>
	{
//		private Activity  context;
		private final String[]  stringList;
		private final Integer[] imageList;
		
		public MyAdapter(Activity activity,String[] strings,Integer[] images)
		{
			super(activity,-1,-1,strings);
//			this.context    = activity;
			this.stringList = strings;
			this.imageList  = images;
		}
		
		@Override
		public View getView(int position,View convertView,ViewGroup parent)
		{
			LinearLayout listLayout = new LinearLayout(MainActivity.this);
			listLayout.setLayoutParams(new AbsListView.LayoutParams(AbsListView.LayoutParams.WRAP_CONTENT,AbsListView.LayoutParams.WRAP_CONTENT));
			listLayout.setGravity(Gravity.CENTER_VERTICAL);
			listLayout.setId(5000);
			
			ImageView picture = new ImageView(MainActivity.this);
			picture.setId(5001);
			picture.setImageResource(imageList[position]);
			listLayout.addView(picture);
			
			TextView listText = new TextView(MainActivity.this);
			listText.setId(5002);			
			listLayout.addView(listText);
			listText.setText(super.getItem(position));
			listText.setOnClickListener(new TextOnClickListener());
			
			return listLayout;
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
