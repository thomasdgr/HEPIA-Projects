use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::fmt;

use crate::routes::Routes;

#[derive(Debug,Clone)]
pub struct Stoptimes {
    pub trip_id: String,
    pub arrival_time: String,
    pub departure_time: String,
    pub stop_id: String,
    pub stop_sequence: String,
    pub pickup_type: String,
    pub drop_off_type: String
}

impl From<&Vec<String>> for Stoptimes {
    fn from(v: &Vec<String>) -> Self {
        Stoptimes { 
            trip_id:v[0].to_owned(),
            arrival_time:v[1].to_owned(),
            departure_time:v[2].to_owned(),
            stop_id:v[3].to_owned(),
            stop_sequence:v[4].to_owned(),
            pickup_type:v[5].to_owned(),
            drop_off_type:v[6].to_owned() }
    }
}

impl fmt::Display for Stoptimes {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "\"{}\",\"{}\",\"{}\",\"{}\",{},{},{}", 
            self.trip_id, 
            self.arrival_time, 
            self.departure_time, 
            self.stop_id, 
            self.stop_sequence, 
            self.pickup_type, 
            self.drop_off_type)
    }
}

impl PartialEq for Stoptimes {
    fn eq(&self, other: &Stoptimes) -> bool {
        self.trip_id.eq(&other.trip_id) && 
        self.arrival_time.eq(&other.arrival_time) &&
        self.departure_time.eq(&other.departure_time) &&
        self.stop_id.eq(&other.stop_id) &&
        self.stop_sequence.eq(&other.stop_sequence) &&
        self.pickup_type.eq(&other.pickup_type) &&
        self.drop_off_type.eq(&other.drop_off_type)
    }
}

impl Stoptimes {
    /// Return an option on a vector of Stoptimes created from a file and a vector of Routes
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Stoptimes::*;
    /// 
    ///let stop_times = Stoptimes::read_stop_times(&routes_vec, "./tpg_input/stop_times.txt".to_string()).unwrap();
    ///
    ///let header = "trip_id,arrival_time,departure_time,stop_id,stop_sequence,pickup_type,drop_off_type";
    ///write_content(&stop_times, "./tpg_output/stop_times.txt", header);
    /// ```
    pub fn read_stop_times(routes: &[Routes], path: String) -> Option<Vec<Stoptimes>> {
        let reader = BufReader::new(File::open(path).ok()?);
        let mut stop_times = reader.lines()
            .into_iter()
            .flat_map(|line| {
                let v = line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                routes.iter()
                    .filter(|route| v[0].split('.')
                        .any(|x| x == &(route.route_id)[..]))
                    .map(|_route_id| Stoptimes::from(&v))
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>();
        stop_times.dedup();
        Some(stop_times)
    }
    
    /// Return an option on a vector of Stoptimes created from a file with data that has already been filtereds
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Stoptimes::*;
    /// 
    ///let stop_times = Stoptimes::read_filtered_stop_times("./tpg_input/stop_times.txt".to_string()).unwrap();
    /// ```
    pub fn read_filtered_stop_times(path: String) -> Option<Vec<Stoptimes>> {
        let mut stop_times: Vec<Stoptimes> = Vec::new();
        let mut reader = BufReader::new(File::open(path).ok()?);
        let _ = reader.read_line(&mut String::new());
        reader.lines()
            .map(|line| { 
                stop_times.push(Stoptimes::from(&line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>()));
            })
            .for_each(|_| {});
        Some(stop_times)
    }
}