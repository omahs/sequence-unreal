package com.Plugins.SequencePlugin;

public class SequenceOldGoogleSignInHelper {
    private static final String TAG = "SequenceGoogleSignIn";

    private GoogleSignInClient mGoogleSignInClient;
    private static final int REQUEST_GOOGLE_SIGN_IN_OLD = 1234;

    public SequenceOldGoogleSignInHelper(Context context) {
        GoogleSignInOptions gso = new GoogleSignInOptions.Builder(
                GoogleSignInOptions.DEFAULT_SIGN_IN
        ).requestIdToken("970987756660-35a6tc48hvi8cev9cnknp0iugv9poa23.apps.googleusercontent.com").build();

        mGoogleSignInClient = GoogleSignIn.getClient(context, gso);
    }

    public void signIn(Activity activity) {
        Intent intent = mGoogleSignInClient.getSignInIntent();
        activity.startActivityForResult(intent, REQUEST_GOOGLE_SIGN_IN_OLD);
    }

    public onStartCheckIdToken(Context context) {
        GoogleSignInAccount account = GoogleSignIn.getLastSignedInAccount(this);
        if (account != null) {
            Log.d(TAG, "onStart id token: " + account.getIdToken());
        } else {
            Log.d(TAG, "onStart no id token, user not logged in");
        }
    }

    public onActivityResult(int requestCode, Intent data) {
        if (requestCode == REQUEST_GOOGLE_SIGN_IN_OLD) {
            Task<GoogleSignInAccount> task = GoogleSignIn.getSignedInAccountFromIntent(data);
            try {
                GoogleSignInAccount account = task.getResult(ApiException.class);
                Log.d(TAG, "sign-in success, got id token: " + account.getIdToken());
            } catch (ApiException e) {
                Log.e(TAG, "sign-in failed: " + e.getStatusCode());
            }
        }        
    }
}