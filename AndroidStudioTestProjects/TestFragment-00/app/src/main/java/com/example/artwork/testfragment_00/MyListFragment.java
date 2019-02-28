package com.example.artwork.testfragment_00;

import android.app.Activity;
import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;

/**
 * Created by artwork on 6/17/2015.
 */
public class MyListFragment extends Fragment {

    private OnItemSelectedListener listener;

    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceData) {
        View view = inflater.inflate(R.layout.fragment_rsslist_overview,container,false);
        Button button = (Button)view.findViewById(R.id.button1);

        button.setOnClickListener(new View.OnClickListener() {
            @Override public void onClick(View v) {
                updateDetail();
            }
        });

        return view;
    }

    public interface OnItemSelectedListener {
        public void onRssItemSelected(String link);
    }

    @Override public void onAttach(Activity activity) {
        super.onAttach(activity);

        if ( activity instanceof OnItemSelectedListener ) {
            listener = (OnItemSelectedListener)activity;
        } else {
            throw new ClassCastException(activity.toString() + " must implement MyListFragment.OnItemSelectedListener");
        }
    }

    // triggers update of the detail fragment

    public void updateDetail() {
        // create fake data

        String newTime = String.valueOf(System.currentTimeMillis());

        // send data to activity

        listener.onRssItemSelected(newTime);
    }
}
