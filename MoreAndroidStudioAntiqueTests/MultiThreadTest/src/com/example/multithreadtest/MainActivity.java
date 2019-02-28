package com.example.multithreadtest;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.annotation.SuppressLint;
import android.app.Activity;
import android.view.Menu;
import android.view.MotionEvent;
import android.widget.TextView;

@SuppressLint("HandlerLeak")
public class MainActivity extends Activity {
	
	private MyThread myThread;           // out Thread instance var
	private TextView threadModifiedText; // text view influenced by our thread

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		threadModifiedText = (TextView)findViewById(R.id.text);
		
		// initializing and starting our thread
		
		myThread = new MyThread(mainHandler);
		myThread.start();
	}
	
	// Manage screen touch events
	
	@Override
	public boolean onTouchEvent(MotionEvent event)
	{
		if ( event.getAction() == MotionEvent.ACTION_DOWN)
		{
			// prepare a message with touch location data
			Message messageToThread = new Message();
			Bundle  messageData     = new Bundle();
			
			messageToThread.what = 0;
			messageData.putFloat("location_x",event.getX());
			messageData.putFloat("location_y",event.getY());
			messageToThread.setData(messageData);
			
			// send message to MyThread
			
			myThread.getHandler().sendMessage(messageToThread);
		}
		return super.onTouchEvent(event);
	}
	
	// manages messages for current thread(main) received from out thread
	
	public Handler mainHandler = new Handler()
	{
		public void handleMessage(android.os.Message msg)
		{
			if ( msg.what == 0 )
			{
				// updates the TextView with the received text
				threadModifiedText.setText(msg.getData().getString("text"));
			}
		};
	};
}
