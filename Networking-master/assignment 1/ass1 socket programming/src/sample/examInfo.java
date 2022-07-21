package sample;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class examInfo {

    public String startTime;
    public String endTime;
    public int interval;
    public String name;

    examInfo(String en,String st,String et,int it)
    {
        this.startTime=st;
        this.endTime=et;
        this.name=en;
        this.interval=it;
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
