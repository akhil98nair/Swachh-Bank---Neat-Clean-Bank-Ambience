package com.example.bank;

import android.app.Notification;
import android.app.NotificationManager;
import android.support.annotation.NonNull;
import android.support.v4.app.NotificationCompat;
import android.support.v4.app.NotificationManagerCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import java.util.ArrayList;
import java.util.List;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemSelectedListener;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;


public class MainActivity extends AppCompatActivity {
    TextView dustbin,air_quality;
    DatabaseReference databaseReference;
    String airquality,dustbin_quality;
    private  NotificationManagerCompat notificationManagerCompat;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        dustbin = (TextView) findViewById(R.id.dustbin);
        air_quality = (TextView) findViewById(R.id.air_quality);
        databaseReference = FirebaseDatabase.getInstance().getReference().child("Profile").child("kush");
        databaseReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                airquality = dataSnapshot.child("Air quality").getValue().toString();
                dustbin_quality = dataSnapshot.child("Dustbin").getValue().toString();
                air_quality.setText(airquality);
                dustbin.setText(dustbin_quality);
                Integer integer = Integer.parseInt(airquality);
                Integer dustbin = Integer.parseInt(dustbin_quality);
                notificationManagerCompat = NotificationManagerCompat.from(getApplicationContext());
                if (integer > 400 || dustbin < 3){
                    if(integer >400){
                    Exampledialog exampledialog = new Exampledialog();
                    exampledialog.show(getSupportFragmentManager(),"example dialog");
                    }
                    else if (dustbin<3){
                        Dustbindialog dustbindialog = new Dustbindialog();
                        dustbindialog.show(getSupportFragmentManager(),"example");
                    }
                }

            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });


    }
    public void sendnotification(View view){
        Notification notification = new NotificationCompat.Builder(this,App.air_quality).setSmallIcon(R.drawable.appicon).setContentTitle("Bad air quality")
                .setContentText("perform the following actions").setPriority(NotificationCompat.PRIORITY_HIGH).setCategory(NotificationCompat.CATEGORY_ALARM).build();
        notificationManagerCompat.notify(1,notification);

    }
}
