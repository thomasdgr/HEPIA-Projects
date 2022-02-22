import java.util.List;
import java.util.Random;
import java.util.stream.*;
import java.util.*;
import java.util.stream.Collectors;
import ch.hepia.devices.database.*;
import ch.hepia.devices.status.*;
import ch.hepia.devices.device.*;

public class Main {
    public static void populate(Database db, int number){
        Stream.generate( StateDevice::random ).limit(number).forEach(db::add);
    }

    public static Map<Class<?>,List<Device>> partition(Database db){
        return db.devices().stream().collect(Collectors.groupingBy( (Device d) -> d.status().getClass() ));                
    }

    public static Map<Class<?>,List<Device>> stabilize(Database db){
        Map<Class<?>,List<Device>> part = partition(db);
        /*while (part.get(Status.Off.class).size() > 0 || part.get(Status.Err.class).size() > 0) {
            part.get(Status.Off.class).stream().peek( d -> d.start() );
            part.get(Status.class).stream().peek( d -> d.reboot() );
            part = partition(db);
        }*/
        return part;
    }
    
    public static void main(String[] args) {

        Database database = new InMemoryDatabase();
        populate(database, 5);
        //System.out.println(database.devices());

        Map<Class<?>,List<Device>> partitioning = partition(database);
        partitioning.forEach((key, value) -> System.out.println(key + ":" + value));

        //Map<Class<?>,List<Device>> stabilising = stabilize(database);
        //stabilising.forEach((key, value) -> System.out.println(key + ":" + value));
    }
}