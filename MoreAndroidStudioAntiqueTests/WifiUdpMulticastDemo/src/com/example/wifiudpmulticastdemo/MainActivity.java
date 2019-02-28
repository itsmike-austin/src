package com.example.wifiudpmulticastdemo;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.SocketTimeoutException;

import android.net.ConnectivityManager;
import android.net.DhcpInfo;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.net.wifi.WifiManager.MulticastLock;
import android.net.wifi.WifiManager.WifiLock;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.content.Context;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {
	
	private static TextView tv;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		Thread bg;
		
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		tv = (TextView)findViewById(R.id.textView1);
		
		// Build the thread used to receive broadcast messages.
		
		try {
			bg = new Thread(new Runnable() {
				byte[]         message;
				DatagramPacket packet;
				DatagramSocket socket;
				
				public void run()
				{
					try {
						// Loop control variables
						
						boolean bLoop      = true;
						int     iLoopCount = 0;
						
						message          = new byte[1500];
						packet           = new DatagramPacket(message,message.length);
						socket           = new DatagramSocket(1600);
						
						// XXX: This call stops all network activity ...
						//
						// DatagramChannel channel = socket.getChannel();
						// channel.configureBlocking(true);
						// socket.getChannel().configureBlocking(true);
						
						socket.setSoTimeout(250);    // 250ms delay timer to wait from (demo only).
						socket.setBroadcast(true);   // Flag this guy for receiving broadcasting messages
						
						// Receive the broadcast message from the caller and report it.
						
						while( bLoop ) {
						
							try {
								socket.receive(packet);
								bLoop = false;
							} catch (SocketTimeoutException e) {
								// this is a simple timeout loop that works with broadcast messages								
								setTextMessage("Loop Count: " + iLoopCount);
								++iLoopCount;
								socket.setSoTimeout(250);
							}
						}
						
						// Got our only message, so either report the data or the error.
						
						socket.close();
						
						setTextMessage(new String(packet.getData()));
					} catch(IOException e) {
						setTextMessage(e.getLocalizedMessage());
					} catch(Exception p) {
						setTextMessage(p.getLocalizedMessage());
					}
				}
			});
			bg.start();
			
		} catch (Exception e) {
			tv.setText(e.getLocalizedMessage());
		}
		
		// Build the thread that sends the broadcast data to the other socket

		try {
			Thread sender = new Thread(new Runnable() {
				@SuppressWarnings("unused")
				public void run()
				{
					String        multAddr = "224.0.0.1";    // rf. www.iana.org/assignments/multicast-addresses.xhtml (etc)
					String        discAddr = "224.0.0.255";  // discovery address (unassigned and used as rqd."
					WifiLock      wifiLock = null;
					MulticastLock mcLock   = null;
					try {
						String stMsg  = "Howdy Ma!";        // Message to send
						byte[] bArray = stMsg.getBytes();   // Transfer format
						
						// Try and get your local address
						
						ConnectivityManager cm = (ConnectivityManager)MainActivity.this.getSystemService(Context.CONNECTIVITY_SERVICE);
						NetworkInfo         ni = cm.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
						
						if ( ni.isConnected() ) {
						
							WifiManager wf = (WifiManager)MainActivity.this.getSystemService(Context.WIFI_SERVICE);
							DhcpInfo    di = wf.getDhcpInfo();

							int broadcast = di.ipAddress;
							byte[] quads = new byte[4];
							
							for( int i=0 ; i < 4 ; ++i ) quads[i] = (byte)((broadcast >> i * 8) & 0xFF);
							InetAddress iaddr = InetAddress.getByAddress(quads);
							
							// Get the Wifi and Multicast Locks to disable multicast filtering.
							
							wifiLock = wf.createWifiLock(WifiManager.WIFI_MODE_FULL, "replicationLock");
							wifiLock.setReferenceCounted(true);
						    wifiLock.acquire();

					        mcLock = wf.createMulticastLock("replicationMulticastLock");
					        mcLock.setReferenceCounted(true);
					        mcLock.acquire();
					        
					        // Build the output datagram socket and data buffer
						
							MulticastSocket msock = new MulticastSocket();

							msock.setTimeToLive(2);
							msock.joinGroup(InetAddress.getByName(multAddr));

							DatagramPacket dpack = new DatagramPacket(bArray,bArray.length,iaddr,1600);
							
							// Wait for 8 seconds so the counter loop executes
							
							Thread.sleep(8000);
							
							// Send the data and allow this thread to die from natural causes.
							
							msock.send(dpack);
							
							mcLock.release();
							wifiLock.release();
							
							msock.close();
						}
					} catch(IOException e) {
						if ( null != mcLock   ) mcLock.release();
						if ( null != wifiLock ) wifiLock.release();
						setTextMessage(e.getLocalizedMessage());
					} catch(Exception p) {
						if ( null != mcLock   ) mcLock.release();
						if ( null != wifiLock ) wifiLock.release();
						setTextMessage(p.getLocalizedMessage());
					}
				}
			});
			sender.start();
			
		} catch(Exception e) {
			tv.setText(e.getLocalizedMessage());
		}
	}
	
	// This handler paints messages on this thread (the user interface thread)
	
	static Handler handler = new Handler() {
		@Override
		public void handleMessage(Message msg) {
			Bundle   bd = msg.getData();
			String   mg = bd.getString("resMsg");
			tv.setText(mg);
		}
	};

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	// Send a message to the user interface thread.
	
	synchronized void setTextMessage(String msg)
	{
		Message mg = handler.obtainMessage();
		Bundle  bd = new Bundle();
		
		bd.putString("resMsg", msg);
		mg.setData(bd);
		handler.sendMessage(mg);
	}
	
	// Make sure a network connection is available so sockets can be created.
	
	public static boolean isNetworkAvailable(Context context)
	{
		boolean isConnected = false;
		
		// Get the connectivity manager and retrieve an array that
		// contains an entry for each possible network type.
		
		ConnectivityManager cm   = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo[]       nets = cm.getAllNetworkInfo();
		
		// Make sure one of the supported networks is available.
		
		if ( null != nets )
		{
			for( NetworkInfo ni : nets )
			{
				if ( ni.isConnected() ) {
					int netType = ni.getType();
					isConnected = (netType == ConnectivityManager.TYPE_ETHERNET ? true :
						           netType == ConnectivityManager.TYPE_MOBILE   ? true :
						           netType == ConnectivityManager.TYPE_WIFI     ? true :
						           netType == ConnectivityManager.TYPE_WIMAX    ? true : false);
					if ( true == isConnected ) break;
				}
			}
		}
		return isConnected;
	}
	
	// Get wifi flag
	
	public static boolean isEthernetConnected(Context context)
	{
		ConnectivityManager cm = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
		return cm.getNetworkInfo(ConnectivityManager.TYPE_ETHERNET).isConnected();
	}
	
	public static boolean isWifiConnected(Context context)
	{
		ConnectivityManager cm = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
		return cm.getNetworkInfo(ConnectivityManager.TYPE_WIFI).isConnected();
	}
	
	public static NetworkInfo getCurrentNetwork(Context context)
	{
		ConnectivityManager cm = (ConnectivityManager)context.getSystemService(Context.CONNECTIVITY_SERVICE);
		return cm.getActiveNetworkInfo();
	}
	
	
	// Get the broadcast address for this network address.
	
	@SuppressWarnings("unused")
	InetAddress getBroadcastAddress() throws IOException
	{
		int      iNetType;
		DhcpInfo dhcp;
		WifiManager wifi = null;
		
		Context context = MainActivity.this;
		if ( false == isNetworkAvailable(context) ) throw new IOException("No Connected Network");
		
		iNetType = getCurrentNetwork(context).getType();
		
		if ( getCurrentNetwork(context).getType() == ConnectivityManager.TYPE_WIFI ) {
			wifi = (WifiManager)context.getSystemService(Context.WIFI_SERVICE);
		} 

		// Get the Broadcast address
/*		
		WifiManager wifi = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
		DhcpInfo dhcp;
*/		
		try {
			dhcp = wifi.getDhcpInfo();
		} catch (Exception e) {
			throw new IOException(e.getLocalizedMessage());
		}
		// handle null somehow
		
		int broadcast = (dhcp.ipAddress & dhcp.netmask) | ~dhcp.netmask;
		byte[] quads = new byte[4];
		
		for( int i=0 ; i < 4 ; ++i ) quads[i] = (byte)((broadcast >> i * 8) & 0xFF);
		return InetAddress.getByAddress(quads);
	}
}
