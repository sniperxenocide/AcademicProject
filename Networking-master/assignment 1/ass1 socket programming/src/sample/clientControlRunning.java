package sample;



import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.stage.DirectoryChooser;
import javafx.stage.Stage;

import java.io.*;
import java.net.Socket;
import java.net.URL;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.ResourceBundle;
import java.util.concurrent.TimeUnit;

public class clientControlRunning implements Initializable{

    public Stage runningWindow;
    public void setRunningWindow(Stage stage){this.runningWindow=stage;}

    public client cl;
    public void setClient(client c)
    {
        this.cl=c;
    }

    @FXML
    private Label nameSet;

    @FXML
    private Label stSet;

    @FXML
    private Label stID;

    @FXML
    private Label etSet;

    @FXML
    private Label bckSet;

    @FXML
    private Label ctSet;

    @FXML
    private Label timeLeft;

    @FXML
    private Button Choose;

    @FXML
    void chooseFolder(ActionEvent event) throws IOException {
        Stage stg=new Stage();
        DirectoryChooser dc=new DirectoryChooser();
        dc.setTitle("Choose Destination Folder");
        File f=dc.showDialog(stg);
        String s=f.getAbsolutePath()+"/"+client.studentID+".doc";
        System.out.println(s);
        f=new File(s);
        if(f.exists()==false) {f.createNewFile();}
        client.examScript=f;
    }


    @Override
    public void initialize(URL location, ResourceBundle resources) {

        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                nameSet.setText(client.eI.name);
                stID.setText(client.studentID);
                stSet.setText(fixTime(client.eI.startTime).toString());
                etSet.setText(fixTime(client.eI.endTime).toString());
                Integer i = client.eI.interval;
                bckSet.setText(i.toString() + " Second");
                ctSet.setText(new Date().toString());
            }
        });
        Thread s=new Thread(new Runnable() {
            @Override
            public void run() {
                examStarted();
            }
        });s.start();


    }

    public void examStarted()
    {

        Thread receiveQuestion=new Thread(new Runnable() {            /////question receive
            @Override
            public void run() {
                //code here
                System.out.println("Awaiting Question");
                client.DownloadFile(client.examScript,clientControl.socket,clientControl.br);
            }
        });receiveQuestion.start();

        Thread sendBackup=new Thread(new Runnable() {          ///send backup file
            @Override
            public void run() {
                //code here
                try {
                    Date st=fixTime(client.eI.startTime);
                    Date et=fixTime(client.eI.endTime);
                    while (true)
                    {
                        Date t=new Date();
                        if(t.compareTo(st)==1 && t.compareTo(et)==-1)
                        {
                            TimeUnit.SECONDS.sleep(client.eI.interval);
                            client.SendFile(client.examScript,clientControl.socket,clientControl.pr);
                        }
                        if(t.compareTo(et)==1) break;
                    }
                }
                catch (Exception e){e.printStackTrace();}

            }
        });sendBackup.start();




        Thread startMsg=new Thread(new Runnable() {
            @Override
            public void run() {

                Date st=fixTime(client.eI.startTime);
                while (true)
                {
                    try {
                        Date t = new Date();
                        //System.out.println(t.compareTo(st));
                        if (t.compareTo(st) == 1) {
                            System.out.println("Exam Started. Check Your Exam Script");
                            /*Platform.runLater(new Runnable() {
                                @Override
                                public void run() {
                                    try {
                                        cl.examStartedWindow();
                                    }
                                    catch (Exception e){e.printStackTrace();}

                                }
                            });*/
                            //cl.examStartedWindow();
                            break;
                        }
                    }
                    catch (Exception e){e.printStackTrace();}
                }
            }
        }); startMsg.start();




        Thread sendWarning=new Thread(new Runnable() {        ///warning remainder
            @Override
            public void run() {
                //code here
                Date st=fixTime(client.eI.startTime);
                Date et=fixTime(client.eI.endTime);
                try {
                    while (true)
                    {
                        Date t=new Date();
                        if(t.compareTo(st)==1 && t.compareTo(et)==-1)
                        {
                            TimeUnit.MINUTES.sleep(5);
                            long i=(et.getTime()-t.getTime())/60000;
                            System.out.println(i+" minutes left");
                        }
                        if(t.compareTo(et)==1) break;
                    }
                }
                catch (Exception e) {e.printStackTrace();}

            }
        });//sendWarning.start();





        Thread finishMsg=new Thread(new Runnable() {
            @Override
            public void run() {

                Date et=fixTime(client.eI.endTime);
                while (true)                                   /////exam finished
                {
                    try {
                        Date t = new Date();
                        if (t.compareTo(et) == 1) {
                            System.out.println("Exam Finished. Stop Writting");
                            client.SendFile(client.examScript, clientControl.socket, clientControl.pr);
                            //cl.ExamEndWindow();
                            break;
                        }
                    }
                    catch (Exception e){e.printStackTrace();}
                }
            }
        }); finishMsg.start();


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

