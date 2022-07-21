package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.URL;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.ResourceBundle;


public class serverControl implements Initializable{
    server srv;
    Stage configServer;

    public void setStage(Stage stage) {
        this.configServer = stage;
    }

    public void setServer(server s)
    {
        this.srv=s;
    }

    private BufferedReader br;
    private PrintWriter pr;

    @FXML
    private TextField examName;

    @FXML
    private TextField startTime;

    @FXML
    private TextField endTime;

    @FXML
    private TextField backup;

    @FXML
    private Button setServer;

    @FXML
    void configerServer(ActionEvent event) {             ////set button

        String name=examName.getText();
        String st=startTime.getText();
        String et=endTime.getText();
        int bck=Integer.parseInt(backup.getText());
        server.eI=new examInfo(name,st,et,bck);
        configServer.close();

    }


    public void startServer(){
        try {
            ServerSocket srskt=new ServerSocket(5555);
            System.out.println("server has been started at 5555 port");
            String path="src/sample/examinees";
            File f=new File(path);
            f.mkdir();

            while(true)
            {
                try {
                    Socket s = srskt.accept();
                    System.out.println("client connected " + s);
                    br = new BufferedReader(new InputStreamReader(s.getInputStream()));
                    pr = new PrintWriter(s.getOutputStream());
                    int id = Integer.parseInt(br.readLine());
                    if(id<1305001 && id> 1305060)
                    {
                        s.close();
                        continue;
                    }
                    System.out.println("Student id: " + id);

                    path=path+"/"+Integer.toString(id)+".doc";
                    f=new File(path);
                    if(f.exists()==false) {f.createNewFile();}
                    //server.question=f;

                    activeClient ct = new activeClient(s,br,pr,f);
                    Thread t = new Thread(ct);

                    Student st=new Student(id,s,ct,path);
                    server.mp.put(st.ip, st);

                    pr.println(server.eI.name);
                    pr.flush();
                    pr.println(server.eI.startTime);
                    pr.flush();
                    pr.println(server.eI.endTime);
                    pr.flush();
                    pr.println(server.eI.interval);
                    pr.flush();

                    t.start();

                }
                catch (Exception e)
                {
                    e.printStackTrace();
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public void initialize(URL location, ResourceBundle resources) {
        Thread t=new Thread(new Runnable() {
            @Override
            public void run() {
                startServer();
            }
        }); t.start();

    }
}

class activeClient implements Runnable
{
    private Socket s;
    private InputStream is;
    private OutputStream os;
    public BufferedReader br;
    public PrintWriter pr;
    public File destination;
    activeClient(Socket skt,BufferedReader b,PrintWriter p,File f)  {
        this.s=skt;
        try
        {
            this.is=this.s.getInputStream();
            this.os=this.s.getOutputStream();
            this.br=b;
            this.pr=p;
            this.destination=f;
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    @Override
    public void run() {


        Thread sendQs=new Thread(new Runnable() {
            @Override
            public void run() {
                Date st=fixTime(server.eI.startTime);
                Date et=fixTime(server.eI.endTime);
                while (true)
                {
                    try {
                        Date t = new Date();
                        if (t.compareTo(st) == 1) {
                            //code for sending exam question
                            server.SendFile(server.question, s, pr);
                            break;
                        }
                    }
                    catch (Exception e){e.printStackTrace();}
                }
            }
        }) ;sendQs.start();


        Thread receiveBackup=new Thread(new Runnable() {
            @Override
            public void run() {
                //code for receiving backup
                server.DownloadFile(destination,s,br);
            }
        });receiveBackup.start();
        while (true)
        {
            int i=0;
        }
    }

    public Date fixTime(String s)
    {
        Date t=new Date();
        Date b=new Date();
        try {
            DateFormat dt=new SimpleDateFormat("HH:mm:ss");
            t=dt.parse(s);
            b.setHours(t.getHours());
            b.setMinutes(t.getMinutes());
            b.setSeconds(t.getSeconds());
        } catch (ParseException e) {
            e.printStackTrace();
        }
        return  b;
    }


}



