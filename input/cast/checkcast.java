package input.cast;

public class checkcast {
  
  public static void main(String[] args) {
    Object c1 = new checkcast();
    Object c2 = ((checkcast)c1).new Teste();
    checkcast c3 = (checkcast)c2; // Deve dar erro
  }
  public class Teste{}
}
