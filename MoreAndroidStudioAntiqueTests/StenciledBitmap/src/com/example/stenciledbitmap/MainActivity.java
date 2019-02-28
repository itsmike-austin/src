package com.example.stenciledbitmap;

import android.os.Bundle;
import android.app.Activity;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuffXfermode;
import android.graphics.RectF;
import android.view.Menu;
import android.widget.ImageView;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		
		ImageView iv = new ImageView(this);
		
		// Create and load images (immutable, typically)
		
		Bitmap source = BitmapFactory.decodeResource(getResources(),R.drawable.welcome);
		
		// Create a "mutable" location, and a canvas to draw into it
		
		Bitmap result = Bitmap.createBitmap(source.getWidth(),source.getHeight(),Config.ARGB_8888);
		Canvas canvas = new Canvas(result);
		Paint  paint  = new Paint(Paint.ANTI_ALIAS_FLAG);
		
		// Create and draw the rounded rectangle "mask" first
		
		RectF rect = new RectF(0,0,source.getWidth(),source.getHeight());
		float radius = 25.0f;
		
		paint.setColor(Color.BLACK);
		canvas.drawRoundRect(rect,radius,radius,paint);
		
		// Switch over and paint the source using the transfer mode
		
		paint.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.SRC_IN));
		canvas.drawBitmap(source,0,0,paint);
		paint.setXfermode(null);
		
		iv.setImageBitmap(result);
		setContentView(iv);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

}
