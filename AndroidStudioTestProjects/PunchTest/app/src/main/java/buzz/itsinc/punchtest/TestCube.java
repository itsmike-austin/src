package buzz.itsinc.punchtest;

/* ==============================================================================================
 * Test Cube
 *
 * This object is nothing more than a drawable cube. Each of the faces will ultimately end up with
 * an individual texture. This will be used as a button flipper effect when pressed to assure the
 * best opportunity to port the base code to other platforms.
 * ============================================================================================== */

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.GLUtils;
import android.opengl.Matrix;
import android.os.SystemClock;

import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class TestCube implements GLSurfaceView.Renderer {

    /* -------------------------------------------------------------
     * Rendering (Draw) Method
     * ------------------------------------------------------------- */

    public void onDrawFrame(GL10 glUnused) {

        // Set background color blue and clear the depth buffer

        GLES20.glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
        GLES20.glClear(GLES20.GL_DEPTH_BUFFER_BIT | GLES20.GL_COLOR_BUFFER_BIT);

        // Select the shading program

        GLES20.glUseProgram(mProgram);
        if ( GLES20.GL_NO_ERROR != GLES20.glGetError() ) throw new RuntimeException("onDrawFrame(glUseProgram)");

        // Activate the required texture

        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D,mTextureID);

        // Bind the shader variables

        mCubeVertices.position(VERTICES_OFFSET);
        GLES20.glVertexAttribPointer(maPositionHandle,3,GLES20.GL_FLOAT,false,DATA_STRIDE_BYTES,mCubeVertices);
        if ( GLES20.GL_NO_ERROR != GLES20.glGetError() ) throw new RuntimeException("onDrawFrame(maPositionHandle)");

        mCubeVertices.position(UV_OFFSET);
        GLES20.glEnableVertexAttribArray(maPositionHandle);
        if ( GLES20.GL_NO_ERROR != GLES20.glGetError() ) throw new RuntimeException("onDrawFrame(enableAttribArray)");
        GLES20.glVertexAttribPointer(maTextureHandle,2,GLES20.GL_FLOAT,false,DATA_STRIDE_BYTES,mCubeVertices);
        if ( GLES20.GL_NO_ERROR != GLES20.glGetError() ) throw new RuntimeException("onDrawFrame(vertexAttribPointer)");
        GLES20.glEnableVertexAttribArray(maTextureHandle);
        if ( GLES20.GL_NO_ERROR != GLES20.glGetError() ) throw new RuntimeException("onDrawFrame(maTextureHandle)");

        // Rotate the cube.

        long  time   = SystemClock.uptimeMillis() % 4000L;
        float angle = 0.090f * ((int)time);

        Matrix.setRotateM(mMMatrix, 0, angle, 0, 0, 1.0f);
        Matrix.multiplyMM(mMVPMatrix,0,mVMatrix,0,mMMatrix,0);
        Matrix.multiplyMM(mMVPMatrix, 0, mProjMatrix, 0, mMVPMatrix, 0);

        // Copy the MVP matrix into the program

        GLES20.glUniformMatrix4fv(muMVPMatrixHandle,1,false,mMVPMatrix,0);

        // Draw the picture

        GLES20.glDrawArrays(GLES20.GL_TRIANGLES,0,3);
        if ( GLES20.GL_NO_ERROR != GLES20.glGetError() ) throw new RuntimeException("onDrawFrame(drawArrays)");
    }

    /* -------------------------------------------------------------
     * Private Attribute Definition Area
     * ------------------------------------------------------------- */

    private Context mContext;

    // Triangle to simulate cube data.

    private final float[] mCubeData = { // X, Y, Z, U, V
            -1.0f, -0.5f, 0, -0.5f,  0.0f,
            1.0f, -0.5f, 0,  1.5f, -0.0f,
            0.0f, 1.11803399f, 0, 0.5f, 1.61803399f };

    // Allocated program memory that changes for painting

    private FloatBuffer mCubeVertices;

    // Vertex Shader

    private final String mVertexShader =
            "uniform   mat4 uMVPMatrix;\n"                +
                    "attribute vec4 aPosition;\n"                 +
                    "attribute vec2 aTextureCoord;\n"             +
                    "varying   vec2 vTextureCoord;\n"             +
                    "void main() {\n"                             +
                    "  gl_Position   = uMVPMatrix * aPosition;\n" +
                    "  vTextureCoord = aTextureCoord;\n"          +
                    "}\n";

    // Fragment Shader

    private final String mFragmentShader =
            "precision mediump float;\n"                            +
                    "varying vec2 vTextureCoord;\n"                         +
                    "uniform sampler2D mTexture;\n"                         +
                    "void main() {\n"                                       +
                    "  gl_FragColor = texture2D(sTexture,vTextureCoord);\n" +
                    "}\n";

    // Various matrices

    private float[] mMVPMatrix  = new float[16];
    private float[] mProjMatrix = new float[16];
    private float[] mMMatrix    = new float[16];
    private float[] mVMatrix    = new float[16];

    // Various Program Handles

    private int mProgram;
    private int mTextureID;

    private int muMVPMatrixHandle;
    private int maPositionHandle;
    private int maTextureHandle;

    private static String TAG = "Cube Test";

    /* -------------------------------------------------------------
     * Singular constructor
     * ------------------------------------------------------------- */

    public TestCube(Context context) {

        mContext = context;
        mCubeVertices = ByteBuffer.allocateDirect(mCubeData.length * FLOAT_SIZE_BYTES).order(ByteOrder.nativeOrder()).asFloatBuffer();
        mCubeVertices.put(mCubeData).position(0);
    }

    /* -------------------------------------------------------------
     * Surfaced Changed Callback
     * ------------------------------------------------------------- */

    public void onSurfaceChanged(GL10 glUnused,int width,int height) {
        GLES20.glViewport(0,0,width,height);
        float ratio = (float) width / height;
        Matrix.frustumM(mProjMatrix,0,-ratio,ratio,-1,1,3,7);
    }

    /* -------------------------------------------------------------
     * Surface Created Callback
     * ------------------------------------------------------------- */

    public void onSurfaceCreated(GL10 glUnused,EGLConfig config) {

        int[] statusCode = new int[1];

        // Create the vertex shader

        int vertexShader = GLES20.glCreateShader(GLES20.GL_VERTEX_SHADER);

        if ( 0 == vertexShader ) throw new RuntimeException("glCreateShader(GL_VERTEX_SHADER) failed\n");

        GLES20.glShaderSource(vertexShader,mVertexShader);
        GLES20.glCompileShader(vertexShader);
        GLES20.glGetShaderiv(vertexShader,GLES20.GL_COMPILE_STATUS,statusCode,0);

        if ( 0 == statusCode[0] ) {
            GLES20.glDeleteShader(vertexShader);
            throw new RuntimeException("glCompileShader(vertexShader)");
        }

        // Create the pixel shader

        int pixelShader = GLES20.glCreateShader(GLES20.GL_FRAGMENT_SHADER);

        if ( 0 == pixelShader ) throw new RuntimeException("glCreateShader(GL_FRAGMENT_SHADER) failed");

        GLES20.glShaderSource(pixelShader,mFragmentShader);
        GLES20.glCompileShader(pixelShader);
        GLES20.glGetShaderiv(pixelShader,GLES20.GL_COMPILE_STATUS,statusCode,0);

        if ( 0 == statusCode[0] ) {
            GLES20.glDeleteShader(vertexShader);
            GLES20.glDeleteShader(pixelShader);
            throw new RuntimeException("glCompileShader(pixelShader)");
        }

        // Create the shader program (this has a single program)

        int program = GLES20.glCreateProgram();

        if ( 0 != program ) {
            GLES20.glAttachShader(program,vertexShader);
            if ( GLES20.GL_NO_ERROR != GLES20.glGetError() ) throw new RuntimeException("glAttachShader; glError: " + GLES20.glGetError());

            GLES20.glAttachShader(program,pixelShader);
            if ( GLES20.GL_NO_ERROR != GLES20.glGetError() ) throw new RuntimeException("glAttachShader; glError: " + GLES20.glGetError());

            GLES20.glLinkProgram(program);
            int[] linkStatus = new int[1];
            GLES20.glGetProgramiv(program,GLES20.GL_LINK_STATUS,linkStatus,0);
            if ( linkStatus[0] != GLES20.GL_TRUE ) {
                GLES20.glDeleteProgram(program);
                program = 0;
                throw new RuntimeException("glLinkProgram: glError");
            }
        }

        // Get the attribute handles

        maPositionHandle = GLES20.glGetAttribLocation(mProgram,"aPosition");
        if ( GLES20.GL_NO_ERROR != GLES20.glGetError() || -1 == maPositionHandle ) throw new RuntimeException("getAttributeLocation(aPosition)");

        maTextureHandle = GLES20.glGetAttribLocation(mProgram,"aTexutreCoord");
        if ( GLES20.GL_NO_ERROR != GLES20.glGetError() || -1 == maTextureHandle ) throw new RuntimeException("getAttributeLocation(aTextureCoord)");

        muMVPMatrixHandle = GLES20.glGetUniformLocation(mProgram,"uMVPMatrix");
        if ( GLES20.GL_NO_ERROR != GLES20.glGetError() || -1 == muMVPMatrixHandle ) throw new RuntimeException("getUniformLocation(uMVPMatrix)");

        // Create the texture

        int[] textures = new int[1];
        GLES20.glGenTextures(1,textures,0);

        mTextureID = textures[0];

        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mTextureID);

        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_NEAREST);
        GLES20.glTexParameterf(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_REPEAT);

        InputStream is = mContext.getResources().openRawResource(R.raw.robot);

        Bitmap bitmap;

        try {
            bitmap = BitmapFactory.decodeStream(is);
        } finally {
            try {
                is.close();
            } catch (IOException e) {
                // Ignore.
            }
        }

        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
        bitmap.recycle();

        Matrix.setLookAtM(mVMatrix, 0, 0, 0, -5, 0f, 0f, 0f, 0f, 1.0f, 0.0f);
    }

    private static final int FLOAT_SIZE_BYTES  = 4;
    private static final int DATA_STRIDE_BYTES = 5 * FLOAT_SIZE_BYTES;
    private static final int VERTICES_OFFSET   = 0;
    private static final int UV_OFFSET         = 3;

}
