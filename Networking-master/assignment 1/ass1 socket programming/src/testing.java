import java.io.File;
import java.io.FileOutputStream;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.TimeZone;
import java.util.Timer;

/**
 * Created by 13050 on 3/11/2017.
 */
public class testing {


    public static void main(String[] args) {
        try {

            Date t1=new Date();
            Date t2=fixTime("02:00:00");
            System.out.println(t1.getTime()-t2.getTime());


        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public static Date fixTime(String s)
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
