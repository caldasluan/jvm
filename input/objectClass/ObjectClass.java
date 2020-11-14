package input.objectClass;

// compile with "javac -source 8 -target 8 input/objectClass/ObjectClass.java"

public class ObjectClass {
  public static void main(String[] args) {
    ObjectClass o = new ObjectClass();
    ObjectClass o2 = new ObjectClass();
    System.out.println(o == o2);
  }
}
