package input.joga;

public class joga {

  public static void teste() throws Exception
  {
    throw new Exception();
  }
  public static void main(String[] args) {
    try {
      teste();
    } catch (Exception e) {}
  }
}
