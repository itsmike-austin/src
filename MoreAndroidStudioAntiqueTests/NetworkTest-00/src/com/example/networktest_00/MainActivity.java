package com.example.networktest_00;

import java.net.InetAddress;
import java.net.UnknownHostException;

import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		String st = "";

		ConnectivityManager cman = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
		
		NetworkInfo netlist[] = cman.getAllNetworkInfo();
		
		for( int i=0 ; i < netlist.length ; ++i )
		{
			switch( netlist[i].getType() )
			{
			case ConnectivityManager.TYPE_BLUETOOTH:
				if ( NetworkInfo.State.CONNECTED == netlist[i].getState() ) st += " Bluetooth ";
				break;
					
			case ConnectivityManager.TYPE_DUMMY:
				if ( NetworkInfo.State.CONNECTED == netlist[i].getState() ) st += " Dummy ";
				break;
				
			case ConnectivityManager.TYPE_ETHERNET:
				if ( NetworkInfo.State.CONNECTED == netlist[i].getState() ) st += " Ethernet ";
				break;
				
			case ConnectivityManager.TYPE_MOBILE:
				if ( NetworkInfo.State.CONNECTED == netlist[i].getState() ) st += " Mobile ";
				break;
				
			case ConnectivityManager.TYPE_MOBILE_DUN:
				if ( NetworkInfo.State.CONNECTED == netlist[i].getState() ) st += " DUN ";
				break;
				
			case ConnectivityManager.TYPE_MOBILE_HIPRI:
				if ( NetworkInfo.State.CONNECTED == netlist[i].getState() ) st += " HIPRI ";
				break;
				
			case ConnectivityManager.TYPE_MOBILE_MMS:
				if ( NetworkInfo.State.CONNECTED == netlist[i].getState() ) st += " MMS ";
				break;
				
			case ConnectivityManager.TYPE_MOBILE_SUPL:
				if ( NetworkInfo.State.CONNECTED == netlist[i].getState() ) st += " SUPL ";
				break;
				
			case ConnectivityManager.TYPE_WIFI:
				if ( NetworkInfo.State.CONNECTED == netlist[i].getState() ) st += " WIFI ";
				break;
				
			case ConnectivityManager.TYPE_WIMAX:
				if ( NetworkInfo.State.CONNECTED == netlist[i].getState() ) st += " WiMax ";
				break;
				
			}
		}
		
		new Thread (new Runnable()
		{
			public void run()
			{
				TextView tv1 = (TextView) findViewById(R.id.textView2);
				String   tvs = "";
				try {
					InetAddress inetAddressList[] = InetAddress.getAllByName("www.google.com");
					for( InetAddress addrList : inetAddressList ) tvs += addrList.toString();
					tv1.setText(tvs);
				}catch ( UnknownHostException e ) {
					return;
				} catch ( Exception e1 ) {
					e1.printStackTrace();
				}
			}
		}).start();
		
		TextView tv = (TextView)this.findViewById(R.id.textVIew1);
		tv.setText(st);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
