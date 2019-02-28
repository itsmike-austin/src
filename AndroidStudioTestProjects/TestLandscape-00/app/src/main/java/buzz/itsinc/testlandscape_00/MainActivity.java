package buzz.itsinc.testlandscape_00;

import android.content.ClipData;
import android.content.Context;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.support.v4.content.ContextCompat;
import android.support.v4.content.res.ResourcesCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.DragEvent;
import android.view.Menu;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

public class MainActivity extends AppCompatActivity {

    @Override protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.myimage1).setOnTouchListener(new MyTouchListener());
        findViewById(R.id.myimage2).setOnTouchListener(new MyTouchListener());
        findViewById(R.id.myimage3).setOnTouchListener(new MyTouchListener());
        findViewById(R.id.myimage4).setOnTouchListener(new MyTouchListener());

        findViewById(R.id.topleft).    setOnDragListener(new MyDragListener());
        findViewById(R.id.topright).   setOnDragListener(new MyDragListener());
        findViewById(R.id.bottomleft). setOnDragListener(new MyDragListener());
        findViewById(R.id.bottomright).setOnDragListener(new MyDragListener());
    }

    private final class MyTouchListener implements View.OnTouchListener {
        public boolean onTouch(View view,MotionEvent motionEvent) {
            boolean bRc = false;
            if ( motionEvent.getAction() == MotionEvent.ACTION_DOWN )
            {
                ClipData data = ClipData.newPlainText("","");
                View.DragShadowBuilder shadowBuilder = new View.DragShadowBuilder(view);

                if ( Build.VERSION.SDK_INT > Build.VERSION_CODES.N )
                {
                    view.startDragAndDrop(data,shadowBuilder,view,0);
                    view.setVisibility(View.INVISIBLE);
                }
                else
                {
                    view.startDrag(data,shadowBuilder,view,0);
                    view.setVisibility(View.INVISIBLE);
                }
                bRc = true;
            }
            return bRc;
        }
    }

    class MyDragListener implements View.OnDragListener {

        Drawable enterShape  = ResourcesCompat.getDrawable(getResources(),R.drawable.shape_droptarget,null);
        Drawable normalShape = ResourcesCompat.getDrawable(getResources(),R.drawable.shape_normal,null);

        @Override public boolean onDrag(View v,DragEvent event)
        {
            int action = event.getAction();

            switch( action )
            {
                case DragEvent.ACTION_DRAG_STARTED:
                    // do nothing
                    break;

                case DragEvent.ACTION_DRAG_ENTERED:
                    v.setBackground(enterShape);
                    break;

                case DragEvent.ACTION_DRAG_EXITED:
                    v.setBackground(enterShape);
                    break;

                case DragEvent.ACTION_DROP:
                    // Dropped, reassign view to viewGroup
                    View view = (View)event.getLocalState();
                    ViewGroup owner = (ViewGroup)view.getParent();
                    owner.removeView(view);
                    LinearLayout container = (LinearLayout)v;
                    container.addView(view);
                    view.setVisibility(View.VISIBLE);
                    break;

                case DragEvent.ACTION_DRAG_ENDED:
                    v.setBackground(enterShape);

                default:
                    break;
            }
            return true;
        }
    }

    @Override public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu;l this adds items to the action bar if it is present
        getMenuInflater().inflate(R.menu.menu,menu);
        return true;
    }
}
