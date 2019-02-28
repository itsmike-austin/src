package com.example.networktest_01;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		String localAddress = "";
		
		boolean bDoMore = true;

		try {
			for( Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces() ; en.hasMoreElements() && bDoMore ; )
			{
				NetworkInterface netif = en.nextElement();
				for( Enumeration<InetAddress> enumIpAddr = netif.getInetAddresses() ; enumIpAddr.hasMoreElements() && bDoMore ; )
				{
					InetAddress inetAddress = (InetAddress)enumIpAddr.nextElement();
					if ( !inetAddress.isLoopbackAddress() )
					{
						// Actually, the accept will make this better
						localAddress = inetAddress.getHostAddress().toString();
						if ( localAddress.length() < 16 ) bDoMore = false;
					}
				}
			}
		} catch(SocketException e) {
			localAddress += "Socket Exception";
		}

		TextView tv = (TextView)findViewById(R.id.testView1);
		tv.setText(localAddress);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
