package com.example.superflipper;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.AnimationUtils;
import android.widget.ImageView;

public class MainActivity extends Activity {

	boolean isHeads;
	Animation shrink, grow;
	ImageView flipImage;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		flipImage = (ImageView)findViewById(R.id.flip_image);
		flipImage.setImageResource(R.drawable.heads);
		isHeads = true;
		
		shrink = AnimationUtils.loadAnimation(this,R.anim.shrink);
		
		shrink.setAnimationListener(new Animation.AnimationListener() {
			@Override
			public void onAnimationStart(Animation animation) {}
			
			@Override
			public void onAnimationRepeat(Animation animation) {}

			@Override
			public void onAnimationEnd(Animation animation) {
				if ( isHeads )
				{
					isHeads = false;
					flipImage.setImageResource(R.drawable.tails);
				}
				else
				{
					isHeads = true;
					flipImage.setImageResource(R.drawable.heads);
				}
				flipImage.startAnimation(grow);
			}
		});
		
		grow = AnimationUtils.loadAnimation(this,R.anim.grow);
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if ( event.getAction() == MotionEvent.ACTION_DOWN )
		{
			flipImage.startAnimation(shrink);
			return true;
		}
		return super.onTouchEvent(event);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

}
