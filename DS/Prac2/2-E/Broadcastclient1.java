import java.net.*;
import java.io.*;
public class Broadcastclient1
{
    public static final int PORT = 1234;
    public static void main(String args[])throws Exception
    {
        MulticastSocket socket;
        DatagramPacket packet;
        InetAddress address;
        // set the mulitcast address to your local subnet
        address = InetAddress.getByName("239.1.2.3");
        socket = new MulticastSocket(PORT);
        //join a Multicast group and wait for a message
        socket.joinGroup(address);
        byte[] data = new byte[100];
        packet = new DatagramPacket(data,data.length);
        for(;;)
        {
            // receive the packets
            socket.receive(packet);
            String str = new String(packet.getData());
            System.out.println("Message received from "+ packet.getAddress() + " Message is :"+str);
        }
    }
}
