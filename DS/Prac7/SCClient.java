import java.io.*;
import java.net.*;
public class SCClient
{
    public static void main(String args[])throws Exception
    {
        InetAddress lclhost;
        lclhost=InetAddress.getLocalHost();
        while(true)
        {
            Client cntl=new Client(lclhost);
            cntl.sendPort(9001);
            cntl.sendData();
        }
    }
}
class Client
{
    InetAddress lclhost;
    int senport;
    Client(InetAddress lclhost)
    {
        this.lclhost=lclhost;
    }
    void sendPort(int senport)
    {
        this.senport=senport;
    }
    void sendData()throws Exception
    {
        DatagramPacket dp;
        DatagramSocket ds;
        BufferedReader br;
        br=new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter the data");
        String str=br.readLine();
        ds = new DatagramSocket(senport);
        dp = new DatagramPacket(str.getBytes(),str.length(),lclhost,senport-
                1000);
        ds.send(dp);
        ds.close();
    }
}
