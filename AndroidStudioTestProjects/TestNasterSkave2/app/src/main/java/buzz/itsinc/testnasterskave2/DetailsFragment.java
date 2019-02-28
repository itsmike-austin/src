package buzz.itsinc.testnasterskave2;

import android.app.Activity;
import android.app.Fragment;
import android.content.Context;
import android.os.Bundle;
import android.util.AttributeSet;
import android.util.Log;

/**
 * Created by artwork on 1/28/2017.
 */

public class DetailsFragment extends Fragment {

    private int mIndex = 0;

    public static DetailsFragment newInstance(int index) {
        Log.v(MainActivity.TAG,"in DetailsFragment newInstance( " + index + " )");
        DetailsFragment df = new DetailsFragment();

        // Supply index input as an argument

        Bundle args = new Bundle();
        args.putInt("index",index);
        df.setArguments(args);
        return df;
    }

    public static DetailsFragment newInstance(Bundle bundle) {
        int index = bundle.getInt("index",0);
        return newInstance(index);
    }

    @Override public void onInflate(Context context, AttributeSet attrs, Bundle savedInstanceState) {
        Log.v(MainActivity.TAG,"in DetailsFragment onInflate. Attribute set contains");
        for( int i=0 ; i < attrs.getAttributeCount() ; ++i ) {
            Log.v(MainActivity.TAG,"    " + attrs.getAttributeName(i));
        }
        super.onInflate(context,attrs,savedInstanceState);
    }

    @Override public void onAttach(Context context) {
        Activity a;

        super.onAttach(context);
        Log.v(MainActivity.TAG,"in DetailsFragment onAttach");
        if ( context instanceof Activity ) {
            a = (Activity)context;
        }
        super.onAttach(context);
    }

    @Override public void onCreate() {

    }

}
