package com.example.audiofiletest;

import java.io.File;
import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import android.app.ActionBar.LayoutParams;
import android.app.Dialog;
import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioRecord;
import android.media.MediaPlayer;
import android.media.MediaRecorder;
import android.view.Gravity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemSelectedListener;

public class AudioFileDialog extends Dialog
{
	private Dialog       audioDialog       = null;
	private LinearLayout layoutBackground  = null;
	private LinearLayout fileNameLayout    = null;
	private TextView     fileNameLabel     = null;
	private EditText     fileNameField     = null;
	private LinearLayout sampleRateLayout  = null;
	private TextView     sampleRateLabel   = null;
	private Spinner      sampleRateSpinner = null;
	private LinearLayout channelLayout     = null;
	private TextView     channelLabel      = null;
	private Spinner      channelSpinner    = null;
	private LinearLayout bitsLayout        = null;
	private TextView     bitsLabel         = null;
	private Spinner      bitsSpinner       = null;
	private LinearLayout recordLayout      = null;
	private Button       recordButton      = null;
	private Button       stopRecButton     = null;
	private Button       previewButton     = null;
	private LinearLayout buttonSepLayout   = null;
	private View         buttonSeparator   = null;
	private LinearLayout buttonLayout      = null;
	private Button       okButton          = null;
	private View         buttonDivider     = null;
	private Button       cancelButton      = null;
	
	private String       tempFileName      = null;
	private String       finalFileName     = null;
	
	private int          minBufReadSize    = 0;
	private AudioRecord  recorder          = null;
	private boolean      isRecording       = false;
	private Thread       recordingThread   = null;
	
	private static final int    recButtonId     = 1;
	private static final int    stopRecButtonId = 2;
	private static final int    previewButtonId = 3;
	private static final int    recButtonWidth  = 190;
	private static final String ChannelType[]   = {"Stereo","Mono"};
	private static final String AudioBits[]     = {"16 Bit","8 Bit"};
	private static final String SampleRates[]   = {"8000","11025","16000","22050","44100"};
	
	// The default values for the settings.
	
	private int    ChannelCount  = 2;
	private int    AudioBitCount = 16;
	private int    SampleCount   = 8000;
	private String AudioFileName = "";
	
	private MainActivity mainActivity = null;

	public AudioFileDialog(Context context,MainActivity act) {
		super(context);
		
		mainActivity = act;
		
		// Save the dialog to facilitate button methods
		
		audioDialog = this;
		audioDialog.setTitle("Audio File Parameters");
		
		// Create the primary layout for the dialog
		
		layoutBackground = new LinearLayout(context);
		layoutBackground.setOrientation(LinearLayout.VERTICAL);
		layoutBackground.setLayoutParams(new LinearLayout.LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT));
		
		// Create the container for the file name
		
		fileNameLayout = new LinearLayout(context);
		fileNameLayout.setOrientation(LinearLayout.HORIZONTAL);
		
		fileNameLabel = new TextView(context);
		fileNameLabel.setText("File Name: ");

		fileNameField = new EditText(context);
		fileNameField.setSingleLine();
 		fileNameField.setText("");
 		fileNameField.setEms(10);
		
		fileNameLayout.addView(fileNameLabel);
		fileNameLayout.addView(fileNameField);
		
		// Create the container for the sample rate
		
		sampleRateLayout = new LinearLayout(context);
		sampleRateLayout.setOrientation(LinearLayout.HORIZONTAL);
		
		sampleRateLabel = new TextView(context);
		sampleRateLabel.setText("Sample Rate: ");
		
		sampleRateSpinner = new Spinner(context);
        List<String> sample_rate_list = new ArrayList<String>();
        for( int i=0 ; i < SampleRates.length ; ++i ) sample_rate_list.add(SampleRates[i]);        
        ArrayAdapter<String> sampleRateAdapter = new ArrayAdapter<String>(context,android.R.layout.simple_spinner_dropdown_item,sample_rate_list);
        sampleRateAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        sampleRateSpinner.setAdapter(sampleRateAdapter);
        sampleRateSpinner.setOnItemSelectedListener(new SampleRateType());
        
        sampleRateLayout.addView(sampleRateLabel);
        sampleRateLayout.addView(sampleRateSpinner);
        
        // Create the container for the channel type (stereo/mono)
        
        channelLayout = new LinearLayout(context);
        channelLayout.setOrientation(LinearLayout.HORIZONTAL);
        
        channelLabel = new TextView(context);
        channelLabel.setText("Channel Type: ");
        
        channelSpinner = new Spinner(context);
        List<String> channel_type_list = new ArrayList<String>();
        for( int i=0 ; i < ChannelType.length ; ++i ) channel_type_list.add(ChannelType[i]);
        ArrayAdapter<String> channelTypeAdapter = new ArrayAdapter<String>(context,android.R.layout.simple_spinner_dropdown_item,channel_type_list);
        channelTypeAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        channelSpinner.setAdapter(channelTypeAdapter);
        channelSpinner.setOnItemSelectedListener(new PickChannelType());
        
        channelLayout.addView(channelLabel);
        channelLayout.addView(channelSpinner);
        
        // Create the container for the bits per sample.
        
        bitsLayout = new LinearLayout(context);
        bitsLayout.setOrientation(LinearLayout.HORIZONTAL);
        
        bitsLabel = new TextView(context);
        bitsLabel.setText("Bits Per Sample: ");
        
        bitsSpinner = new Spinner(context);
        List<String> bits_type_list = new ArrayList<String>();
        for( int i=0 ; i < AudioBits.length ; ++i ) bits_type_list.add(AudioBits[i]);
        ArrayAdapter<String> bitsTypeAdapter = new ArrayAdapter<String>(context,android.R.layout.simple_spinner_dropdown_item,bits_type_list);
        bitsTypeAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        bitsSpinner.setAdapter(bitsTypeAdapter);
        bitsSpinner.setOnItemSelectedListener(new PickBitsType());
        
        bitsLayout.addView(bitsLabel);
        bitsLayout.addView(bitsSpinner);
        
        recordLayout = new LinearLayout(context);
        recordLayout.setOrientation(LinearLayout.HORIZONTAL);
        recordLayout.setGravity(Gravity.CENTER);
        
        recordButton = new Button(context);
        recordButton.setText("Record");
        recordButton.setId(recButtonId);
        recordButton.setEnabled(true);
        recordButton.setWidth(recButtonWidth);
        recordButton.setOnClickListener(recBtnClick);
        
        stopRecButton = new Button(context);
        stopRecButton.setText("Stop");
        stopRecButton.setId(stopRecButtonId);
        stopRecButton.setEnabled(false);
        stopRecButton.setWidth(recButtonWidth);
        stopRecButton.setOnClickListener(recBtnClick);
        
        previewButton = new Button(context);
        previewButton.setText("Preview");
        previewButton.setId(previewButtonId);
        previewButton.setEnabled(false);
        previewButton.setWidth(recButtonWidth);
        previewButton.setOnClickListener(recBtnClick);
        
        recordLayout.addView(recordButton);
        recordLayout.addView(stopRecButton);
        recordLayout.addView(previewButton);
        
        // Create a long separator for the button bar
        
    	buttonSepLayout = new LinearLayout(context);
    	buttonSepLayout.setOrientation(LinearLayout.HORIZONTAL);
    	buttonSepLayout.setGravity(Gravity.CENTER);

    	buttonSeparator = new View(context);
        RelativeLayout.LayoutParams bbParms = new RelativeLayout.LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT);
        bbParms.addRule(RelativeLayout.BELOW,5);
        bbParms.addRule(RelativeLayout.CENTER_HORIZONTAL);
        bbParms.height = 2;
        buttonSeparator.setBackgroundColor(0xFF808080);
        buttonSeparator.setLayoutParams(bbParms);
        
        buttonSepLayout.addView(buttonSeparator);
        
        // Create the buttons for dialog actions.
        
        buttonLayout = new LinearLayout(context,null,android.R.style.DeviceDefault_ButtonBar);
        buttonLayout.setOrientation(LinearLayout.HORIZONTAL);
        buttonLayout.setGravity(Gravity.CENTER_HORIZONTAL);
        LinearLayout.LayoutParams lParms = new LinearLayout.LayoutParams(LayoutParams.MATCH_PARENT,60);
        lParms.weight = 1.0f;
        buttonLayout.setLayoutParams(lParms);
        
        okButton = new Button(context,null,android.R.style.DeviceDefault_SegmentedButton);
        okButton.setText(android.R.string.ok);
        okButton.setWidth(250);
        okButton.setHeight(60);
        okButton.setGravity(Gravity.CENTER);
        okButton.setOnClickListener(new PickDialogOkButton());

    	buttonDivider = new View(context);
        RelativeLayout.LayoutParams lineParms = new RelativeLayout.LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT);
        lineParms.setMargins(0,10,0,0);
        lineParms.addRule(RelativeLayout.BELOW,5);
        lineParms.addRule(RelativeLayout.CENTER_HORIZONTAL);
        lineParms.width = 2;
        buttonDivider.setBackgroundColor(0xFF808080);
        buttonDivider.setLayoutParams(lineParms);
    	
        cancelButton = new Button(context,null,android.R.style.DeviceDefault_SegmentedButton);
        cancelButton.setText(android.R.string.cancel);
        cancelButton.setWidth(270);
        cancelButton.setHeight(60);
        cancelButton.setGravity(Gravity.CENTER);
        cancelButton.setOnClickListener(new PickDialogCancelButton());
        
        buttonLayout.addView(okButton);
        buttonLayout.addView(buttonDivider);
        buttonLayout.addView(cancelButton);
        
        // Build the layout structure.
        
		layoutBackground.addView(fileNameLayout);
		layoutBackground.addView(sampleRateLayout);
		layoutBackground.addView(channelLayout);
		layoutBackground.addView(bitsLayout);
		layoutBackground.addView(recordLayout);
		layoutBackground.addView(buttonSepLayout);
		layoutBackground.addView(buttonLayout);
		
		layoutBackground.requestLayout();
		
		// Display the final layout.
		
		setContentView(layoutBackground);
	}
	
    private class SampleRateType implements OnItemSelectedListener
    {
    	public void onItemSelected(AdapterView<?> parent,View view,int pos,long id)
    	{
    		SampleCount = (0 == pos ?  8000 :
    			           1 == pos ? 11025 :
    			           2 == pos ? 16000 :
    			           3 == pos ? 22050 :
    			           4 == pos ? 44100 :
    			           SampleCount);
    	}

		@Override
		public void onNothingSelected(AdapterView<?> arg0) {}
    }
    
    private class PickChannelType implements OnItemSelectedListener
    {
    	public void onItemSelected(AdapterView<?> parent,View view,int pos,long id)
    	{
    		if ( 0 == pos )
    			ChannelCount = 2;
    		else
    			ChannelCount = 1;
    	}

    	@Override
    	public void onNothingSelected(AdapterView<?> arg0) {}
    }

    private class PickBitsType implements OnItemSelectedListener
    {
    	public void onItemSelected(AdapterView<?> parent,View view,int pos,long id)
    	{
    		if ( 0 == pos )
    			AudioBitCount = 16;
    		else
    			AudioBitCount = 8;
    	}

    	@Override
    	public void onNothingSelected(AdapterView<?> arg0) {}
    }
    
    private class PickDialogOkButton implements View.OnClickListener
    {
		@Override
		public void onClick(View v) {
			
			File ffile = new File(audioDialog.getContext().getFilesDir()+"/"+finalFileName);

			if ( null  != finalFileName   &&
				 null  != mainActivity    &&
				 ffile.exists()           &&
				 false != ffile.canRead() &&
				 0     <= ffile.length()  )
			{
				mainActivity.addFileToList(finalFileName);
				if ( null != recorder )
				{
					if ( 1 == recorder.getState() ) recorder.stop();
					recorder.release();
					recorder = null;
				}
				mainActivity.clearDialog();
				if ( null != tempFileName ) (new File(audioDialog.getContext().getFilesDir()+"/"+tempFileName)).delete();
				tempFileName = null;
				audioDialog.dismiss();
				audioDialog = null;
			}
		}
    }
    
    private class PickDialogCancelButton implements View.OnClickListener
    {
		@Override
		public void onClick(View v) {
			if ( null != audioDialog )
			{
				if ( null != recorder )
				{
					if ( 1 == recorder.getState() ) recorder.stop();
					recorder.release();
					recorder = null;
				}
				if ( null != tempFileName  )
				{
					(new File(audioDialog.getContext().getFilesDir()+"/"+tempFileName)).delete();
					tempFileName = null;
				}
				if ( null != finalFileName )
				{
					(new File(audioDialog.getContext().getFilesDir()+"/"+finalFileName)).delete();
					finalFileName = null;
				}
				audioDialog.dismiss();
				mainActivity.clearDialog();
				audioDialog = null;
			}
		}
    }
    
    // Accessor methods for external guys.
    
    public String getAudioFileName()            { return AudioFileName;   }
    public void   setAudioFileName(String name) { AudioFileName = name;   }
    public int    getChannelCount()             { return ChannelCount;    }
    public void   setChannelCount(int iCount)   { ChannelCount = iCount;  }
    public int    getBitCount()                 { return AudioBitCount;   }
    public void   setBitCount(int iCount)       { AudioBitCount = iCount; }
    public int    getSampleRate()               { return SampleCount;     }
    public void   setSampleRate(int iCount)
    {
    	boolean bMatch = false;
    	String sSize = Integer.toString(iCount);
    	for( int i=0 ; i < SampleRates.length ; ++i ) if ( SampleRates[i].equals(sSize) ) bMatch = true;
    	SampleCount = (true == bMatch ? iCount : SampleCount);
    }
    
    // Get the temporary file name
    
    private String getTempFileName()
    {
    	return Long.toString(System.currentTimeMillis());
    }
    
    // Get the save file name
    
    private String getFinalFileName()
    {
    	String fName = fileNameField.getText().toString();
     	
    	if ( 0 == fName.length() ) {
    		(Toast.makeText(audioDialog.getContext(), "File Name is Required!", Toast.LENGTH_SHORT)).show();
    		fName = null;
    	} else if ( false == fName.endsWith(".wav") ) {
    		fName += ".wav";
    	}
    	return fName;
    }
    
    // Get the recording settings
    
    private boolean getRecordingSettings()
    {
    	int pos = sampleRateSpinner.getSelectedItemPosition();

    	SampleCount = (0 == pos ?  8000 :
    		           1 == pos ? 11025 :
    		           2 == pos ? 16000 :
    		           3 == pos ? 22050 : 44100);
    	
    	pos = channelSpinner.getSelectedItemPosition();
    	if ( pos == 0 )
    		ChannelCount = AudioFormat.CHANNEL_IN_STEREO;
    	else
    		ChannelCount = AudioFormat.CHANNEL_IN_MONO;
    	
    	pos = bitsSpinner.getSelectedItemPosition();
    	if ( pos == 0 )
    		AudioBitCount = AudioFormat.ENCODING_PCM_16BIT;
    	else
    		AudioBitCount = AudioFormat.ENCODING_PCM_8BIT;
    	
    	minBufReadSize = AudioRecord.getMinBufferSize(SampleCount, ChannelCount, AudioBitCount);
    	
    	if ( AudioRecord.ERROR == minBufReadSize ) {
    		(Toast.makeText(audioDialog.getContext(), "Unable to access audio hardware!", Toast.LENGTH_SHORT)).show();
    		return false;
    	}
    	
    	if ( AudioRecord.ERROR_BAD_VALUE == minBufReadSize ) {
    		(Toast.makeText(audioDialog.getContext(),"Invalid audio settings for this hardware!",Toast.LENGTH_SHORT)).show();
    		return false;
    	}

    	return true;
    }
    
    // Start recording the new audio file
    
    private void startRecording()
    {
    	if ( null != tempFileName )
    	{
    		(new File(audioDialog.getContext().getFilesDir()+"/"+tempFileName)).delete();
    		tempFileName = null;
    	}
    	if ( null != finalFileName )
    	{
    		(new File(audioDialog.getContext().getFilesDir()+"/"+finalFileName)).delete();
    		finalFileName = null;
    	}
    	
    	tempFileName = getTempFileName();
    	if ( null == (finalFileName=getFinalFileName()) ) return;
    	
    	if ( false == getRecordingSettings() ) return;
    	
    	recorder = new AudioRecord(MediaRecorder.AudioSource.MIC,
                SampleCount,
                ChannelCount,
                AudioBitCount,
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
    	setRecButtons();
    }
    
    // Write audio to a temporary data file.
    
    private void writeAudioDataToFile()
    {
    	byte             data[] = new byte[minBufReadSize];
    	FileOutputStream os     = null;
    	
    	if ( null == recorder ) return;
    	
    	if ( null == tempFileName )
    	{
    		if ( 1 == recorder.getState() ) recorder.stop();
    		recorder.release();
    		return;
    	}
 
    	try
    	{
    		os = audioDialog.getContext().openFileOutput(tempFileName,Context.MODE_PRIVATE);
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
    				e0.printStackTrace();     // XXX: This needs to go away ... just {} will do
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
    		finalFileName = getFinalFileName();
    		if ( null != (finalFileName=getFinalFileName()) )
    		{
    			copyWaveFile(tempFileName,finalFileName);
    			(new File(audioDialog.getContext().getFilesDir()+"/"+tempFileName)).delete();
    			tempFileName = null;
    		}
    	}
    }
    
    // Stop recording when the button is pressed
    
    private void stopRecording()
    {
    	setStopRecButtons();
    	isRecording = false;
    }
    
    private void previewRecording()
    {
    	if ( null == finalFileName ||
    		false == (new File(audioDialog.getContext().getFilesDir()+"/"+finalFileName)).canRead() )
    	{
    		previewButton.setEnabled(false);
    		return;
    	}
    	
    	final String soundName = finalFileName;

    	new Thread(new Runnable()
    	{
    		public void run()
    		{

    			FileInputStream in = null;
    			FileDescriptor  df = null;

    			try
    			{
    				in = audioDialog.getContext().openFileInput(soundName);
    				df = in.getFD();
    			}
    			catch(IOException io0)
    			{
    				return;   // Fail silently.
    			}
    			
    			MediaPlayer dp = new MediaPlayer();
    			
    			// Setup the data source for the audio selection when touched.
    			
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
    
    private void copyWaveFile(String inFilename,String outFilename)
    {
    	FileInputStream  in             = null;
    	FileOutputStream out            = null;
    	long             totalAudioLen  = 0;
    	long             totalDataLen   = totalAudioLen + 36;
    	long             longSampleRate = SampleCount;
    	int              channels       = (ChannelCount  == AudioFormat.CHANNEL_IN_STEREO ? 2 :  1);
    	long             byteRate       = (AudioBitCount == AudioFormat.ENCODING_PCM_8BIT ? 8 : 16) * channels * longSampleRate / 8;
   			
//    	long byteRate                  = RECORDER_BPP * RECORDER_SAMPLERATE * channels/8;
    	
    	byte[] data = new byte[minBufReadSize];
    	
// XXX:    	Check final index of filename = .wav so this can be added to the file name list.
    	
    	try {
    		in  = audioDialog.getContext().openFileInput(tempFileName);
    		out = audioDialog.getContext().openFileOutput(finalFileName,Context.MODE_PRIVATE);
    		
    		totalAudioLen = in.getChannel().size();
    		totalDataLen  = totalAudioLen + 36;
    		
//    		AppLog.logString("File size: " + totalDataLen);
    		
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
    	header[34] = (byte)(AudioBitCount == AudioFormat.ENCODING_PCM_8BIT ? 8 : 16);
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
    
    // Button click activation methods for the recording and stop recording buttons.

    private void setRecButtons()
    {
    	recordButton.setEnabled(false);
    	stopRecButton.setEnabled(true);
    }
    
    private void setStopRecButtons()
    {
    	boolean previewState = (recorder != null ? true : false);
    	
    	recordButton.setEnabled(true);
    	stopRecButton.setEnabled(false);
    	previewButton.setEnabled(previewState);
    }
    
    // Button click methods for recording a new file
    
    private View.OnClickListener recBtnClick = new View.OnClickListener()
    {
		
		@Override
		public void onClick(View v) {
			switch( v.getId() )
			{
			case recButtonId:
				startRecording();
				break;
			case stopRecButtonId:
				stopRecording();
				break;
			case previewButtonId:
				previewRecording();
				break;
			}
		}
	};
}

