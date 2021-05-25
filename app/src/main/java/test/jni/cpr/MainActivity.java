package test.jni.cpr;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.util.Log;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String url = "http:example.com";
        File caFilePath = new File(getApplicationContext().getFilesDir(), "cacert.pem");
        android.util.Log.i("TEST", "PATH=" + caFilePath.getAbsolutePath());
        Log.i("TEST", "RESP="+request(url, caFilePath.getAbsolutePath()));
    }


    public native String request(String url, String capath);
}
