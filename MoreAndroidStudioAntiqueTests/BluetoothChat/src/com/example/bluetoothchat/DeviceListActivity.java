package com.example.bluetoothchat;

import java.lang.reflect.Method;
import java.util.Set;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemLongClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

public class DeviceListActivity extends Activity
{
	// Debugging
	
	private static final String  TAG = "DeviceListActivity";
	private static final boolean D   = true;
	
	// Return Intent extra
	
	public static String EXTRA_DEVICE_ADDRESS = "device_address";
	
	// Member fields
	
	private BluetoothAdapter     mBtAdapter;
	private ArrayAdapter<String> mPairedDevicesArrayAdapter;
	private ArrayAdapter<String> mNewDevicesArrayAdapter;
	
	@Override
	protected void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		
		// Setup the window
		
		requestWindowFeature(Window.FEATURE_INDETERMINATE_PROGRESS);
		setContentView(R.layout.device_list);
		
		// Set result CANCELED in case the user backs out

		setResult(Activity.RESULT_CANCELED);
		
		// Initialize the button to perform device discovery
		
		Button scanButton = (Button)findViewById(R.id.button_scan);
		scanButton.setOnClickListener(new View.OnClickListener() {
			@Override public void onClick(View v) {
				doDiscovery();
				v.setVisibility(View.GONE);
			}
		});
		
		// Initialize array adapters. One for already paired devices and
		// one for newly discovered devices
		
		mPairedDevicesArrayAdapter = new ArrayAdapter<String>(this,R.layout.device_name);
		mNewDevicesArrayAdapter    = new ArrayAdapter<String>(this,R.layout.device_name);
		
		// Find and set up the ListView for paired devices
		
		ListView pairedListView = (ListView)findViewById(R.id.paired_devices);
		pairedListView.setAdapter(mPairedDevicesArrayAdapter);
		pairedListView.setOnItemClickListener(mDeviceClickListener);
		pairedListView.setOnItemLongClickListener(mUnpairSet);
		
		// XXX: MDB: Added code for scan adapter
		
		ListView newListView = (ListView)findViewById(R.id.new_devices);
		newListView.setAdapter(mNewDevicesArrayAdapter);
		newListView.setOnItemClickListener(mPairClickListener);
		// XXX: Callback required --		newListView.setOnItemClickListener(mDeviceClickListener);
				
		// Register for broadcasts when a device is discovered devices
		
		IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
		filter.addAction(BluetoothDevice.ACTION_BOND_STATE_CHANGED);
		DeviceListActivity.this.registerReceiver(mReceiver, filter);
		
		// Get the local Bluetooth adapter
		
		mBtAdapter = BluetoothAdapter.getDefaultAdapter();
		
		// Get a set of currently paired devices
		
		Set<BluetoothDevice> pairedDevices = mBtAdapter.getBondedDevices();
		
		// If there are paired devices, add each one to the ArrayAdapter
		
		if ( pairedDevices.size() > 0 ) {
			findViewById(R.id.title_paired_devices).setVisibility(View.VISIBLE);
			for( BluetoothDevice device : pairedDevices ) {
				mPairedDevicesArrayAdapter.add(device.getName() + "\n" + device.getAddress());
			}
		} else {
			String noDevices = getResources().getText(R.string.none_paired).toString();
			mPairedDevicesArrayAdapter.add(noDevices);
		}
	}
	
	@Override
	protected void onDestroy()
	{
		super.onDestroy();
		
		// Make sure we're not doing discovery anymore
		
		if ( mBtAdapter != null ) mBtAdapter.cancelDiscovery();
		
		// Unregister broadcast listeners
		
		this.unregisterReceiver(mReceiver);
	}
	
	// Start device discovery with the BluetoothAdapter
	
	private void doDiscovery()
	{
		if (D) Log.d(TAG,"doDiscovery()");
		
		// Indicate scanning in the title
		
		setProgressBarIndeterminateVisibility(true);
		setTitle(R.string.scanning);
		
		// Turn on sub-title for new devices
		
		findViewById(R.id.title_new_devices).setVisibility(View.VISIBLE);
		
		// If we're already discovering stop it
		
		if ( mBtAdapter.isDiscovering() ) mBtAdapter.cancelDiscovery();
		
		// Request discover from BluetoothAdapter
		
		mBtAdapter.startDiscovery();
	}
	
	// The on-click listener for all devices in the ListViews
	
	private OnItemClickListener mDeviceClickListener = new OnItemClickListener() {
		public void onItemClick(AdapterView<?> av,View v,int arg2,long arg3)
		{
			// Cancel discovery because it's costly and we're about to connect
			
			mBtAdapter.cancelDiscovery();
			
			// Get the device MAC address, which is the 17 chars in the View
			
			String info    = ((TextView)v).getText().toString();
			String address = info.substring(info.length() - 17);
			
			// Create the result Intent and include the MAC address
			
			Intent intent = new Intent();
			intent.putExtra(EXTRA_DEVICE_ADDRESS, address);
			
			// Set result and finish this Activity
			
			setResult(Activity.RESULT_OK,intent);
			finish();
		}
	};
	
	private OnItemLongClickListener mUnpairSet = new OnItemLongClickListener() {
		public boolean onItemLongClick(AdapterView<?> av, View v,int arg2, long arg3)
		{
			// Cancel discovery because it's costly and we're doing other things.
			
			mBtAdapter.cancelDiscovery();
			
			// Get the device data for deletion
			
			String info    = ((TextView)v).getText().toString();
			String address = info.substring(info.length() - 17);
			
			BluetoothDevice btd = mBtAdapter.getRemoteDevice(address);
			
			unpairDevice(btd);
			
			// Create the result Intent and include the MAC address
			
			Intent intent = new Intent();
			intent.putExtra(EXTRA_DEVICE_ADDRESS, address);
			
			setResult(Activity.RESULT_CANCELED,intent);
			finish();
			
			return false;
		}
	};
	
	
	private void pairDevice(BluetoothDevice device)
	{
		try {
			Method m = device.getClass().getMethod("createBond",(Class[])null);
			m.invoke(device, (Object[])null);
		} catch (Exception e) {}
	}
	
	private void unpairDevice(BluetoothDevice device)
	{
		try {
			Method m = device.getClass().getMethod("removeBond", (Class[])null);
			m.invoke(device, (Object[])null);
		} catch (Exception e) {}
	}
	
	private OnItemClickListener mPairClickListener = new OnItemClickListener() {
		public void onItemClick(AdapterView<?> av,View v,int arg2,long arg3)
		{
			// Cancel discovery because we don't need it
			
			mBtAdapter.cancelDiscovery();
			
			// Get the device MAC address, which is the 17 chars in the View
			
			String info    = ((TextView)v).getText().toString();
			String address = info.substring(info.length() - 17);
			
			// Build the remote device from the supplied address
			
			BluetoothDevice btd = mBtAdapter.getRemoteDevice(address);
			pairDevice(btd);
			
			return;
		}
	};
	
	// The BroadcastReceiver that listens for discovered devices and
	// changes the title when discovery is finished
	
	private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
		@Override
		public void onReceive(Context context,Intent intent)
		{
			String action = intent.getAction();
			
			// When discovery finds a device
			
			if ( BluetoothDevice.ACTION_FOUND.equals(action) ) {
				
				// Get the BluetoothDevice object from the Intent
				
				BluetoothDevice device = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
				
				// If it's already paired. skip it, because it's already been listed
				
				if ( device.getBondState() != BluetoothDevice.BOND_BONDED ) {
					boolean bGotIt = false;
					String  aName = device.getName();
					String  aAddr = device.getAddress();
					String  aFin  = aName + "\n" + aAddr;
					
					for( int i=0 ; i < mNewDevicesArrayAdapter.getCount() ; ++i )
					{
						String mAdapterItem = mNewDevicesArrayAdapter.getItem(i).toString();
						if ( mAdapterItem.equals(aFin) ) bGotIt = true;
						if( mNewDevicesArrayAdapter.getItem(i).toString().equals(aFin) ) bGotIt = true;
					}
					
					if ( false == bGotIt )
					{
						mNewDevicesArrayAdapter.add(aFin);
						mNewDevicesArrayAdapter.notifyDataSetChanged();
					}
				}
			} else if ( BluetoothDevice.ACTION_BOND_STATE_CHANGED.equals(action) ) {

				BluetoothDevice dev1 = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
				
				if ( BluetoothDevice.BOND_BONDED == dev1.getBondState() ) {

					String address = dev1.getAddress();
					
					Intent newBond = new Intent();
					newBond.putExtra(EXTRA_DEVICE_ADDRESS, address);
					
					// Set result and finish this Activity
					
					DeviceListActivity.this.setResult(Activity.RESULT_OK,newBond);
					finish();
				} else if ( BluetoothDevice.BOND_NONE == dev1.getBondState() ) {
					
					String address = dev1.getAddress();
					
					Intent stopBond = new Intent();
					stopBond.putExtra(EXTRA_DEVICE_ADDRESS, address);
					
					DeviceListActivity.this.setResult(Activity.RESULT_CANCELED,stopBond);
					finish();
				}
			} else {
				// When discovery is finished, change the Activity title
				
				setProgressBarIndeterminateVisibility(false);
				setTitle(R.string.select_device);
				if ( mNewDevicesArrayAdapter.getCount() == 0 ) {
					String noDevices = getResources().getText(R.string.none_found).toString();
					mNewDevicesArrayAdapter.add(noDevices);
				}
			}
		}
	};
}