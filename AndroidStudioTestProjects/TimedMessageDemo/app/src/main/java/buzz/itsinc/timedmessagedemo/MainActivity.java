package buzz.itsinc.timedmessagedemo;

import android.app.Activity;
import android.os.Handler;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends Activity {

    TextView timerTextView;
    long startTime = 0;
    int  iLoopTime = 0;

    Handler timerHandler = new Handler();
    Runnable timerRunnable = new Runnable() {
        @Override public void run() {
            long millis = System.currentTimeMillis() - startTime;
            int seconds = (int)(millis / 1000);
            int minutes = seconds / 60;

            seconds = seconds % 60;

            timerTextView.setText(String.format("%d:%02d",minutes,seconds));

            timerHandler.postDelayed(this,500);

            ++iLoopTime;
            if ( iLoopTime == 20 ) {
                System.exit(0);
            }
        }
    };

    @Override protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        timerTextView = (TextView)findViewById(R.id.timerTextView);

        Button b = (Button)findViewById(R.id.button);
        b.setText("start");
        b.setOnClickListener(new View.OnClickListener() {
            @Override public void onClick(View v) {
                Button b = (Button)v;
                if ( b.getText().equals("stop")) {
                    timerHandler.removeCallbacks(timerRunnable);
                    b.setText("start");
                }else{
                    startTime = System.currentTimeMillis();
                    timerHandler.postDelayed(timerRunnable,0);
                    b.setText("stop");
                }
            }
        });
    }

    @Override public void onPause() {
        super.onPause();
        timerHandler.removeCallbacks(timerRunnable);
        Button b = (Button)findViewById(R.id.button);
        b.setText("start");
    }
}
