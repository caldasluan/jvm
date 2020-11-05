package zzz;

import java.util.Scanner;
import zzz.pacote.Parent;

// compile with "javac -source 8 -target 8 MainAct.java"

public class MainAct extends Parent implements Runner {

	public static final int seiLa = 4123213;

	public final int teste = 3;

	private int timesRan;

	private static Helper putz;

	static {
		System.out.println("1");
	}

	public void run() {
		if (timesRan == maxTimesRan) {
			System.out.printf("Fim\n");
		} else {
			timesRan++;
			System.out.print("Run number " + timesRan + "\n");
			run();
			return;
		}
		putz = new Helper();
		putz.HelperCode = -timesRan;
	}
	
	public static void staticMethod()
	{
		System.out.println("3");
	}

	public static void main(String args[]) {
		int a = 2475558;
		float b = 2.14f;
		long c = 1000000000000L, d = 1000000000000L, e = 1000000000000L;

		Scanner scanner = new Scanner(System.in);
		int i = scanner.nextInt();
		a += i;
		c += i;
		d += i;
		e += i;
		scanner.close();

		int shiftar = 80, neg = -300;

		shiftar = shiftar >> 32;
		System.out.println(shiftar);
		neg = neg >> 8;
		System.out.println(neg);

		int[] array = new int[5];
		char[][] multi = new char[8][3];
		multi[2][3] = 'a';

		a /= 3 + array[2];
		

		Runner runner = new MainAct();
		runner.run();
		MainAct ma = (MainAct)runner;
		ma.nop();

		a += putz.HelperCode;

		System.out.print("Kek" + a + " : " + b + " rs " + (c + 2 * d + 3 * e) + "\n");
		System.out.println("SeiLa2" + (seiLa + a + i));
	}

	public void nop() {}
	public void pon() {}

	private class Helper
	{
		public int HelperCode;
	}
}
