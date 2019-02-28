package com.example.notificationtest01;

import android.os.Bundle;
import android.app.Activity;
import android.app.Notification;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.content.res.Resources;
import android.view.Menu;

public class MainActivity extends Activity {
	
	private static final int HELLO_ID = 1337;
	
	private static Context context;

	@SuppressWarnings("unused")
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		MainActivity.context = getApplicationContext();
		
		// Create the notification intent
		
		Intent notificationIntent = new Intent(context,Activity.class);

		PendingIntent contentIntent = 
				PendingIntent.getActivity(this,
						HELLO_ID,
						notificationIntent,
						PendingIntent.FLAG_CANCEL_CURRENT);
		
		NotificationManager nm = (NotificationManager)this.getSystemService(Context.NOTIFICATION_SERVICE);
		
		Resources res = context.getResources();
		
		Notification.Builder builder = new Notification.Builder(this);
		
		builder.setContentIntent(contentIntent)
					.setSmallIcon(R.drawable.ic_launcher)
					.setTicker("TickerString")
					.setWhen(System.currentTimeMillis())
					.setAutoCancel(true)
					.setContentTitle("Notification Title")
					.setContentText("Notification Content");
		
		Notification n = builder.build();
		
		nm.notify(HELLO_ID,n);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
