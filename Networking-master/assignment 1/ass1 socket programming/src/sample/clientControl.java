package sample;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class clientControl {

    public static BufferedReader br;
    public static PrintWriter pr;
    public Stage connectionWindow;


    public void setConnectionWindow(Stage stage) {
        this.connectionWindow = stage;
    }


    public client cl;
    public void setClient(client c)
    {
        this.cl=c;
    }
    public static Socket socket;
    public int port;
    public String ip;
    public int studentID;

    @FXML
    private TextField IP;

    @FXML
    private TextField SID;

    @FXML
    private TextField PORT;

    @FXML
    private Button connect;

    @FXML
    void connectToServer(ActionEvent event) {
        try {
            this.ip = IP.getText();
            this.studentID = Integer.parseInt(SID.getText());
            cl.studentID=SID.getText();
            this.port = Integer.parseInt(PORT.getText());
            socket = new Socket(ip, port);
            br=new BufferedReader(new InputStreamReader(socket.getInputStream()));
            pr=new PrintWriter(socket.getOutputStream());
            pr.println(studentID);
            pr.flush();
            System.out.println("sent sid");
            connectionWindow.close();
            clientIsConnected();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public void clientIsConnected()
    {
        try {
            String name = br.readLine();
            String st = br.readLine();
            String et = br.readLine();
            int bck = Integer.parseInt(br.readLine());
            client.eI = new examInfo(name, st, et, bck);
            System.out.println(name+" "+st+" "+et+" "+bck);
            cl.examRunningWindow();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }



}


