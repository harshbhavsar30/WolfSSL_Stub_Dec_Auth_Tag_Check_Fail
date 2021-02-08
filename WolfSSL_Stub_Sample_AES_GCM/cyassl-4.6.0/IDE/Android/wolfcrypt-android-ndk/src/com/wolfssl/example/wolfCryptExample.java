/* wolfCryptExample.java
 *
 * Copyright (C) 2006-2017 wolfSSL Inc.  All rights reserved.
 *
 * This file is part of wolfSSL.
 *
 * Contact licensing@wolfssl.com with any questions or comments.
 *
 * http://www.wolfssl.com
 */


package com.wolfssl.example;

import java.util.*;
import java.io.*;
import java.nio.*;

import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.widget.*;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.view.View.OnClickListener;

import com.wolfssl.wolfcrypt.*;
import com.wolfssl.wolfcrypt.Fips.ErrorCallback;

/**
 * Main activity class for wolfCrypt Example NDK App.
 *
 * @author wolfSSL
 * @version 1.0, April 2015
 */
public class wolfCryptExample extends Activity {

    private Thread exampleThread;

    private OnClickListener myButtonListener = new OnClickListener()
    {
        public void onClick(View v) {
            exampleThread = new Thread(new wolfCryptExampleDriver());
            exampleThread.start();
        }
    };

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        /* set up app layout */
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        /* capture our button from layout */
        Button btnOne = (Button) findViewById(R.id.runButton);

        /* register our button onClick listeners */
        btnOne.setOnClickListener(myButtonListener);

        TextView tv = (TextView) findViewById(R.id.textView1);
        tv.setMovementMethod(new ScrollingMovementMethod());
        tv.setTextSize(10);
    }


    public class wolfCryptExampleDriver implements Runnable, ErrorCallback
    {
        public wolfCryptExampleDriver()
        {
        }

        /* wolfCrypt FIPS Error Callback Example
         *
         * This is a example of using the wolfCrypt FIPS error callback. The
         * callback is called when the in core verify hash check fails, and
         * allows the user to view the expected hash that should match the
         * value for "verifyCore" in <wolfssl_root>/ctaocrypt/src/fips_test.c.
         *
         * Note that an alternative to using this callback mechanism is to
         * call Fips.wolfCrypt_GetCoreHash_fips() as shown in the SHA test
         * code below. This will return to the application a Java String
         * that contains the expected hash value.
         */
        @Override
        public void errorCallback(int ok, int err, String hash) {
            /* output to both TextView and logcat */
            appendText("---------------------------------------\n");
            appendText("in FIPS error callback, ok =" + ok + " err = " +
                    err + "\n");
            appendText("hash = " + hash + "\n");

            System.out.println("---------------------------------------");
            System.out.println("in FIPS error callback, ok =" + ok + " err = " +
                    err);
            System.out.println("hash = " + hash);

            if (err == -203) {
                appendText("In core integrity hash check failure, " +
                        "copy above hash\n");
                appendText("into verifyCore[] in fips_test.c " +
                    "and rebuild\n");
                appendText("---------------------------------------\n");

                System.out.println("In core integrity hash check failure, " +
                        "copy above hash");
                System.out.println("into verifyCore[] in fips_test.c " +
                    "and rebuild");
                System.out.println("---------------------------------------");
            }
        }


        @Override
        public void run()
        {
            while (!Thread.currentThread().isInterrupted()) {

                /* this is only required when using the FIPS error callback,
                 * see note above */
                Fips.wolfCrypt_SetCb_fips(this);

                /* as an example, do a quick SHA test */
                ShaFipsTest();

                Thread.currentThread().interrupt();
            }
        }

        public void ShaFipsTest() {

            int i, ret;

            ByteBuffer data     = ByteBuffer.allocateDirect(32);
            ByteBuffer result   = ByteBuffer.allocateDirect(Sha.DIGEST_SIZE);
            ByteBuffer expected = ByteBuffer.allocateDirect(Sha.DIGEST_SIZE);

            String[] dataVector = new String[] {
                "",
                "226833eca43edeab",
                "01ae37df5128cb6059b57a904e834ca9",
                "421b944a38f03450b21d1c8c6514461fb82ef846cc9eebe7",
                "9f1daf4748d7aa20a359a7d8a220446de1a918e6dad68bda5894eb312ebbbc2e" };

            String[] hashVector = new String[] {
                "da39a3ee5e6b4b0d3255bfef95601890afd80709",
                "69e8fb462869452f0387733b03045dc0835531e5",
                "6849e5d39ac08f5daec25b91c4f4160cd921f8b7",
                "7e328a4e252a2d901a7f79365953a5e0682a8a9d",
                "22bbfc22a78aef3e356a32066eee78fc2ce28d8c" };

            appendText("Starting SHA Example\n\n");

            for (i = 0; i < dataVector.length; i++) {

                appendText("SHA [vector " + i + "]: \n");
                Sha sha = new Sha();

                data.put(Util.h2b(dataVector[i])).rewind();
                expected.put(Util.h2b(hashVector[i])).rewind();

                ret = Fips.InitSha_fips(sha);
                if (ret != WolfCrypt.SUCCESS) {
                    appendText("     RESULT: FAIL (InitSha_fips)\n");
                    ret = Fips.wolfCrypt_GetStatus_fips();
                    appendText("     " + WolfCryptError.fromInt(ret));
                    appendText("     " + Fips.wolfCrypt_GetCoreHash_fips());
                    break;
                }

                ret = Fips.ShaUpdate_fips(sha, data, dataVector[i].length()/2);
                if (ret != WolfCrypt.SUCCESS) {
                    appendText("     RESULT: FAIL (ShaUpdate_fips)\n");
                    ret = Fips.wolfCrypt_GetStatus_fips();
                    appendText("     " + WolfCryptError.fromInt(ret));
                    appendText("     " + Fips.wolfCrypt_GetCoreHash_fips());
                    break;
                }

                ret = Fips.ShaFinal_fips(sha, result);
                if (ret != WolfCrypt.SUCCESS) {
                    appendText("     RESULT: FAIL (ShaFinal_fips)\n");
                    ret = Fips.wolfCrypt_GetStatus_fips();
                    appendText("     " + WolfCryptError.fromInt(ret));
                    appendText("     " + Fips.wolfCrypt_GetCoreHash_fips());
                    break;
                }

                expected.rewind();
                result.rewind();
                if (expected.compareTo(result) == 0) {
                    appendText("     RESULT: PASS\n");
                } else {
                    appendText("     RESULT: FAIL\n");
                }
            }

        } /* end ShaFipsTest */

        /**
         * Appends text to the main output TextView.
         *
         * @param msg message to be printed to TextView
         */
        public void appendText(final String msg)
        {
            runOnUiThread(new Runnable() {
                @Override
                public void run()
                {
                    TextView tv = (TextView) findViewById(R.id.textView1);
                    tv.append(msg);
                }
            });
        }

    } /* end wolfCryptExampleDriver class */

    static {
        System.loadLibrary("wolfssl");
        System.loadLibrary("wolfcryptjni");
        System.loadLibrary("wolfcryptexample");
    }
}

