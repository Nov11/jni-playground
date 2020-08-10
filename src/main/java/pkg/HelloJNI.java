package pkg;

public class HelloJNI {  // Save as HelloJNI.java
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

    public native double[][] search(double[][] embedding);

    // Test Driver
    public static void main(String[] args) {
        HelloJNI helloJNI = new HelloJNI();
        helloJNI.sayHello();  // Create an instance and invoke the native method

        long ret = helloJNI.sumIntegers(1, 2);
        System.out.println(ret);

        String hello = helloJNI.sayHelloToMe("name", false);
        System.out.println(hello);
    }
}