package com.example.testbluetoothsearch;

import java.util.ArrayList;

import android.os.Bundle;
import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.view.Menu;

public class MainActivity extends Activity {
	
	private ArrayList<String> deviceList = null;
	private BluetoothReceiver blueListen = null;
	private BluetoothAdapter  mBluetoothAdapter = null;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		deviceList = new ArrayList<String>();
		
		mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		
		blueListen = new BluetoothReceiver();
		IntentFilter filter = new IntentFilter();
		filter.addAction(BluetoothDevice.ACTION_FOUND);
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	private class BluetoothReceiver extends BroadcastReceiver
	{
		@Override
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if ( BluetoothDevice.ACTION_FOUND.equals(action) )
			{
				BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
				deviceList.add(device.getName()+"\n"+device.getAddress());
			} else {
				// When discovery is finished, change the Activity title
				deviceList.add("endOfList");
			}
		}
	}
}
