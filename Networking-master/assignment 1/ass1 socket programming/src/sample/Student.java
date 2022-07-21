package sample;


import java.net.Socket;

public class Student {
    public String ip;
    public int sid;
    public Socket s;
    public activeClient ct;
    public String backupFilePath;
    Student(int id,Socket s,activeClient ct,String p)
    {
        this.sid=id;
        this.s=s;
        this.ip=s.getInetAddress().toString();
        this.ct=ct;
        this.backupFilePath=p;
    }
}
