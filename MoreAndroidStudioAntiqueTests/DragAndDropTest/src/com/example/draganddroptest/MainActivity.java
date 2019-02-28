package com.example.draganddroptest;

import android.os.Build;
import android.os.Bundle;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.ClipData;
import android.graphics.drawable.Drawable;
import android.view.DragEvent;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.DragShadowBuilder;
import android.view.View.OnDragListener;
import android.view.View.OnTouchListener;
import android.widget.LinearLayout;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		findViewById(R.id.myimage1).setOnTouchListener(new MyTouchListener());
		findViewById(R.id.myimage2).setOnTouchListener(new MyTouchListener());
		findViewById(R.id.myimage3).setOnTouchListener(new MyTouchListener());
		findViewById(R.id.myimage4).setOnTouchListener(new MyTouchListener());
		findViewById(R.id.topleft).setOnTouchListener(new MyTouchListener());
		findViewById(R.id.topright).setOnTouchListener(new MyTouchListener());
		findViewById(R.id.bottomleft).setOnTouchListener(new MyTouchListener());
		findViewById(R.id.bottomright).setOnTouchListener(new MyTouchListener());
	}
	
	private final class MyTouchListener implements OnTouchListener {
		public boolean onTouch(View view,MotionEvent motionEvent) {
			if ( motionEvent.getAction() == MotionEvent.ACTION_DOWN )
			{
				ClipData data = ClipData.newPlainText("", "");
				DragShadowBuilder shadowBuilder = new View.DragShadowBuilder(view);
				view.startDrag(data, shadowBuilder, view, 0);
				view.setVisibility(View.INVISIBLE);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	
	class MyDragListener implements OnDragListener {
		Drawable enterShape  = getResources().getDrawable(R.drawable.shape_droptarget);
		Drawable normalShape = getResources().getDrawable(R.drawable.shape);
		
		@TargetApi(Build.VERSION_CODES.JELLY_BEAN)
		@Override
		public boolean onDrag(View v,DragEvent event)
		{
			int action = event.getAction();

			switch( action )
			{
			case DragEvent.ACTION_DRAG_STARTED:
				// do nothing
				break;
				
			case DragEvent.ACTION_DRAG_ENTERED:
				v.setBackground(enterShape);
				break;

			case DragEvent.ACTION_DRAG_EXITED:
				v.setBackground(normalShape);
				break;
				
			case DragEvent.ACTION_DROP:
				// Dropped, reassign view to viewGroup
				View view = (View)event.getLocalState();
				ViewGroup owner = (ViewGroup)view.getParent();
				owner.removeView(view);
				LinearLayout container = (LinearLayout)v;
				container.addView(view);
				view.setVisibility(View.VISIBLE);
				break;
				
			case DragEvent.ACTION_DRAG_ENDED:
				v.setBackground(normalShape);
				
			default:
				break;
			}
			
			return true;
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
