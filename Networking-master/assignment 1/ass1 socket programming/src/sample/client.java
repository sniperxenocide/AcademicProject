package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.*;
import java.net.Socket;

public class client extends Application {
    Stage connectionWindow;
    public static examInfo eI;
    public static String studentID;
    public static File examScript=new File("src/default.doc");

    @Override
    public void start(Stage primaryStage) throws Exception{
        connectionWindow=primaryStage;
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("client1.fxml"));
        Parent root=loader.load();

        clientControl cn=loader.getController();
        cn.setClient(this);
        cn.setConnectionWindow(connectionWindow);

        Scene scene=new Scene(root, 600, 400);
        primaryStage.setTitle("Client Connection");
        primaryStage.setScene(scene);
        primaryStage.show();
    }


    public void examRunningWindow() throws Exception
    {
        Stage s=new Stage();
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("client2.fxml"));
        Parent root=loader.load();

        clientControlRunning cn=loader.getController();
        cn.setClient(this);
        cn.setRunningWindow(s);

        Scene scene=new Scene(root, 600, 400);
        s.setTitle("Exam Status");
        s.setScene(scene);
        s.show();
    }


    public void examStartedWindow() throws Exception
    {
        Stage s=new Stage();
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("exStarted.fxml"));
        Parent root=loader.load();

        /*clientControlRunning cn=loader.getController();
        cn.setClient(this);
        cn.setRunningWindow(s);*/

        Scene scene=new Scene(root, 600, 400);
        s.setTitle("Exam Started");
        s.setScene(scene);
        s.show();

    }

    public void WarningWindow() throws Exception
    {
        Stage s=new Stage();
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("Warning.fxml"));
        Parent root=loader.load();

        /*clientControlRunning cn=loader.getController();
        cn.setClient(this);
        cn.setRunningWindow(s);*/

        Scene scene=new Scene(root, 600, 400);
        s.setTitle("Warning");
        s.setScene(scene);
        s.show();
    }

    public void ExamEndWindow() throws Exception
    {
        Stage s=new Stage();
        FXMLLoader loader= new FXMLLoader();
        loader.setLocation(getClass().getResource("exFinished.fxml"));
        Parent root=loader.load();

        /*clientControlRunning cn=loader.getController();
        cn.setClient(this);
        cn.setRunningWindow(s);*/

        Scene scene=new Scene(root, 600, 400);
        s.setTitle("Exam Finished");
        s.setScene(scene);
        s.show();
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
                    sent = fileLength;
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

            System.out.println("Length: "+fileLength);

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
                System.out.println(buffer.toString());
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
