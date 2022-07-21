package sample;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;


public class server {

    public static void main(String[] args) {
        try {
            ServerSocket srskt=new ServerSocket(5555);
            System.out.println("server has been started at 5555 port");

            while(true)
            {
                Socket s=srskt.accept();
                System.out.println("client connected "+s+" "+s.getInetAddress().toString());
                ClientThread ct=new ClientThread(s);
                Thread t=new Thread(ct);
                t.start();
                //System.out.println("main thread started");
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}

class ClientThread implements Runnable
{
    private Socket s;
    private InputStream is;
    private OutputStream os;
    ClientThread(Socket skt)  {
        this.s=skt;
       try
       {
           this.is=this.s.getInputStream();
           this.os=this.s.getOutputStream();
       }
       catch (Exception e)
       {
           e.printStackTrace();
       }
    }

    @Override
    public void run() {
        BufferedReader br=new BufferedReader(new InputStreamReader(is));
        PrintWriter pr=new PrintWriter(os);
        Scanner input=new Scanner(System.in);
        System.out.println(br+" "+pr);
        //System.out.println("before sec thread");


        Thread t1=new Thread(new Runnable() {   ////read thread
            @Override
            public void run() {
                //System.out.println("inside read thread");
                try {
                    while (true)
                    {
                        //System.out.println(br);
                        String rcvMsg=br.readLine();
                        System.out.println("Client: " + rcvMsg);
                    }
                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        }); t1.start();

        Thread t2=new Thread(new Runnable() {   ////write Thread
            @Override
            public void run() {
                //System.out.println("inside write thread");
                try {
                    while (true)
                    {
                        //System.out.print("Server: ");
                        String sentMsg=input.nextLine();
                        pr.println(sentMsg);
                        pr.flush();
                    }

                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        }); t2.start();
        //System.out.println("after thread");

    }

    void SendFile(File f,Socket s,PrintWriter pr)
    {
        try
        {
            FileInputStream fis=new FileInputStream(f);
            BufferedInputStream bis=new BufferedInputStream(fis);
            OutputStream os=s.getOutputStream();

            int size=10000;
            long fileLength=f.length();
            long sent=0;
            byte[] buffer=new  byte[size];
            pr.println(f.getName());
            pr.flush();
            pr.println(String.valueOf(fileLength));
            pr.flush();

            while (sent!=fileLength)
            {
                if(fileLength - sent >= size)
                    sent += size;
                else{
                    size = (int)(fileLength - sent);
                    sent = fileLength;
                }
                bis.read(buffer, 0, size);
                os.write(buffer);
            }
            os.flush();

        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    void DownloadFile(File f,Socket s,BufferedReader br)
    {
        try
        {
            String name=br.readLine();
            long fileLength=Integer.parseInt(br.readLine());

            byte[] buffer = new byte[10000];

            FileOutputStream fos = new FileOutputStream(f);
            BufferedOutputStream bos = new BufferedOutputStream(fos);
            InputStream is = s.getInputStream();

            int bytesRead = 0;
            int total=0;			//how many bytes read

            while(total!=fileLength)	//loop is continued until received byte=totalfilesize
            {
                bytesRead=is.read(buffer);
                total+=bytesRead;
                bos.write(buffer, 0, bytesRead);
            }
            bos.flush();
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
