package input.strings;

// compile with "javac -source 8 -target 8 input/strings/stringTest.java"

public class stringTest {
  public static void main(String[] args) {
    System.out.println(args.length);
    if(args.length > 0)
      System.out.println(args[0].length());

    for(int i = 0; i < args.length; i++)
      System.out.println(args[i]);
  }
  
}
