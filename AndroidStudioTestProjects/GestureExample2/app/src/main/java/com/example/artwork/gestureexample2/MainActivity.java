package com.example.artwork.gestureexample2;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.view.animation.TranslateAnimation;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity {
    Button b;
    EditText edit;
    View layout;

    /**
     * Called when the activity is first created.
     */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        edit = (EditText) findViewById(R.id.edittext);
        b = (Button) findViewById(R.id.button);
        layout = (View) findViewById(R.id.layout);
        b.setOnClickListener(new View.OnClickListener() {

            @Override
            public void onClick(View v) {
                edit.setVisibility(View.VISIBLE);
                TranslateAnimation slide = new TranslateAnimation(0, 0, 100, 0);
                slide.setDuration(1000);
                slide.setFillAfter(true);
                edit.startAnimation(slide);
            }
        });
    }
}
