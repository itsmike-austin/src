package com.example.httpgetdemo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;

import android.os.AsyncTask;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;

public class MainActivity extends Activity {
	
	private TextView contentView;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		contentView = (TextView)findViewById(R.id.textView1);
		try {
			String retData = new DownloadTask().execute("http://code.google.com/android/").get();
			contentView.setText(retData);
		} catch (Exception e) {
			contentView.setText(e.getLocalizedMessage());
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	private class DownloadTask extends AsyncTask<String,Void,String>
	{
		@Override
		protected String doInBackground(String... urls) {
			
			BufferedReader in = null;

			try {
				HttpClient   client   = new DefaultHttpClient();
				HttpGet      request  = new HttpGet(urls[0]);
				HttpResponse response = client.execute(request);
				
				in = new BufferedReader(new InputStreamReader(response.getEntity().getContent()));
				
				StringBuffer sb   = new StringBuffer("");
				String       line = "";
				String       NL   = System.getProperty("line.separator");
				
				while( (line=in.readLine()) != null ) sb.append(line+NL);
				
				in.close();
				
				String page = sb.toString();
				
				return page;				
			} catch (Exception e) {
				return e.getLocalizedMessage();
			} finally {
				if ( in != null ) {
					try {
						in.close();
					} catch (IOException e) {
						return e.getLocalizedMessage();
					}
				}
			}
		}
		
		@Override protected void onPostExecute(String result) { super.onPostExecute(result); }
	}
}
