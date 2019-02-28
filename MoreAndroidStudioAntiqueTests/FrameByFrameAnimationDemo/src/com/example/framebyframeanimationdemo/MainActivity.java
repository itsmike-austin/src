package com.example.framebyframeanimationdemo;

import android.support.v7.app.ActionBarActivity;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;

public class MainActivity extends ActionBarActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);		
	      setContentView(R.layout.frame_animations_layout);
	      this.setupButton();
	}

	   private void setupButton() {
	   Button b = (Button)this.findViewById(R.id.startFAButtonId);
	   b.setOnClickListener(
	      new Button.OnClickListener() {
	         public void onClick(View v) {
	         parentButtonClicked(v);
	         }
	      });
	   }

	   private void parentButtonClicked(View v) {
		      animate();
		   }

	   
	   private void animate() {
		      ImageView imgView = (ImageView)findViewById(R.id.animationImage);                                        
		      imgView.setVisibility(ImageView.VISIBLE);
		      imgView.setBackgroundResource(R.drawable.frame_animation);

		      AnimationDrawable frameAnimation =
		      (AnimationDrawable) imgView.getBackground();

		      if (frameAnimation.isRunning()) {
		         frameAnimation.stop();
		      }
		      else {
		         frameAnimation.stop();
		         frameAnimation.start();
		      }
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
}
