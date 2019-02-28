package com.example.dynamiclistview;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

import android.os.Environment;

public class ExternalStorage
{
	public static final String SD_CARD = "sdCard";
	public static final String EXTERNAL_SD_CARD = "externalSdCard";
	
	// return true if external storage is available. False otherwise.
	
	public static boolean isAvailable()
	{
		String state = Environment.getExternalStorageState();
		
		return (Environment.MEDIA_MOUNTED.equals(state) || Environment.MEDIA_MOUNTED_READ_ONLY.equals(state) ? true : false);
	}
	
	public static String getSdCardPath()
	{
		return Environment.getExternalStorageDirectory().getPath() + "/";
	}
	
	// Return true if the external storage is writable. False otherwise.
	
	public static boolean isWritable()
	{
		String state = Environment.getExternalStorageState();
		
		return (Environment.MEDIA_MOUNTED.equals(state) ? true : false);
	}
	
	// Return a map of all storage locations available.
	
	public static Map<String,File> getAllStorageLocations()
	{
		Map<String,File> map = new HashMap<String,File>(10);
		
		List<String> mMounts = new ArrayList<String>(10);
		List<String> mVold   = new ArrayList<String>(10);
		
		mMounts.add("/mnt/sdcard");
		mVold.add("/mnt/sdcard");
		
		try {
			File mountFile = new File("/proc/mounts");
			if ( mountFile.exists() )
			{
				Scanner scanner = new Scanner(mountFile);
				
				while( scanner.hasNext() )
				{
					String line = scanner.nextLine();
					if ( line.startsWith("/dev/block/vold") )
					{
						String[] lineElements = line.split(" ");
						String element = lineElements[1];
						
						// Don't add the default mount path. Its already in the list.
						
						if ( !element.equals("/mnt/sdcard") )
						{
							mMounts.add(element);
						}
					}
				}
				scanner.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		try {
			File voldFile = new File("/system/etc/vold.fstab");
			
			if ( voldFile.exists() )
			{
				Scanner scanner = new Scanner(voldFile);
				
				while( scanner.hasNext() )
				{
					String line = scanner.nextLine();
					
					if ( line.startsWith("dev_mount") )
					{
						String[] lineElements = line.split(" ");
						String element = lineElements[2];
						
						if ( element.contains(":") ) element = element.substring(0,element.indexOf(":"));
						if ( !element.equals("/mnt/sdcard") ) mVold.add(element);
					}
				}
				scanner.close();
			}
		} catch( Exception e ) {
			e.printStackTrace();
		}
		
		for( int i=0 ; i < mMounts.size() ; ++i )
		{
			String mount = mMounts.get(i);
			
			if ( !mVold.contains(mount) ) mMounts.remove(i--);
		}
		
		mVold.clear();
		
		List<String> mountHash = new ArrayList<String>(10);
		
		for( String mount : mMounts )
		{
			File root = new File(mount);
			
			if ( root.exists() && root.isDirectory() && root.canWrite() )
			{
				File[] list = root.listFiles();
				
				String hash = "[";
				
				if ( list != null )
				{
					for( File f : list )
					{
						hash += f.getName().hashCode()+":"+f.length()+", ";
					}
				}
				hash += "]";
				
				if ( !mountHash.contains(hash) )
				{
					String key = SD_CARD + "_" + map.size();
					
					if ( map.size() == 0 )
					{
						key = SD_CARD;
					}
					else if ( map.size() == 1 )
					{
						key = EXTERNAL_SD_CARD;
					}
					mountHash.add(hash);
					map.put(key, root);
				}
			}
		}
		mMounts.clear();
		
		if ( map.isEmpty() )
		{
			map.put(SD_CARD,Environment.getExternalStorageDirectory());
		}
		return map;
	}
}