package com.example.waterqualitydetection;

import androidx.appcompat.app.AppCompatActivity;
import androidx.swiperefreshlayout.widget.SwipeRefreshLayout;

import android.os.Bundle;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import org.jetbrains.annotations.NotNull;

import java.io.IOException;
import java.util.Date;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;

public class MainActivity extends AppCompatActivity {

    private String t_id = "N.A.";
    private String  dat = "N.A.";
    private String  tim = "N.A.";
    private String pH_val = "N.A.";
    private String tur_val = "N.A.";
    private String temp_val = "N.A.";
    private String port_val = "N.A.";

    private TextView tidTextView;
    private TextView dateTextView;
    private TextView timeTextView;
    private TextView phTextView;
    private TextView turTextView;
    private TextView tempTextView;
    private TextView portTextView;

    private SwipeRefreshLayout refreshLayout;
    private LinearLayout swipeLayout;
    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        refreshLayout = findViewById(R.id.swipe);
        swipeLayout = findViewById(R.id.swipeLayout);

        tidTextView = (TextView) findViewById(R.id.tid);
        dateTextView = (TextView) findViewById(R.id.date);
        timeTextView = (TextView) findViewById(R.id.time);
        phTextView = (TextView) findViewById(R.id.pH);
        turTextView = (TextView) findViewById(R.id.tur);
        tempTextView = (TextView) findViewById(R.id.temp);
        portTextView = (TextView) findViewById(R.id.port);


        OkHttpClient okhttpclient = new OkHttpClient();
        Request request = new Request.Builder().url("https://waterqualitydetection.herokuapp.com/mobile/").build();
        System.out.println("STARTED");
        okhttpclient.newCall(request).enqueue(new Callback() {
            @Override
            public void onFailure(@NotNull Call call, @NotNull IOException e) {
                System.out.println("ERROR");
                runOnUiThread(() -> {
                    final Toast toast = Toast.makeText(MainActivity.this,"Network Error",Toast.LENGTH_LONG);
                    toast.show();
                });
            }
            @Override
            public void onResponse(@NotNull Call call, @NotNull Response response) throws IOException {
                String str = response.body().string();
                String[] s = str.split("\\s");
                t_id = s[0];
                dat = s[1];
                tim = s[2];
                pH_val = s[3];
                tur_val = s[4];
                temp_val = s[5];
                port_val = s[6];
            }
        });

        refreshLayout.setOnRefreshListener(() -> {
            tidTextView.setText("Test id: "+t_id);
            dateTextView.setText("Date: "+dat);
            timeTextView.setText("Time: "+tim);
            phTextView.setText("pH value: "+pH_val);
            turTextView.setText("Turbidity: "+tur_val);
            tempTextView.setText("Temperature: "+temp_val);
            portTextView.setText("PORTABILITY: "+port_val);
            refreshLayout.setRefreshing(false);
        });
    }
}