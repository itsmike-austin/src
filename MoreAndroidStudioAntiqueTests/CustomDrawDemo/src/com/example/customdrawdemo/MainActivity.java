package com.example.customdrawdemo;

import android.support.v7.app.ActionBarActivity;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout.LayoutParams;

public class MainActivity extends ActionBarActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		LinearLayout container = (LinearLayout)findViewById(R.id.container);
		
		final BasicView view = new BasicView(this);
		
		view.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,LinearLayout.LayoutParams.MATCH_PARENT));
		
		container.addView(view);
		
		Button button = (Button)findViewById(R.id.button1);
		button.setOnClickListener(new OnClickListener() {
			public void onClick(View v) {
				view.increment();
				try {
					Thread.sleep(250);
				}catch(InterruptedException e){}
				
//				view.increment();
			}
		});
		
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	private class BasicView extends View {
		private Paint mLinePaint;
		private Paint mTextPaint;
		
		private int   mCount;
		
		public BasicView(Context context) {
			super(context);
			
			mLinePaint = new Paint();
			mLinePaint.setStyle(Paint.Style.STROKE);
			mLinePaint.setARGB(200, 0, 255, 0);
			mLinePaint.setAntiAlias(true);
			mLinePaint.setStrokeWidth(10);
			
			mTextPaint = new Paint();
			mTextPaint.setTextSize(50);
			mTextPaint.setColor(Color.RED);
		}
		
		public void onDraw(Canvas canvas) {
			int width  = getWidth();
			int height = getHeight();
			
			canvas.drawLine(0,0,width-1,height-1,mLinePaint);
			canvas.drawRect(0, 0,width-1,height-1,mLinePaint);
			canvas.drawText("Count:" + mCount,30,height*0.25f,mTextPaint);
		}
		
		public void increment() {
			mCount++;
			invalidate();
		}
		
		public int getCount() {
			return mCount;
		}
		
		public void setCount(int count) {
			mCount = count;
			invalidate();
		}
	}
	
}
