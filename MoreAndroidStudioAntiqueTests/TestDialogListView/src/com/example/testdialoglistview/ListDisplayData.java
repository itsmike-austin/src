package com.example.testdialoglistview;

public class ListDisplayData
{
	private int    item;
	private String name;
	
	public ListDisplayData(int item,String name)
	{
		this.item = item;
		this.name = name;
	}
	
	public int    getItemId()   { return this.item; }
	public String getItemName() { return this.name; }
	
	public void setItemId  (int nId     ) { this.item = nId;  }
	public void setItemName(String name ) { this.name = name; }
}
