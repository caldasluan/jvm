package input.mainArgs;

// compile with "javac -source 8 -target 8 input/mainArgs/MainArgs.java"

public class MainArgs {
  public static void main(String[] args) {
    for(int i = 0; i < args.length; i++)
      System.out.println(args[i]);
  }
}
