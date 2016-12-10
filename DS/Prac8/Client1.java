import java.io.*;
import java.net.*;
class Client1
{
    public static void main(String args[]) throws Exception
    {
        BufferedReader brd = new BufferedReader(new InputStreamReader(System.in));
        String serverMsg, clientMsg;
        Socket s=new Socket("localhost",4722);
        BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
        PrintStream ps = new PrintStream(s.getOutputStream());
        serverMsg = br.readLine();
        System.out.println(serverMsg);
        clientMsg = brd.readLine();
        ps.println(clientMsg);
        ps.flush();
        serverMsg = br.readLine();
        System.out.println(serverMsg);
    }
}
