package com.example.artwork.ajunktestpager;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

/**
 * Created by artwork on 6/26/2015.
 */
public class SecondFragment extends Fragment {

    private String title;
    private int page;

    public static SecondFragment newInstance(int page,String title) {
        SecondFragment fragmentSecond = new SecondFragment();
        Bundle args = new Bundle();
        args.putInt("someInt", page);
        args.putString("someTitle", title);
        fragmentSecond.setArguments(args);
        return fragmentSecond;
    }

    @Override public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        page = getArguments().getInt("someInt");
        title = getArguments().getString("someTitle");
    }

    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_second,container,false);
        TextView tvLabel = (TextView)view.findViewById(R.id.tvLabel);
        tvLabel.setText(page + " == " + title);
        return view;
    }
}
