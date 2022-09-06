use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::fmt;

use crate::trips::Trips;

#[derive(Debug)]
pub struct Calendardates {
    pub service_id: String,
    pub date: String,
    pub exception_type: String
}

impl From<&Vec<String>> for Calendardates {
    fn from(v: &Vec<String>) -> Self {
        Calendardates { 
            service_id:v[0].to_owned(),
            date:v[1].to_owned(),
            exception_type:v[2].to_owned() }
    }
}

impl fmt::Display for Calendardates {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "\"{}\",\"{}\",\"{}\"", 
            self.service_id, 
            self.date, 
            self.exception_type)
    }
}

impl PartialEq for Calendardates {
    fn eq(&self, other: &Calendardates) -> bool {
        self.service_id.eq(&other.service_id) && 
        self.date.eq(&other.date) &&
        self.exception_type.eq(&other.exception_type)
    }
}

impl Calendardates {
    /// Return an option on a vector of Calendardates created from a file and a vector of Trips
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::Trips::*;
    ///use gtfs::Calendardates::*;
    /// 
    ///let calendar_dates = read_calendar_dates(&trips_vec, "./tpg_input/calendar_dates.txt".to_string()).unwrap();
    /// 
    ///let header = "service_id,date,exception_type";
    ///write_content(&calendar_dates, "./tpg_output/calendar_dates.txt", header);
    /// ```
    pub fn read_calendar_dates(trips: &[Trips], path: String) -> Option<Vec<Calendardates>> {
        let reader = BufReader::new(File::open(path).ok()?);
        let mut calendar_dates = reader.lines()
            .flat_map(|line| {
                let v = line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                trips.iter()
                    .filter(|trip| v[0] == trip.service_id)
                    .map(|_service_id| Calendardates::from(&v))
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>();
        calendar_dates.dedup();
        Some(calendar_dates)
    }
}