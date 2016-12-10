import java.io.*;
import java.net.*;
public class EchoServer implements Runnable
{
    Socket socket=null;
    static ServerSocket ss;
    EchoServer(Socket newSocket)
    {
        this.socket=newSocket;
    }
    public static void main(String args[]) throws IOException
    {
        ss=new ServerSocket(7000);
        System.out.println("Server Started");
        while(true)
        {
            Socket s = ss.accept();
            EchoServer es = new EchoServer(s);
            Thread t = new Thread(es);
            t.start();
        }
    }
    public void run()
    {
        try
        {
            BufferedReader in = new BufferedReader(new
                    InputStreamReader(socket.getInputStream()));
            while(true)
            {
                System.out.println(in.readLine());
            }
        }
        catch(Exception e){}
    }
}
