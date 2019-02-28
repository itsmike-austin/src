package buzz.itsinc.demosocketclient;

/*
 * Simple program to shut down the server from any java device
 */

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public class MainActivity extends Activity {

    private Socket socket;  // Socket to connect to the server
    private OutputStream sout;    // Socket writer channel
    private InputStream sin;     // Socket reader channel

    private Button shutdownButton;         // UI shutdown button
    private Button cancelButton;           // UI cancel button
    private TextView statusBar;            // UI status bar

    private WifiManager wifi;              // Manager for the wifi interface

    private String serverAddr = "10.100.20.1";
    private int    port       = 92;

    private boolean busy;

    private boolean bCompares;
    private boolean bWifiStatus;
    private String  resultString;

    int iLoopCount = 0;

    Handler timerHandler = new Handler();
    Runnable timerRunnable = new Runnable() {
        @Override public void run() {
            if ( iLoopCount % 2 != 0 ) {
                statusBar.setText(resultString);
            }else{
                statusBar.setText("");
            }
            if ( ++iLoopCount == 10 ) {
                wifi.setWifiEnabled(false);
                if ( Build.VERSION.SDK_INT >= 21) {
                    finishAndRemoveTask();
                } else {
                    finish();
                }
                System.exit(0);
            }
            timerHandler.postDelayed(this,500);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // Initialize the variables

        socket = null;
        busy = false;

        // Create the user interface

        setContentView(R.layout.activity_main);

        // Get the buttons from the user interface.

        shutdownButton = (Button) findViewById(R.id.shutdown_button);
        cancelButton   = (Button) findViewById(R.id.cancel_button);
        statusBar      = (TextView)findViewById(R.id.status_line);

        // Try and open your wifi connection

        new Thread(new Runnable() {
            public void run() {
                // wifi = (WifiManager) getSystemService(Context.WIFI_SERVICE);
                 wifi = (WifiManager)getApplicationContext().getSystemService(Context.WIFI_SERVICE);

                // Get the wifi up and running. If not running, simply offer the opportunity and leave.

                bWifiStatus = wifi.isWifiEnabled();

                if (wifi.isWifiEnabled() == false) {
                    wifi.setWifiEnabled(true);
                    startActivity(new Intent(WifiManager.ACTION_PICK_WIFI_NETWORK));
                }
            }
        }).start();

        // Execute the shutdown. XXX: Additional error checking is required.

        shutdownButton.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {

                        bCompares = true;

                        if (true == busy) return;

                        busy = true;

                        Thread t = new Thread(new Runnable() {
                            public void run() {
                                int iStat = 0;
                                byte[] buffer = new byte[1024];

                                try {

                                    socket = new Socket(serverAddr, port);
                                    sout = socket.getOutputStream();
                                    sin = socket.getInputStream();

                                    try {
                                        sout.write("shutdown".getBytes());
                                    } catch (IOException e1) {
                                    }

                                    // Find out iof the server is ammenable.

                                    try {
                                        int iRc = sin.read(buffer);
                                        byte[] term = "terminate".getBytes();

                                        if (0 < iRc) {
                                            boolean bContinue = true;
                                            for (int i = 0; i < iRc && bContinue; ++i) {
                                                if (term[i] != buffer[i]) {
                                                    bCompares = false;
                                                    bContinue = false;
                                                }
                                            }
                                        }
/*
                                        TextView tv = (TextView)findViewById(R.id.status_line);
                                        tv.setVisibility(View.VISIBLE);

                                        if ( bComp == true ) {
                                            tv.setText("Stopping");
                                        }else{
                                            tv.setText("Busy");
                                        }
                                        */
                                    } catch (IOException e2) {
                                    }

                                    // Done with this connection so close the input and output streams

                                    try {
                                        sin.close();
                                    } catch (IOException e4) {
                                    }

                                    try {
                                        sout.close();
                                    } catch (IOException e5) {
                                    }

                                    // All completed, so exit

                                } catch (IOException ioe1) {
                                }
                            }
                        });

                        t.start();

                        try {
                            t.join();
                        } catch (InterruptedException ie1) {
                        }

                        if (true == bCompares) {
                            resultString = "Shutdown Scheduled";
                        } else {
                            resultString = "Shutdown Failed";
                        }

                        timerHandler.postDelayed(timerRunnable,0);
                    }
                }
        );

        // We entered the app, but don't want to do anything. Handle the open connection.

        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if ( bWifiStatus == false ) wifi.setWifiEnabled(false);

                if ( Build.VERSION.SDK_INT >= 21 ) {
                    finishAndRemoveTask();
                }
                else
                {
                    finish();
                }
                System.exit(0);
            }
       });
    }
}
