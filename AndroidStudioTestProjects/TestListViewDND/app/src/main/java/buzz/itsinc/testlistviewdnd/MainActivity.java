package buzz.itsinc.testlistviewdnd;

import android.app.ActionBar;
import android.app.Activity;
import android.app.IntentService;
import android.os.Bundle;
import android.view.Gravity;
import android.view.Menu;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.GridLayout;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends Activity {

    String[] wordList = new String[] { "a","b","c","d"};

    Integer[] imageId = {
            R.mipmap.ic_launcher,
            R.mipmap.ic_launcher,
            R.mipmap.ic_launcher,
            R.mipmap.ic_launcher
};

    String[] wordData = new String[] { "acey", "deycey","booger","bummer"};

    @Override protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        GridLayout gl = (GridLayout)findViewById(R.id.activity_main);

        ListView list = new ListView(this);
        list.setAdapter(new MyAdapter(this,wordList,imageId));
        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override public void onItemClick(AdapterView<?> adapterView,View view,int position,long l) {
                Toast.makeText(MainActivity.this,"You clicked " + wordList[position],Toast.LENGTH_SHORT).show();
            }
        });

        ListView lv = new ListView(this);
        lv.setAdapter(new MyAdapter(this,wordData,imageId));
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override public void onItemClick(AdapterView<?> adapterView,View view,int position,long l) {
                Toast.makeText(MainActivity.this,"You clicked " + wordData[position],Toast.LENGTH_SHORT).show();
            }
        });

        gl.addView(list,0);
        gl.addView(lv,1);

        LinearLayout.LayoutParams params1 = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT,LinearLayout.LayoutParams.MATCH_PARENT);
        params1.weight = 1.0f;
        params1.gravity = Gravity.FILL_HORIZONTAL;

        LinearLayout.LayoutParams params2 = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT,LinearLayout.LayoutParams.MATCH_PARENT);
        params2.weight = 1.0f;
        params2.gravity = Gravity.FILL_HORIZONTAL;


        // ((LinearLayout.LayoutParams)list.getLayoutParams()).gravity = Gravity.FILL_HORIZONTAL;
        // ((LinearLayout.LayoutParams)lv.getLayoutParams()).gravity = Gravity.FILL_HORIZONTAL;

        list.setLayoutParams(params1);
        lv.setLayoutParams(params2);

        // gl.setRowCount(1);
        // gl.setColumnCount(2);
    }

    public class TextOnClickListener implements View.OnClickListener {
        public void myOnClickListener() {}

        @Override public void onClick(View v)
        {
            TextView tv = (TextView) v;
            String value = tv.getText().toString();

            int i;
            boolean b = true;

            for( i=0 ; i < wordList.length && b ; ++i )
            {
                if ( value.equals(wordList[i]))
                {
                    Toast.makeText(MainActivity.this,"You clicked: " + wordList[i],Toast.LENGTH_SHORT).show();
                    b = false;
                }
            }
        }
    }

    private class MyAdapter extends ArrayAdapter<String> {
        private final String[] stringList;
        private final Integer[] imageList;

        public MyAdapter(Activity activity,String[] strings,Integer[] images)
        {
            super(activity,-1,-1,strings);
            this.stringList = strings;
            this.imageList = images;
        }

        @Override public View getView(int position,View convertView,ViewGroup parent) {
            LinearLayout listLayout = new LinearLayout(MainActivity.this);
            listLayout.setLayoutParams(new AbsListView.LayoutParams(AbsListView.LayoutParams.WRAP_CONTENT,AbsListView.LayoutParams.WRAP_CONTENT));
            listLayout.setGravity(Gravity.CENTER_VERTICAL);
            listLayout.setId(5000);

            ImageView picture = new ImageView(MainActivity.this);
            picture.setId(5001);
            picture.setImageResource(imageList[position]);
            listLayout.addView(picture);

            TextView listText = new TextView(MainActivity.this);
            listText.setId(5002);
            String sData = super.getItem(position);
            listText.setText(sData);
            listText.setOnClickListener(new TextOnClickListener());
            listLayout.addView(listText);

            return listLayout;
        }
    }

    @Override public boolean onCreateOptionsMenu(Menu menu)
    {
        getMenuInflater().inflate(R.menu.menu,menu);
        return true;
    }
}
