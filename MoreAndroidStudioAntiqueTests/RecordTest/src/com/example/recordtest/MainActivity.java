package com.example.recordtest;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.view.View;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.Toast;

public class MainActivity extends Activity
{
//    private static final int RECORDER_BPP = 16;
//    private static final String AUDIO_RECORDER_FOLDER = "AudioRecorder";
//    private static final String AUDIO_RECORDER_TEMP_FILE = "record_temp.raw";
	
	private static final String ChannelType[] = {"Mono","Stereo"};
	private static final String AudioBits[]   = {"8 Bit","16 Bit"};
	private static final String SampleRates[] = {"8000","11025","16000","22050","44100"};

	private static final String AUDIO_RECORDER_FILE_EXT_WAV = ".wav";
    private static final String AUDIO_RECORDER_SAVE_FILE = "SaveFile";
    
    private static int    RECORDER_SAMPLERATE = 44100;
    private static int    RECORDER_AUDIO_ENCODING = AudioFormat.ENCODING_PCM_16BIT;
    private static String AUDIO_RECORDER_FILE_EXT_RAW = ".raw";
    private static int    RECORDER_CHANNELS = AudioFormat.CHANNEL_IN_STEREO;
    private static byte   RECORDER_BPP = (byte)(RECORDER_AUDIO_ENCODING == AudioFormat.ENCODING_PCM_16BIT ? 16 : 8);
    
    private AudioRecord recorder        = null;
    private int         minBufReadSize  = 0;
    private Thread      recordingThread = null;
    private boolean     isRecording     = false;
    private String      tempFileName    = null;
    private String      finalFileName   = null;
    
    private Spinner     spinner1        = null;
    private Spinner     spinner2        = null;
    private Spinner     spinner3        = null;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
    	super.onCreate(savedInstanceState);
    	setContentView(R.layout.activity_main);
    	
    	setButtonHandlers();
    	enableButtons(false);
    	
        minBufReadSize  = AudioRecord.getMinBufferSize(RECORDER_SAMPLERATE, RECORDER_CHANNELS, RECORDER_AUDIO_ENCODING);
        
        spinner1 = (Spinner)findViewById(R.id.spinner1);
        
        List<String> channel_type_list = new ArrayList<String>();
        for( int i=0 ; i < ChannelType.length ; ++i ) channel_type_list.add(ChannelType[i]);
        
        ArrayAdapter<String> dataAdapter = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_dropdown_item,channel_type_list);
        
        dataAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        
        spinner1.setAdapter(dataAdapter);
        
        spinner1.setOnItemSelectedListener(new PickChannelType());
        
        spinner2 = (Spinner)findViewById(R.id.spinner2);
        
        List<String> audio_bits_list = new ArrayList<String>();
        for( int i=0 ; i < AudioBits.length ; ++i ) audio_bits_list.add(AudioBits[i]);
        
        ArrayAdapter<String> bitsAdapter = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_dropdown_item,audio_bits_list);
        
        bitsAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        
        spinner2.setAdapter(bitsAdapter);
        
        spinner2.setOnItemSelectedListener(new PickBitsType());
        
        spinner3 = (Spinner)findViewById(R.id.spinner3);
        
        List<String> sample_rate_list = new ArrayList<String>();
        for( int i=0; i < SampleRates.length ; ++i ) sample_rate_list.add(SampleRates[i]);
        
        ArrayAdapter<String> rateAdapter = new ArrayAdapter<String>(this,android.R.layout.simple_spinner_dropdown_item,sample_rate_list);
        
        rateAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        
        spinner3.setAdapter(rateAdapter);
        
        spinner3.setOnItemSelectedListener(new SampleRateType());
    }

    private void setButtonHandlers()
    {
    	((Button)findViewById(R.id.btnStart)).setOnClickListener(btnClick);
    	((Button)findViewById(R.id.btnStop)).setOnClickListener(btnClick);
    }
     
    private void enableButton(int id,boolean isEnable){
    	((Button)findViewById(id)).setEnabled(isEnable);
    }
     
    private void enableButtons(boolean isRecording) {
    	enableButton(R.id.btnStart,!isRecording);
    	enableButton(R.id.btnStop,isRecording);
    }
    
    private String getSaveFileName()
    {
    	return AUDIO_RECORDER_SAVE_FILE + AUDIO_RECORDER_FILE_EXT_WAV;
    }
    
    private String getTempFileName()
    {
    	return (null == tempFileName ? System.currentTimeMillis()+AUDIO_RECORDER_FILE_EXT_RAW : tempFileName);
    }
     
    private void startRecording()
    {
    	if ( null != tempFileName )
    	{
    		(new File(getFilesDir()+"/"+tempFileName)).delete();
    		tempFileName = null;
    	}
    	
    	if ( null != finalFileName )
    	{
    		(new File(getFilesDir()+"/"+finalFileName)).delete();
    		finalFileName = null;
    	}
    	
    	finalFileName = getSaveFileName();
    	tempFileName  = getTempFileName();
    	
    	recorder = new AudioRecord(MediaRecorder.AudioSource.MIC,
    			                   RECORDER_SAMPLERATE,
    			                   RECORDER_CHANNELS,
    			                   RECORDER_AUDIO_ENCODING,
    			                   minBufReadSize);
             
    	if ( 1 == recorder.getState() ) recorder.startRecording();

    	isRecording = true;
    	
        recordingThread = new Thread(new Runnable() {
        	@Override
            public void run()
        	{
        		writeAudioDataToFile();
        	}
        },"AudioRecorder Thread");
        
        recordingThread.start();
    }
     
    private void writeAudioDataToFile()
    {
    	byte             data[] = new byte[minBufReadSize];
    	FileOutputStream os     = null;
    	
    	try {
    		os= openFileOutput(tempFileName,Context.MODE_PRIVATE);
    	} catch( IOException ioex ) {
    		ioex.printStackTrace();
    	}
    	
    	int read = 0;
    	
    	if(null != os)
    	{
    		while(isRecording)
    		{
    			read = recorder.read(data, 0, minBufReadSize);
    			
    			if(AudioRecord.ERROR_INVALID_OPERATION != read)
    			{
    				try {
    					os.write(data);
    				} catch (IOException e) {
    					e.printStackTrace();
    				}
    			}
    		}
    		
    		try {
    			os.close();
    		} catch (IOException e) {
    			e.printStackTrace();
    		}
    	}
    }
    
    private void stopRecording()
    {
    	if(null != recorder)
    	{
    		isRecording = false;
    		
    		if ( 1 == recorder.getState() ) recorder.stop();
    		
    		recorder.release();
    		
    		recorder = null;
    		recordingThread = null;
    	}
         copyWaveFile(tempFileName,finalFileName);
         deleteTempFile();
    }

    private void deleteTempFile()
    {
    	(new File(tempFileName)).delete();
    }
    
    private void copyWaveFile(String inFilename,String outFilename)
    {
    	FileInputStream  in            = null;
    	FileOutputStream out           = null;
    	long             totalAudioLen = 0;
    	long             totalDataLen  = totalAudioLen + 36;
    	long longSampleRate            = RECORDER_SAMPLERATE;
    	int channels                   = (RECORDER_CHANNELS == AudioFormat.CHANNEL_IN_STEREO ? 2 : 1);
    	long byteRate                  = RECORDER_BPP * RECORDER_SAMPLERATE * channels/8;
    	
    	byte[] data = new byte[minBufReadSize];
    	
    	try {
    		in  = openFileInput(tempFileName);
    		out = openFileOutput(finalFileName,Context.MODE_PRIVATE);
/*    		
    		in  = new FileInputStream(inFilename);
    		out = new FileOutputStream(outFilename);
 */   		
    		totalAudioLen = in.getChannel().size();
    		totalDataLen  = totalAudioLen + 36;
    		
    		AppLog.logString("File size: " + totalDataLen);
    		
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
    								 long             byteRate) throws IOException {
    	
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
    	header[34] = RECORDER_BPP;  // bits per sample
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
    
    private View.OnClickListener btnClick = new View.OnClickListener()
    {
    	@Override
    	public void onClick(View v)
    	{
    		switch(v.getId())
    		{
    		case R.id.btnStart:
    			{
    				AppLog.logString("Start Recording");
    				
    				enableButtons(true);
    				startRecording();
    				
    				break;
    			}
    		case R.id.btnStop:
    			{
    				AppLog.logString("Start Recording");
    				
    				enableButtons(false);
    				stopRecording();
    				
    				break;
    			}
    		}
    	}
    };
    
    private class PickChannelType implements OnItemSelectedListener
    {
    	public void onItemSelected(AdapterView<?> parent,View view,int pos,long id)
    	{
    		Toast.makeText(parent.getContext(), "On Item Select " + parent.getItemAtPosition(pos).toString(), Toast.LENGTH_LONG).show();
    	}

		@Override
		public void onNothingSelected(AdapterView<?> arg0) {}
    }
    
    private class PickBitsType implements OnItemSelectedListener
    {
    	public void onItemSelected(AdapterView<?> parent,View view,int pos,long id)
    	{
    		Toast.makeText(parent.getContext(), "On ItemSelect " + parent.getItemAtPosition(pos).toString(), Toast.LENGTH_LONG).show();
    	}

		@Override
		public void onNothingSelected(AdapterView<?> arg0) {}
    }
    
    private class SampleRateType implements OnItemSelectedListener
    {
    	public void onItemSelected(AdapterView<?> parent,View view,int pos,long id)
    	{
    		Toast.makeText(parent.getContext(), "On ItemSelect " + parent.getItemAtPosition(pos).toString(), Toast.LENGTH_LONG).show();
    	}

		@Override
		public void onNothingSelected(AdapterView<?> arg0) {}
    }
}
