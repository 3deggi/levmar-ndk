package hvrl.levmar;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;

public class levmarActivity extends Activity {
    private static final String    TAG = "Levmar Activity";
   
    public levmarActivity() {
        Log.i(TAG, "Instantiated new " + this.getClass());
    }

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.i(TAG, "called onCreate");
        super.onCreate(savedInstanceState);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        setContentView(R.layout.driver_view);
        System.loadLibrary("lmdriver");
        final Button button = (Button) findViewById(R.id.execDriver);
        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
            	Driver();
            }
        });
     }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
    	return true;
    }

    @Override
    public void onPause()
    {
        super.onPause();
     }

    @Override
    public void onResume()
    {
        super.onResume();
    }

    public void onDestroy() {
        super.onDestroy();
     }

    public boolean onOptionsItemSelected(MenuItem item) {
        return true;
    }
    
    public native int Driver(); 
}
