package buzz.itsinc.testnasterskave2;

import android.app.Activity;
import android.app.Fragment;
import android.app.FragmentManager;
import android.app.FragmentTransaction;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;
import android.util.Log;

public class MainActivity extends Activity {

    public static final String TAG = "Shakespeare";

    @Override protected void onCreate(Bundle savedInstanceState) {
        Log.v(TAG,"in MainActivity onCreate");
        super.onCreate(savedInstanceState);
        FragmentManager.enableDebugLogging(true);
        setContentView(R.layout.activity_main);
    }

    @Override public void onAttachFragment(Fragment fragment) {
        Log.v(TAG,"in MainActivity onAttachFragment, fragment id = " + fragment.getId());
        super.onAttachFragment(fragment);
    }

    @Override public void onStart() {
        Log.v(TAG,"in MainActivity onStart");
        super.onStart();
    }

    @Override public void onResume() {
        Log.v(TAG,"in MainActivity onResume");
        super.onResume();
    }

    @Override public void onPause() {
        Log.v(TAG,"in MainActivity onPause");
        super.onPause();
    }

    @Override public void onStop() {
        Log.v(TAG,"in MainActivity onStop");
        super.onStop();
    }

    @Override public void onSaveInstanceState(Bundle outState) {
        Log.v(MainActivity.TAG,"in MainActivity onSaveInstanceState");
        super.onSaveInstanceState(outState);
    }

    @Override public void onDestroy() {
        Log.v(TAG,"in MainActivity onDestroy");
        super.onDestroy();
    }

    public boolean isMultiPane() {
        return getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE;
    }

    /**
     * Helper function to show the details of a selected item, either by
     * diplaying a fragment in-place in the current UI, or starting a
     * whole new activiy in which it is displayed.
     */

    public void showDetails(int index) {

        // Check what fragment is displayed, replace if necessary

        DetailsFragment details = (DetailsFragment)getFragmentManager().findFragmentById(R.id.details);

        if ( details == null || details.getShownIndex() != index ) {
            // Make a new fragment to show this selection.

            details = DetailsFragment.newInstance(index);

            // Execute a transaction replacing any prior fragment
            // with this one in the current frame

            Log.v(TAG,"about to run fragment transaction");

            FragmentTransaction ft = getFragmentManager().beginTransaction();
            ft.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_FADE);
            //ft.addToBackstack("details");
            ft.replace(R.id.details,details);
            ft.commit();
        }
    }else{
        // Otherwise you need to launch a new activity to display
        // the dialog fraement with selected text

        Intent intent = new Intent();
        intent.setClass(this,DetailsActivity.class);
        intent.putExtra("index",index);
        startActivity(intent);
    }

