import java.rmi.*;
import java.io.*;
public class Clientconvert3
{
public static void main(String args[]) throws Exception
{
Interconvert3 h1 = (Interconvert3)Naming.lookup("Wrd");
BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
System.out.println("Enter a number : \t");
String no = br.readLine();
String ans = h1.convertDigit(no);
System.out.println("The WORD representation of the entered digit is : " +ans);
}
}
