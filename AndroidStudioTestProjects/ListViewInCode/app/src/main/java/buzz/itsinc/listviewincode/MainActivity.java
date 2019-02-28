package buzz.itsinc.listviewincode;

import android.app.Activity;
import android.content.res.Configuration;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    String[] wordList = new String[] { "aceydeucey","b","c","d" };

    Integer[] imageId = {
            R.mipmap.ic_launcher,
            R.mipmap.ic_launcher,
            R.mipmap.ic_launcher,
            R.mipmap.ic_launcher };

    @Override protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        ListView list = new ListView(this);
        list.setAdapter(new MyAdapter(this,wordList,imageId));
        list.setAdapter(new MyAdapter(this,wordList,imageId));
        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int position, long l) {
                Toast.makeText(MainActivity.this,"You clicked at " +wordList[+ position], Toast.LENGTH_SHORT).show();
            }
        });

        setContentView(list);
    }

    public class TextOnClickListener implements View.OnClickListener {
        public void myOnClickListener() {
        }

        @Override
        public void onClick(View v) {
            TextView tv = (TextView) v;
            String value = tv.getText().toString();

            int i;
            boolean b = true;

            for( i=0 ; i < wordList.length && b ; ++i ) {
                if ( value.equals(wordList[i])) {
                    Toast.makeText(MainActivity.this,"You clicked: " +wordList[+ i] + " with id: " + i, Toast.LENGTH_SHORT).show();
                    b = false;
                }
            }

            /*
            String k = value;
            int whoareyou = tv.getId();
            int iValue = whoareyou - 5000;

            Toast.makeText(MainActivity.this,"ID is acutally: " + whoareyou,Toast.LENGTH_SHORT).show();
            int l = whoareyou;
            */

        }
    }

    private class MyAdapter extends ArrayAdapter<String> {
        private final String[] stringList;
        private final Integer[] imageList;

        public MyAdapter(Activity activity, String[] strings, Integer[] images)
        {
            super(activity,-1,-1,strings);
            this.stringList = strings;
            this.imageList  = images;
        }

        @Override public View getView(int position, View convertView, ViewGroup parent)
        {
            LinearLayout listLayout = new LinearLayout(MainActivity.this);
            listLayout.setLayoutParams(new AbsListView.LayoutParams(AbsListView.LayoutParams.WRAP_CONTENT,AbsListView.LayoutParams.WRAP_CONTENT));
            listLayout.setGravity(Gravity.CENTER_VERTICAL);
            listLayout.setId(5000);

            ImageView picture = new ImageView(MainActivity.this);
            picture.setId(5001);
            picture.setImageResource((imageList[position]));
            listLayout.addView(picture);

            TextView listText = new TextView(MainActivity.this);
            listText.setId(5002);
            listLayout.addView(listText);
            listText.setText(super.getItem(position));
            listText.setOnClickListener(new TextOnClickListener());
	    listLayout.addView(listText);

            return listLayout;
        }
    }

    @Override public boolean onCreateOptionsMenu(Menu menu)
    {
        getMenuInflater().inflate(R.menu.main,menu);
        return true;
    }
}
