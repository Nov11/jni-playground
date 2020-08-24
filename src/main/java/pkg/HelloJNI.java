package pkg;

import org.slf4j.Logger;

import static org.slf4j.LoggerFactory.getLogger;

public class HelloJNI {  // Save as HelloJNI.java
    private static final Logger logger = getLogger(HelloJNI.class);

    static {
        System.loadLibrary("native"); // Load native library hello.dll (Windows) or libhello.so (Unixes)
        //  at runtime
        // This library contains a native method called sayHello()
    }

    // Declare an instance native method sayHello() which receives no parameter and returns void
    private native void sayHello();

    private native long sumIntegers(int first, int second);

    private native String sayHelloToMe(String name, boolean isFemale);

    public native UserData createUser(String name, double balance);

    public native String printUserData(UserData user);

    public native double[][][] search(double[][] embedding, int count);

    private static void showMatrix(double[][] input) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < input[i].length; j++) {
                logger.info("[{}, {}]  : {}", i, j, input[i][j]);
            }
        }
    }

    // Test Driver
    public static void main(String[] args) {
        HelloJNI helloJNI = new HelloJNI();
        helloJNI.sayHello();  // Create an instance and invoke the native method

        long ret = helloJNI.sumIntegers(1, 2);
        System.out.println(ret);

        String hello = helloJNI.sayHelloToMe("name", false);
        System.out.println(hello);

        double[][] input = new double[5][];
        for (int i = 0; i < 5; i++) {
            double[] tmp = new double[2];
            for (int j = 0; j < 2; j++) {
                tmp[j] = i + j + 1;
            }
            input[i] = tmp;
        }

        logger.info("inputs:model");
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 2; j++) {
                logger.info("[{}, {}] {}", i, j, input[i][j]);
            }
        }

        double[][][] output = helloJNI.search(input, 3);
        double[][] nearest = output[0];
        double[][] score = output[1];
        logger.info("nearest :");
        showMatrix(nearest);
        logger.info("score :");
        showMatrix(score);

    }
}