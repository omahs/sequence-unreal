package com.Plugins.SequencePlugin;


import android.content.Intent;
import android.net.Uri;
import com.epicgames.unreal.GameActivity;


public class AndroidNativeBridge {
    public static native void nativeHandleDeepLink(String deeplink);
    
    public static void onCreate(GameActivity gameActivity) {
        Intent intent = gameActivity.getIntent();

        if (intent == null) {
            return;
        }

        String action = intent.getAction();
        Uri data = intent.getData();

        if (Intent.ACTION_VIEW.equals(action) && data != null) {
            nativeHandleDeepLink(data.toString());
        }
    }
}