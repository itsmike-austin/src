package com.example.vexpandablelisttest;

import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.graphics.Typeface;
import android.util.DisplayMetrics;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseExpandableListAdapter;
import android.widget.ExpandableListView;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

	private List<String> groupList;
	private List<String> childList;
	private static Map<String,List<String>> laptopCollection;
	ExpandableListView expListView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		createGroupList();
		createCollection();
		
		expListView = (ExpandableListView)findViewById(R.id.laptop_list);
		
		final ExpandableListAdapter expListAdapter = new ExpandableListAdapter(this,groupList,laptopCollection);
		
		expListView.setAdapter(expListAdapter);
		
		// setGroupIndicatorToRight()
		
		expListView.setOnChildClickListener(new ExpandableListView.OnChildClickListener() {
			public boolean onChildClick(ExpandableListView parent,View v,int groupPosition,int childPosition,long id)
			{
				final String selected = (String)expListAdapter.getChild(groupPosition, childPosition);
				Toast.makeText(getBaseContext(), selected, Toast.LENGTH_LONG).show();
				return true;
			}
		});
	}
	
	private void createGroupList()
	{
		groupList = new ArrayList<String>();
		groupList.add("HP");
		groupList.add("Dell");
		groupList.add("Lenovo");
		groupList.add("Sony");
		groupList.add("HCL");
		groupList.add("Samsung");
	}
	
	private void createCollection()
	{
		// preparing laptops collection(child)
		
		String[] hpModels      = { "HP Pavilion G6","HP Pro Book","HP Envy" };
		String[] hclModels     = { "HCL 2012", "HCL 2013", "HCL 2014" };
		String[] lenovoModels  = { "Idea Series 1", "Idea Series 2", "Thinkpad X Series" };
		String[] sonyModels    = { "VAIO A Series", "VAIO B Series", "VAIO C Series" };
		String[] dellModels    = { "Insperion", "Vostro", "XPS" };
		String[] samsungModels = { "NP Series", "Series 5", "SF Series" };
		
		laptopCollection = new LinkedHashMap<String,List<String>>();
		
		for( String laptop : groupList )
		{
			if (laptop.equals("HP")) {
				loadChild(hpModels);
			}else if (laptop.equals("Dell")) {
				loadChild(dellModels);
			}else if (laptop.equals("Sony")) {
				loadChild(sonyModels);
			}else if (laptop.equals("HCL")) {
				loadChild(hclModels);
			}else if (laptop.equals("Samsung")) {
				loadChild(samsungModels);
			}else{
				loadChild(lenovoModels);
			}
			laptopCollection.put(laptop,childList);
		}
	}
	
	private void loadChild(String[] laptopModels)
	{
		childList = new ArrayList<String>();
		for( String model : laptopModels ) childList.add(model);
	}
	
	@SuppressWarnings("unused")
	private void setGroupIndicatorToRight()
	{
		/* Get the screenwidth */
		DisplayMetrics dm = new DisplayMetrics();
		getWindowManager().getDefaultDisplay().getMetrics(dm);
		int width = dm.widthPixels;
		
		expListView.setIndicatorBounds(width - getDipsFromPixel(35), width - getDipsFromPixel(5));
	}
	
	// Convert pixel to dip
	
	public int getDipsFromPixel(float pixels)
	{
		// Get the screens density scale
		
		final float scale = getResources().getDisplayMetrics().density;
		
		// Convert thedps to pixels, based on density scale
		
		return (int) (pixels*scale+0.5f);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	private class ExpandableListAdapter extends BaseExpandableListAdapter {
		
		private Activity context;
		private Map<String,List<String>> laptopCollections;
		private List<String> laptops;
		
		public ExpandableListAdapter(Activity context,List<String> laptops,Map<String,List<String>> laptopCollections)
		{
			this.context = context;
			this.laptopCollections = laptopCollections;
			this.laptops = laptops;
		}
		
		public Object getChild(int groupPosition,int childPosition)
		{
			/*
			String       baseGroup = groupList.get(groupPosition);
			List<String> childList = laptopCollections.get(baseGroup);
			String       theChild  = childList.get(childPosition);
			*/
			
			return laptopCollections.get(groupList.get(groupPosition)).get(childPosition);
		}
		
		public long getChildId(int groupPosition,int childPosition)
		{
			return childPosition;
		}
		
		public View getChildView(final int groupPosition,final int childPosition,
				boolean isLastChild,View convertView,ViewGroup parent )
		{
			final String laptop = (String)getChild(groupPosition,childPosition);
			
			LayoutInflater inflater = context.getLayoutInflater();
			
			if ( null == convertView )
			{
				convertView = inflater.inflate(R.layout.child_item,null);
			}
			
			TextView item = (TextView)convertView.findViewById(R.id.laptop);
			
			ImageView delete = (ImageView)convertView.findViewById(R.id.delete);
			
			delete.setOnClickListener(new ImageView.OnClickListener() 
			{
				public void onClick(View v)
				{
					AlertDialog.Builder builder = new AlertDialog.Builder(context);
					builder.setMessage("Do you want to remove?");
					builder.setCancelable(false);
					builder.setPositiveButton("Yes",
							new DialogInterface.OnClickListener() {	
								@Override
								public void onClick(DialogInterface dialog, int id) {
									List<String> child = laptopCollections.get(laptops.get(groupPosition));
									child.remove(childPosition);
									notifyDataSetChanged();
								}
							});
					builder.setNegativeButton("No",
							new DialogInterface.OnClickListener() {
								@Override
								public void onClick(DialogInterface dialog, int which) {
									dialog.cancel();
								}
							});
					AlertDialog alertDialog = builder.create();
					alertDialog.show();
				}
			});
			item.setText(laptop);
			return convertView;
		}
		
		public int getChildrenCount(int groupPosition) {
			return laptopCollections.get(laptops.get(groupPosition)).size();
		}
		
		public Object getGroup(int groupPosition) {
			return laptops.get(groupPosition);
		}
		
		public int getGroupCount() {
			return laptops.size();
		}
		
		public long getGroupId(int groupPosition)
		{
			return groupPosition;
		}
		
		public View getGroupView(int groupPosition,boolean isExpanded,View convertView,ViewGroup parent)
		{
			String laptopName = (String)getGroup(groupPosition);
			
			if ( convertView == null )
			{
				LayoutInflater infalInflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
				
				convertView = infalInflater.inflate(R.layout.group_item,null);
			}
			
			TextView item =(TextView)convertView.findViewById(R.id.laptop);
			
			item.setTypeface(null,Typeface.BOLD);
			item.setText(laptopName);
			
			return convertView;
		}
		
		public boolean hasStableIds() {
			return true;
		}
		
		public boolean isChildSelectable(int groupPosition,int childPosition)
		{
			return true;
		}
	}
}
