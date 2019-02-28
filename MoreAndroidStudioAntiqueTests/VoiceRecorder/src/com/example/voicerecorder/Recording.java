package com.example.voicerecorder;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;

public class Recording
{
	private DefaultAttributes appDefaults    = null;
	private String            outputFileName = null;
	private String            baseFileName   = null;
	private String            tempFileName   = null;
	private String            finalFileName  = null;
	private boolean           isRecording    = false;
	private int    	          minBufReadSize;
	private AudioRecord       recorder;
	private Thread            recordingThread;
	
	private static final String waveExtension = ".wav";
	
	// Default Constructor
	
	Recording(DefaultAttributes defaults) throws IllegalArgumentException { appDefaults = defaults; startRawRecording(defaults); }
	
	private void startRecording(DefaultAttributes defaults)
	{
//		if ( appDefaults.getOutputFormat() == )
	}

	/* -------------------------------------------------------------------------------
     * Start recording the new audio file
     * ------------------------------------------------------------------------------- */
    
    private void startRawRecording(DefaultAttributes defaults)
    {
    	// Get the name of the new  output file.

    	tempFileName   = defaults.getAbsoluteFileName();
    	baseFileName   = tempFileName.substring(tempFileName.lastIndexOf('/')+1);
    	finalFileName  = tempFileName + waveExtension;
    	outputFileName = baseFileName + waveExtension;

    	if ( true == (new File(finalFileName)).exists() )
    	{
    		AlertDialog.Builder builder = new AlertDialog.Builder(defaults.getContext());
    		builder.setCancelable(true);
    		builder.setTitle("Duplicate File Name");
    		builder.setInverseBackgroundForced(true);
			builder.setPositiveButton("Yes", new DialogInterface.OnClickListener() { @Override public void onClick(DialogInterface dialog, int which) { dialog.dismiss(); } });
			builder.setPositiveButton("No", new DialogInterface.OnClickListener()  { @Override public void onClick(DialogInterface dialog, int which) { dialog.dismiss(); } });
			AlertDialog alert = builder.create();
			alert.show();
			return;
   		}
    	
    	// Instance a new recorder

        minBufReadSize = AudioRecord.getMinBufferSize((int)defaults.getSampleRate(), defaults.getAudioFormat(), defaults.getBitsPerSample());
    	
    	recorder = new AudioRecord(MediaRecorder.AudioSource.MIC,
    			                   (int)defaults.getSampleRate(),
    			                   defaults.getAudioFormat(),
    			                   defaults.getBitsPerSample(),
    			                   minBufReadSize);
    	
    	// Start recording
    	
    	if ( 1 == recorder.getState() ) recorder.startRecording();

    	isRecording = true;
    	
    	// Save the data in a separate thread
    	// This makes it look like a separate thread is doing the recording.
    	
    	recordingThread = new Thread(new Runnable() {
    		@Override
    		public void run()
    		{
    			writeAudioDataToFile();
    		}
    	},"AudioRecorder Thread");
    	
    	recordingThread.start();
    }
    
    /* -------------------------------------------------------------------------------
     * Write audio to a temporary data file.
     * ------------------------------------------------------------------------------- */
    
    private void writeAudioDataToFile()
    {
    	if ( null == recorder ) return;
    	
    	if ( null == baseFileName || null == outputFileName )
    	{
    		if ( 1 == recorder.getState() ) recorder.stop();
    		recorder.release();
    		return;
    	}
 
    	byte             data[] = new byte[minBufReadSize];
    	FileOutputStream os     = null;
    	
    	try
    	{
    		os = appDefaults.getContext().openFileOutput(baseFileName,Context.MODE_PRIVATE);
    	}
    	catch( IOException ioex )
    	{
    		if ( 1 == recorder.getState() ) recorder.stop();
    		recorder.release();
    		ioex.printStackTrace();
    		return;
    	}
    	
    	int read = 0;
    	
    	while( isRecording )
    	{
    		read = recorder.read(data,0,minBufReadSize);
    		
    		if ( AudioRecord.ERROR_INVALID_OPERATION != read )
    		{
    			try {
    				os.write(data);
    			}catch( IOException e0 ) {
    				isRecording = false;
    				try { os.close(); } catch(IOException e1) {}
    				os = null;
    			}
    		}
    		else
    		{
    			isRecording = false;
    			try { os.close(); } catch(IOException e) {}
    		}
    	}
    	
    	if ( 1 == recorder.getState() ) recorder.stop();
    	
    	recorder.release();
    	
    	recorder = null;
    		
    	if ( null != os )
    	{
    		try { os.close(); } catch (IOException e) {}
    		copyWaveFile(baseFileName,outputFileName);
    		(new File(tempFileName)).delete();
    		baseFileName = null;
    		tempFileName = null;
    	}
    }
    
    // Stop recording when the button is pressed
    
    public void stopRecording()
    {
    	isRecording = false;
    }
    
    private void copyWaveFile(String inFilename,String outFilename)
    {
    	FileInputStream  in             = null;
    	FileOutputStream out            = null;
    	long             totalAudioLen  = 0;
    	long             totalDataLen   = totalAudioLen + 36;
    	long             longSampleRate = appDefaults.getSampleRate();
    	int              channels       = appDefaults.getChannels();
    	long             byteRate       = appDefaults.getByteRate();
    	
    	byte[] data = new byte[minBufReadSize];
    	
    	try {
    		in  = appDefaults.getContext().openFileInput(inFilename);
    		out = appDefaults.getContext().openFileOutput(outFilename, Context.MODE_PRIVATE);
    		/*
    		in  = appDefaults.getContext().openFileInput(baseFileName);
    		out = appDefaults.getContext().openFileOutput(outputFileName,Context.MODE_PRIVATE);
    		*/
    		
    		totalAudioLen = in.getChannel().size();
    		totalDataLen  = totalAudioLen + 36;
    		
    		WriteWaveFileHeader(out, totalAudioLen, totalDataLen, longSampleRate, channels, byteRate);
    		
    		while(in.read(data) != -1) out.write(data);
    		
    		in.close();
    		out.close();
    	} catch (FileNotFoundException e) {
    		e.printStackTrace();
    	} catch (IOException e) {
    		e.printStackTrace();
    	}
    }
    
    private void WriteWaveFileHeader(FileOutputStream out,
    		                         long             totalAudioLen,
    		                         long             totalDataLen,
    		                         long             longSampleRate,
    		                         int              channels,
    		                         long             byteRate) throws IOException
    		                         {

    	byte[] header = new byte[44];

    	header[ 0] = 'R';  // RIFF/WAVE header
    	header[ 1] = 'I';
    	header[ 2] = 'F';
    	header[ 3] = 'F';
    	header[ 4] = (byte) (totalDataLen & 0xff);
    	header[ 5] = (byte) ((totalDataLen >> 8) & 0xff);
    	header[ 6] = (byte) ((totalDataLen >> 16) & 0xff);
    	header[ 7] = (byte) ((totalDataLen >> 24) & 0xff);
    	header[ 8] = 'W';
    	header[ 9] = 'A';
    	header[10] = 'V';
    	header[11] = 'E';
    	header[12] = 'f';  // 'fmt ' chunk
    	header[13] = 'm';
    	header[14] = 't';
    	header[15] = ' ';
    	header[16] = 16;  // 4 bytes: size of 'fmt ' chunk
    	header[17] = 0;
    	header[18] = 0;
    	header[19] = 0;
    	header[20] = 1;  // format = 1
    	header[21] = 0;
    	header[22] = (byte) channels;
    	header[23] = 0;
    	header[24] = (byte) (longSampleRate & 0xff);
    	header[25] = (byte) ((longSampleRate >> 8) & 0xff);
    	header[26] = (byte) ((longSampleRate >> 16) & 0xff);
    	header[27] = (byte) ((longSampleRate >> 24) & 0xff);
    	header[28] = (byte) (byteRate & 0xff);
    	header[29] = (byte) ((byteRate >> 8) & 0xff);
    	header[30] = (byte) ((byteRate >> 16) & 0xff);
    	header[31] = (byte) ((byteRate >> 24) & 0xff);
    	header[32] = (byte) (2 * 16 / 8);  // block align
    	header[33] = 0;
    	header[34] = (byte)(appDefaults.getBitsPerSample() == AudioFormat.ENCODING_PCM_8BIT ? 8 : 16);
    	header[35] = 0;
    	header[36] = 'd';
    	header[37] = 'a';
    	header[38] = 't';
    	header[39] = 'a';
    	header[40] = (byte) (totalAudioLen & 0xff);
    	header[41] = (byte) ((totalAudioLen >> 8) & 0xff);
    	header[42] = (byte) ((totalAudioLen >> 16) & 0xff);
    	header[43] = (byte) ((totalAudioLen >> 24) & 0xff);

    	out.write(header, 0, 44);
    }
}