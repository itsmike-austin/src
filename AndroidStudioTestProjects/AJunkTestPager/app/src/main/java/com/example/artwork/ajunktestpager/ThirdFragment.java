package com.example.artwork.ajunktestpager;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

/**
 * Created by artwork on 6/26/2015.
 */
public class ThirdFragment extends Fragment {
    public static ThirdFragment newInstance(int page,String title) {
        ThirdFragment third = new ThirdFragment();
        return third;
    }

    @Override public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override public View onCreateView(LayoutInflater inflater,ViewGroup container,Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.button_box,container,false);
        return view;
    }
}
