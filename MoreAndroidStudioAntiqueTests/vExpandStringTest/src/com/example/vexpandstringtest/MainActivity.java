package com.example.vexpandstringtest;

import android.os.Bundle;
import android.app.ExpandableListActivity;
import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseExpandableListAdapter;
import android.widget.TextView;

public class MainActivity extends ExpandableListActivity {
    private static final String arrGroupElements[] = {
    	"Item1", "Item2", "Item3", "Item4", "Item5",
    	"Item6", "Item7", "Item8", "Item9" };

    /**
     * strings for child elements
     */

    private static final String arrChildElements[][] = {
    	{ "Details1 A","Details1 B", "Details1 C" },
    	{ "Details2 A","Details2 B", "Details2 C" },
    	{ "Details3 A","Details3 B", "Details3 C" },
    	{ "Details4 A","Details4 B", "Details4 C" },
    	{ "Details5 A","Details5 B", "Details5 C" },
    	{ "Details6 A","Details6 B", "Details6 C" },
    	{ "Details7" },
    	{ "Details8" },
    	{ "Details9" } };

    @Override
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);
    	setContentView(R.layout.activity_main);
    	setListAdapter((android.widget.ExpandableListAdapter)new ExpandableListAdapter(this));
    }

    private class ExpandableListAdapter extends BaseExpandableListAdapter
    {
    	private Context myContext;

    	public ExpandableListAdapter(Context context) {
    	    myContext = context;
    	}

    	@Override
    	public Object getChild(int groupPosition, int childPosition) {
    	    return null;
    	}

    	@Override
    	public long getChildId(int groupPosition, int childPosition) {
    	    return 0;
    	}

    	@Override
    	public View getChildView(int groupPosition, int childPosition, boolean isLastChild, View convertView, ViewGroup parent)
    	{
    	    if (convertView == null) {
    	    	LayoutInflater inflater = (LayoutInflater) myContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    	    	convertView = inflater.inflate(R.layout.list_child, null);
    	    }

    	    TextView yourSelection = (TextView)convertView.findViewById(R.id.articleContentTextView);
    	    yourSelection.setText(arrChildElements[groupPosition][childPosition]);
    	    return convertView;
    	}

    	@Override
    	public int getChildrenCount(int groupPosition) {
    	    return arrChildElements[groupPosition].length;
    	}

    	@Override
    	public Object getGroup(int groupPosition) {
    	    return null;
    	}

    	@Override
    	public int getGroupCount() {
    	    return arrGroupElements.length;
    	}

    	@Override
    	public long getGroupId(int groupPosition) {
    	    return 0;
    	}

    	@Override
    	public View getGroupView(int groupPosition, boolean isExpanded, View convertView, ViewGroup parent)
    	{
    	    if (convertView == null)
    	    {
    	    	LayoutInflater inflater = (LayoutInflater) myContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    	    	convertView = inflater.inflate(R.layout.list_item, null);
    	    }

    	    TextView groupName = (TextView) convertView.findViewById(R.id.articleHeaderTextView);
    	    groupName.setText(arrGroupElements[groupPosition]);
    	    return convertView;
    	}

    	@Override
    	public boolean hasStableIds() {
    	    return false;
    	}

    	@Override
    	public boolean isChildSelectable(int groupPosition, int childPosition) {
    	    return true;
    	}
    }
}
