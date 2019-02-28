package com.example.wifiservicediscovery;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

import android.os.Handler;
import android.util.Log;

public class ChatManager implements Runnable
{
	private Socket socket = null;
	private Handler handler;
	
	public ChatManager(Socket socket,Handler handler)
	{
		this.socket = socket;
		this.handler = handler;
	}
	
	private InputStream  iStream;
	private OutputStream oStream;
	private static final String TAG = "ChatHandler";
	
	@Override
	public void run() {
		try {
			iStream = socket.getInputStream();
			oStream = socket.getOutputStream();
			byte[] buffer = new byte[1024];
			int bytes;
			
			handler.obtainMessage(WiFiServiceDiscoveryActivity.MY_HANDLE,this).sendToTarget();
			
			while( true ) {
				try {
					// Read from the input stream.
					if ( -1 == (bytes=iStream.read(buffer)) ) break;
					
					handler.obtainMessage(WiFiServiceDiscoveryActivity.MESSAGE_READ,bytes,-1,buffer).sendToTarget();
				} catch( IOException e ) {
					Log.e(TAG,"disconnected",e);
				}
			}
		} catch( IOException e ) {
			e.printStackTrace();
		} finally {
			try {
				socket.close();
			} catch ( IOException e ) {
				e.printStackTrace();
			}
		}
	}
	
	public void write(byte[] buffer)
	{
		try {
			oStream.write(buffer);
		} catch( IOException e) {
			Log.e(TAG,"Exception during write",e);
		}
	}
}