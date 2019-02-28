package com.example.testmediaplayer1;

import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import android.media.AudioManager;
import android.media.MediaPlayer;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.app.Activity;
import android.content.Context;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnTouchListener;
import android.widget.TextView;

public class MainActivity extends Activity implements OnTouchListener {

	MediaPlayer bgMusic = null;                             // Background Music for Game
	
	// These files are stored in the APK assets area. They must be copied there in order to
	// facilitate creation of the external files for single playback.

	final static String backgroundMusic = "background.mp3"; // Background Music File to create in internal storage
	final static String dingMusic       = "ding.mp3";       // Touch (Strike) Music file to create in internal storage
	final static String popSplat01      = "popsplat01.mp3"; // Long Smash/Splat Music when an object is hit
	final static String popSplat02      = "popsplat02.mp3"; // Shorter Smash/Splat Music when an object is hit
	final static String popSplat03      = "popsplat03.mp3"; // Shorter Smash/Splat Music when an object is hit
	final static String popSplat04      = "popsplat04.mp3"; // Really short Smash/Splat Music when an object is hit
	final static String splat01         = "splat01.mp3";    // Instant hit music

	static TextView thisText;                               // XXX: Dump this with UI update
	
	final static String[] fileNameList = new String[]{backgroundMusic,dingMusic,popSplat01,popSplat02,popSplat03,popSplat04,splat01};
	
	final static String[] hitNameList = new String[]{dingMusic,splat01,popSplat04,popSplat03,popSplat02,popSplat01};
	
	AudioManager audioManager = null;                       // Used to handle volume buttons on device
	
	static int iSound;

	@Override
	protected void onCreate(Bundle savedInstanceState) {

		// Setup the app and open the default layout
		// XXX: May require mods later
		
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		// Get the audio manager so you can handle volume button requests
		
		audioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
		
		// XXX: This should go away with user interface update

		thisText = (TextView)findViewById(R.id.text_view);

		// Setup the app audio and video files in the internal storage area.
		// XXX: thisText will probably be dumped later (might be useful for error)
		
		try
		{
			setup();
		}
		catch( IOException ex1 )
		{
			thisText.setText(ex1.getMessage());
			return;
		}
		
		// Start playing the background music
		
		startMusic();
		
		iSound = 0;
	}
	
	@Override
	public void onPause()
	{
		super.onPause();
		thisText.setText("Paused");
		if ( null != bgMusic ) bgMusic.pause();
	}
	
	@Override
	public void onResume()
	{
		super.onResume();
		if ( null != bgMusic ) bgMusic.start();
		thisText.setText("Resume");
	}
	
	@Override
	public void onStop()
	{
		super.onStop();
		thisText.setText("Stop");
	}
	
	@Override
	public void onDestroy()
	{
		if ( null != bgMusic ) bgMusic.release();
		bgMusic = null;
	}

	@Override
	public boolean onKeyDown(int KeyCode,KeyEvent event)
	{
		switch( KeyCode )
		{
		case KeyEvent.KEYCODE_VOLUME_UP:
			audioManager.adjustStreamVolume(AudioManager.STREAM_MUSIC,AudioManager.ADJUST_RAISE,AudioManager.FLAG_SHOW_UI);
			return true;
			
		case KeyEvent.KEYCODE_VOLUME_DOWN:
			audioManager.adjustStreamVolume(AudioManager.STREAM_MUSIC,AudioManager.ADJUST_LOWER,AudioManager.FLAG_SHOW_UI);
			return true;
			
		default:
			return false;	
		}
	}
	
	static Handler handler = new Handler()
	{
		@Override
		public void handleMessage(Message msg)
		{
			Bundle bundle = msg.getData();
			String string = bundle.getString("myKey");
			thisText.setText(string);
		}
	};
	
	public void startMusic()
	{
		new Thread(new Runnable()
		{
			public void run()
			{
				FileInputStream in = null;
				FileDescriptor  df = null;
				
				try
				{
					in = openFileInput(backgroundMusic);
					df = in.getFD();
				}
				catch(IOException io0)
				{
					return;   // Fail silently.
				}
				
				MediaPlayer dp = new MediaPlayer();
				
				// Setup the data source for the "ding" when touched.
				
				try
				{
					dp.setDataSource(df);
				}
				catch( Exception ex0 )
				{
					try { in.close(); } catch(IOException io0) {}
					return;      // Fail silently.
				}

				// Loop the main tune.
				
				dp.setLooping(true);
				
				// Setup the listener for the prepare (question if this is required!)
				// Maybe just go directly to start!
				
				dp.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
					@Override
					public void onPrepared(MediaPlayer xp) {
						xp.start();
					}
				});
				
				// Make sure all resources are gone once the sound has been played
				
				dp.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
					@Override
					public void onCompletion(MediaPlayer pb) {
						pb.start();
					}
				});
				
				// Run the prepare method to build things through.
				
				try
				{
					dp.prepareAsync();
				}
				catch( IllegalStateException ioe)
				{
					try { in.close(); } catch(IOException io1) {}
				}
				
				bgMusic = dp;
			}
		}).start();
	}
	
	public void playTouchSound(final String soundName)
	{
		new Thread(new Runnable()
		{
			public void run()
			{
				FileInputStream in = null;
				FileDescriptor  df = null;
				
				try
				{
					in = openFileInput(soundName);
					df = in.getFD();
				}
				catch(IOException io0)
				{
					return;   // Fail silently.
				}
				
				MediaPlayer dp = new MediaPlayer();

				// Setup the data source for the "ding" when touched.
				
				try
				{
					dp.setDataSource(df);
				}
				catch( Exception ex0 )
				{
					try { in.close(); } catch(IOException io0) {}
					return;      // Fail silently.
				}
				
				// Setup the listener for the prepare (question if this is required!)
				// Maybe just go directly to start!
				
				dp.setOnPreparedListener(new MediaPlayer.OnPreparedListener() {
					@Override
					public void onPrepared(MediaPlayer xp) {
						xp.start();
					}
				});
				
				// Make sure all resources are gone once the sound has been played
				
				dp.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
					@Override
					public void onCompletion(MediaPlayer pb) {
						pb.start();
						pb.reset();
						pb.release();
					}
				});
				
				// Run the prepare method to build things through.
				
				try
				{
					dp.prepareAsync();
				}
				catch( IllegalStateException ioe)
				{
					try { in.close(); } catch(IOException io1) {}
				}
			}
		}).start();
	}
	
	@Override
    public boolean onTouch(View v, MotionEvent event) {
		
        if (event.getAction() == MotionEvent.ACTION_DOWN) playTouchSound(hitNameList[iSound]);
        return false;
    }

	@Override
	public boolean onTouchEvent(MotionEvent e)
	{
        if (e.getAction() == MotionEvent.ACTION_DOWN)
        	{
        	   playTouchSound(hitNameList[iSound]);
        	   iSound = (iSound + 1 < hitNameList.length ? ++iSound : 0);
        	}
        // Log.d("Done","Click");
		return false;
	}
	
	public void copyFile(String s_Filename) throws IOException
	{
		InputStream      in = null;
		FileOutputStream fo = null;
		byte             buff[];
		int              read;
		
		buff = new byte[1024];
		read = 0;
		
		// Check to see if the file exists
		
		File fm = new File(getFilesDir() + "/" + s_Filename);
		
		// If copies exist, simply return.
		
		if ( fm.exists() && fm.length() > 0 ) return;
		
		// Open the source file for reading
		
		try
		{
			in = getResources().getAssets().open(s_Filename);
		}
		catch( IOException io1 )
		{
			throw new IOException("Open file: " + s_Filename + " for Reading Failed");
		}
		
		// Create a new background music file in the internal directory.
		
		try
		{
			fo = openFileOutput(s_Filename,Context.MODE_PRIVATE);
		}
		catch ( IOException io2 )
		{
			throw new IOException("Open file: " + s_Filename + " for Writing Failed");
		}
		
		// Copy the contents from assets to internal file.
		
		try
		{
			while( (read=in.read(buff)) >= 0 ) fo.write(buff,0,read);
		}
		catch ( IOException io3 )
		{
			throw new IOException("Copy File: " + s_Filename + " Failed");
		}
		
		in.close();
		fo.close();
	}

	public void setup() throws IOException
	{
		try
		{
			for( int i=0 ; i < fileNameList.length ; ++i ) copyFile(fileNameList[i]);
		}
		catch( IOException ioex )
		{
			throw new IOException(ioex.getMessage());
		}
	}
}
