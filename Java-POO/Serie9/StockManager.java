import java.util.List;
import java.util.ArrayList;
import java.time.LocalDate;
import java.util.stream.*;
import java.util.*;

record Patient(String name, LocalDate birthday, List<Consultation> consults) {}
record Consultation(LocalDate date, int duration) {}

public class StockManager {
    private static List<Patient> origin = new ArrayList<>();

    private static List<String> name(List<Patient> origin){
        return origin.stream()
            .flatMap( (Patient p) -> Stream.of(p.name())).collect(Collectors.toList());
    }

    private static List<String> bornIn2000(List<Patient> origin){
        return origin.stream()
            .filter( (Patient pe) -> pe.birthday().getYear() == 2000 ).flatMap( (Patient p) -> Stream.of(p.name() ) ).collect(Collectors.toList());
    }

    private static List<Patient> threeConsultsOrMore(List<Patient> origin){
        return origin.stream()
            .filter( (Patient p) -> p.consults().size() >= 3 )
            .collect(Collectors.toList());
    }

    private static List<Consultation> allConsults(List<Patient> origin){
        return origin.stream()
            .flatMap( (Patient p) -> p.consults().stream() )
            .collect(Collectors.toList());
    }

    private static int totalDurationFromAllConsults(List<Patient> origin){
        List<Consultation> allConsults = allConsults(origin);
        return allConsults.stream()
            .mapToInt( (Consultation p) -> p.duration() )
            .sum();
    }

    private static Double averageDurationOfAConsult(List<Patient> origin){
        List<Consultation> allConsults = allConsults(origin);
        return allConsults.stream()
            .mapToInt( (Consultation p) -> p.duration() )
            .average().orElse(-1);
    }

    private static Map<Character,List<Patient>> groupPatientsByName(List<Patient> origin){
        return origin.stream()
            .collect(Collectors.groupingBy( p -> p.name().charAt(0) ));
    }

    private static Map<Boolean,List<Patient>> partitionPatientsBornBeforeOrAfter2000(List<Patient> origin){
        return origin.stream()
            .collect(Collectors.partitioningBy( (Patient p) -> p.birthday().getYear() < 2000 ));                
    }

    public static void main(String... args) {
        Patient persoA = new Patient("Marc Us", LocalDate.of(1998,10,10), List.of(new Consultation(LocalDate.now().plusDays(1), 30))); 
        origin.add(persoA);
        Patient persoB = new Patient("Marc Assin", LocalDate.of(2000,10,10), List.of(new Consultation(LocalDate.now().plusDays(1), 30)));
        origin.add(persoB);
        Patient persoC = new Patient("Marc Enciel", LocalDate.of(2000,10,10), List.of(new Consultation(LocalDate.now().plusDays(1), 30)));
        origin.add(persoC);
        Patient persoD = new Patient("Marc Eau", LocalDate.of(2001,10,10), List.of(new Consultation(LocalDate.now().plusDays(1), 30)));
        origin.add(persoD);
        Patient persoE = new Patient("Antwan", LocalDate.of(1999,11,8), List.of(new Consultation(LocalDate.now().plusDays(1), 30),new Consultation(LocalDate.now().plusDays(1), 30),new Consultation(LocalDate.now().plusDays(1), 30)));
        origin.add(persoE);

        //List<String> kek = name(origin);
        //kek.forEach(value -> System.out.println(value));

        //List<String> kek2 = bornIn2000(origin);
        //kek2.forEach(value -> System.out.println(value));

        //List<Patient> kek3 = threeConsultsOrMore(origin);
        //kek3.forEach(value -> System.out.println(value));

        //List<Consultation> kek4 = allConsults(origin);
        //kek4.forEach(value -> System.out.println(value));

        //int kek5 = totalDurationFromAllConsults(origin);
        //System.out.println(kek5);
    
        //Double kek6 = averageDurationOfAConsult(origin);
        //System.out.println(kek6);

        //Map<Character,List<Patient>> kek7 = groupPatientsByName(origin);
        //System.out.println(kek7);

        Map<Boolean,List<Patient>> kek8 = partitionPatientsBornBeforeOrAfter2000(origin);
        System.out.println(kek8);

    }
}