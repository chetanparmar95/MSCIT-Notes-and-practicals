import java.io.*;
import java.net.*;
class Server
{
    public static void main(String args[]) throws Exception
    {
        ServerSocket ss=new ServerSocket(4722);
        System.out.println("Server Started.......");
        Socket s1 = ss.accept();
        System.out.println("First client connected......");
        BufferedReader br1 = new BufferedReader(new InputStreamReader
                (s1.getInputStream()));
        PrintStream ps1 = new PrintStream(s1.getOutputStream());
        ps1.println("Welcome client 1..... Enter commit or abort to proceed : ");
        ps1.flush();
        Socket s2 = ss.accept();
        System.out.println("2nd client connected ....");
        BufferedReader br2 = new BufferedReader(new InputStreamReader
                (s2.getInputStream()));
        PrintStream ps2 = new PrintStream(s2.getOutputStream());
        ps2.println("Welcome client 2..... Enter commit or abort to proceed : ");
        ps2.flush();
        String str1 = br1.readLine();
        String str2 = br2.readLine();
        if(str1.equalsIgnoreCase("commit") && str2.equalsIgnoreCase("commit"))
        {
            System.out.println("1st client said : " + str1 );
            System.out.println("2nd client said : " + str2 );
            System.out.println("Result : doCommit");
            ps1.println("Result : doCommit");
            ps1.flush();
            ps2.println("Result : doCommit");
            ps2.flush();
        }
        else
        {
            System.out.println("1st client said : " + str1 );
            System.out.println("2nd client said : " + str2 );
            System.out.println("Result : doAbort");
            ps1.println("Result : doAbort");
            ps1.flush();
            ps2.println("Result : doAbort");
            ps2.flush();
        }
    }
}
