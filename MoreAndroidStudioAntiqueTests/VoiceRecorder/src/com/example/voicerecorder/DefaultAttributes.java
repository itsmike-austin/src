package com.example.voicerecorder;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;

import android.app.Dialog;
import android.content.Context;
import android.graphics.Color;
import android.media.AudioFormat;
import android.media.MediaRecorder;
import android.os.Environment;
import android.os.Handler;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.BaseExpandableListAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ExpandableListView;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;

public class DefaultAttributes
{
	// XXX: This list should probably used to dynamically construct the
	//      lists for the ExpandableListView structures.
	
	public enum OutputFormat
	{
		RAW      (0,-100,"RAW",android.os.Build.VERSION_CODES.BASE,-1),
		WAV      (1,-200,"WAV",android.os.Build.VERSION_CODES.BASE,-1),
		AAC_ADTS (2,MediaRecorder.OutputFormat.AAC_ADTS,"AAC_ADTS",android.os.Build.VERSION_CODES.JELLY_BEAN,-1),
		AMR_NB   (3,MediaRecorder.OutputFormat.AMR_NB,"AMR_NB",android.os.Build.VERSION_CODES.BASE,-1),
		AMR_WB   (4,MediaRecorder.OutputFormat.AMR_WB,"AMR_WB",android.os.Build.VERSION_CODES.BASE,-1),
		MPEG4    (5,MediaRecorder.OutputFormat.MPEG_4,"MPEG_4",android.os.Build.VERSION_CODES.BASE,-1),
		@SuppressWarnings("deprecation")
		RAW_AMR  (6,MediaRecorder.OutputFormat.RAW_AMR,"RAW_AMR",android.os.Build.VERSION_CODES.BASE,android.os.Build.VERSION_CODES.JELLY_BEAN),
		THREE_GPP(7,MediaRecorder.OutputFormat.THREE_GPP,"THREE_GPP",android.os.Build.VERSION_CODES.BASE,-1);
		
		private int    id;
		private int    type;
		private String name;
		private int    minver;
		private int    maxver;

		private OutputFormat(int iId,int iValue,String sName,int iMin,int iMax) {
			id     = iId;
			type   = iValue;
			name   = sName;
			minver = iMin;
			maxver = iMax;
		}
		
		public int toId()   { return id;     };
		public int toInt()  { return id;     };
		public int toType() { return type;   };
		public int toMin()  { return minver; };
		public int toMax()  { return maxver; };
		
		@Override public String toString() { return name; }
	}
	
	public enum EncodingFormat
	{
		AAC    (0,"AAC",    MediaRecorder.AudioEncoder.AAC,    android.os.Build.VERSION_CODES.GINGERBREAD,-1),
		AAC_ELD(1,"AAC_ELD",MediaRecorder.AudioEncoder.AAC_ELD,android.os.Build.VERSION_CODES.JELLY_BEAN,-1),
		AMR_NB (2,"AMB_NB", MediaRecorder.AudioEncoder.AMR_NB, android.os.Build.VERSION_CODES.BASE,-1),
		AMR_WB (3,"AMR_WB", MediaRecorder.AudioEncoder.AMR_WB, android.os.Build.VERSION_CODES.GINGERBREAD,-1),
		HE_AAC (4,"HE_AAC", MediaRecorder.AudioEncoder.HE_AAC, android.os.Build.VERSION_CODES.JELLY_BEAN,-1);
		
		private int    id;
		private String name;
		private int    encodingFormat;
		private int    minVersion;
		private int    maxVersion;
		
		EncodingFormat(int iId,String sName,int iFormat,int iMin,int iMax)
		{
			id             = iId;
			name           = sName;
			encodingFormat = iFormat;
			minVersion     = iMin;
			maxVersion     = iMax;
		}
		
		public int toId()   { return id;             }
		public int toType() { return encodingFormat; }
		public int toMin()  { return minVersion;     }
		public int toMax()  { return maxVersion;     }
		
		@Override public String toString() { return name; }
	}

	public enum RawGroupList
	{
		OUTPUT_FORMAT  (0,"Output Format"   ),
		SAMPLE_RATE    (1,"Sample Rate"     ),
		CHANNEL_TYPE   (2,"Channel Type"    ),
		BITS_PER_SAMPLE(3,"Sample Bit Count");
		
		private int id;
		private String header;
		
		RawGroupList(int id,String header)
		{
			this.id = id;
			this.header = header;
		}
		
		public int toId() { return id; }
		@Override public String toString() { return header; }
	}
	
//	private String rawStringList[] = { "Output Format", "Sample Rate", "Channel Type", "Sample Bit Count" };

	private Object rawDataList[][] = {
			{ OutputFormat.RAW, OutputFormat.WAV },
			{ SampleRate.e8000, SampleRate.e11025, SampleRate.e16000, SampleRate.e22050, SampleRate.e44100 },
			{ ChannelType.STEREO, ChannelType.MONO },
			{ SampleBitCount.BITS_8, SampleBitCount.BITS_16 }
	};
	
	public enum FormattedGroupList
	{
		OUTPUT_FORMAT   (0,"Output Format"),
		ENCODING_FORMAT (1,"Encoding Format"),
		SAMPLE_RATE     (2,"Sample Rate"),
		CHANNEL_TYPE    (3,"Channel Type"),
		BITS_PER_SAMPLE (4,"Sample Bit Count");
		
		private int    id;
		private String header;
		
		FormattedGroupList(int id,String header)
		{
			this.id     = id;
			this.header = header;
		}
		
		public int toId() { return id; }
		@Override public String toString() { return header; }
	}
	
//	private String formattedStringList[] = { "Output Format", "Encoding Format", "Sample Rate", "Channel Type", "Sample Bit Count" };
	
	private Object formattedDataList[][] = {
			{ OutputFormat.AAC_ADTS, OutputFormat.AMR_NB, OutputFormat.AMR_WB, OutputFormat.MPEG4, OutputFormat.RAW_AMR, OutputFormat.THREE_GPP },
			{ EncodingFormat.AAC, EncodingFormat.AAC_ELD, EncodingFormat.AMR_NB, EncodingFormat.AMR_WB, EncodingFormat.HE_AAC },
			{ SampleRate.e8000, SampleRate.e11025, SampleRate.e16000, SampleRate.e22050, SampleRate.e44100 },
			{ ChannelType.STEREO, ChannelType.MONO },
			{ SampleBitCount.BITS_8, SampleBitCount.BITS_16 }
	};
	
	public enum SampleRate 
	{
		e8000 (0,"8000" ,8000),
		e11025(1,"11025",11025),
		e16000(2,"16000",16000),
		e22050(3,"22050",22050),
		e44100(4,"44100",44100);
		
		private int    id;
		private String name;
		private long   rate;
		
		SampleRate(int nId,String sName,long lRate)
		{
			id   = nId;
			name = sName;
			rate = lRate;
		}
		
		public int  toId()   { return id;   }
		public long toLong() { return rate; }

		@Override public String toString() { return name; }
	}
	
	public enum ChannelType
	{
		STEREO(0,"STEREO",2,AudioFormat.CHANNEL_IN_STEREO),
		MONO  (1,"MONO",1,AudioFormat.CHANNEL_IN_MONO);
		
		private int    id;
		private String name;
		private int    channelCount;
		private int    channelType;
		
		ChannelType(int nId,String sName,int iCount,int iType)
		{
			id           = nId;
			name         = sName;
			channelCount = iCount;
			channelType  = iType;
		}
		
		public int toId()   { return id;           }
		public int toInt()  { return channelCount; }
		public int toType() { return channelType;  }
		
		@Override public String toString() { return name; }
	}
	
	public enum SampleBitCount
	{
		BITS_8 (0,"8 BITS",  8,AudioFormat.ENCODING_PCM_8BIT),
		BITS_16(1,"16 BITS",16,AudioFormat.ENCODING_PCM_16BIT);

		private int    id;
		private String name;
		private int    bitCount;
		private int    bitFormat;
		
		SampleBitCount(int nId,String sName,int iCount,int iFormat)
		{
			id        = nId;
			name      = sName;
			bitCount  = iCount;
			bitFormat = iFormat;
		}
		
		public int toId()   { return id;        }
		public int toInt()  { return bitCount;  }
		public int toType() { return bitFormat; }
		
		@Override public String toString() { return name; }
	}
	
	private static final String dbFileName     = "db.dat";

	private Context context = null;
	private String  defaultDirectory;
	private String  currentDirectory;

	private static int  audioFormat   = AudioFormat.CHANNEL_IN_STEREO;
	private static int  bitsPerSample = AudioFormat.ENCODING_PCM_16BIT;
	private static long sampleRate    = 8000;
	private static int  channels      = (audioFormat   == AudioFormat.CHANNEL_IN_STEREO ? 2 :  1);
	private static long byteRate      = (bitsPerSample == AudioFormat.ENCODING_PCM_8BIT ? 8 : 16) * channels * sampleRate / 8;
	private static int  outputFormat  = MediaRecorder.OutputFormat.DEFAULT;
	private static int  audioEncoder  = MediaRecorder.AudioEncoder.DEFAULT;
	
	private static OutputFormat   outputType   = OutputFormat.WAV;
	private static EncodingFormat encodingType = EncodingFormat.AMR_NB;
	
	private String outputTypeSelectionList[];
	
	/* ********************************************************************
	 * Constructor
	 * ******************************************************************** */
	
	public DefaultAttributes(Context ctx)
	{
		context = ctx;
		defaultDirectory = context.getFilesDir().getAbsolutePath();
	}
	
	/* ********************************************************************
	 * Accessors
	 * ******************************************************************** */
	
	public int     getAudioFormat()   { return audioFormat;      }
	public int     getBitsPerSample() { return bitsPerSample;    }
	public long    getSampleRate()    { return sampleRate;       }
	public int     getChannels()      { return channels;         }
	public long    getByteRate()      { return byteRate;         }
	public Context getContext()       { return context;          }
	public String  getDefaultDir()    { return defaultDirectory; }
	public int     getOutputFormat()  { return outputFormat;     }
	public int     getAudioEncoder()  { return audioEncoder;     }

	public OutputFormat     getOutputType()     { return outputType; }
	
	public String  getAbsoluteFileName() { return defaultDirectory + "/" + String.valueOf(System.currentTimeMillis()); }
	public String  getFileName()         { return String.valueOf(System.currentTimeMillis());                          }
	
	/* ********************************************************************
	 * Value set methods
	 * ******************************************************************** */
	
	public void setAudioOutputFormatToDefault()  { audioEncoder = MediaRecorder.AudioEncoder.DEFAULT; }
	public void setAudioEncoderFormatToDefault() { outputFormat = MediaRecorder.OutputFormat.DEFAULT; }
	
	public void setAudioFormat(int aFormat) throws IllegalArgumentException
	{
		// Verify the input format value
		
		boolean bValue = (aFormat == AudioFormat.CHANNEL_IN_STEREO || aFormat == AudioFormat.CHANNEL_IN_MONO ? true : false);
		
		if ( false == bValue ) throw new IllegalArgumentException("Invalid Format");
		
		// Save the format and recalculate the byte rate
		
		audioFormat = aFormat;
		channels = (aFormat == AudioFormat.CHANNEL_IN_STEREO ? 2 : 1);
		byteRate = (bitsPerSample == AudioFormat.ENCODING_PCM_8BIT ? 8 : 16) * channels * sampleRate / 8;
	}
	
	public void setAudioFormat(ChannelType channelType) throws IllegalArgumentException
	{
		boolean bFail = true;
		
		if ( channelType.toType() == AudioFormat.CHANNEL_IN_STEREO )
		{
			audioFormat = channelType.toType();
			channels    = 2;
			byteRate    = (bitsPerSample == AudioFormat.ENCODING_PCM_8BIT ? 8 : 16) * channels * sampleRate / 8;
			bFail       = false;
		}
		else if ( channelType.toType() == AudioFormat.CHANNEL_IN_MONO )
		{
			audioFormat = channelType.toType();
			channels    = 1;
			byteRate    = (bitsPerSample == AudioFormat.ENCODING_PCM_16BIT ? 8 : 16) * channels * sampleRate / 8;
			bFail       = false;
		}
		
		if ( true == bFail ) throw new IllegalArgumentException("Invalid Audio Format");
	}
	
	public void setBitsPerSample(int bits) throws IllegalArgumentException
	{
		// Verify the bit per sample value
		
		boolean bValue = (bits == AudioFormat.ENCODING_PCM_8BIT || bits == AudioFormat.ENCODING_PCM_16BIT ? true : false);
		
		if ( false == bValue ) throw new IllegalArgumentException("Invalid Format");
		
		// Save the sample size data and recalculate the byte rate
		
		byteRate = (bitsPerSample == AudioFormat.ENCODING_PCM_8BIT ? 8 : 16) * channels * sampleRate / 8;
	}
	
	public void setBitsPerSample(SampleBitCount sampBitCount) throws IllegalArgumentException
	{
		boolean bFail = true;
		
		if ( sampBitCount.toType() == AudioFormat.ENCODING_PCM_8BIT )
		{
			bitsPerSample = sampBitCount.toType();
			byteRate      = 8 * channels * sampleRate / 8;
			bFail         = false;
		}
		else if ( sampBitCount.toType() == AudioFormat.ENCODING_PCM_16BIT )
		{
			bitsPerSample = sampBitCount.toType();
			byteRate      = 16 * channels * sampleRate / 8;
			bFail         = false;
		}
		if ( true == bFail) throw new IllegalArgumentException("Invalid Bits Per Sample");
	}
	
	public void setSampleRate(long lrate) throws IllegalArgumentException
	{
		boolean bValue = false;
		
		// Verify the byte rate.
		
		for( SampleRate k : SampleRate.values() )
		{
			if ( k.toLong() == lrate )
			{
				bValue = true;
				break;
			}
		}
		
		if ( false == bValue ) throw new IllegalArgumentException("Invalid Format");
		
		// Save the valid rate and recalculate the byteRate
		
		sampleRate = lrate;
		
		byteRate = (bitsPerSample == AudioFormat.ENCODING_PCM_8BIT ? 8 : 16) * channels * sampleRate / 8;
	}
	
	public void setDefaultDir(String dir) throws IllegalArgumentException
	{
		File dfile = null;
		if ( null == dir ) throw new IllegalArgumentException("Directory name is required.");
		
		dfile = new File(dir);
		
		if ( null == dfile || false == dfile.isDirectory() || false == dfile.mkdirs() ) throw new IllegalArgumentException("Invalid directory name: " + dir);
		
		defaultDirectory = dir;
	}
	
	@SuppressWarnings("deprecation")
	public void setAudioOutputFormat(int audioFormat) throws IllegalArgumentException
	{
		if ( android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.JELLY_BEAN )
		{
			if ( audioFormat == MediaRecorder.OutputFormat.AMR_NB   ||
				 audioFormat == MediaRecorder.OutputFormat.AMR_WB   ||
				 audioFormat == MediaRecorder.OutputFormat.MPEG_4   ||
				 audioFormat == MediaRecorder.OutputFormat.RAW_AMR  ||
				 audioFormat == MediaRecorder.OutputFormat.THREE_GPP )
			{
				outputFormat = audioFormat;
				outputType = (audioFormat == OutputFormat.AMR_NB.toType()  ? OutputFormat.AMR_NB  :
					          audioFormat == OutputFormat.AMR_WB.toType()  ? OutputFormat.AMR_WB  :
					          audioFormat == OutputFormat.MPEG4.toType()   ? OutputFormat.MPEG4   :
					          audioFormat == OutputFormat.RAW_AMR.toType() ? OutputFormat.RAW_AMR : OutputFormat.THREE_GPP);
				return;
			}
		}
		else if ( audioFormat == MediaRecorder.OutputFormat.AAC_ADTS ||
				  audioFormat == MediaRecorder.OutputFormat.AMR_NB   ||
				  audioFormat == MediaRecorder.OutputFormat.AMR_WB   ||
				  audioFormat == MediaRecorder.OutputFormat.MPEG_4   ||
				  audioFormat == MediaRecorder.OutputFormat.THREE_GPP )
		{
			outputFormat = audioFormat;
			outputType = (audioFormat == OutputFormat.AAC_ADTS.toType() ? OutputFormat.AAC_ADTS :
				          audioFormat == OutputFormat.AMR_NB.toType()   ? OutputFormat.AMR_NB   :
				          audioFormat == OutputFormat.AMR_WB.toType()   ? OutputFormat.AMR_WB   :
				          audioFormat == OutputFormat.MPEG4.toType()    ? OutputFormat.MPEG4    : OutputFormat.THREE_GPP);
			return;
		}

		throw new IllegalArgumentException("OutputFormat is invalid.");
	}
	
	public void setAudioOutputFormat(OutputFormat outFormat) throws IllegalArgumentException
	{
		for( OutputFormat f : OutputFormat.values() )
		{
			if ( f == outFormat )
			{
				try {
					setAudioOutputFormat( outFormat.toType() );
				}catch( IllegalArgumentException e) {
					throw e;
				}
			}
		}
	}
		
	public void setAudioEncoderFormat(int audioEncFormat ) throws IllegalArgumentException
	{
		if ( audioEncFormat == MediaRecorder.AudioEncoder.AAC     ||
			 audioEncFormat == MediaRecorder.AudioEncoder.AAC_ELD ||
			 audioEncFormat == MediaRecorder.AudioEncoder.AMR_NB  ||
			 audioEncFormat == MediaRecorder.AudioEncoder.AMR_WB  ||
			 audioEncFormat == MediaRecorder.AudioEncoder.HE_AAC  )
			{
				audioEncoder = audioEncFormat;
				return;
			}
		
		throw new IllegalArgumentException("Audio Encode Format is invalid.");
		
	}
	
	public void setAudioEncoderFormat(EncodingFormat encForm)
	{
		for( EncodingFormat f : EncodingFormat.values() )
		{
			if ( f == encForm )
			{
				try {
					setAudioEncoderFormat( encForm.toType() );
				}catch (IllegalArgumentException e) {
					throw e;
				}
			}
		}
	}
	
	public void setOutputType(OutputFormat theType) throws IllegalArgumentException
	{
		// XXX: This is probably wrong ... Check the encoding version
		//      (rf. setEncodingType()
		//      ... 
		
		switch( theType )
		{
		case RAW:
		case WAV:
			outputType = theType;
			outputFormat = -1;
			break;

		case RAW_AMR:
			if ( android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.ICE_CREAM_SANDWICH_MR1 )
				throw new IllegalArgumentException("Deprecated");
			
			outputType = theType;
			outputFormat = theType.toType();
			break;
			
		case AAC_ADTS:
			if ( android.os.Build.VERSION.SDK_INT < android.os.Build.VERSION_CODES.JELLY_BEAN )
				throw new IllegalArgumentException("Jelly Bean or Greater is Required");

		case AMR_NB:
		case AMR_WB:
		case MPEG4:

		case THREE_GPP:
			outputType = theType;
			outputFormat = theType.toType();
			break;
		}
	}
	
	public void setEncodingType(EncodingFormat theType) throws IllegalArgumentException
	{
		int iVersion = android.os.Build.VERSION.SDK_INT;
		
		if ( theType.toMin() >= iVersion && theType.toMax() <= iVersion ) {
			encodingType = theType;
		} else {
			throw new IllegalArgumentException("Invalid Type for this OS version.");
		}
	}
	
	/* ********************************************************************
	 * Method to save the default values.
	 * 
	 * The data is:
	 *     AudioFormat   (Either MONO or STEREO). Surround not supported
	 *     BitsPerSample (Either 8 or 16 Bits per Sample)
	 *     SampleRate    (Rf. SampleRates[] for valid rates)
	 *     
	 * ******************************************************************** */
	
	public void saveDefaults() throws IOException
	{
		FileOutputStream out = null;
		
		// You need a valid context to operate on the defaults file.
		
		if ( null == context ) throw new IOException("Invalid Context");
		
		try {
			// Determine which audio encoder to output.
			
			String sEncoderFormat = null;
			
			for( EncodingFormat e : EncodingFormat.values() )
			{
				if ( e.toType() == audioEncoder )
				{
					sEncoderFormat = e.toString();
					break;
				}
			}
			
			if ( null == sEncoderFormat ) sEncoderFormat = "DEFAULT";
			
			// Open the output file
			
			out = context.openFileOutput(dbFileName,Context.MODE_PRIVATE);

			byte[] iAudioFormat  = new byte[32];
			byte[] iBitsPerSamp  = new byte[32];
			byte[] iSampleRate   = new byte[32];
			byte[] iDefDir       = new byte[defaultDirectory.length()+1];
			byte[] iCurDir       = new byte[currentDirectory.length()+1];
			byte[] iEncodeFormat = new byte[sEncoderFormat.length()+1];
			byte[] iOutputType   = new byte[outputType.toString().length()+1];
			
			for( int i=0 ; i < 32 ; ++i )
			{
				iAudioFormat[i] = '\0';
				iBitsPerSamp[i] = '\0';
				iSampleRate[i]  = '\0'; 
			}

			// Convert the data to human readable format.
			
			String sAudioFormat   = (audioFormat   == AudioFormat.CHANNEL_IN_STEREO ? "STEREO\n" : "MONO\n");
			String sBitsPerSample = (bitsPerSample == AudioFormat.ENCODING_PCM_16BIT ? "16BIT\n"  : "8BIT\n");
			String sSampleRate    = String.valueOf(sampleRate)+"\n";
			String sOutputFormat  = outputType.toString();
			
			iDefDir[defaultDirectory.length()]     = '\n';
			iCurDir[currentDirectory.length()]     = '\n';
			iOutputType[sOutputFormat.length()]    = '\n';
			iEncodeFormat[sEncoderFormat.length()] = '\n';
			
			// Prepare the data to write it to the file.

			for( int i=0 ; i < sAudioFormat.length()     ; ++i ) iAudioFormat[i]  = (byte)sAudioFormat.charAt(i);
			for( int i=0 ; i < sBitsPerSample.length()   ; ++i ) iBitsPerSamp[i]  = (byte)sBitsPerSample.charAt(i);
			for( int i=0 ; i < sSampleRate.length()      ; ++i ) iSampleRate[i]   = (byte)sSampleRate.charAt(i);
			for( int i=0 ; i < defaultDirectory.length() ; ++i ) iDefDir[i]       = (byte)defaultDirectory.charAt(i);
			for( int i=0 ; i < currentDirectory.length() ; ++i ) iCurDir[i]       = (byte)currentDirectory.charAt(i);
			for( int i=0 ; i < sEncoderFormat.length()   ; ++i ) iEncodeFormat[i] = (byte)sEncoderFormat.charAt(i);
			for( int i=0 ; i < sOutputFormat.length()    ; ++i ) iOutputType[i]   = (byte)sOutputFormat.charAt(i);

			// Write the output data
			
			out.write(iAudioFormat);
			out.write(iBitsPerSamp);
			out.write(iSampleRate);
			out.write(iDefDir);
			out.write(iEncodeFormat);
			out.write(iOutputType);
			
			// Close the file.
			
			out.close();
			
		}catch( IOException e ) {
			throw e;
		}
	}
	
	/* ********************************************************************
	 * Method to get the default values.
	 * 
	 * The data is:
	 *     AudioFormat   (Either MONO or STEREO). Surround not supported
	 *     BitsPerSample (Either 8 or 16 Bits per Sample)
	 *     SampleRate    (Rf. SampleRates[] for valid rates)
	 *     
	 * If the file doesn't exist simply leave the static default
	 * values set by the program in place.
	 * ******************************************************************** */
	
	public void getDefaults() throws IOException
	{
		// Make sure you have a valid context for file operations
		
		if ( null == context ) throw new IOException("Invalid context");
		
		// Check to see if the file exists.
		
		File dbFile = new File(context.getFilesDir()+"/"+dbFileName);
		
		if ( null == dbFile || false == dbFile.canRead() )
		{
//			defaultDirectory = Environment.getExternalStorageDirectory().toString();
			defaultDirectory = context.getFilesDir().toString();
			currentDirectory = context.getFilesDir().toString();
			return;
		}
		
		try {
			// Allocate the read buffer, open the file and read the values
			
			byte[] ibuf = new byte[1024];
			
			FileInputStream in = context.openFileInput(dbFileName);
			
			// Read the raw audio format (either mono or stereo for raw style data input
			
			in.read(ibuf);
			audioFormat = (0 == ibuf.toString().compareTo("STEREO") ? AudioFormat.CHANNEL_IN_STEREO : AudioFormat.CHANNEL_IN_MONO);
			channels    = (AudioFormat.CHANNEL_IN_STEREO == audioFormat ? 2 : 1);
			
			// Read the raw sample bit count format (either 8 or 16 bits for raw style data input).
			
			in.read(ibuf);
			bitsPerSample = (0 == ibuf.toString().compareTo("16BIT") ? AudioFormat.ENCODING_PCM_16BIT : AudioFormat.ENCODING_PCM_8BIT);
			
			// Read the raw sample input rate
			
			in.read(ibuf);
			for( SampleRate s : SampleRate.values() )
			{
				if ( 0 == ibuf.toString().compareTo(s.toString()) )
				{
					sampleRate = s.toLong();
					break;
				}
			}
			
			// Read the default directory
			
			in.read(ibuf);
			defaultDirectory = ibuf.toString();
			
			// Read in the current directory
			
			in.read(ibuf);
			currentDirectory = ibuf.toString();
			
			// Get the audio encoder for recoding formats that require a MediaRecorder
			
			in.read(ibuf);
			audioEncoder = MediaRecorder.AudioEncoder.DEFAULT;
			for( EncodingFormat e : EncodingFormat.values() )
			{
				if ( 0 == ibuf.toString().compareTo(e.toString()) )
				{
					audioEncoder = e.toType();
					break;
				}
			}
			
			// Get the output format type.
			
			in.read(ibuf);
			outputFormat = MediaRecorder.OutputFormat.DEFAULT;
			outputType   = OutputFormat.WAV;
			for( OutputFormat o : OutputFormat.values() )
			{
				if ( 0 == ibuf.toString().compareTo(o.toString()) )
				{
					outputFormat = o.toType();
					outputType = o;
					break;
				}
			}
			
			// Defaults are now set.
			
			in.close();
			
		}catch (IOException e) {
			throw e;
		}
	}
	
	public OutputTypeSelectionDialog getOutputTypeDialog(Context ctext) { return new OutputTypeSelectionDialog(ctext); }

	public class OutputTypeSelectionDialog extends Dialog
	{
//		private String tempOutputTypeSelection = null; // XXX: Used to preset the OutputFormat
		private OutputTypeSelectionDialog thisDialog = null;
	 	
		public OutputTypeSelectionDialog(Context ctext)
		{
			super(ctext);
			
			ArrayList<String> aOutputType = new ArrayList<String>();
			
			int iApiVersion = android.os.Build.VERSION.SDK_INT;
			
			for( OutputFormat o : OutputFormat.values() )
			{
				if ( o.minver <= iApiVersion && o.maxver <= iApiVersion ) aOutputType.add(o.toString());
			}
			
			outputTypeSelectionList = new String[aOutputType.size()];
			for( int i=0 ; i < aOutputType.size() ; ++i ) outputTypeSelectionList[i] = aOutputType.get(i);
			
			LayoutInflater inflater = this.getLayoutInflater();
			inflater.inflate(R.layout.output_type_selection_dialog, null);
			
			setContentView(R.layout.output_type_selection_dialog);
			thisDialog = this;
			setTitle(R.string.output_type_selection_dialog_label_string);

			ListView lv = (ListView)findViewById(R.id.output_type_selection_dialog_spinner);
			ArrayAdapter<String> adapter = new ArrayAdapter<String>(context, android.R.layout.simple_list_item_1, outputTypeSelectionList);
			lv.setAdapter(adapter);
			lv.setBackgroundResource(R.drawable.blue_gradient);
			lv.setOnItemClickListener(new OutputTypeSelectionListener());
			
			Button cnButton = (Button)findViewById(R.id.output_type_selection_dialog_cancel_button);
			
			cnButton.setOnClickListener(new Button.OnClickListener() {
				@Override public void onClick(View v) { thisDialog.dismiss(); }
			});
		}
		
		private class OutputTypeSelectionListener implements AdapterView.OnItemClickListener
		{
			@Override
			public void onItemClick(AdapterView<?> parent, View v, int position, long id) {
				
				if ( position < OutputFormat.values().length )
				{
					String rqstFormat = outputTypeSelectionList[position];
					
					for( OutputFormat o : OutputFormat.values() )
					{
						if ( 0 == o.toString().compareTo(rqstFormat) )
						{
							int iType = o.toType();
							if ( -100 == iType || -200 == iType ) {
//								tempOutputTypeSelection = o.toString();
								RawOutputAttributesDlg rd = getRawOutputAttributesDlg(context);
								rd.setTitle(R.string.raw_output_attributes_dialog_label_string);
								rd.show();
							}else{
//								tempOutputTypeSelection = o.toString();
								FormattedOutputAttributesDlg fd = getFormattedOutputAttributesDlg(context);
								fd.setTitle(R.string.form_output_attributes_dialog_label_string);
								fd.show();
							}
						}
					}
				}
			}	
		}
	}
	
	public FormattedOutputAttributesDlg getFormattedOutputAttributesDlg(Context ctxt) { return new FormattedOutputAttributesDlg(ctxt); }
	
	private class FormattedOutputAttributesDlg extends Dialog
	{
		private ArrayList<View> groupWidgetList = null;
		private ArrayList<View> childWidgetList = null;

		private RelativeLayout childView;
		
		private int     iFlashCount;
		private Handler timerHandler = new Handler();
		
		private FormattedOutputAttributesDlg formattedAttributesDlg;
		
		public FormattedOutputAttributesDlg(Context ctxt)
		{
			super(ctxt);
			LayoutInflater dialogLayoutInflater = this.getLayoutInflater();
			dialogLayoutInflater.inflate(R.layout.formatted_output_attributes_dlg, null);
			setContentView(R.layout.formatted_output_attributes_dlg);
			
			formattedAttributesDlg = this;
			
			ExpandableListView ev = (ExpandableListView)findViewById(R.id.formatted_output_attributes_dlg_list);
			ev.setAdapter(new ExpandableListAdapter(ctxt));
			ev.setOnChildClickListener(new FormattedOutputAttributesListener());
			
			Button okButton = (Button)findViewById(R.id.formatted_output_attributes_dlg_ok_button);
			Button cnButton = (Button)findViewById(R.id.formatted_output_attributes_dlg_cancel_button);
			
			okButton.setOnClickListener(new Button.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						saveDefaults();
					}catch ( IOException e ) {
						(Toast.makeText(context, e.getLocalizedMessage(), Toast.LENGTH_LONG)).show();
					}finally{
						formattedAttributesDlg.dismiss();
					}					
				}
			});
			
			cnButton.setOnClickListener(new Button.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						getDefaults();
					} catch( IOException e) {
						(Toast.makeText(context, e.getLocalizedMessage(), Toast.LENGTH_LONG)).show();
					}finally{
						formattedAttributesDlg.dismiss();
					}
				}
			});			
		}
		
		Runnable timerRunnable = new Runnable() {
			@Override
			public void run() {
				if ( 0 == iFlashCount ) {
					childView.setBackgroundColor(Color.DKGRAY);
					++iFlashCount;
					timerHandler.postDelayed(this, 50);
				}else if ( 1 == iFlashCount ) {
					childView.setBackgroundColor(Color.WHITE);
					++iFlashCount;
					timerHandler.postDelayed(this, 50);
				}else if ( 2 == iFlashCount ) {
					childView.setBackgroundColor(Color.DKGRAY);
					++iFlashCount;
					timerHandler.postDelayed(this, 50);
				}else if ( 3 == iFlashCount ) {
					childView.setBackgroundColor(Color.LTGRAY);
					timerHandler.removeCallbacks(timerRunnable,0);
					iFlashCount       = 0;
				}
				childView.invalidate();
			}
		};
		
		private class FormattedOutputAttributesListener implements ExpandableListView.OnChildClickListener
		{
			@Override
			public boolean onChildClick(ExpandableListView parent, View v, int groupPosition, int childPosition, long id) {
				boolean bRc = false;
				switch( groupPosition )
				{
				case 0:
					// OutputFormat
					
					iFlashCount    = 0;
					
					childView      = (RelativeLayout)v;
					
					childView.setBackgroundColor(Color.DKGRAY);
					childView.invalidate();
					
					setOutputType((childPosition == 0 ? OutputFormat.AAC_ADTS :
							       childPosition == 1 ? OutputFormat.AMR_NB   :
							       childPosition == 2 ? OutputFormat.AMR_WB   :
							       childPosition == 3 ? OutputFormat.MPEG4    :
							       childPosition == 4 ? OutputFormat.RAW_AMR  : OutputFormat.THREE_GPP));

					((TextView)((RelativeLayout)groupWidgetList.get(groupPosition))
							.getChildAt(0))
							.setText(RawGroupList.OUTPUT_FORMAT.toString() + ": " + outputType.toString());
					
					timerHandler.postDelayed(timerRunnable,0);
					
					bRc = true;
					break;
					
				case 1:
					// Encoding Format
					
					iFlashCount = 0;
					
					childView = (RelativeLayout)v;
					
					childView.setBackgroundColor(Color.DKGRAY);
					childView.invalidate();
					
					setEncodingType((childPosition == 0 ? EncodingFormat.AAC    :
									 childPosition == 1 ? EncodingFormat.AMR_NB :
									 childPosition == 2 ? EncodingFormat.AMR_WB : EncodingFormat.HE_AAC));

					
				case 2:
					// Sample Rate

					iFlashCount    = 0;
					
					childView      = (RelativeLayout)v;

					childView.setBackgroundColor(Color.DKGRAY);
					childView.invalidate();

					if ( 0 == childPosition )
						setSampleRate(SampleRate.e8000.toLong());
					else if ( 1 == childPosition )
						setSampleRate(SampleRate.e11025.toLong());
					else if ( 2 == childPosition )
						setSampleRate(SampleRate.e16000.toLong());
					else if ( 3 == childPosition )
						setSampleRate(SampleRate.e22050.toLong());
					else
						setSampleRate(SampleRate.e44100.toLong());
					bRc = true;

					((TextView)((RelativeLayout)groupWidgetList.get(groupPosition))
							.getChildAt(0))
							.setText(RawGroupList.OUTPUT_FORMAT.toString() + ": " + Long.toString(sampleRate));
					
					timerHandler.postDelayed(timerRunnable,0);
					
					break;
					
				case 3:
					// Channel Type

					iFlashCount    = 0;
					
					childView      = (RelativeLayout)v;
					
					childView.setBackgroundColor(Color.DKGRAY);
					childView.invalidate();
					
					setAudioFormat((0 == childPosition ? ChannelType.STEREO.toType() : ChannelType.MONO.toType()));

					((TextView)((RelativeLayout)groupWidgetList.get(groupPosition))
							.getChildAt(0))
							.setText(RawGroupList.CHANNEL_TYPE.toString() + ": " + 
							          (0 == childPosition ? ChannelType.STEREO.toString() : ChannelType.MONO.toString()));
					
					timerHandler.postDelayed(timerRunnable,0);
					
					bRc = true;
					break;
					
				case 4:
					// Sample Bit Count
					
					iFlashCount    = 0;
					
					childView      = (RelativeLayout)v;

					childView.setBackgroundColor(Color.DKGRAY);
					childView.invalidate();

					setBitsPerSample((0 == childPosition ? SampleBitCount.BITS_8.toType() : SampleBitCount.BITS_16.toType()));

					((TextView)((RelativeLayout)groupWidgetList.get(groupPosition))
							.getChildAt(0))
							.setText(RawGroupList.BITS_PER_SAMPLE.toString() + ": " + 
							    (0 == childPosition ? SampleBitCount.BITS_8.toString() : SampleBitCount.BITS_16.toString()));
					
					timerHandler.postDelayed(timerRunnable,0);
					
					bRc = true;
					break;
				}
				return bRc;
			}
		}
		
	    private class ExpandableListAdapter extends BaseExpandableListAdapter
	    {
	    	private Context myContext;

	    	public ExpandableListAdapter(Context context) {
	    	    myContext = context;
	    	}

	    	@Override
	    	public View getGroupView(int groupPosition, boolean isExpanded, View convertView, ViewGroup parent)
	    	{
	    	    if (convertView == null)
	    	    {
	    	    	LayoutInflater inflater = (LayoutInflater) myContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
	    	    	convertView = inflater.inflate(R.layout.raw_output_attributes_list, null);
	    	    }
	    	    
	    	    // Check to make sure that this doesn't leak!
	    	    
		    	if ( 0 == groupPosition ) groupWidgetList = new ArrayList<View>();
		    	groupWidgetList.add(convertView);

		    	TextView groupName = (TextView)convertView.findViewById(R.id.raw_output_attributes_list_text_view);
		    	groupName.setTextColor(Color.LTGRAY);
		    	
		    	for( FormattedGroupList f : FormattedGroupList.values() )
		    	{
		    		if ( groupPosition == f.toId() )
		    		{
		    			if ( f.equals(FormattedGroupList.OUTPUT_FORMAT) ) {
		    				groupName.setText(f.toString() + ": " + outputType.toString());
		    			}else if ( f.equals(FormattedGroupList.ENCODING_FORMAT) ) {
		    				groupName.setText(f.toString() + ": " + encodingType.toString());
		    			}else if ( f.equals(FormattedGroupList.SAMPLE_RATE) ) {
		    				groupName.setText(f.toString() + ": " + Long.toString(sampleRate));
		    			}else if ( f.equals(FormattedGroupList.CHANNEL_TYPE) ) {
	    	    			groupName.setText(f.toString() + ": " + (audioFormat == ChannelType.STEREO.toType() ? ChannelType.STEREO.toString() : ChannelType.MONO.toString()));    	    			
	    	    		}else if ( f.equals(RawGroupList.BITS_PER_SAMPLE) ) {
	    	    			groupName.setText(f.toString() + ": " + (bitsPerSample == SampleBitCount.BITS_16.toType() ? SampleBitCount.BITS_16.toString() : SampleBitCount.BITS_8.toString()));
	    	    		}
		    		}
		    	}
	    	    return convertView;
	    	}

	    	@Override
	    	public View getChildView(int groupPosition, int childPosition, boolean isLastChild, View convertView, ViewGroup parent)
	    	{
	    	    if (convertView == null) {
	    	    	LayoutInflater inflater = (LayoutInflater) myContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
	    	    	convertView = inflater.inflate(R.layout.raw_output_attributes_item,null);
	    	    }
	    	    
	    	    if ( 0 == childPosition ) childWidgetList = new ArrayList<View>();
	    	    
	    	    childWidgetList.add(convertView);

	    	    TextView yourSelection = (TextView)convertView.findViewById(R.id.raw_output_attributes_item_text_view);
	    	    String text = (formattedDataList[groupPosition][childPosition]).toString();
	    	    yourSelection.setText(text);
	    	    
	    	    //yourSelection.setText((rawDataList[groupPosition][childPosition]).toString());

	    	    return convertView;
	    	}

	    	@Override
	    	public Object getChild(int groupPosition, int childPosition) {
	    	    return null;
	    	}

	    	@Override
	    	public long getChildId(int groupPosition, int childPosition) {
	    	    return 0;
	    	}

	    	@Override
	    	public int getChildrenCount(int groupPosition) {
	    		return formattedDataList[groupPosition].length;
	    	}

	    	@Override
	    	public Object getGroup(int groupPosition) {
	    	    return null;
	    	}

	    	@Override
	    	public int getGroupCount() {
	    		return FormattedGroupList.values().length;
	    	}

	    	@Override
	    	public long getGroupId(int groupPosition) {
	    	    return 0;
	    	}

	    	@Override
	    	public boolean hasStableIds() {
	    	    return false;
	    	}

	    	@Override
	    	public boolean isChildSelectable(int groupPosition, int childPosition) {
	    	    return true;
	    	}
	    }
	}
	
	public RawOutputAttributesDlg getRawOutputAttributesDlg(Context context) { return new RawOutputAttributesDlg(context); }
	
	private class RawOutputAttributesDlg extends Dialog
	{
		private ArrayList<View> groupWidgetList = null;
		private ArrayList<View> childWidgetList = null;
		private RelativeLayout childView;

		private int     iFlashCount;
		private Handler timerHandler  = new Handler();
		
		private RawOutputAttributesDlg rawAttributesDlg;
		
		public RawOutputAttributesDlg(Context ctxt) {
			super(ctxt);
			LayoutInflater dialogLayoutInflater = this.getLayoutInflater();
			dialogLayoutInflater.inflate(R.layout.raw_output_attributes_dlg, null);
			setContentView(R.layout.raw_output_attributes_dlg);
			
			rawAttributesDlg = this;
			
			ExpandableListView ev = (ExpandableListView)findViewById(R.id.raw_output_attributes_dlg_list);
			ev.setAdapter(new ExpandableListAdapter(ctxt));
			ev.setOnChildClickListener(new RawOutputAttributesListener());
			
			Button okButton = (Button)findViewById(R.id.raw_output_attributes_dlg_ok_button);
			Button cnButton = (Button)findViewById(R.id.raw_output_attributes_dlg_cancel_button);
			
			okButton.setOnClickListener(new Button.OnClickListener() {
				@Override
				public void onClick(View arg0) {
					try {
						saveDefaults();
					}catch ( IOException e ) {
						(Toast.makeText(context, e.getLocalizedMessage(), Toast.LENGTH_LONG)).show();
					}finally{
						rawAttributesDlg.dismiss();
					}
				}
			});
			
			cnButton.setOnClickListener(new Button.OnClickListener() {
				@Override
				public void onClick(View v) {
					try {
						getDefaults();
					} catch( IOException e) {
						(Toast.makeText(context, e.getLocalizedMessage(), Toast.LENGTH_LONG)).show();
					}finally{
						rawAttributesDlg.dismiss();
					}
				}
			});
		}
		
		Runnable timerRunnable = new Runnable() {
			@Override
			public void run() {
				if ( 0 == iFlashCount ) {
					childView.setBackgroundColor(Color.DKGRAY);
					++iFlashCount;
					timerHandler.postDelayed(this, 50);
				}else if ( 1 == iFlashCount ) {
					childView.setBackgroundColor(Color.WHITE);
					++iFlashCount;
					timerHandler.postDelayed(this, 50);
				}else if ( 2 == iFlashCount ) {
					childView.setBackgroundColor(Color.DKGRAY);
					++iFlashCount;
					timerHandler.postDelayed(this, 50);
				}else if ( 3 == iFlashCount ) {
					childView.setBackgroundColor(Color.LTGRAY);
					timerHandler.removeCallbacks(timerRunnable,0);
					iFlashCount       = 0;
				}
				childView.invalidate();
			}
		};
		
		private class RawOutputAttributesListener implements ExpandableListView.OnChildClickListener
		{
			@Override
			public boolean onChildClick(ExpandableListView parent, View v, int groupPosition, int childPosition, long id) {
				boolean bRc = false;
				switch( groupPosition )
				{
				case 0:
					// OutputFormat (WAV or RAW)
					
					iFlashCount    = 0;
					
					childView      = (RelativeLayout)v;
					
					childView.setBackgroundColor(Color.DKGRAY);
					childView.invalidate();
					
					setOutputType((childPosition == 0 ? OutputFormat.RAW : OutputFormat.WAV));

					((TextView)((RelativeLayout)groupWidgetList.get(groupPosition))
							.getChildAt(0))
							.setText(RawGroupList.OUTPUT_FORMAT.toString() + ": " + outputType.toString());
					
					timerHandler.postDelayed(timerRunnable,0);
					
					bRc = true;
					break;
					
				case 1:
					// Sample Rate

					iFlashCount    = 0;
					
					childView      = (RelativeLayout)v;

					childView.setBackgroundColor(Color.DKGRAY);
					childView.invalidate();

					if ( 0 == childPosition )
						setSampleRate(SampleRate.e8000.toLong());
					else if ( 1 == childPosition )
						setSampleRate(SampleRate.e11025.toLong());
					else if ( 2 == childPosition )
						setSampleRate(SampleRate.e16000.toLong());
					else if ( 3 == childPosition )
						setSampleRate(SampleRate.e22050.toLong());
					else
						setSampleRate(SampleRate.e44100.toLong());
					bRc = true;

					((TextView)((RelativeLayout)groupWidgetList.get(groupPosition))
							.getChildAt(0))
							.setText(RawGroupList.OUTPUT_FORMAT.toString() + ": " + Long.toString(sampleRate));
					
					timerHandler.postDelayed(timerRunnable,0);
					
					break;
					
				case 2:
					// Channel Type

					iFlashCount    = 0;
					
					childView      = (RelativeLayout)v;
					
					childView.setBackgroundColor(Color.DKGRAY);
					childView.invalidate();
					
					setAudioFormat((0 == childPosition ? ChannelType.STEREO.toType() : ChannelType.MONO.toType()));

					((TextView)((RelativeLayout)groupWidgetList.get(groupPosition))
							.getChildAt(0))
							.setText(RawGroupList.CHANNEL_TYPE.toString() + ": " + 
							          (0 == childPosition ? ChannelType.STEREO.toString() : ChannelType.MONO.toString()));
					
					timerHandler.postDelayed(timerRunnable,0);
					
					bRc = true;
					break;
					
				case 3:
					// Sample Bit Count
					
					iFlashCount    = 0;
					
					childView      = (RelativeLayout)v;

					childView.setBackgroundColor(Color.DKGRAY);
					childView.invalidate();

					setBitsPerSample((0 == childPosition ? SampleBitCount.BITS_8.toType() : SampleBitCount.BITS_16.toType()));

					((TextView)((RelativeLayout)groupWidgetList.get(groupPosition))
							.getChildAt(0))
							.setText(RawGroupList.BITS_PER_SAMPLE.toString() + ": " + 
							    (0 == childPosition ? SampleBitCount.BITS_8.toString() : SampleBitCount.BITS_16.toString()));
					
					timerHandler.postDelayed(timerRunnable,0);
					
					bRc = true;
					break;
				}
				return bRc;
			}
		}
		
	    private class ExpandableListAdapter extends BaseExpandableListAdapter
	    {
	    	private Context myContext;

	    	public ExpandableListAdapter(Context context) {
	    	    myContext = context;
	    	}

	    	@Override
	    	public View getGroupView(int groupPosition, boolean isExpanded, View convertView, ViewGroup parent)
	    	{
	    	    if (convertView == null)
	    	    {
	    	    	LayoutInflater inflater = (LayoutInflater) myContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
	    	    	convertView = inflater.inflate(R.layout.raw_output_attributes_list, null);
	    	    }
	    	    
	    	    // Check to make sure that this doesn't leak!
	    	    
		    	if ( 0 == groupPosition ) groupWidgetList = new ArrayList<View>();
		    	groupWidgetList.add(convertView);

		    	TextView groupName = (TextView)convertView.findViewById(R.id.raw_output_attributes_list_text_view);
		    	groupName.setTextColor(Color.LTGRAY);
	    	    for( RawGroupList r : RawGroupList.values() )
	    	    {
	    	    	if ( groupPosition == r.toId() )
	    	    	{
	    	    		if ( r.equals(RawGroupList.OUTPUT_FORMAT) ) {
	    	    			groupName.setText(r.toString() + ": " + outputType.toString());
	    	    		}else if ( r.equals(RawGroupList.SAMPLE_RATE) ) {
	    	    			groupName.setText(r.toString() + ": " + Long.toString(sampleRate));
	    	    		}else if ( r.equals(RawGroupList.CHANNEL_TYPE) ) {
	    	    			groupName.setText(r.toString() + ": " + (audioFormat == ChannelType.STEREO.toType() ? ChannelType.STEREO.toString() : ChannelType.MONO.toString()));    	    			
	    	    		}else if ( r.equals(RawGroupList.BITS_PER_SAMPLE) ) {
	    	    			groupName.setText(r.toString() + ": " + (bitsPerSample == SampleBitCount.BITS_16.toType() ? SampleBitCount.BITS_16.toString() : SampleBitCount.BITS_8.toString()));
	    	    		}
	    	    	}
	    	    }
	    	    return convertView;
	    	}

	    	@Override
	    	public View getChildView(int groupPosition, int childPosition, boolean isLastChild, View convertView, ViewGroup parent)
	    	{
	    	    if (convertView == null) {
	    	    	LayoutInflater inflater = (LayoutInflater) myContext.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
	    	    	convertView = inflater.inflate(R.layout.raw_output_attributes_item,null);
	    	    }
	    	    
	    	    if ( 0 == childPosition ) childWidgetList = new ArrayList<View>();
	    	    
	    	    childWidgetList.add(convertView);

	    	    TextView yourSelection = (TextView)convertView.findViewById(R.id.raw_output_attributes_item_text_view);
	    	    String text = (rawDataList[groupPosition][childPosition]).toString();
	    	    yourSelection.setText(text);
	    	    
	    	    //yourSelection.setText((rawDataList[groupPosition][childPosition]).toString());

	    	    return convertView;
	    	}

	    	@Override
	    	public Object getChild(int groupPosition, int childPosition) {
	    	    return null;
	    	}

	    	@Override
	    	public long getChildId(int groupPosition, int childPosition) {
	    	    return 0;
	    	}

	    	@Override
	    	public int getChildrenCount(int groupPosition) {
	    		return rawDataList[groupPosition].length;
	    	}

	    	@Override
	    	public Object getGroup(int groupPosition) {
	    	    return null;
	    	}

	    	@Override
	    	public int getGroupCount() {
	    		return RawGroupList.values().length;
//	    		return rawStringList.length;
	    	}

	    	@Override
	    	public long getGroupId(int groupPosition) {
	    	    return 0;
	    	}

	    	@Override
	    	public boolean hasStableIds() {
	    	    return false;
	    	}

	    	@Override
	    	public boolean isChildSelectable(int groupPosition, int childPosition) {
	    	    return true;
	    	}
	    }
	}
	
	public DefaultDirectoryDialog getDefaultDirectoryDialog(Context ctext) { return new DefaultDirectoryDialog(ctext); }
	
	public class DefaultDirectoryDialog extends Dialog
	{
		private DefaultDirectoryDialog thisDialog;
		private ListView               thisDirList;
		private TextView               topDirName;
		private TextView               curDirName;
		
		private String[]               directList;
		
		public DefaultDirectoryDialog(Context ctext)
		{
			super(ctext);

			LayoutInflater dialogLayoutInflater = this.getLayoutInflater();
			dialogLayoutInflater.inflate(R.layout.default_file_dialog_layout,null);
			setContentView(R.layout.default_file_dialog_layout);
			
			thisDialog = this;
			setTitle(R.string.default_directory_title_label);
			
			topDirName = (TextView)findViewById(R.id.default_directory_top_level_dir);
			curDirName = (TextView)findViewById(R.id.default_directory_current_dir);

			String sDefDir = (0 == defaultDirectory.compareTo(ctext.getFilesDir().toString())                       ? ctext.getString(R.string.default_directory_label)  :
				              0 == defaultDirectory.compareTo(Environment.getExternalStorageDirectory().toString()) ? ctext.getString(R.string.external_directory_label) :
				              defaultDirectory);
			
			String sCurDir = (0 == currentDirectory.compareTo(ctext.getFilesDir().toString())                       ? ctext.getString(R.string.default_directory_label)  :
	                          0 == currentDirectory.compareTo(Environment.getExternalStorageDirectory().toString()) ? ctext.getString(R.string.external_directory_label) :
	                          currentDirectory);

			topDirName.setText(sDefDir);
			curDirName.setText(sCurDir);

			File file = new File(defaultDirectory);
			
			String tempList[] = file.list();
			directList = null;
			
			if ( 0 < tempList.length )
			{
				ArrayList<String> dirListTemp = new ArrayList<String>();
			
				for( int i=0 ; i < tempList.length ; ++i )
				{
					File tfile = new File(tempList[i]);
					if ( true == tfile.isDirectory() && true == tfile.canWrite() ) dirListTemp.add(tempList[i]);
				}
			
				if ( 0 != defaultDirectory.compareTo(currentDirectory) ) dirListTemp.add("..");
			
				if ( 0 < dirListTemp.size() )
				{
					directList = new String[dirListTemp.size()];
					for( int i=0 ; i < dirListTemp.size(); ++i ) directList[i] = dirListTemp.get(i);
				}
				
				String emptyStringSet[] = { "Empty" };

				thisDirList = (ListView)findViewById(R.id.default_directory_list_view);
				CustomDirList adapter = new CustomDirList(ctext,(null != directList ? directList : emptyStringSet));
				thisDirList.setAdapter(adapter);
				thisDirList.setOnItemClickListener(new DirectorySelectionListener());
			
				Button okButton = (Button)findViewById(R.id.default_directory_dlg_ok_button);
				Button cnButton = (Button)findViewById(R.id.default_directory_dlg_cancel_button);
				Button nwButton = (Button)findViewById(R.id.default_directory_dlg_newdir_button);
			
				okButton.setOnClickListener(new Button.OnClickListener() {
					@Override public void onClick(View v) { thisDialog.dismiss(); }
				});
			
				cnButton.setOnClickListener(new Button.OnClickListener() {
					@Override public void onClick(View v) { thisDialog.dismiss(); }
				});
				
				nwButton.setOnClickListener(new Button.OnClickListener() {
					@Override public void onClick(View v)
					{
						// XXX: An update directory method with dismiss for this dialog should
						//      be completed
						NewDirectoryDialog dlg = new NewDirectoryDialog(thisDialog.getContext(),thisDialog);
						dlg.show();
//						thisDialog.dismiss();
					}
				});
			}
		}
		
		private class CustomDirList extends ArrayAdapter<String>
		{
			public CustomDirList(Context ctext,String[] dirList)
			{
				super(ctext,R.layout.default_directory_list_item,dirList);
			}
			
			@Override
			public View getView(int position, View view, ViewGroup parent)
			{
				LayoutInflater dlgInflater = thisDialog.getLayoutInflater();
				
				View rowView = dlgInflater.inflate(R.layout.default_directory_list_item, null, true);
				
				ImageView      imgView  = (ImageView)rowView.findViewById(R.id.default_directory_dir_image);
				TextView       dirName  = (TextView)rowView.findViewById(R.id.default_directory_dir_name);
				
				if ( null != directList )
				{
					if ( 0 == position && 0 == directList[position].compareTo("..") ) {
						imgView.setImageResource(R.drawable.return_arrow);
					}else{
						imgView.setImageResource(R.drawable.folder);
					}
					
					dirName.setText(directList[position]);
					rowView.setBackgroundResource(R.drawable.blue_gradient);
				}
				else
				{
					dirName.setGravity(Gravity.CENTER_VERTICAL);
					dirName.setText("Empty Directory");
					rowView.setBackgroundResource(R.drawable.red_gradient);
				}
				
				return rowView;
			}
		}
		
		private class DirectorySelectionListener implements ListView.OnItemClickListener
		{
			@Override
			public void onItemClick(AdapterView<?> parent, View v, int position, long itemId)
			{
				if ( null == directList ) {
					(Toast.makeText(thisDialog.getContext(), thisDialog.getContext().getString(R.string.exception_no_subdirectory), Toast.LENGTH_SHORT)).show();
				} else {
					
					File file = new File(directList[position]);
					
					if ( file.isDirectory() && file.canWrite() )
					{
						String curDirName = directList[position];
						
						String baseDirList[] = file.list();
						ArrayList<String> dirList = new ArrayList<String>();
						
						for( int i=0 ; i < baseDirList.length ; ++i )
						{
							File testFile = new File(baseDirList[i]);
							if ( testFile.isDirectory() && testFile.canWrite() ) dirList.add(baseDirList[i]);
							
						}
						
						if ( 0 < dirList.size() ) {
							directList = new String[dirList.size()];
							for( int i=0 ; i < dirList.size() ; ++i ) directList[i] = dirList.get(i);
							currentDirectory = curDirName;
							thisDirList.invalidateViews();
						} else {
							(Toast.makeText(thisDialog.getContext(), thisDialog.getContext().getString(R.string.exception_file_access), Toast.LENGTH_SHORT)).show();
						}
					}
				}
			}
		}
	}
	
	public class NewDirectoryDialog extends Dialog
	{
		private Dialog             theCallingDlg; // The dialog that instanced this NewDirectoryDialog
		private NewDirectoryDialog thisDialog;    // This dialog
		private TextView           thisCurDir;    // The value of currentDirectory
		private EditText           thisNewDir;    // The new directory text field
		
		public NewDirectoryDialog(Context ctext,Dialog callingDialog)
		{
			// Initialize the dialog
			
			super(ctext);
			
			theCallingDlg = callingDialog;

			LayoutInflater dialogLayoutInflater = this.getLayoutInflater();
			dialogLayoutInflater.inflate(R.layout.new_directory_dialog,null);
			setContentView(R.layout.new_directory_dialog);
			
			thisDialog = this;
			setTitle(R.string.default_directory_title_label);
			
			// Get the current directory text field and new directory edit text

			thisCurDir = (TextView)findViewById(R.id.new_directory_current_dir);
			thisNewDir = (EditText)findViewById(R.id.new_directory_new_dir);
			
			// Finish initializing the dialog.
			
			thisCurDir.setText(currentDirectory);
			thisNewDir.setText("");
			
			Button okButton = (Button)findViewById(R.id.new_directory_dlg_ok_button);
			Button cnButton = (Button)findViewById(R.id.new_directory_dlg_cancel_button);
			
			okButton.setOnClickListener(new Button.OnClickListener() {
				@Override public void onClick(View v)
				{
					boolean bClearDialog = true;                      // Flag to dismiss this and calling dialog
					String theDir = thisNewDir.getText().toString();  // Get the requested new directory
					
					if ( 0 < theDir.length() ) {
						theDir = currentDirectory + "/" + theDir;    // Build the fully qualified dir name.
						File newFile = new File(theDir);
						if ( false == newFile.mkdirs() ) {           // Create the directory tree
							String errMsg = thisDialog.getContext().getString(R.string.exception_create_dir_failed) + theDir;
							(Toast.makeText(thisDialog.getContext(), errMsg, Toast.LENGTH_LONG)).show();
							bClearDialog = false;
						}else{
							// Save the default directory and save the changed value to the defaults file.
							try {
								setDefaultDir(theDir);
								saveDefaults();
							}catch( IOException e ) {
								(Toast.makeText(thisDialog.getContext(),e.getLocalizedMessage(),Toast.LENGTH_LONG)).show();
							}
						}
					}
					
					// Dismiss the dialog list if everything worked well.
					
					if ( true == bClearDialog )
					{
						thisDialog.dismiss();
						theCallingDlg.dismiss();
					}
				}
			});
			
			// The cancel button simply dismisses thisDialog.
			
			cnButton.setOnClickListener(new Button.OnClickListener() {
				@Override public void onClick(View v) { thisDialog.dismiss(); }
			});
		}
	}
}