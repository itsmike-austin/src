package com.example.multithreadtest;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

public class MyThread extends Thread {
	
	// constants with display size info
	
	private static final double STOP_HEIGHT_RATION = 0.8;
	private static final int HEIGHT = 480;
	private static final int WIDTH = 320;
	
	// instance vars for managing text move
	
	private String  myText;
	private int     currentPosition;
	private boolean moveLeft;
	
	// reference to mainHandler from the mainThread
	
	private Handler parentHandler;
	
	// local Handler manages messages for MyThread received from  mainThread
	
	@SuppressLint("HandlerLeak")
	private Handler myThreadHandler = new Handler()
	{
		public void handleMessage(Message msg)
		{
			if ( msg.what == 0 )
			{
				// stop this Thread if bottom side of the screen was touched
				
				if ( (int)msg.getData().getFloat("location_y") > (STOP_HEIGHT_RATION * HEIGHT) )
				{
					interrupt();
				}
				
				// set moving direction for the text
				
				if ( (int)msg.getData().getFloat("location_x") < (WIDTH/2) )
				{
					moveLeft = true;
				} else {
					moveLeft = false;
				}
			}
		}
	};
	
	// constructor
	
	public MyThread(Handler parentHandler )
	{
		// initialize instance vars
		
		this.parentHandler = parentHandler;
		
		currentPosition = 0;
		moveLeft       = true;
		
		myText = new String("Text changed from MyThread! Do you like it?");
	}
	
	@Override
	public void run()
	{
		super.run();
		try
		{
			// Thread loop
			
			Message messageToParent = new Message();
			Bundle  messageData     = new Bundle();
			
			messageToParent.what = 0;
			
			messageData.putString("text",updateText(myText));
			
			messageToParent.setData(messageData);
			
			// send message to mainThread
			
			parentHandler.sendMessage(messageToParent);
			
			// update currentPosition value for moving text ternary if form used
			
			if ( moveLeft )
			{
				currentPosition = (currentPosition == myText.length()) ? 0 : currentPosition + 1;
			}else{
				currentPosition = (currentPosition == 0) ? myText.length() : currentPosition - 1;
			}
			sleep(100);
		}
		catch( Exception e )
		{
			// Logging exception
			Log.e("TestingAreaLOG","Main loop exception - " + e);
		}
	}
	
	// getter for local handler
	
	public Handler getHandler()
	{
		return myThreadHandler;
	}
	
	// updates the text based on the currentPosition
	
	private String updateText(String text)
	{
		return text.substring(currentPosition)+text.substring(0,currentPosition);
	}
}