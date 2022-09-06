use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::fmt;

use crate::agency::Agency;
use crate::stop_times::Stoptimes;
use crate::trips::Trips;

#[derive(Debug, Clone)]
pub struct Routes {
    pub route_id: String,
    pub agency_id: String,
    pub route_short_name: String,
    pub route_long_name: String,
    pub route_desc: String,
    pub route_type: String,
    pub route_trips: Vec<Trips>,
    pub route_stoptimes: Vec<Stoptimes>
}

impl From<&Vec<String>> for Routes {
    fn from(v: &Vec<String>) -> Self {
        Routes { route_id:v[0].to_owned(),
            agency_id:v[1].to_owned(),
            route_short_name:v[2].to_owned(),
            route_long_name:v[3].to_owned(),
            route_desc:v[4].to_owned(),
            route_type:v[5].to_owned(),
            route_trips:vec![],
            route_stoptimes:vec![] }
    }
}

impl fmt::Display for Routes {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        // overwrite route_type as A-B/Street expect it to be 3 and not 700 (buses) / 900 (tramways)
        write!(f, "\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",3", 
            self.route_id, 
            self.agency_id, 
            self.route_short_name, 
            self.route_long_name, 
            self.route_desc)
    }
}

impl PartialEq for Routes {
    fn eq(&self, other: &Routes) -> bool {
        self.route_id.eq(&other.route_id) && 
        self.agency_id.eq(&other.agency_id) &&
        self.route_short_name.eq(&other.route_short_name) &&
        self.route_long_name.eq(&other.route_long_name) &&
        self.route_desc.eq(&other.route_desc) &&
        self.route_type.eq(&other.route_type) &&
        self.route_trips.eq(&other.route_trips) &&
        self.route_stoptimes.eq(&other.route_stoptimes)
    }
}

impl Routes {
    /// Return an option on a vector of Routes created from a file and a vector of Agencies
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Routes::*;
    /// 
    ///let routes = Routes::read_routes(&agencies, "./tpg_input/routes.txt".to_string()).unwrap();
    ///
    ///let header = "route_id,agency_id,route_short_name,route_long_name,route_desc,route_type";
    ///write_content(&routes, "./tpg_output/routes.txt", header);
    /// ```
    pub fn read_routes(agencies: &[Agency], path: String) -> Option<Vec<Routes>> {
        let file = File::open(path).ok()?;
        let reader = BufReader::new(file);
        let mut routes = reader.lines()
            .into_iter()
            .flat_map(|line| {
                let v = line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                agencies.iter()
                    .filter(|agency| agency.agency_id == v[1])
                    .map(|_agency_id| Routes::from(&v))
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>();
        routes.dedup();
        Some(routes)
    }

    /// Update the routes with the corresponding trips
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Routes::*;
    ///use gtfs::Trips::*;
    /// 
    ///let mut routes = Routes::read_routes(&agencies, "./tpg_input/routes.txt".to_string()).unwrap();
    ///Routes::update_routes_trips(&mut routes, &trips_vec).unwrap();
    /// ```
    pub fn update_routes_trips(routes: &mut Vec<Routes>, trips: &[Trips]) {
        for route in routes {
            route.route_trips = trips.iter()
                .cloned()
                .filter(|trip| trip.route_id == route.route_id)
                .collect::<Vec<Trips>>();
        }
    }
    
    /// Update the routes with the corresponding trips
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Routes::*;
    ///use gtfs::Stoptimes::*;
    /// 
    ///let mut routes = Routes::read_routes(&agencies, "./tpg_input/routes.txt".to_string()).unwrap();
    ///Routes::update_routes_stoptimes(&mut routes, &stop_times_vec).unwrap();
    /// ```
    pub fn update_routes_stoptimes(routes: &mut Vec<Routes>, stoptimes: &[Stoptimes]) {
        for route in routes {
            route.route_stoptimes = stoptimes.iter()
                .cloned()
                .filter(|stoptime| stoptime.trip_id.contains(&route.route_id))
                .collect::<Vec<Stoptimes>>();
        }
    }

    pub fn filter_routes(routes: &mut Vec<Routes>){
        routes.retain(|route| route.route_short_name != "NA");
        routes.retain(|route| route.route_short_name != "NC");
        routes.retain(|route| route.route_short_name != "ND");
        routes.retain(|route| route.route_short_name != "NE");
        routes.retain(|route| route.route_short_name != "NJ");
        routes.retain(|route| route.route_short_name != "NK");
        routes.retain(|route| route.route_short_name != "NM");
        routes.retain(|route| route.route_short_name != "NO");
        routes.retain(|route| route.route_short_name != "NP");
        routes.retain(|route| route.route_short_name != "NS");
        routes.retain(|route| route.route_short_name != "NT");
        routes.retain(|route| route.route_short_name != "NV");
        routes.retain(|route| route.route_short_name != "X2");
    }
}