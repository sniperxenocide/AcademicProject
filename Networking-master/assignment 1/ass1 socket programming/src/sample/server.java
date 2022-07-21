package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;

public class server extends Application {

    public static HashMap<String,Student> mp=new HashMap<String,Student>();
    public static examInfo eI;
    public Stage configerServer;
    public static File question=new File("src/sample/question/q.doc");



    @Override
    public void start(Stage primaryStage) throws Exception{
        configerServer=primaryStage;
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("server1.fxml"));
        Parent root=loader.load();
        System.out.println("loaded");

        serverControl cn=loader.getController();
        cn.setStage(configerServer);
        cn.setServer(this);

        Scene scene=new Scene(root, 600, 400);
        primaryStage.setTitle("Server");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void SendFile(File source,Socket s,PrintWriter pr)
    {
        try
        {
            FileInputStream fis=new FileInputStream(source);
            BufferedInputStream bis=new BufferedInputStream(fis);
            OutputStream os=s.getOutputStream();

            int size=10000;
            long fileLength=source.length();
            long sent=0;
            byte[] buffer=new  byte[size];
            //pr.println(f.getName());
            //pr.flush();
            pr.println(String.valueOf(fileLength));
            pr.flush();

            while (sent<=fileLength)
            {
                /*if(fileLength - sent >= size)
                    sent += size;
                else{
                    size = (int)(fileLength - sent);
                    sent += size;
                }*/
                sent+=size;
                bis.read(buffer, 0, size);
                os.write(buffer);
                System.out.println(buffer);
            }
            os.flush();
            System.out.println("File sent");

        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public static void DownloadFile(File destination,Socket s,BufferedReader br)
    {
        try
        {
            //String name=br.readLine();
            long fileLength=Integer.parseInt(br.readLine());

            byte[] buffer = new byte[10000];

            FileOutputStream fos = new FileOutputStream(destination);
            BufferedOutputStream bos = new BufferedOutputStream(fos);
            InputStream is = s.getInputStream();

            int bytesRead = 0;
            int total=0;			//how many bytes read

            while(total<=fileLength)	//loop is continued until received byte=totalfilesize
            {
                bytesRead=is.read(buffer);
                total+=bytesRead;
                bos.write(buffer, 0, bytesRead);
                System.out.println(buffer);
            }
            bos.flush();
            System.out.println("File received");
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }


    public static void main(String[] args) {
        launch(args);
    }
}
