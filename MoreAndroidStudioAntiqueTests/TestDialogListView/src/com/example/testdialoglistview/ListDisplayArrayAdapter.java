package com.example.testdialoglistview;

import java.util.ArrayList;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

public class ListDisplayArrayAdapter extends ArrayAdapter<ListDisplayData>
{
	// Declaration of a list of items.
	
	private ArrayList<ListDisplayData> objects;
	
	// Primary constructor.
	
	public ListDisplayArrayAdapter(Context ctx, int iResourceId, ArrayList<ListDisplayData> objects)
	{
		super(ctx,iResourceId,objects);
		this.objects = objects;
	}
	
	// Required getView method.
	
	public View getView(int position,View convertView,ViewGroup parent)
	{
		View v = convertView;
		
		if ( null == v )
		{
			LayoutInflater inflater = (LayoutInflater) getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			v = inflater.inflate(R.layout.item_layout,null);
		}
		
		ListDisplayData i = objects.get(position);
		
		if ( null != i )
		{
			ImageView img = (ImageView)v.findViewById(R.id.imageView1);
			TextView  txt = (TextView) v.findViewById(R.id.textView1);
			
			if ( null != img ) img.setImageResource(i.getItemId());
			if ( null != txt ) txt.setText(i.getItemName());
		}
		
		return v;
	}
	
}