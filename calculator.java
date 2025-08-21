public class Calculator {

    public Calculator() { }

    public int add(int a, int b) {
        return a + b;
    }

    public int subtract(int a, int b) {
        return a - b;
    }

    public int multiply(int a, int b) {
        return a * b;
    }

    // Example where conflict could occur: change signature or return type differently on main and feature
    public double divide(int a, int b) {
        if (b == 0) throw new IllegalArgumentException("Division by zero");
        return (double) a / b;
    }
}

