import java.io.*;
import java.net.*;
import java.sql.*;
public class SCServer
{
public static void main(String args[])throws Exception
{
InetAddress lclhost;
lclhost=InetAddress.getLocalHost();
long maxtime,skewtime,datatime;
String maxtimestr,skewtimestr;
BufferedReader br;
ClntServer ser=new ClntServer(lclhost);
System.out.println("Enter the maximum time");
br = new BufferedReader(new InputStreamReader(System.in));
maxtimestr=br.readLine();
System.out.println("Enter the maximum skew time");
br = new BufferedReader(new InputStreamReader(System.in));
skewtimestr=br.readLine();
maxtime=Long.parseLong(maxtimestr);
skewtime=Long.parseLong(skewtimestr);
while(true)
{
datatime = System.currentTimeMillis();
long G = datatime-maxtime-skewtime;
System.out.println("G ="+G);
ser.setTimeStamp(new Timestamp(G));
ser.recPort(8001);
ser.recData();
}
}
}
class ClntServer
{
InetAddress lclhost;
int recport;
Timestamp obtmp;
ClntServer(InetAddress lclhost)
{
this.lclhost = lclhost;
}
void recPort(int recport)
{
this.recport = recport;
}
void setTimeStamp(Timestamp obtmp)
{
this.obtmp = obtmp;
}
void recData()throws Exception
{
String msgstr="";
DatagramSocket ds;
DatagramPacket dp;
BufferedReader br;
byte buf[] = new byte[256];
ds = new DatagramSocket(recport);
dp = new DatagramPacket(buf,buf.length);
ds.receive(dp);
ds.close();
msgstr = new String(dp.getData(),0,dp.getLength());
System.out.println(msgstr);
Timestamp obtmp = new Timestamp(Long.parseLong(msgstr));
if(this.obtmp.before(obtmp) == true)
{
System.out.println("The Message is accepted");
}
else
{
System.out.println("The Message is rejected");
}
}
}
