package sample;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;


public class client {

    public static Socket skt=null;

    public static void main(String[] args) {
        try
        {
            skt=new Socket("localhost",5555);
            System.out.println("connected to server  " + skt);
            BufferedReader br= new BufferedReader(new InputStreamReader(skt.getInputStream()));
            PrintWriter pr= new PrintWriter(skt.getOutputStream());

            Scanner input =new Scanner(System.in);
            //System.out.println("before entering thread");


            Thread t1=new Thread(new Runnable() {     ////read thread
                @Override
                public void run() {
                    //System.out.println("inside read thread");
                    try {
                        while (true)
                        {
                            String rcvMsg=br.readLine();
                            System.out.println("Server: "+rcvMsg);
                        }
                    }
                    catch (Exception e)
                    {
                        e.printStackTrace();
                    }
                }
            }); t1.start();

            Thread t2=new Thread(new Runnable() {   ////writing thread
                @Override
                public void run() {
                    //System.out.println("inside write thread");
                    try {
                        while (true)
                        {
                            //System.out.print("Client: ");
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
            });
            t2.start();
            //System.out.println("after thread");
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}
