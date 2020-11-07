package zzz;

import java.util.Scanner;
import zzz.pacote.Parent;

// compile with "javac -source 8 -target 8 zzz/MainAct.java"

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

		int i = 1;
		a += i;
		c += i;
		d += i;
		e += i;

		int shiftar = 80, neg = -300;

		shiftar = shiftar >> 32;
		System.out.println(shiftar);
		neg = neg >> 8;
		System.out.println(neg);

		int[] array = new int[5];
		char[][] multi = new char[8][4];
		Helper[] test = new Helper[2];
		multi[2][3] = 'a';

		a /= 3 + array[2];
		

		Runner runner = new MainAct();
		runner.run();
		MainAct ma = (MainAct)runner;
		ma.nop();

		MainAct.sTeste(3l);

		a += putz.HelperCode + test[0].HelperCode;

		System.out.print("Kek");
		System.out.println(" SeiLa2");
	}

	public static void sTeste(long a) {}

	public void nop() {}
	public void pon() {}

	private class Helper
	{
		public int HelperCode;
	}
}
