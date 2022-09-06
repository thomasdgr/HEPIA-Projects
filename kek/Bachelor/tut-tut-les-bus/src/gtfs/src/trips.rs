use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::collections::HashMap;
use std::fmt;

use crate::routes::Routes;
use crate::stop_times::Stoptimes;
use crate::stops::Stops;

#[derive(Debug, Clone)]
pub struct Trips {
    pub route_id: String,
    pub service_id: String,
    pub trip_id: String,
    pub trip_headsign: String,
    pub trip_short_name: String,
    pub direction_id: String,
    pub shape_id: String
}

impl From<&Vec<String>> for Trips {
    fn from(v: &Vec<String>) -> Self {
        Trips { 
            route_id:v[0].to_owned(),
            service_id:v[1].to_owned(),
            trip_id:v[2].to_owned(),
            trip_headsign:v[3].to_owned(),
            trip_short_name:v[4].to_owned(),
            direction_id:v[5].to_owned(),
            shape_id:v[6].to_owned() }
    }
}

impl fmt::Display for Trips {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // overwrite direction_id as A-B/Street expect it to be 1 or 0
        write!(f, "\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",{}", 
            self.route_id, 
            self.service_id, 
            self.trip_id, 
            self.trip_headsign,
            self.trip_short_name, 
            1, 
            self.shape_id)
    }
}

impl PartialEq for Trips {
    fn eq(&self, other: &Trips) -> bool {
        self.route_id.eq(&other.route_id) && 
        self.service_id.eq(&other.service_id) &&
        self.trip_id.eq(&other.trip_id) &&
        self.trip_headsign.eq(&other.trip_headsign) &&
        self.trip_short_name.eq(&other.trip_short_name) &&
        self.direction_id.eq(&other.direction_id) &&
        self.shape_id.eq(&other.shape_id)
    }
}


impl Trips {
    /// Return an option on a vector of Transfers created from a file and a vector of Routes
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Trips::*;
    /// 
    ///let trips = Trips::read_trips(&routes_vec, "./tpg_input/trips.txt".to_string()).unwrap();
    ///
    ///let header = "route_id,service_id,trip_id,trip_headsign,trip_short_name,direction_id,shape_id";
    ///write_content(&trips, "./tpg_output/trips.txt", header);
    /// ```
    pub fn read_trips(routes: &[Routes], path: String) -> Option<Vec<Trips>> {
        let reader = BufReader::new(File::open(path).ok()?);
        let mut trips = reader.lines()
            .flat_map(|line| {
                let v = line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                routes.iter()
                    .filter(|route| v[0].split('.')
                        .any(|x| x == &(route.route_id)[..]))
                    .map(|_route_id| Trips::from(&v))
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>();
        trips.dedup();
        // updating the shapes as the same trips should have the same shape
        for i in 0..trips.len() {
            for j in 0..trips.len() {
                if trips[i].route_id == trips[j].route_id &&
                   trips[i].trip_headsign == trips[j].trip_headsign && 
                   trips[i].trip_short_name == trips[j].trip_short_name &&
                   i != j {
                    trips[j].shape_id = (&trips[i].shape_id).to_string();
                }
            }
        }
        Some(trips)
    }
    
    /// Return an option on a vector of Transfers created from a file with data that has already been filtered
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Trips::*;
    /// 
    ///let trips = Trips::read_filtered_trips("./tpg_input/trips.txt".to_string()).unwrap();
    /// ```
    pub fn read_filtered_trips(path: String) -> Option<Vec<Trips>> {
        let mut reader = BufReader::new(File::open(path).ok()?);
        let _ = reader.read_line(&mut String::new());
        let trips = reader.lines()
            .map(|line| {
                Trips::from(&line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', "")).collect::<Vec<_>>())
        })
        .collect::<Vec<_>>();
        Some(trips)
    }
    
    /// Return an option on a vector of Transfers created from a file with data that has already been filtered
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Trips::*;
    /// 
    ///let trips = Trips::read_filtered_trips("./tpg_input/trips.txt".to_string()).unwrap();
    ///
    ///let new_trips = Trips::sort_trips(trips, &routes, &stops);
    ///
    ///let header_trips = "route_id,service_id,trip_id,trip_headsign,trip_short_name,direction_id,shape_id";
    ///write_content(&new_trips.0, "./tpg_output/trips.txt", header_trips);
    /// 
    ///let header_stop_times = "trip_id,arrival_time,departure_time,stop_id,stop_sequence,pickup_type,drop_off_type";
    ///write_content(&new_trips.1, "./tpg_output/stoptimes.txt", header_stop_times);
    /// ```
    pub fn sort_trips(trips: Vec<Trips>, routes: &[Routes], stops: &[Stops]) -> (Vec<Trips>, Vec<Stoptimes>) {
        let mut new_trips: Vec<Trips> = Vec::new();
        let mut new_stoptimes: Vec<Stoptimes> = Vec::new();
        // count the number of appearances of a stop at the beginning of each trip to figure out the "common" trip for a route
        routes.iter()
            .for_each(|r| {
                let mut array_of_stops = HashMap::new();
                r.route_stoptimes.iter()
                    .for_each(|stop| {
                        if stop.stop_sequence.parse::<i32>().unwrap() == 1 {
                            if array_of_stops.contains_key(&stop.stop_id) {
                                array_of_stops.insert(&stop.stop_id, array_of_stops.get(&stop.stop_id).unwrap() + 1);
                            } else {
                                array_of_stops.insert(&stop.stop_id, 1);
                            }
                        }
                    });
                // we assume the highest number of appearances for a stop define wich stop is the departure stop
                let departure_stop = stops.iter()
                    .find(|s| s.stop_id == array_of_stops.iter()
                        .max_by_key(|entry | entry.1)
                        .unwrap()
                        .0.to_string())
                    .unwrap();
                array_of_stops.remove(&array_of_stops.iter()
                    .max_by_key(|entry | entry.1)
                    .unwrap()
                    .0.to_string());
                // we assume the next stop with the most appearances define wich stop is the arrival stop
                let mut arrival_stop = stops.iter()
                    .find(|s| s.stop_id == array_of_stops.iter()
                        .max_by_key(|entry | entry.1)
                        .unwrap_or((&&"0".to_string(),&0))
                        .0.to_string())
                    .unwrap_or(departure_stop);
                // for some lines, we need to manage special cases
                arrival_stop = match &r.route_short_name[..] {
                    "36" | "47" | "72" => departure_stop, // routes that loop themselves
                    "A1" | "A2" | "A3" | "A4" | "A6" => stops.iter()
                        .find(|s| s.stop_id == *"8592943")
                        .unwrap(), // routes that only go forward (same direction)
                    "A5" => stops.iter()
                        .find(|s| s.stop_id == *"8593012")
                        .unwrap(), // routes that only go forward (other direction)
                    _ => arrival_stop // else, they are fine
                };
                // we select the trip that start with the departure stop and end with the arrival stop 
                let mut trip = Trips::get_trip_id_from_stops(departure_stop, arrival_stop, &r.route_stoptimes);
                // the trip has an id, we can add it to the new trips
                new_trips.push(trips.iter()
                    .find(|t| t.trip_id == trip.0)
                    .unwrap()
                    .clone());
                trip.1.iter()
                    .for_each(|stop| new_stoptimes.push((*stop).clone()));
                trip = match &r.route_short_name[..] {
                    "A1" | "A2" | "A3" | "A4" | "A5" | "A6" => Trips::get_trip_id_from_stops(departure_stop, arrival_stop, &r.route_stoptimes), // for the routes that only go forward the backward trip is the same
                    _ => Trips::get_trip_id_from_stops(arrival_stop, departure_stop, &r.route_stoptimes) // else, they are fine
                };
                new_trips.push(trips.iter()
                    .find(|t| t.trip_id == trip.0)
                    .unwrap()
                    .clone());
                trip.1.iter()
                    .for_each(|stop| new_stoptimes.push((*stop).clone()));
            });
            (new_trips, new_stoptimes)
    }
    
    /// Return the trip (id, stoptimes-sequence) that start with the departure stop and end with the arrival stop
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Trips::*;
    /// 
    ///let (trip_id, stop_times) = Trips::get_trip_id_from_stops(arrival_stop, departure_stop, &r.route_stoptimes);
    /// ```
    fn get_trip_id_from_stops<'a>(departure_stop: &'a Stops, arrival_stop: &'a Stops, stop_times: &'a [Stoptimes]) -> (String, Vec<&'a Stoptimes>) {
        let mut trips_starting_at_departure_stop = stop_times.iter()
            .filter(|stop| stop.stop_id == departure_stop.stop_id && stop.stop_sequence.parse::<i32>().unwrap() == 1)
            .map(|stop| stop.trip_id.to_owned())
            .collect::<Vec<_>>();
        trips_starting_at_departure_stop.dedup();
        for trip in trips_starting_at_departure_stop {
            let mut stops_of_trip = stop_times.iter().filter(|stop| stop.trip_id == trip).collect::<Vec<_>>();
            stops_of_trip.dedup();
            if stops_of_trip.last().unwrap().stop_id.contains(&arrival_stop.stop_id[..]) {
                return (trip, stops_of_trip);
            }
        }
        ("".to_owned(), Vec::new())
    }   
}