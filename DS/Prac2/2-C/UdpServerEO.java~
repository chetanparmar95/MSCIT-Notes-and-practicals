import java.io.*;
import java.net.*;
public class UdpServerEO
{
public static void main(String args[])
{
try
{
DatagramSocket ds = new DatagramSocket(3000); 
byte b[] = new byte[1024];
DatagramPacket dp = new DatagramPacket(b,b.length); 
ds.receive(dp);
String str = new String(dp.getData(),0,dp.getLength());
System.out.println(str);
int a= Integer.parseInt(str);
String s= new String();
if (a%2 == 0)
s = "NUMBER IS EVEN...";
else
s = "NUMBER IS ODD...";
byte b1[] = new byte[1024]; b1 = s.getBytes();
DatagramPacket dp1 = new
DatagramPacket(b1,b1.length,InetAddress.getLocalHost(),2000);
ds.send(dp1);
}
catch(Exception e)
{
e.printStackTrace();
}
}
}
