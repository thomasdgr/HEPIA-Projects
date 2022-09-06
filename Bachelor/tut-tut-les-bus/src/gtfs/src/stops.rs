use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::fmt;
use std::collections::HashMap;

use crate::stop_times::{Stoptimes};

#[derive(Debug, Clone)]
pub struct Stops {
    pub stop_id: String,
    pub stop_name: String,
    pub stop_lat: String,
    pub stop_lon: String,
    pub location_type: String,
    pub parent_station: String,
    pub routes: String,
}

impl From<&Vec<String>> for Stops {
    fn from(v: &Vec<String>) -> Self {
        Stops { stop_id:v[0].to_owned(),
            stop_name:v[1].to_owned(),
            stop_lat:v[2].to_owned(),
            stop_lon:v[3].to_owned(),
            location_type:v[4].to_owned(),
            parent_station:v[5].to_owned(),
            routes:v[6].to_owned() }
    }
}

impl fmt::Display for Stops {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{},\"{}\",{},{},{},{},\"{}\"", 
            self.stop_id,
            self.stop_name, 
            self.stop_lat, 
            self.stop_lon, 
            self.location_type, 
            self.parent_station, 
            self.routes)
    }
}

// compare two Stops
impl PartialEq for Stops {
    fn eq(&self, other: &Stops) -> bool {
        self.stop_id.eq(&other.stop_id) && 
        self.stop_name.eq(&other.stop_name) &&
        self.stop_lat.eq(&other.stop_lat) &&
        self.stop_lon.eq(&other.stop_lon) &&
        self.location_type.eq(&other.location_type) &&
        self.parent_station.eq(&other.parent_station) &&
        self.routes.eq(&other.routes)
    }
}

impl Stops {
    /// Return an option on a vector of Stops created from a file and a vector of Stoptimes
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Stops::*;
    /// 
    ///let stops = Stops::read_stops(&stop_times_vec, "./tpg_input/stops.txt".to_string()).unwrap();
    ///
    ///let header = "stop_id,stop_name,stop_lat,stop_lon,location_type,parent_station,routes";
    ///write_content(&stops, "./tpg_output/stops.txt", header);
    /// ```
    pub fn read_stops(stop_times: &[Stoptimes], path: String) -> Option<Vec<Stops>> {
        let reader = BufReader::new(File::open(path).ok()?);
        let mut stops = reader.lines()
            .into_iter()
            .flat_map(|line| {
                let v = line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
            stop_times.iter()
                .filter(|stop_time| v[0] == stop_time.stop_id)
                .map(|_stop_id| Stops::from(&v))
                .collect::<Vec<_>>()})
        .collect::<Vec<_>>();
        stops.dedup();
        Some(stops)
    }
    
    /// Return an option on a vector of Stops created from a file with data that has already been filtered
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Stops::*;
    /// 
    ///let stops = Stops::read_filtered_stops("./tpg_input/stops.txt".to_string()).unwrap();
    /// ```
    pub fn read_filtered_stops(path: String) -> Option<Vec<Stops>> {
        let mut stops: Vec<Stops> = Vec::new();
        let mut reader = BufReader::new(File::open(path).unwrap());
        let _ = reader.read_line(&mut String::new());
        reader.lines()
            .map(|line| { 
                let v = line.unwrap()
                    .split(",\"")
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                let coords = v.get(1)
                    .unwrap()
                    .split(',')
                    .map(|word| word.to_string())
                    .collect::<Vec<_>>();            
                stops.push(Stops::from(&vec![v[0].to_owned(),
                    coords[0].to_owned(),
                    coords[1].to_owned(),
                    coords[2].to_owned(), 
                    coords[3].to_owned(),
                    coords[3].to_owned(),
                    v[2].to_owned()]));
            }).for_each(|_| {});        
        Some(stops)
    }

    /// Return a vector of Stops with unique ids from a vector of Stops
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Stops::*;
    /// 
    ///let stops = Stops::make_all_stops_unique(&stops_vec).unwrap();
    /// ```
    pub fn make_all_stops_unique(stops: &[Stops]) -> Vec<Stops> {
        let mut new_stops = Vec::new();
        let mut stop_id_set = HashMap::new();
        for s in stops.iter() {
            if !stop_id_set.contains_key(&s.stop_id) {
                new_stops.push(Stops::from(&vec![ format!("{}-1", s.stop_id.to_owned()), 
                    s.stop_name.to_owned(), 
                    s.stop_lat.to_owned(), 
                    s.stop_lon.to_owned(), 
                    s.location_type.to_owned(), 
                    s.parent_station.to_owned(), 
                    s.routes.to_owned()]));
                stop_id_set.insert(s.stop_id.to_owned(),1);
            } else {
                let stop_id_index = *stop_id_set.get(&s.stop_id).unwrap() + 1;
                new_stops.push(Stops::from(&vec![format!("{}-{}", s.stop_id.to_owned(),
                    stop_id_index), 
                    s.stop_name.to_owned(), 
                    s.stop_lat.to_owned(), 
                    s.stop_lon.to_owned(), 
                    s.location_type.to_owned(), 
                    s.parent_station.to_owned(), 
                    s.routes.to_owned()]));
                stop_id_set.insert(s.stop_id.to_owned(), stop_id_index);
            }
        }
        new_stops
    }
}
