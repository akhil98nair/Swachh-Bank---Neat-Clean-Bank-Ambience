package com.example.bank;

import android.app.Application;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.os.Build;

public class App extends Application {
    public static final String air_quality = "airquality";
    @Override
    public void onCreate() {
        super.onCreate();
        createnotification();
    }
    private void createnotification(){
        if(Build.VERSION.SDK_INT >= Build.VERSION_CODES.O){
            NotificationChannel notificationChannel = new NotificationChannel(air_quality,"air", NotificationManager.IMPORTANCE_HIGH);
            notificationChannel.setDescription("bad air quality");
            NotificationManager manager = getSystemService(NotificationManager.class);
            manager.createNotificationChannel(notificationChannel);
        }
    }
}
