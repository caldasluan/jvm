package input.arrays;

// compile with "javac -source 8 -target 8 input/arrays/multia.java"

public class multia {
  public static void main(String[] args) {
    multia[][] m = new multia[2][3];
    m[0][0] = new multia();
    multia[] m2 = new multia[0];
    System.out.println(m2.length);
  }
}
