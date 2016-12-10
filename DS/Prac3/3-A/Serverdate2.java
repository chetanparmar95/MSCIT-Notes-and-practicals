import java.rmi.*;
import java.rmi.server.*;
import java.util.*;
public class Serverdate2 extends UnicastRemoteObject implements Interdate2
{
public Serverdate2() throws Exception
{
}
public String display() throws Exception
{
String str = "";
Date d = new Date();
str = d.toString();
return str;
}
public static void main(String args[]) throws Exception
{
Serverdate2 s1 = new Serverdate2();
Naming.bind("DS",s1);
System.out.println("Object registered.....");
}
}
