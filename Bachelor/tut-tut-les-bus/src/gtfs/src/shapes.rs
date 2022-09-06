use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::fmt;

use regex::Regex;
use sublime_fuzzy::{FuzzySearch, Scoring};
use unidecode::unidecode;

use crate::stops::Stops;
use crate::stop_times::Stoptimes;
use crate::routes::Routes;

#[derive(Debug)]
pub struct Shapes {
    pub shape_id: String,
    pub shape_pt_lat: String,
    pub shape_pt_lon: String,
    pub shape_pt_sequence: String,
    pub shape_dist_traveled: String
}

impl From<&Vec<String>> for Shapes {
    fn from(v: &Vec<String>) -> Self {
        Shapes { shape_id:v[0].to_owned(),
            shape_pt_lat:v[1].to_owned(),
            shape_pt_lon:v[2].to_owned(),
            shape_pt_sequence:v[3].to_owned(),
            shape_dist_traveled:v[4].to_owned() }
    }
}

impl fmt::Display for Shapes {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{},{},{},{},{}", 
            self.shape_id, 
            self.shape_pt_lat, 
            self.shape_pt_lon, 
            self.shape_pt_sequence,
            self.shape_dist_traveled)
    }
}

impl PartialEq for Shapes {
    fn eq(&self, other: &Shapes) -> bool {
        self.shape_id.eq(&other.shape_id) && 
        self.shape_pt_lat.eq(&other.shape_pt_lat) &&
        self.shape_pt_lon.eq(&other.shape_pt_lon) &&
        self.shape_pt_sequence.eq(&other.shape_pt_sequence) &&
        self.shape_dist_traveled.eq(&other.shape_dist_traveled)
    }
}

impl Shapes {
    /// Return an option on a vector of Shapes created from a file
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Shapes::*;
    /// 
    ///let shapes = Shapes::read_shapes("./tpg_input/shapes.txt".to_string()).unwrap();
    ///
    ///let header = "shape_id,shape_pt_lat,shape_pt_lon,shape_pt_sequence,shape_dist_traveled";
    ///write_content(&shapes, "./tpg_output/shapes.txt", header);
    /// ```
    pub fn read_shapes(path: String) -> Option<Vec<Shapes>> {
        let file = File::open(path).ok()?;
        let reader = BufReader::new(file);
        let shapes = reader.lines()
            .into_iter()
            .map(|line| {
                let v = line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                Shapes::from(&vec![v[0].to_owned(), 
                    v[1].to_owned(), 
                    v[2].to_owned(), 
                    v[3].to_owned(), 
                    v[4].to_owned()])
            })
            .collect::<Vec<_>>();
        Some(shapes)
    }

    /// Return an option on a vector of Shapes created from a vector of routes and a vector of stops
    /// Update the vector of stops and stoptimes (for each route) with unique ids 
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Shapes::*;
    /// 
    ///let shapes = Shapes::build_shapes_and_update_routes(&mut routes_vec, &mut stops_vec).unwrap();
    /// ```
    pub fn build_shapes_and_update_routes(routes: &mut [Routes], stops: &mut [Stops]) -> Option<Vec<Shapes>> {
        let mut shapes: Vec<Shapes> = Vec::new();
        Stops::make_all_stops_unique(stops);
        for r in routes {
            let mut new_stop_times: Vec<Stoptimes> = Vec::new();
            for s in r.route_stoptimes.iter() {
                let trip = r.route_trips.iter()
                    .find(|t| t.trip_id.eq(&s.trip_id))
                    .unwrap()
                    .clone();
                let trip_direction = format!("{}{}",trip.trip_headsign, trip.trip_short_name)
                    .to_lowercase()
                    .replace('-', " ");
                /*let new_stops = Shapes::get_stops_from_route_trip(stops.iter()
                    .filter(|s2| s2.stop_id == s.stop_id)
                    .collect::<Vec<_>>(),
                    r);*/
                let new_stops = stops.iter()
                .filter(|s2| s2.stop_id == s.stop_id)
                .map(|s| s.to_owned())
                .collect::<Vec<_>>();
                let (mut stop, best_match) = Shapes::find_goog_stop(new_stops.clone(), unidecode(&trip_direction));                     
                if best_match < 300 {
                    let tmp = Shapes::find_goog_stop(new_stops.clone(), unidecode(&trip.trip_short_name.to_lowercase()));                     
                    stop = tmp.0;
                }
                let shape_id = r.route_trips.iter()
                    .find(|trip| trip.trip_id == s.trip_id)
                    .unwrap()
                    .clone()
                    .shape_id;
                shapes.push(Shapes::from(&vec![shape_id, 
                    stop.stop_lat.to_owned(), 
                    stop.stop_lon.to_owned(), 
                    s.stop_sequence.to_owned(), 
                    0.to_string()]));
                let good_stop_id = stops.iter()
                    .find(|s| s.stop_lat == stop.stop_lat && s.stop_lon == stop.stop_lon)
                    .unwrap()
                    .stop_id
                    .clone();
                new_stop_times.push(Stoptimes::from(&vec![s.trip_id.to_owned(), 
                    s.arrival_time.to_owned(), 
                    s.departure_time.to_owned(), 
                    good_stop_id.to_owned(), 
                    s.stop_sequence.to_owned(), 
                    s.pickup_type.to_owned(), 
                    s.drop_off_type.to_owned()]));
            }
            r.route_stoptimes = new_stop_times;
        }
        Some(shapes)
    }
    /// Take a vector of stops (should be the same stops but with different ids as there is at least two stops for each side of the road)
    /// Return the best match and the score of the stops that is on the good side of the road (using the trip_direction)
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Shapes::*;
    /// 
    ///let (mut stop, score) = Shapes::find_goog_stop(&stops_vec, "Onex-Cité");
    /// ```
    fn find_goog_stop(stops: Vec<Stops>, trip_direction: String) -> (Stops, isize) {
        let scoring = Scoring { bonus_consecutive: 128, bonus_word_start: 0, ..Scoring::default() };
        let re = Regex::new(r" [0-9A-ZÀ-ú]{1,2} ").unwrap();
        let mut values = Vec::new();
        for stop in stops.iter() {
            let kek2 = re.replace_all(&stop.routes, " ")
                .replace('-', " ")
                .replace("  ", " ")
                .to_lowercase();
            match FuzzySearch::new(&trip_direction, &unidecode(&kek2))
            .case_sensitive()
            .score_with(&scoring)
            .best_match(){
                Some(r) => values.push(r.score()),
                None => values.push(Shapes::count_word(&trip_direction, &stop.stop_name)),
            };
        }
        let best_match = values.iter()
            .max()
            .unwrap();
        let index = values.iter()
            .position(|x| x == best_match)
            .unwrap();
        let stop = stops.get(index)
            .unwrap()
            .clone();
        (stop, *best_match)
    }

    /// Take a vector of all Stops and return a vector that contains every stops of a route given
    /// Used before in build_shapes_and_update_routes()
    /// 
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Shapes::*;
    /// 
    ///let route_stops = Shapes::get_stops_from_route_trip(&stops_vec, route);
    /// ```
    #[allow(dead_code)]
    fn get_stops_from_route_trip(stops: Vec<&Stops>, route: &Routes) -> Vec<Stops>{
        let mut route_stops = Vec::new();
        let re = Regex::new(r"\([^)]*\)").unwrap();
        for s in stops.iter() {
            let stop_route = re.replace_all(&s.routes, "")
                .replace(')', "")
                .replace('(', "")
                .replace("  ", " ")
                .replace(',', " ");
            if stop_route.contains(format!("{} ",route.route_short_name).as_str()) {
                route_stops.push((*s).clone().to_owned());
            }
        }   
        route_stops
    }

    /// Return the number of words that are in both str1 and str2
    /// 
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Shapes::*;
    /// 
    ///let word_count = Shapes::count_word("Vernier-village", "Vernier");
    /// ```
    fn count_word(str1: &str, str2: &str) -> isize {
        let stop_name = str1.split(' ').collect::<Vec<_>>();
        let kml_stop_name = str2.split(' ').collect::<Vec<_>>();
        let mut count = 0;
        if stop_name.len() > kml_stop_name.len() {
            for word in stop_name {
                if kml_stop_name.contains(&word) {
                    count += 1;
                }
            }
        } else {
            for word in kml_stop_name {
                if stop_name.contains(&word) {
                    count += 1;
                }
            }
        }
        count
    }
}
