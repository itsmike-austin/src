package buzz.itsinc.testui_handler;

import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    final int Msg1 = 1018;

    Thread   two;
    Handler  joe;
    Message  msg;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        final TextView statusBar;
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        statusBar = (TextView)findViewById(R.id.statusBar);

        msg = Message.obtain();

        joe = new Handler() {
            @Override public void handleMessage(Message mesg) {
                switch( mesg.what ) {
                    case 1018:
                        statusBar.setText("Howdy Ma");
                        break;
                    case 1019:
                        break;
                    default:
                        super.handleMessage(msg);
                }
            }
        };

        new Thread(new Runnable() {
            public void run() {
                msg.what = Msg1;
                joe.sendMessage(msg);
            }
        }).start();
    }
}
