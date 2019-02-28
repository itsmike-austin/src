package com.example.dynamiclistview;

import java.io.File;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

import android.os.Bundle;
import android.annotation.TargetApi;
import android.app.Activity;
import android.view.Menu;

public class MainActivity extends Activity {

	@SuppressWarnings("unused")
	@TargetApi(19)
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
/*		
		Map<String,File> externalLocations = ExternalStorage.getAllStorageLocations();
		
		File sdCard = externalLocations.get(ExternalStorage.SD_CARD);
		File externalSdCard = externalLocations.get(ExternalStorage.EXTERNAL_SD_CARD);
	*/	
		// String path = Environment.getExternalStorageDirectory().toString();
		String path = "/";
		File f = new File(path);
		
		if ( f != (File)null )
		{
			try {
				File file[] = f.listFiles();
				
				int p = file.length;
				
				// Get the files from the slash directory, put them into a string
				// array and sort them.

				IgnoreCaseComparator icc      = new IgnoreCaseComparator();
				ArrayList<String>    fileList = new ArrayList<String>(p);
				for( int i=0 ; i < p ; ++i ) fileList.add(file[i].getName());

				java.util.Collections.sort(fileList,icc);
				Collections.sort(fileList);
				
				for( String k : fileList )
				{
					String l = k;
					
				}

			}catch (Exception e) {
				e.printStackTrace();
			}
		}
		
		File[] extList = getExternalFilesDirs(null);
		
		int iLen = extList.length;
		int j = iLen;
	}
	
	class IgnoreCaseComparator implements Comparator<String>
	{
		public int compare(String strA,String strB)
		{
			return strA.compareToIgnoreCase(strB);
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
