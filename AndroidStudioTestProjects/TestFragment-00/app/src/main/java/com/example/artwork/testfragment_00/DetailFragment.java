package com.example.artwork.testfragment_00;

import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

/**
 * Created by artwork on 6/17/2015.
 */
public class DetailFragment extends Fragment {

    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState) {

        View view = inflater.inflate(R.layout.fragnent_rssitem_layout,container,false);

        return view;
    }

    public void setText(String item) {

        TextView view = (TextView) getView().findViewById(R.id.detailsText);
        view.setText(item);

    }
}
