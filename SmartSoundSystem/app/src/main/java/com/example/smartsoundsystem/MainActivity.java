package com.example.smartsoundsystem;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{

    DatabaseReference reff;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        reff = FirebaseDatabase.getInstance().getReference().child("Instructions");

        Button btn_vol_up = findViewById(R.id.btn_vol_up);
        Button btn_vol_down = findViewById(R.id.btn_vol_down);
        Button btn_prev = findViewById(R.id.btn_prev);
        Button btn_next = findViewById(R.id.btn_next);
        Button btn_play = findViewById(R.id.btn_play);
        Button btn_on_off = findViewById(R.id.btn_on_off);
        Button btn_left = findViewById(R.id.btn_left);
        Button btn_right = findViewById(R.id.btn_right);

        btn_vol_up.setOnClickListener(this);
        btn_vol_down.setOnClickListener(this);
        btn_prev.setOnClickListener(this);
        btn_next.setOnClickListener(this);
        btn_play.setOnClickListener(this);
        btn_on_off.setOnClickListener(this);
        btn_left.setOnClickListener(this);
        btn_right.setOnClickListener(this);

    }

    @Override
    public void onClick(View v) {
        switch (v.getId()){
            case R.id.btn_vol_up:
                reff.push().setValue("UP");
                break;
            case R.id.btn_vol_down:
                reff.push().setValue("DOWN");
                break;
            case R.id.btn_prev:
                reff.push().setValue("PREV");
                break;
            case R.id.btn_next:
                reff.push().setValue("NEXT");
                break;
            case R.id.btn_play:
                reff.push().setValue("PLAY");
                break;
            case R.id.btn_on_off:
                reff.push().setValue("ONOFF");
                break;
            case R.id.btn_left:
                reff.push().setValue("LEFT");
                break;
            case R.id.btn_right:
                reff.push().setValue("RIGHT");
                break;
        }
    }
}
